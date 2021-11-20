#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BUILDDIR="build"
mkdir -p "${BUILDDIR}" && cd "${BUILDDIR}"
INSTALL_PREFIX="${INSTALL_PREFIX-${HOME}/.local}"

BUILDTYPE="${1-default}"
case "${BUILDTYPE}" in
	default)
		RELEASE=Release
		DEBUG=0
		COVERAGE=0
		VERBOSE=0
	;;
	coverage)
		RELEASE=Debug
		DEBUG=1
		COVERAGE=1
		VERBOSE=0
	;;
	debug)
		RELEASE=Debug
		DEBUG=10
		COVERAGE=0
		VERBOSE=1
	;;
	optimized)
		RELEASE=Release
		DEBUG=0
		COVERAGE=0
		VERBOSE=0
		_CXX_FLAGS="-O3 -g -march=haswell"
	;;
	*)
		echo "Unrecognized option ${BUILDTYPE}"
		exit 1
	;;
esac

if [[ "${BUILDTYPE}" == "optimized" ]] && [[ ${COVERAGE} -eq 0 ]]; then
	_CC=$(which $(ls -1 "/usr/bin/clang-"[0-9]* | sed 's/\.[0-9].*$//;s#.*/##' | sort -rV | head -1))
	_CXXC=$(which $(ls -1 "/usr/bin/clang++-"[0-9]* | sed 's/\.[0-9].*$//;s#.*/##' | sort -rV | head -1))
fi
[[ "${_CC-x}" == "x" ]] && _CC=$(which gcc)
[[ "${_CXXC-x}" == "x" ]] && _CXXC=$(which g++)

echo "Building profile: ${BUILDTYPE}"
cmake .. -DCMAKE_BUILDTYPE="${RELEASE}" -DCMAKE_C_COMPILER="${_CC}" -DCMAKE_CXX_COMPILER="${_CXXC}" -DCMAKE_INSTALL_PREFIX="${INSTALL_PREFIX}" -DCMAKE_CXX_FLAGS="${_CXX_FLAGS}" -DDEBUG=${DEBUG} -DCOVERAGE=${COVERAGE}
make -j $(nproc)

if [[ ${COVERAGE} -gt 0 ]]; then
	make coverage
fi

unset _CC _CXXC _CXX_FLAGS
