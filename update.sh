#!/bin/bash
SCRIPTS=(build tests coverage profiling documentation cleanup tests)
for SCRIPT in "scripts/${SCRIPTS[@]}"; do
	SCRIPT="${SCRIPT}.sh"
	[[ -x "${SCRIPT}" ]] && "${SCRIPT}"
done
