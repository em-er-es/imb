#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BIN="build/bin/imb"
[[ ! -x "$BIN" ]] && exit 2

OUTPUTDIR="output"
INPUT="input"
INPUTS=("${INPUT}/palette-"*.png)

for INPUT in "${INPUTS[@]}"; do
	FILE="${INPUT##*/}"
	OUTPUT="${OUTPUTDIR}/${FILE%.*}-filter.${INPUT##*.}"
	"$BIN" -i "$INPUT" -o "${OUTPUT}" || exit 2
done
