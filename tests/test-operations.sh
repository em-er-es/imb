#!/bin/bash
for TEST in "${0%.*}-"*.sh; do
	[[ -x "${TEST}" ]] && bash "${TEST}"
done
