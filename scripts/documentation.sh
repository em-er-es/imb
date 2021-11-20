#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

cd "documentation"
bash doxygen.sh
