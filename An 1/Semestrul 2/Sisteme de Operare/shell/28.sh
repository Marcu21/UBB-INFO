#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file1 file2 ..."
	exit 1
fi

echo -n "Introdu un cuvant: "
read cuv

while [ ! "$cuv" == "stop" ]
do
	echo -n "Introdu inca un cuvant: "
	read cuv2
	for arg in $*
	do
		if file $arg | grep -q "ASCII text"
		then
			echo "Fisier: $arg"
			voc=$(grep -o -i "[aeiou]" "$arg" | wc -l)
			con=$(grep -o -i "[^aeiou]" "$arg" | wc -l)
			echo "Raport vocale consoane: $voc / $con"
			sed -i "s/$cuv/$cuv2/g" "$arg"
		else
			echo "Fisier: $arg"
			echo "Fisierul dat nu e de tip texxt."
		fi
	done
	echo -n "Introdu un cuvant: "
	read cuv
done

exit 0
