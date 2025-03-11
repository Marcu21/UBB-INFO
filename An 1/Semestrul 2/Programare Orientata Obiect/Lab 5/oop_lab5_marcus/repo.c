#include <stdlib.h>
#include "repo.h"
#include <string.h>

MateriiPrime* creeaza_vid()
{
    MateriiPrime* materii_prime = malloc(sizeof(MateriiPrime));
    materii_prime->capacity = 1;
    materii_prime->array = malloc(sizeof(MateriePrima)*materii_prime->capacity);
    materii_prime->used = 0;
    return materii_prime;
}

MateriiPrime* copy_list(MateriiPrime* materii_prime)
{
    MateriiPrime* rez = creeaza_vid();
    for (int i = 0; i < materii_prime->used; i++)
    {
        ElemType m = materii_prime->array[i];
        adauga_materie_prima(rez, copy_materie(m));
    }
    return rez;
}


void adauga_materie_prima(MateriiPrime* materii_destinatie, ElemType materii_sursa)
{
    if (materii_destinatie->used + 1 >= materii_destinatie->capacity)
    {
        while (materii_destinatie->used + 1 >= materii_destinatie->capacity)
        {
            materii_destinatie->capacity *= 2;
        }
        materii_destinatie->array = realloc(materii_destinatie->array, sizeof(ElemType) * materii_destinatie->capacity);
    }

    materii_destinatie->array[materii_destinatie->used++] = materii_sursa;
}


void modifica_materie_prima(MateriiPrime* materii_prime, int index_modificare, MateriePrima materie_noua)
{

    ((MateriePrima*)materii_prime->array[index_modificare])->cantitate = materie_noua.cantitate;
    strcpy(((MateriePrima*)materii_prime->array[index_modificare])->producator, materie_noua.producator);
    strcpy(((MateriePrima*)materii_prime->array[index_modificare])->nume, materie_noua.nume);
}



void sterge_materie_prima(MateriiPrime* materii_prime, int index_stergere){
    MateriePrima* to_be_freed = materii_prime->array[index_stergere];
    for (int i = index_stergere; i < materii_prime->used-1; i++)
    {
        materii_prime->array[i] = materii_prime->array[i+1];
    }
    materii_prime->used--;
    distruge_materie_prima(to_be_freed);
}

void distruge_lista_materii(MateriiPrime* materii_prime){
    distruge_materii_prime(materii_prime, (DestroyFunction)distruge_materie_prima);
}

void distruge_materii_prime(MateriiPrime* materii_prime, DestroyFunction destrF)
{
    for (int i = 0; i < materii_prime->used; i++)
    {
        ElemType m = materii_prime->array[i];
        destrF(m);
    }
    free(materii_prime->array);
    free(materii_prime);
}
/*
void delete_last_element(MateriiPrime* undoL) {
    if (undoL->used == 1) {
        printf("The undoL list is empty!\n");
        return;
    }

    // Free the memory associated with the last element
    distruge_lista_materii(undoL->array[undoL->used - 1]);

    // Decrement the 'used' variable to indicate removal of the last element
    undoL->used--;
}

*/