#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare:" $0 'nume_director'
	exit 1
fi

DIR=$1
FILES=$(find $DIR -type f | sort)

for FILE in $FILES
do
	if cat $FILE | grep -E '[1-9][0-9]{4,}'
	then
		echo "Fisier: $(basename "$FILE")"
	fi
done

exit 0
