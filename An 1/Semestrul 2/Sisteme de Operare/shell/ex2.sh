#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare:" $0 'nume_director'
	exit 1
fi

DIR=$1

for FILE in $(find $DIR -type f | sort)
do
	if file $FILE | grep -q 'ASCII text$'
	then
		echo "Fisier: $(basename "$FILE")"
		NL=$(cat $FILE | wc -l)
		if [ $NL -lt 6 ]
		then
			cat $FILE
		else
			echo "HEAD"
			head -n 3 $FILE
			echo "TAIL"
			tail -n 3 $FILE
		fi
	fi
done

exit 0
