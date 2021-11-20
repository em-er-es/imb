#!/bin/bash
TAG=".base"
PROJECT=""

until [ -n "${PROJECT}" ]; do
	if [[ "${PWD}" == "/" ]]; then
		exit 2
	elif [ -f "${TAG}" ]; then
		PROJECT=$(cat "${TAG}")
		break
	fi
	cd ..
done

echo "${PWD}"
