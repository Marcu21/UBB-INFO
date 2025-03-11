#!/bin/bash

# ./ex1.sh N

#verific numarul de argumente
if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente !"
	echo "Utilizare: $0 N"
	exit 1
fi

N=$1
for X in $(seq 1 $N)
do
	#cream fisier
	touch "file_$X.txt"
	#scriem fisier
	sed -n ''$X',+4p' /etc/passwd >"file_$X.txt"
done

exit 0
