#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 number file1 file2 ..."
	exit 1
fi

n=$1
shift 1
tmp_file="tmp4.txt"
touch $tmp_file
for file in $*
do
	libs=$(grep '^#include <' "$file" | sed -E 's/^#include <([^>]+)>/\1/' | sort | uniq)
	echo "File: $file"
	for lib in $libs
	do
		echo "$lib"
		echo "$lib" >> "$tmp_file"
	done
done

echo "Top $n libraries used:"
sort "$tmp_file" | uniq -c | sort -nr | head -n $n

rm "$tmp_file"
exit 0
