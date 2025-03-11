#!/bin/bash

# ./ex1.sh N
#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo "Numar insuficient de argumente !"
        echo "Utilizare: $0 N"
        exit 1
elif [ ! -d $1 ]
then
	echo "Numele furnizat nu este un director !"
	exit 2
fi

FILES=$(find $1 -type f)
for FILE in $FILES
do
	if file $FILE | grep -q 'ASCII text$'
	then
		echo Fisier: $FILE
		NL=$(cat $FILE | wc -l)
		if [ $NL -lt 6 ]
		then
			cat $FILE
		else
			head -3 $FILE
			tail -3 $FILE
		fi
	fi
done

exit 0
