#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file string1 string2 ..."
	exit 1
fi

file=$1
shift 1

for arg in $*
do
	if $(getent passwd | grep -q "$arg")
	then
		homedir=$(getent passwd | cut -d: -f6)
		dirs=$(find $homedir -type d)
		while IFS= read -r line
		do
			for dir in $dirs
			do
					if [ "$(basename $dir)" == "$line" ]
					then
						echo "$line"
					fi
			done
		done<"$file"
	fi
done

exit 0
