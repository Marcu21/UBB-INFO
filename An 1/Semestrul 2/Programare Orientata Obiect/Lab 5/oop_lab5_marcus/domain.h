#pragma once

#ifndef DOMAIN_H
#define DOMAIN_H
#define MAX_CHAR 100
#define MAX_CHAR_FORMAT "%99s"
#include <stdlib.h>


typedef struct {
    char* nume;
    char* producator;
    int cantitate;
} MateriePrima;

/// @brief creeaza materie prima noua
/// @param nume char[], nume
/// @param producator char[], producator
/// @param cantitate int, cantitate
/// @return obiectul MateriePrima creat
MateriePrima* creeaza_materie_prima(char* nume, char* producator, int cantitate);

/// <summary>
/// Elibereaza memoria ocupata de materia prima
/// </summary>
/// <param name="materie_prima"></param>
void distruge_materie_prima(MateriePrima* materie_prima);

/// @brief valideaza materia prima
/// @param materie_prima materie prima care este validata
/// @return 1 daca e valida, 0 altfel
int validare(MateriePrima materie_prima);
MateriePrima* copy_materie(MateriePrima* m);
#endif