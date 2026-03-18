#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GEN_DIR="${ROOT}/build/generated/frontends/parsers/p4ltl"
BIN="${ROOT}/build/p4ltl_hook_runner"
SRC_DIR="${ROOT}/upstream/P4LTL-Translator/frontends/parsers/p4ltl"

mkdir -p "${GEN_DIR}"

bison -d -o "${GEN_DIR}/p4ltlparser.cpp" "${SRC_DIR}/p4ltlparser.ypp"
flex "${SRC_DIR}/p4ltllexer.ll"
mv "${ROOT}/lex.yy.c" "${GEN_DIR}/p4ltllexer.cpp"

g++ -std=c++17 \
  -I "${ROOT}/upstream/P4LTL-Translator" \
  -I "${ROOT}/build/generated" \
  "${ROOT}/hooks/p4ltl_hook_runner.cpp" \
  "${ROOT}/upstream/P4LTL-Translator/frontends/parsers/p4ltl/p4ltlast.cpp" \
  "${GEN_DIR}/p4ltlparser.cpp" \
  "${GEN_DIR}/p4ltllexer.cpp" \
  -o "${BIN}"

echo "Built ${BIN}"
