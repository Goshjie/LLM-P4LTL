#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
import shlex
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
BUILD_SCRIPT = ROOT / "hooks/build_hook_runner.sh"
RUNNER = ROOT / "build/p4ltl_hook_runner"


def build_runner() -> None:
    subprocess.run(["bash", str(BUILD_SCRIPT)], check=True)


def run_runner(p4_path: Path, p4ltl_path: Path) -> dict:
    result = subprocess.run(
        [str(RUNNER), str(p4_path), str(p4ltl_path)],
        text=True,
        capture_output=True,
        check=True,
    )
    if result.stderr:
        sys.stderr.write(result.stderr)
    return json.loads(result.stdout)


def send_to_program_a(program_a_cmd: str, event: dict) -> subprocess.CompletedProcess:
    return subprocess.run(
        shlex.split(program_a_cmd),
        input=json.dumps(event, ensure_ascii=False, indent=2),
        text=True,
        capture_output=True,
        check=True,
    )


def main() -> int:
    parser = argparse.ArgumentParser(description="Actual parser-backed constraints hook for LLM-P4LTL.")
    parser.add_argument("--p4", required=True, help="Path to the P4 source.")
    parser.add_argument("--p4ltl", required=True, help="Path to the P4LTL file.")
    parser.add_argument(
        "--program-a",
        required=True,
        help='Program A command, e.g. "python3 program_a/save_json_sink.py --output-dir output/program_a"',
    )
    parser.add_argument("--dump-json", help="Optional path to additionally dump the hook event JSON.")
    args = parser.parse_args()

    p4_path = Path(args.p4).resolve()
    p4ltl_path = Path(args.p4ltl).resolve()

    if not p4_path.exists():
        raise FileNotFoundError(f"P4 file not found: {p4_path}")
    if not p4ltl_path.exists():
        raise FileNotFoundError(f"P4LTL file not found: {p4ltl_path}")

    build_runner()
    event = run_runner(p4_path, p4ltl_path)

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
