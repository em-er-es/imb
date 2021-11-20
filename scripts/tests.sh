#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

for SCRIPT in tests/test-*.sh; do
	[[ -x "${SCRIPT}" ]] && { echo "${SCRIPT}"; bash "${SCRIPT}"; }
done
