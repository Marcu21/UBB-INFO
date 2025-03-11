#!/bin/bash

#./ex1.sh N
#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo "Numar insuficient de argumente !"
        echo "Utilizare: $0 N"
        exit 1
fi

NTF=0
NTL=0
FILES=$(find $1 -type f)
for FILE in $FILES
do
        if file $FILE | grep -q 'ASCII text$'
        then
                echo Fisier: $FILE
		NTF=$(($NTF+1))
		NL=$(cat $FILE | wc -l)
		NTL=$(($NTL+$NL))
	fi
done

echo "Numar mediu de linii: " $((NTL/NTF))

exit 0
