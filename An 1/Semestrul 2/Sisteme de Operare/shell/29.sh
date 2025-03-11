#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file1 file2 ..."
	exit 1
fi

echo -n "Introdu un cuvant: "
read cuv

while [ "$cuv" != "stop" ]
do
	for arg in $*
	do
		if file $arg | grep -q "ASCII text"
		then
			echo "Fisier: $arg"
			nr=$(grep -c "$cuv" "$arg")
			echo "Nr de linii: $nr"
			if [ $(($nr % 2)) -eq 0 ]
			then
				sed -i '$a '$cuv'' "$arg"
			fi
		else
			echo "Fisier: $arg"
			echo "Fisierul dat nu este de tip text."
		fi
	done
	echo -n "Introdu un cuvant: "
	read cuv
done

exit 0
