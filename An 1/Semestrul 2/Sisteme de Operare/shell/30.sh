#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 fisier_comenzi"
	exit 1
fi

while IFS= read -r line
do
	com=$(echo "$line" | awk '{print $1" "$2}')
	if [ "$com" == "CREATE DIR" ]
	then
		arg=$(echo "$line" | awk '{print $3}')
		mkdir "$arg"
	elif [ "$com" == "CREATE FILE" ]
	then
		arg=$(echo "$line" | awk '{print $3}')
		touch "$arg"
	elif [ "$com" == "MOVE DIR" ]
	then
		arg1=$(echo "$line" | awk '{print $3}')
		arg2=$(echo "$line" | awk '{print $4}')
		mv "$arg1" "$arg2"
	elif [ "$com" == "SET PERM" ]
	then
		arg1=$(echo "$line" | awk '{print $3}')
                arg2=$(echo "$line" | awk '{print $4}')
		arg1=$(echo "$arg" | sed 's/^\.//')
		if [ -e "$arg1" ]
		then
			chmod "$arg2" "$arg1"
		else
			echo "Cannot set permissions on $arg1: No such file or directory"
		fi
	else
		echo "Nu inteleg comanda: $com"
	fi
done<"$1"

exit 0
