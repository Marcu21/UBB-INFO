#!/bin/bash

if [ ! $# -eq 1 ]
then
	echo "Numar incorect de argumente!"
	echo "Utilizare: $0 restanta1.log"
	exit 1
fi

while IFS= read -r line
do
	cerere=$(echo $line | awk '{print $4}')
	echo $line >> "$cerere.log"
done<"$1"

for file in req[0-9]*.log
do
	id=$(echo $file | grep '^[^\.]*')
	nr=$(grep -c 'error' $file)
	echo "$nr $id" >> "temp.txt"
done
echo "Top erori"
while IFS= read -r line
do
	idd=$(echo $line | awk '{print $2}')
	nrr=$(echo $line | awk '{print $1}')
	echo "Request $idd are $nrr erori"
done<"temp.txt" | sort

exit 0

