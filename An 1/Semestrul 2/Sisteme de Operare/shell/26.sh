#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente!"
	echo "Utilizare: $0 director"
	exit 1
fi

dir=$1

if [ ! -d $dir ]
then
	echo "$dir nu este un director!"
	exit 1
fi

for file in $(find $dir -type f | grep -E ".*\.c")
do
	if file $file | grep -q "C source"
	then
		echo "$file"
	fi
done

sum=0
for file in $(find $dir -type f | grep -E -v ".*\.c")
do
	if file $file | grep -q "C source"
        then
		lines=$(wc -l < $file)
                sum=$(($sum+$lines))
        fi
done
echo "Numarul total de linii: $sum"
exit 0
