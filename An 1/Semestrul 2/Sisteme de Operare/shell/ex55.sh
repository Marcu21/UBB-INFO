#!/bin/bash
if [ $# -eq 0 ]
then
    echo 'Numar insuficient de argumente.'
    echo 'Utilizare:' $0 'nume1 nume2 ...'      # afișez modul de utilizare
    exit 1                                      # termin execuția
fi

for NUME in $*
do
    if [ -d $NUME ]
    then
        echo 'Director:' $NUME
        NF=$(find $NUME -type f | wc -l)
        echo 'Numar fisiere:' $NF
    elif [ -f $NUME ]
    then
        echo 'Fisier:' $NUME
        echo 'Numar linii:' $(wc -l < $NUME)
        echo 'Numar caractere:' $(wc -m <$NUME)
    else
        echo "'$NUME' nu este director sau fisier."
    fi
done

exit 0
