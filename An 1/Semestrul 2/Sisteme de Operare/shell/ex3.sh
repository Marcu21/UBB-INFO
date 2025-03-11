#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare:" $0 'nume_director'
	exit 1
fi

DIR=$1
NTF=0
NTL=0
FILES=$(find $DIR -type f)
for FILE in $FILES
do
	if file $FILE | grep -q 'ASCII text'
	then
		echo 'Fisier:' $FILE
		NR=$(cat $FILE | wc -l)
		NTL=$((NTL+NR))
		NTF=$((NTF+1))
	fi
done

echo -e "Total fisiere: $NTF\nTotal linii: $NTL\nNr mediu linii: $((NTL/NTF))"
exit 0
