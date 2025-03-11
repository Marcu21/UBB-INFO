#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 arg1 arg2 ..."
	exit 1
fi

for arg in $*
do
	if ok=$(getent passwd "$arg")
	then
		echo $ok | awk '{print $5}'
		if on=$(who | grep "$arg")
		then
			ps -ef | grep "$arg" | wc -l
		else
			lin=$(last | grep "$arg" | head -n 1)
			echo $lin | awk '{print $3 " " $7 " " $9 " " $10}'
		fi
	elif [ -f $arg ]
	then
		if [ -r $arg ] && [ -w $arg ]
		then
			sed -i -E 's/-[0-9]+/ERROR/g' "$arg"
		else
			echo "Nu am permisiuni de citire si scriere asupra $arg"
		fi
	elif [ -d $arg ]
	then
		du -s $arg | awk '{print $1}'
	else
		echo "Nu stiu ce este $arg"
	fi
done

exit 0

