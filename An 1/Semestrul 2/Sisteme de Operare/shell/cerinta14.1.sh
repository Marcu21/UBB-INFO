#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 C file"
	exit 1
fi

for arg in $*
do
	nr=$(grep -oE "//.*" "$arg" | wc -l)
	echo "File: $arg, Numar: $nr"
done

exit 0
