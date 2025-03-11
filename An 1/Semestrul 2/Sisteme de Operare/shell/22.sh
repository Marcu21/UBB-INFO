#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 fisier_cuvinte"
	exit 1
fi

echo -n "Introdu un numar intre 0 si 10: "
read N

while [ $N -ne 0 ]
do
	echo -n "Introduceti un nume de fisier: "
	read fisier
	nr_cuv=0
	nr_car=0
	nr_lin=0
	while IFS= read -r line && [ $N -gt 0 ]
	do
		primu="${line:0:1}"
		echo $line " " >> $fisier
		N=$(($N-1))
	done<"$1"
	nr_cuv=$(cat $fisier | wc -w)
	nr_car=$(cat $fisier | wc -c)
	nr_lin=$(cat $fisier | wc -l)
	echo "Fisier: $fisier"
	echo "Linii: $nr_lin Cuvinte: $nr_cuv Caractere: $nr_car"
	echo -n "Introdu un numar intre 0 si 10: "
	read N
done
