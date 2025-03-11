#!/bin/bash

echo "Introdu un cuvant: "
read cuv

nru=0
nrf=0
nra=0

while [ "$cuv" != "stop" ]
do
	if user=$(getent passwd "$cuv")
	then
		ps -u "$cuv" | wc -l
		nru=$(($nru+1))
	elif [ -f $cuv ]
	then
		sed -i 's/a/@/g' "$cuv"
		sed -i 's/e/3/g' "$cuv"
		sed -i 's/i/!/g' "$cuv"
		nrf=$(($nrf+1))
	else
		echo "Nu stiu ce e $cuv"
		nra=$(($nra+1))
	fi

	echo "Introdu un cuvant: "
	read cuv
done

total=$(($nru+$nrf+$nra))

pu=$((100*$nru))
pu=$(($pu/$total))

pf=$((100*$nrf))
pf=$(($pf/$total))

pa=$((100*$nra))
pa=$(($pa/$total))

echo "Username: $pu, File: $pf, Altceva: $pa"

exit 0
