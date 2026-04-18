#!/bin/bash
set -euo pipefail

MODE="${1:-all}"

cmake --preset debug

if [[ "$MODE" == "cli" ]]; then
	cmake --build --preset debug --target klang_cli
else
	cmake --build --preset debug
	ctest --preset debug
fi