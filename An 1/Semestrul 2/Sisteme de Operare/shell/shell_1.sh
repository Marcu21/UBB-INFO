#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 fisier"
	exit 1
fi

while IFS= read -r line
do
	cerere=$(echo $line | grep -o -E 'req[0-9]+')
	if [ ! -e "$cerere.txt" ]
	then
		touch "$cerere.txt"
	fi
	echo $line >> "$cerere.txt"
done<"$1"

touch "tempshell.txt"
for file in req[0-9]*.txt
do
	id=$(echo $file | grep 'req[0-9]*')
	nr=$(grep 'error' $file | wc -l)
	echo "$nr $id" >> "tempshell.txt"
done

while IFS= read -r line
do
	nr=$(echo $line | awk '{print $1}')
	id=$(echo $line | awk '{print $2}')
	echo "Request $id are $nr erori"
done< <(cat "tempshell.txt" | sort)

exit 0
