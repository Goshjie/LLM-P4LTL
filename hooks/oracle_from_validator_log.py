#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import shlex
import subprocess
import sys
import uuid
from pathlib import Path


def detect_status(log_text: str) -> tuple[str, str]:
    result_line = ""
    for line in log_text.splitlines():
        if "RESULT:" in line:
            result_line = line.strip()
    if not result_line:
        return "unknown", ""
    lowered = result_line.lower()
    if "incorrect" in lowered:
        return "incorrect", result_line
    if "correct" in lowered:
        return "correct", result_line
    return "unknown", result_line


def extract_trace_tail(log_text: str, max_lines: int = 40) -> list[str]:
    interesting = []
    for line in log_text.splitlines():
        if line.startswith("[L") or "Stem:" in line or "Loop:" in line or "End of lasso" in line:
            interesting.append(line.rstrip())
    return interesting[-max_lines:]


def send_to_program_a(program_a_cmd: str, event: dict) -> subprocess.CompletedProcess:
    return subprocess.run(
        shlex.split(program_a_cmd),
        input=json.dumps(event, ensure_ascii=False, indent=2),
        text=True,
        capture_output=True,
        check=True,
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Extract oracle JSON from validator output log.")
    parser.add_argument("--log", required=True, help="Validator log file.")
    parser.add_argument("--p4", required=True, help="P4 file path.")
    parser.add_argument("--p4ltl", required=True, help="P4LTL file path.")
    parser.add_argument("--program-a", required=True, help="Program A command.")
    parser.add_argument("--dump-json", help="Optional path to dump oracle JSON.")
    args = parser.parse_args()

    log_path = Path(args.log).resolve()
    log_text = log_path.read_text(encoding="utf-8", errors="replace")
    status, result_line = detect_status(log_text)

    event = {
        "hook_version": 1,
        "event_id": str(uuid.uuid4()),
        "stage": "post_validator_oracle",
        "source": {
            "p4_path": str(Path(args.p4).resolve()),
            "p4ltl_path": str(Path(args.p4ltl).resolve()),
            "validator_log": str(log_path),
        },
        "oracle": {
            "status": status,
            "result_line": result_line,
            "counterexample_present": status == "incorrect",
            "trace_tail": extract_trace_tail(log_text),
        },
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
