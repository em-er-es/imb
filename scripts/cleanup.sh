#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

OUTPUT="output"
ls -1 "${OUTPUT}/"*
rm -Iv "${OUTPUT}/"*
