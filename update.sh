#!/bin/bash
SCRIPTS=(scripts build coverage profiling documentation tests cleanup)
for SCRIPT in "${SCRIPTS[@]}"; do
	if [[ "${SCRIPT}" == "${SCRIPTS[0]}" ]]; then
		continue
	fi
	SCRIPT="${SCRIPTS[0]}/${SCRIPT}.sh"
	echo "Checking ${SCRIPT}"
	if [[ -x "${SCRIPT}" ]]; then
		echo "Running ${SCRIPT}"
		bash "${SCRIPT}"
	fi
done
