#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
P4_FILE="${1:-}"
P4LTL_FILE="${2:-}"
PROGRAM_A_CMD="${3:-python3 ${ROOT}/program_a/save_json_sink.py --output-dir ${ROOT}/output/program_a}"
TRANSLATOR_BIN="/home/gosh/P4LTL/P4LTL-Translator/build/backends/verify"
VALIDATOR_CHECK="/home/gosh/P4LTL/P4LTL-Validator/releaseScripts/default/UP4LTL-linux/UP4LTL-linux/Check.sh"

if [[ -z "${P4_FILE}" || -z "${P4LTL_FILE}" ]]; then
  echo "Usage: $0 <p4-file> <p4ltl-file> [program-a-cmd]"
  exit 1
fi

export PATH="${TRANSLATOR_BIN}:${PATH}"
export JAVA_HOME="${JAVA_HOME:-/usr/lib/jvm/java-11-openjdk-amd64}"
export LLM_P4LTL_ROOT="${ROOT}"
export LLM_P4LTL_PROGRAM_A_CMD="${PROGRAM_A_CMD}"

if ! command -v p4c-translator >/dev/null 2>&1; then
  echo "[full-flow] p4c-translator not found in PATH"
  exit 1
fi

if [[ ! -x "${VALIDATOR_CHECK}" ]]; then
  echo "[full-flow] validator Check.sh not found: ${VALIDATOR_CHECK}"
  exit 1
fi

echo "[full-flow] starting actual Check.sh -> translator -> validator run with hook1 + hook2"
bash "${VALIDATOR_CHECK}" "${P4_FILE}" "${P4LTL_FILE}"
