#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BIN="build/bin/imb"
[[ ! -x "$BIN" ]] && exit 2

OUTPUTDIR="output"
INPUT="input"
INPUTS=("${INPUT}/input"*.png)
PALETTE=1

for INPUT in "${INPUTS[@]}"; do
	OUTPUT="${OUTPUTDIR}/${INPUT##*/}"
	"$BIN" -i "$INPUT" -o "${OUTPUT}" || exit 1
	[[ ! ${PALETTE} -gt 0 ]] || continue
	convert "${INPUT}" -colors 16 -unique-colors -scale 1000% -crop 100%x100% -append "${INPUT%.*}-palette.png"
	convert "${OUTPUT}" -colors 16 -unique-colors -scale 1000% -crop 100%x100% -append "${OUTPUT%.*}-palette.png"
done
