#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BIN="build/bin/imb"
if [[ ! -x "$BIN" ]]; then
	echo "Binary $BIN not found"
	exit 2
fi

INPUT="input"
OUTPUT="output"
INPUTS=("${INPUT}/"*.png)
PALETTE=("input/"*"c64-vic-ii-a.png")

#cd "${BIN%%/*}"

# ImageMagick / IMB
for INPUT in "${INPUTS[@]}"; do
	OUTPUT="output/c64-im-${INPUT##*/}"
	convert "${INPUT}" -dither None -remap "${PALETTE}" "${OUTPUT%.*}-im.png" || echo !! FAILED
	"${BIN}" -i "${INPUT}" -o "${OUTPUT}" || echo !! FAILED
done
