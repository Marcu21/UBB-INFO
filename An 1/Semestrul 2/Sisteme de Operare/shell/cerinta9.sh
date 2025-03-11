#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file1 file2 ..."
	exit 1
fi

for arg in $*
do
	echo "File: $arg"
	grep -oE "[0-9]+" "$arg" | awk '{if ($1 % 2 == 0) frec[$1]++}
	END { for(number in frec) { print number ":" frec[number]} }'
done

exit 0
