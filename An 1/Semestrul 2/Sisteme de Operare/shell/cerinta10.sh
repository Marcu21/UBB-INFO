#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file1 file2 ..."
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
			echo "File: $arg"
			sum=$(grep -oE "[0-9]+" "$arg" | awk 'BEGIN{suma=0} {suma+=$1} END{print suma}')
			if [ $sum -lt $num ]
			then
				m=$(($num-$sum+1))
				sed '$a '$m'' "$arg"
				#echo "$m" >> "$arg"
			fi
		fi
	done
	echo -n "Introdu un numar: "
	read num
done

exit 0
