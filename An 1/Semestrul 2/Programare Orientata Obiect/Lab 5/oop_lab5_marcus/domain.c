#pragma once
#include <string.h>
#include <stdlib.h>
#include "domain.h"

MateriePrima* creeaza_materie_prima(char* nume, char* producator, int cantitate)
{
    MateriePrima* materie_prima = malloc(sizeof(MateriePrima));


    materie_prima->nume = malloc(strlen(nume) + 1);

    strcpy(materie_prima->nume, nume);

    materie_prima->producator = malloc(strlen(producator) + 1);

    strcpy(materie_prima->producator, producator);

    materie_prima->cantitate = cantitate;

    return materie_prima;
}


void distruge_materie_prima(MateriePrima* materie_prima)
{

    free(materie_prima->nume);
    free(materie_prima->producator);
    free(materie_prima);
}


int validare(MateriePrima materie_prima)
{
    if (strlen(materie_prima.nume) == 0) return 0;
    if (strlen(materie_prima.producator) == 0) return 0;
    if (materie_prima.cantitate <= 0) return 0;
    return 1;
}

MateriePrima* copy_materie(MateriePrima* m)
{
    return creeaza_materie_prima(m->nume,m->producator,m->cantitate);
}