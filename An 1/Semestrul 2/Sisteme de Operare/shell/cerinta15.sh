#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 fisier"
	exit 1
fi

fin=$1
fout="output.txt"
touch $fout

echo -n "Introdu un numar: "
read num

while [ $num -ne 0 ]
do
	n=$num
	while IFS= read -r line && [ $n -ne 0 ]
	do
		n=$(($n-1))
		echo "$line">>"$fout"
	done<"$fin"

	echo -n "Introdu un numar: "
	read num
done

exit 0
