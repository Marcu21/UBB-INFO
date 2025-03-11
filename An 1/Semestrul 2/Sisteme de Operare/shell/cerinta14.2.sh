#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 director"
	exit 1
fi

dir=$1
files=$(find $dir -type f)
lin=0
count=0

for file in $files
do
	nrlin=$(cat $file | wc -l)
	lin=$(($lin+$nrlin))
	count=$(($count+1))
done

medie=$(($lin/$count))

echo "Media nr de linii este $medie"

exit 0
