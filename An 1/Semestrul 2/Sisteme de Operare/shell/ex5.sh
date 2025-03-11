#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare:" $0 'nume1 nume2 ...'
	exit 1
fi

for NUME in $*
do
	if [ -f $NUME ]
	then
		echo "Fisier: $NUME"
		NC=$(wc -m < "$NUME")
		NL=$(wc -l < "$NUME")
		echo "Numar de caractere: $NC"
		echo "Numar de linii: $NL"
	elif [ -d $NUME ]
	then
		echo "Director: $NUME"
		FILES=$(find $NUME -type f | wc -l)
		echo "Numar fisiere: $FILES"
	else
		echo "$NUME habar nu am ce este"
	fi
done

exit 0
