#!/bin/bash

read -p "Fisier: " FILE
read -p "Numar linie: " NL

sed -n ''$NL'p' $FILE 
#awk 'NR == '$NL'' $FILE
