#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare:" $0 'fisier1 fisier2 ...'
	exit 1
fi

read -p "Cuvant: " CUVANT

for FILE in $*
do
	NR=0
	CUVINTE=$(cat $FILE)
	for CUV in $CUVINTE
	do
		if [ $CUV == $CUVANT ]
		then
			NR=$((NR+1))
		fi
	done
	
	echo 'Fisier:' $FILE 'Cuvant:' $CUVANT 'Nr. aparitii:' $NR
done

exit 0	
