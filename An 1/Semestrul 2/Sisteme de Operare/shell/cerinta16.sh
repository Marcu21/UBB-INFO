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
		if [ -f $arg ]
		then
			nr=$(grep "$cuv" "$arg" | wc -l)
			echo "File: $arg, Nr: $nr"
			if [ $((nr % 2)) -eq 0 ]
			then
				grep "$cuv" "$arg" | tail -n 1 >> "$arg"
			fi
		else
			echo "Argumentul $arg nu este fisier!"
		fi
	done

	echo -n "Introdu un cuvant: "
	read cuv
done

exit 0
