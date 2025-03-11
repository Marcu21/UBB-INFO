#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 arg1 arg2 ... "
	exit 1
fi

for arg in $*
do
	if [ -d $arg ]
	then
		owner=$(ls -l "$arg" | awk '{ print $3 }' | tail -n 1)
		minsize=99999
		minfile=""
		for file in $(find $arg -type f)
		do
			size=$(stat --format="%s" $file)
			if [ $size -le $minsize ]
			then
				minfile=$file
				minsize=$size
			fi
		done
		echo "Dir: $arg, Owner: $owner, MinFile: $minfile, Size: $minsize"
	elif [ -f $arg ]
	then
		tac "$arg"
	fi
done

exit 0
