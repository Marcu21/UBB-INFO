#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare:" $0 'fisier1 fisier2 ...'
	exit 1
fi

read -p "Cuvant: " CUVANT

for FISIER in $*
do
	APARITII=$(cat $FISIER | grep -o '\b'$CUVANT'\b' | wc -l)
    echo 'Fisier:' $FISIER 'Cuvant:' $CUVANT 'Nr. aparitii:' $APARITII
	
done

exit 0	
