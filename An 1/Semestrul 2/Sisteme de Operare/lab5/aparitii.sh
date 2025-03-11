#!/bin/bash

read -p "Cuvant: " CUV

for FILE in $*
do
	APARITII=0
	CUVINTE=$(cat $FILE)
	for C in $CUVINTE
	do
		if [ "$C" == "$CUV" ]
		then
			APARITII=$((APARITII+1))
		fi
	done
	echo "Cuvantul $CUV apare de $APARITII ori"
done
