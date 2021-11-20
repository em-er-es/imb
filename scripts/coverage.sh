#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BUILDDIR="build"
COVERAGEDIR="coverage"

[[ ! -d "${BUILDDIR}" ]] && { echo "${BUILDDIR} not present"; exit 2; }
#[[ ! -d "${BUILDDIR}" ]] && [[ "${PWD##*/}" != "${BUILDDIR}" ]] && { echo "${BUILDDIR} not present"; exit 2; }
#[[ "${PWD##*/}" == "${BUILDDIR}" ]] || cd "${BUILDDIR}" || exit 2

mkdir -p "${COVERAGEDIR}"
find . -type f \( -iname \*.gcno -or -iname \*.gcda \) -exec cp {} "${COVERAGEDIR}" \;

gcovr -v -r "${COVERAGEDIR}"

#gcovr -r .. .
#gcovr -r .. --html --html-details -o coverage-report.html
