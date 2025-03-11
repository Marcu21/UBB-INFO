#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 word file1 file2 ..."
	exit 1
fi

cuv=$1
shift 1

for file in $*
do
	nr=$(grep -o "$cuv" "$file" | wc -l)
	echo "File: $file aparitii: $nr"
done

exit 0
