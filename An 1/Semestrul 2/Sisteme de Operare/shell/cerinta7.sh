#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 number word file1 file2 ... "
	exit 1
fi

n=$1
w=$2
shift 2

for arg in $*
do
	count=0
	ok=1
	while IFS= read -r line
	do
		if (echo $line | grep -q "$w")
		then
			count=$(($count+1))
		fi
		if [ $count -eq $n ]
		then
			if [ $ok -eq 1 ]
			then
				ok=0
				echo "$line"
			fi
		fi
	done<"$arg"
done

exit 0
