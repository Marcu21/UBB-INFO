#!/bin/bash

if [ $# -lt 3 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 directory D number N username U"
	exit 1
fi

D="$1"
N="$2"
U="$3"
FILES=$(find "$D" -type f -user "$U")

if [ -z "$FILES" ]
then
	echo "No files found in $D owned by $U with size less than $N"
	exit 1
fi

for file in $FILES
do
	echo "Processing file: $file"
	size=$(stat --format=%s "$file")
	if [ $size -lt $N ]
	then
		echo "File $file is good!"
		grep -oE "\<[aeiouAEIOU][a-zA-z'-]*\>" "$file" | sort | uniq -c | sort -nr | 
		head -n 10 | while read count word
		do
			echo "$word: $count"
		done
	else
		echo "File $file is NOT good!"
	fi
done

exit 0
