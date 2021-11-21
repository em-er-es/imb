#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BIN="build/bin/imb"
if [[ ! -x "${BIN}" ]]; then
	echo "Binary ${BIN} not found"
	exit 2
fi
command -v valgrind &>/dev/null && VALGRIND=1
command -v gprof &>/dev/null && GPROF=1

INPUT="input"
OUTPUT="output"
INPUTS=("${INPUT}/"*.png)
PREFIX="valgrind --tool=callgrind"
GP="gprof"
GPOPTIONS=('' '-b' '-b -p' '-P -b' '-q -b' '-Q -b')

cd "${BIN%%/*}"

# Gprof
if [[ ${GPROF} -gt 0 ]]; then
	I=0
	for OPTIONS in "${GPOPTIONS[@]}"; do
		${GP} ${OPTIONS} "${BIN#*/}" gmon.out > "${BIN##*/}-gp${I}.profile"
		I=$((I + 1))
	done
fi

# Valgrind
if [[ ${VALGRIND} -gt 0 ]]; then
	for INPUT in "${INPUTS[@]}"; do
		OUTPUT="output-${INPUT}"
		${PREFIX} "${BIN#*/}" -i "../${INPUT}" -o "../${OUTPUT}" || echo !! FAILED
	done
fi
