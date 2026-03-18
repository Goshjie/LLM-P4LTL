#!/usr/bin/env python3
from __future__ import annotations

import json
import subprocess
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
P4_PATH = ROOT / "upstream/Artifact/benchmark/Temporal Verification/Case Study/P4NIS/main.p4"
P4LTL_PATH = ROOT / "upstream/Artifact/benchmark/Temporal Verification/Case Study/P4NIS/9.p4ltl"
OUTPUT_DIR = ROOT / "output/program_a"
PIPELINE = ROOT / "hooks/p4ltl_hook_pipeline.py"
PROGRAM_A = ROOT / "program_a/save_json_sink.py"


def main() -> int:
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    before = set(OUTPUT_DIR.glob("*.json"))
    cmd = [
        "python3",
        str(PIPELINE),
        "--p4",
        str(P4_PATH),
        "--p4ltl",
        str(P4LTL_PATH),
        "--program-a",
        f"python3 {PROGRAM_A} --output-dir {OUTPUT_DIR}",
        "--dump-json",
        str(ROOT / "output/last_hook_event.json"),
    ]
    result = subprocess.run(cmd, text=True, capture_output=True, check=True)

    after = set(OUTPUT_DIR.glob("*.json"))
    created = sorted(after - before)
    if not created:
        raise RuntimeError("Program A did not persist any JSON output.")

    payload = json.loads(created[-1].read_text(encoding="utf-8"))
    assert payload["stage"] == "pre_solver_constraints_actual_parser"
    assert payload["source"]["p4_path"].endswith("main.p4")
    assert payload["source"]["p4ltl_path"].endswith("9.p4ltl")
    assert payload["raw_sections"]["ltl_property"], "LTLProperty should be present"
    assert payload["raw_sections"]["ltl_fairness"], "LTLFairness should be present"
    assert payload["parsed_formulas"], "actual parser-backed formulas should be present"
    assert payload["packet_constraints"], "packet_constraints should not be empty"
    assert payload["environment_constraints"], "environment_constraints should not be empty"

    print("Created:", created[-1])
    print("packet_constraints:", len(payload["packet_constraints"]))
    print("environment_constraints:", len(payload["environment_constraints"]))
    if result.stdout:
        print("program_a_stdout:", result.stdout.strip())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
