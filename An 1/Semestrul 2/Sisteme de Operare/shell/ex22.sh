#!/bin/bash
if [ $# -eq 0 ]
then
    echo 'Numar insuficient de argumente.'
    echo 'Utilizare:' $0 'nume_director'                # afișez modul de utilizare
    exit 1                                              # termin execuția
fi

DIR=$1

# prima solutie
# ---------------------------------------------------------------

NTF=0                                                   # numărul total de fișiere
NTL=0                                                   # numărul total de linii
FILES=$(find $DIR -type f)
for F in $FILES
do
    if file $F | grep -q 'ASCII text'
    then
        echo "Fisier: $F"
        NL=$(cat $F | wc -l)
        NTL=$(($NTL+$NL))
        NTF=$[$NTF+1]
    fi
done
echo -e "\nTotal fisiere: $NTF\nTotal linii: $NTL\nNumar mediu de linii: $(($NTL/$NTF))"
