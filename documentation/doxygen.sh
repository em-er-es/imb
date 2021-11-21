#!/bin/bash
SCRIPT="${0%.*}"
MODE="${SCRIPT##*-}"
MODE="${1-${MODE}}"

case "${MODE}" in
	c|clean)
		DIRS=(html latex)
		for DIR in "${DIRS[@]}"; do
			[[ -d "${DIR}" ]] && rm -rIv "${DIR}"
		done
	;;
	d|u|doxygen|default|update)
		doxygen doxygen.cfg
	;;
	*)
		echo "Unrecognized mode: ${MODE}"
		exit 1
	;;
esac
