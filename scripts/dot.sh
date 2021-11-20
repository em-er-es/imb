#!/bin/bash
## @file
## @author Ernest Skrzypczyk <emeres.code@onet.eu>
## @version 1.0.1
## @date 12.02.19
## @copyright Ernest Skrzypczyk 2019-2021
## @brief Updates DOT file generated output
## @details Updates DOT file and generates output
## @par Shell:
## @shell{$, bash <filename>}
##

FILE="${0%.*}"
[[ "${FILE}" == "dot" ]] && FILE=(*.dot)
EXTS=(png svg)
PROCESS=0

for FILE in "${FILE[@]}"; do
	# Update DOT file
	if [[ ${PROCESS} -gt 0 ]]; then
		sed 's///g' -i "${FILE}"
	fi

	# Generate output
	for EXT in ${EXTS[@]}; do
		dot "${FILE}" -T"${EXT}" -o "${FILE%.*}.${EXT}"
	done
done
