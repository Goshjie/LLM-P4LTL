# Hook notes

This sandbox currently implements a **phase-1 hook prototype**:

- Trigger point: after a `P4LTL` file has been parsed by the copied C++ parser into structured sections
- Export format: JSON
- Consumer: simulated Program A (`program_a/save_json_sink.py`)

The prototype intentionally exports:

- raw `P4LTL` sections
- conservative `packet_constraints`
- conservative `environment_constraints`

This is sufficient to start validating the external handoff path:

```text
verification-side hook -> JSON -> Program A
```

It does **not** yet modify the upstream C++ / Java verification loop to hook every solver query. The copied upstream files under `upstream/` are there to support the next integration step.
