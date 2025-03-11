#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 arg1 arg2 ..."
	exit 1
fi

nrf=0
nru=0
nra=0

>"file_report.info"
>"user_report.info"
>"error_report.info"

for arg in $*
do
	if [ -f $arg ]
	then
		echo $(realpath "$arg") >> "file_report.info"
		sed -i '/ana/d' "$arg"
		nrf=$(($nrf+1))
	elif info=$(getent passwd "$arg")
	then
		echo "$arg" >> "user_report.info"
		ps -u "$arg" | wc -l >> "user_report.info"
		nru=$(($nru+1))
	else
		echo "$arg" >> "error_report.info"
		nra=$(($nra+1))
	fi
done

total=$(($nrf+$nru+$nra))
pf=$((100*$nrf))
pf=$(($pf/$total))

pu=$((100*$nru))
pu=$(($pu/$total))

pa=$((100*$nra))
pa=$(($pa/$total))

echo "Fisiere: $pf, Username: $pu, Altceva: $pa"

exit 0
