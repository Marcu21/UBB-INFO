#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 arg1 arg2 arg3..."
	exit 1
fi

nrf=0
nrd=0
nro=0

for arg in $*
do
	if [ -d $arg ]
	then
		nrd=$(($nrd+1))
		files=$(find $arg -type f)
		maxsize=0
		maxfile=""
		for file in $files
		do
			size=$(stat --format="%s" $file)
			if [ $size -gt $maxsize ]
			then
				maxsize=$size
				maxfile=$file
			fi
		done
		echo "$maxfile with size $maxsize"
	elif [ -f $arg ]
	then
		nrf=$(($nrf+1))
		line=$(cat $arg | sort | grep "^[A-Z].*" | head -n 1)
		echo "$line"
	else
		nro=$(($nro+1))
		echo "The argument is neither a file or directory"
	fi
done
total=$(($nrd+$nrf+$nro))
#pd=$(($nrd / $total * 100))
#pf=$(($nrf / $total * 100))
#po=$(($nro / $total * 100))
pd=$((100 * nrd / total))
pf=$((100 * nrf / total))
po=$((100 * nro / total))
echo "Director: $pd% Fisier: $pf% Other: $po%"
exit 0
