#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 number file1 file2 ..."
	exit 1
fi

n=$1
shift 1

for arg in $*
do
	grep -oE "\w+" "$arg" | sort | uniq -c | awk -v n=$n '$1 > n {print $2 ":" $1}'
done
