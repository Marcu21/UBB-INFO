#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 fisier_comenzi fisier_propozitii"
	exit 1
fi

comenzi=$1
fisier=$2

while IFS= read -r line
do
	comanda=$(echo $line | awk '{print $1" "$2}')
	if [ "$comanda" == "INSERT LINE" ]
	then
		nr=$(echo $line | awk '{print $3}')
		text=$(echo $line | awk '{print $4}')
		sed -i "${nr}i $text" "$fisier"
	elif [ "$comanda" == "REPLACE WORD" ]
        then
                cuv1=$(echo $line | awk '{print $3}')
                cuv2=$(echo $line | awk '{print $4}')
                sed -i "s/\<$cuv1\>/$cuv2/g" "$fisier"
	elif [ "$comanda" == "APPEND LINE" ]
        then
                text=$(echo $line | awk '{print $3}')
                sed -i '$a '$text'' "$fisier"
	elif [ "$comanda" == "REPLACE CHAR" ]
        then
                ch1=$(echo $line | awk '{print $3}')
                ch2=$(echo $line | awk '{print $4}')
                sed -i "s/$ch1/$ch2/g" "$fisier"
	else
		echo "Comanda nerecunoscuta: $comanda"
	fi
done<"$comenzi"

exit 0
