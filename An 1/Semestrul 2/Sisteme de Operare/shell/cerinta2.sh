#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 word number1 number2 file1 file2 ..."
	exit 1
fi

w=$1
m=$2
n=$3
shift 3

for file in $*
do
	count=0
	while IFS= read -r line
	do
		count=$(($count+1))
		if [ $count -eq $n ]
		then
			echo $line
			nr=$(echo $line | grep -o "$w" | wc -l)
			if [ $nr -ge $m ]
			then
				echo $file
			fi
		fi
	done<"$file"
done

exit 0


#line=$(awk -v num="$n" '{print $num}' "$file")
