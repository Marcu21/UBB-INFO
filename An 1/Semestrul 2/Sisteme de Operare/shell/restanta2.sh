#!/bin/bash
if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 arg1 arg2..."
	exit 1
fi

suma=0
for arg in $*
do
	if [ -f "$arg" ]
	then
		nr=$(wc -w < "$arg")
		suma=$(($suma + $nr))
	fi
done

echo "Suma nr de cuvinte este: $suma"
exit 0
