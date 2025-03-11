#!/bin/bash

if [ $# -lt 2 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 rw- dir1 dir2 ..."
	exit 1
fi

sir="$1"
shift 1

for dir in $*
do
	if [ ! -d $dir ]
	then
		echo "Director: $dir"
		echo "Directorul dat nu exista."
	else
		FILES=$(find $dir -type f)
		for file in $FILES
		do
			perms=$(stat --format=%A "$file")
			if [ "$perms" == "$sir" ]
			then
				cp "$file" "$file.bak"
				chmod u=r "$file.bak"
				permcopy=$(stat --format=%A "$file.bak")
				echo "Permisiuni: $sir"
				echo "Director: $dir"
				echo "	Fisier: $file"
				echo "	Permisiuni: $perms"
				echo "	Copie: $file.bak"
				echo "	Permisiuni: $permcopy"
			fi
		done
	fi
done

exit 0
