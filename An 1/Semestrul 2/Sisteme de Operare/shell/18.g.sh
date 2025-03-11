#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Numar insuficient de argumente!"
    echo "Utilizare: $0 fisier_date.txt"
    exit 1
fi

while IFS= read -r line; do
    zi=$(awk '{print $1}' <<< "$line")
    luna=$(awk '{print $2}' <<< "$line")
    timp=$(awk '{print $3}' <<< "$line")
    ora=$(awk -F. '{print $1}' <<< "$timp")
    minut=$(awk -F. '{print $2}' <<< "$timp")
    echo "Data: $zi $luna"
    echo "Orele: $ora $minut"
    
    while IFS= read -r linie; do
        ora_in=$(awk '{print substr($7, 1, 2)}' <<< "$linie")
        minut_in=$(awk '{print substr($7, 4, 2)}' <<< "$linie")
        ora_out=$(awk '{print substr($9, 1, 2)}' <<< "$linie")
        minut_out=$(awk '{print substr($9, 4, 2)}' <<< "$linie")

        # Determine if the user was connected at the specified time
        if [[ $ora_in -lt $ora && $ora_out -gt $ora ]] ||
           [[ $ora_in -eq $ora && $minut_in -le $minut ]] ||
           [[ $ora_out -eq $ora && $minut_out -ge $minut ]]; then
            user=$(awk '{print $1}' <<< "$linie")
            if passline=$(grep "^$user:" "passwd.fake"); then
                nume=$(awk -F: '{print $5}' <<< "$passline")
                path=$(awk -F: '{print $6}' <<< "$passline")
                grupa=$(awk -F/ '{print $4}' <<< "$path")  # assuming group is 4th field in path
                if [ ! -f "$grupa.txt" ]; then
                    touch "$grupa.txt"
                fi
                echo "$nume" >> "$grupa.txt"
                echo "User: $user, Nume: $nume, Grupa: $grupa"
            fi
        fi
    done < <(grep "$luna $zi" "last.fake")
done < "$1"

exit 0
