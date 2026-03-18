#!/usr/bin/env python3
from __future__ import annotations

import argparse
import json
from datetime import datetime, timezone
from pathlib import Path


def main() -> int:
    parser = argparse.ArgumentParser(description="Simulated Program A JSON sink.")
    parser.add_argument("--output-dir", required=True, help="Directory where received JSON is persisted.")
    args = parser.parse_args()

    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    payload = json.load(fp=__import__("sys").stdin)
    event_id = payload.get("event_id", "unknown-event")
    timestamp = datetime.now(timezone.utc).strftime("%Y%m%dT%H%M%SZ")
    output_path = output_dir / f"{timestamp}_{event_id}.json"
    output_path.write_text(json.dumps(payload, ensure_ascii=False, indent=2), encoding="utf-8")

    print(str(output_path))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
