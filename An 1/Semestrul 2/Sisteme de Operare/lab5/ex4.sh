#!/bin/bash

#./ex1.sh N
#verific numarul de argumente
if [ $# -eq 0 ]
then
        echo "Numar insuficient de argumente !"
        echo "Utilizare: $0 N"
        exit 1
fi

read -p "Numar cifre: " NC

NTF=0
NTL=0
FILES=$(find $1 -type f)
for FILE in $FILES
do
        if cat $FILE | grep -qE "[0-9]{$NC,}"
        then
                echo Fisier: $FILE
        fi
done

exit 0
