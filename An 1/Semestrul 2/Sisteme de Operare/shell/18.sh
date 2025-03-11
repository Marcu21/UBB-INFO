#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 fisier_date.txt"
	exit 1
fi

while IFS= read -r line
do
	count=0
	zi=$(echo $line | awk '{print $1}')
	luna=$(echo $line | awk '{print $2}')
	timp=$(echo $line | awk '{print $3}')
	ora=$(echo $timp | awk -F. '{print $1}')
	minut=$(echo $timp | awk -F. '{print $2}')
	echo "Data: $zi $luna"
        echo "Orele: $ora $minut"
	while IFS= read -r linie
	do
		ok=0
		#echo $linie
		inn=$(echo $linie | awk '{print $7}')
		outt=$(echo $linie | awk '{print $9}')
		ora_in=$(echo $inn | awk -F: '{print $1}')
		minut_in=$(echo $inn | awk -F: '{print $2}')
		ora_out=$(echo $outt | awk -F: '{print $1}')
		minut_out=$(echo $outt | awk -F: '{print $2}')
		if [ $ora_in -lt $ora ] && [ $ora_out -gt $ora ]
		then
			ok=1
		elif [ $ora_in -eq $ora ] && [ $minut_in -le $minut ]
		then
			ok=1
		elif [ $ora_in -lt $ora ] && [ $ora_out -eq $ora ] && [ $minut_out -ge $minut ]
		then
			ok=1
		fi
		#echo $ok
		if [ $ok -eq 1 ]
		then
			count=$(($count+1))
			user=$(echo $linie | awk '{print $1}')
			passline=$(grep "^$user" "passwd.fake")
			nume=$(echo $passline | awk -F: '{print $5}')
			path=$(echo $passline | awk -F: '{print $6}')
			grupa=$(echo $path | awk -F/ '{print $4}')
			if [ ! -e "$grupa.txt" ]
			then
				touch "$grupa.txt"
			fi
			echo "$nume" >> "$grupa.txt"
			echo "User: $user, Nume: $nume, Grupa: $grupa, Count: $count"
		fi
	done< <(grep "$luna  $zi" "last.fake")
	echo "Total studenti: $count"
done<"$1"

exit 0
