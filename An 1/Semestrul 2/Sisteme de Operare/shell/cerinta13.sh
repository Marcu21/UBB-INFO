#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 file1 file2"
	exit 1
fi

ok=0
for arg in $*
do
	if [ -f $arg ]
	then
		ok=1
	fi
done

if [ $ok -eq 0 ]
then
	echo "Nu ai furnizat niciun fisier!"
	exit 1
fi

echo -n "Introdu un numar: "
read num

while [ $num -ne 0 ]
do
	for arg in $*
	do
		if [ -e $arg ] && [ -s $arg ]
		then
			nr=$(grep -oE "\<[0-9]{$num}\>" "$arg" | wc -l)
			echo "File: $arg Numar: $nr"
			if [ $((nr % 2)) -eq 1 ]
			then
				nou=0
				for x in $(seq 1 $num)
				do
					nou=$((nou*10+$x))
				done
				echo "$nou" >> "$arg"
			fi
		else
			echo "Acest fisier nu exista sau este vid!"
		fi
	done

	echo -n "Introdu un numar: "
	read num
done

exit 0
