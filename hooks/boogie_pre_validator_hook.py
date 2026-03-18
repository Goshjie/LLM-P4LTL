#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import re
import shlex
import subprocess
import sys
import uuid
from pathlib import Path


PROC_RE = re.compile(r"^procedure \{?:inline 1\}? ?([A-Za-z0-9_\.]+)\(\)")


def parse_bpl(path: Path) -> dict:
    lines = path.read_text(encoding="utf-8", errors="replace").splitlines()

    ltl_headers = []
    variable_decls = []
    procedures: dict[str, list[str]] = {}
    current_proc = None
    current_body = []
    depth = 0

    for idx, line in enumerate(lines, start=1):
        stripped = line.strip()
        if stripped.startswith("//#"):
            ltl_headers.append({"line": idx, "content": stripped})

        if stripped.startswith("var ") or stripped.startswith("const ") or stripped.startswith("type "):
            variable_decls.append({"line": idx, "content": stripped})

        match = PROC_RE.match(stripped)
        if match:
            current_proc = match.group(1)
            current_body = [stripped]
            depth = 0
            continue

        if current_proc is not None:
            current_body.append(stripped)
            depth += stripped.count("{")
            depth -= stripped.count("}")
            if stripped == "}":
                procedures[current_proc] = current_body[:]
                current_proc = None
                current_body = []
                depth = 0

    return {
        "ltl_headers": ltl_headers,
        "variable_declarations": variable_decls,
        "procedures": procedures,
    }


def extract_constraints(parsed: dict) -> tuple[list[dict], list[dict]]:
    packet_constraints = []
    environment_constraints = []

    for header in parsed["ltl_headers"]:
        if "#LTLProperty:" in header["content"] or "#LTLFairness:" in header["content"]:
            packet_constraints.append(
                {
                    "source": "normalized_ltl_header",
                    "line": header["line"],
                    "expression": header["content"],
                }
            )
        elif "#CPI" in header["content"]:
            environment_constraints.append(
                {
                    "source": "cpi_header",
                    "line": header["line"],
                    "expression": header["content"],
                }
            )

    for proc_name, body in parsed["procedures"].items():
        if proc_name == "havocProcedure":
            for stmt in body:
                if stmt.startswith("havoc ") or stmt.startswith("assume(") or ":=" in stmt:
                    environment_constraints.append(
                        {
                            "source": "havocProcedure",
                            "procedure": proc_name,
                            "statement": stmt,
                        }
                    )
        elif proc_name == "oldProcedure":
            for stmt in body:
                if ":=" in stmt:
                    environment_constraints.append(
                        {
                            "source": "oldProcedure",
                            "procedure": proc_name,
                            "statement": stmt,
                        }
                    )
        elif proc_name == "regWrite":
            for stmt in body:
                if stmt and stmt != "{" and stmt != "}":
                    environment_constraints.append(
                        {
                            "source": "regWrite",
                            "procedure": proc_name,
                            "statement": stmt,
                        }
                    )

    for decl in parsed["variable_declarations"]:
        text = decl["content"]
        if (
            text.startswith("var hdr.")
            or text.startswith("var meta.")
            or text.startswith("var standard_metadata.")
            or text.startswith("var _old_")
        ):
            packet_constraints.append(
                {
                    "source": "boogie_variable",
                    "line": decl["line"],
                    "declaration": text,
                }
            )
        elif text.startswith("var ") or text.startswith("const "):
            environment_constraints.append(
                {
                    "source": "boogie_variable",
                    "line": decl["line"],
                    "declaration": text,
                }
            )

    return packet_constraints, environment_constraints


def send_to_program_a(program_a_cmd: str, event: dict) -> subprocess.CompletedProcess:
    return subprocess.run(
        shlex.split(program_a_cmd),
        input=json.dumps(event, ensure_ascii=False, indent=2),
        text=True,
        capture_output=True,
        check=True,
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Extract pre-validator constraints from generated Boogie.")
    parser.add_argument("--bpl", required=True, help="Generated Boogie file.")
    parser.add_argument("--p4", required=True, help="P4 file path.")
    parser.add_argument("--p4ltl", required=True, help="P4LTL file path.")
    parser.add_argument("--program-a", required=True, help="Program A command.")
    parser.add_argument("--dump-json", help="Optional output path for JSON.")
    args = parser.parse_args()

    bpl_path = Path(args.bpl).resolve()
    parsed = parse_bpl(bpl_path)
    packet_constraints, environment_constraints = extract_constraints(parsed)

    event = {
        "hook_version": 1,
        "event_id": str(uuid.uuid4()),
        "stage": "pre_validator_constraints_from_bpl",
        "source": {
            "p4_path": str(Path(args.p4).resolve()),
            "p4ltl_path": str(Path(args.p4ltl).resolve()),
            "bpl_path": str(bpl_path),
        },
        "packet_constraints": packet_constraints,
        "environment_constraints": environment_constraints,
        "raw_ltl_headers": parsed["ltl_headers"],
        "notes": [
            "This hook runs after translator and before validator.",
            "It extracts constraints from the generated Boogie program rather than from the original P4LTL text.",
        ],
    }

    if args.dump_json:
        dump_path = Path(args.dump_json)
        dump_path.parent.mkdir(parents=True, exist_ok=True)
        dump_path.write_text(json.dumps(event, ensure_ascii=False, indent=2), encoding="utf-8")

    result = send_to_program_a(args.program_a, event)
    if result.stdout:
        sys.stdout.write(result.stdout)
    if result.stderr:
        sys.stderr.write(result.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
