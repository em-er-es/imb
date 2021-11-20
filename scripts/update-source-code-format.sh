#!/bin/bash
BASEDIR="$(find -name base.sh | head -1 | xargs bash)"
cd "${BASEDIR}"

BACKUP="backup"
GENERATELIST=1
CDATE="$(date '+%y%m%d.%H%M%S')"
PROJECT="${PROJECT-imb}"

if [ ${GENERATELIST} -gt 0 ]; then
	find . -type f \( -name '*.cpp' -o -name '*.h' \) -a -not -wholename '*/build/*' > "${0%.*}.ls"
elif [ ! -f "${0%.*}.ls" ]; then
	exit 2
fi

if [ -n "${BACKUP}" ]; then
	mkdir -p "${BACKUP}"
	tar cvJf "${BACKUP}/${PROJECT}.source-code.${CDATE}.tar.xz" -T "${0/.sh/.ls}"
fi

while read FILE; do
	clang-format -style=file -i "${FILE}"
done < "${0/.sh/.ls}"
