#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file1 file2 string1 string2 ..."
	exit 1
fi

f1=$1
f2=$2
shift 2
touch $f1
touch $f2

for arg in $*
do
	if grep -q "^$arg" "passwd.fake"
	then
		name=$(grep "$arg" "passwd.fake" | cut -d: -f5)
		dir=$(grep "$arg" "passwd.fake" | cut -d: -f6)
		size=$(du -s $dir)
		echo $name >> $f2
		echo $size >> $f2
	else
		echo $arg >> $f1
	fi
done

exit 0
