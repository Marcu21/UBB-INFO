#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 sir arg1 arg2..."
	exit 1
fi

sir=$1
shift 1

for arg in $*
do
	if [ -d $arg ]
	then
		FILES=$(find $arg -type f -size 0b)
		for file in $FILES
		do
			if [ "$(basename $file)" == "$sir" ]
			then
				echo "Director: $arg"
			fi
		done
	fi
done

exit 0
