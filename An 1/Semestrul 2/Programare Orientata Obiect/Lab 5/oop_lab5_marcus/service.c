#include "service.h"
#include <string.h>
int adauga_element(MateriiPrime* materii_prime, MateriePrima* materie_prima_adaugata)
{
    if (validare(*materie_prima_adaugata) == 0)
    {
        distruge_materie_prima(materie_prima_adaugata);
        return 0;
    }
    adauga_materie_prima(materii_prime, materie_prima_adaugata);
    return 1;
}

int modifica_element(MateriiPrime* materii_prime, int index_modificare, MateriePrima* materie_noua)
{
    if (index_modificare >= materii_prime->used || index_modificare < 0 || validare(*materie_noua) == 0)
    {
        distruge_materie_prima(materie_noua);
        return 0;
    }
    modifica_materie_prima(materii_prime, index_modificare, *materie_noua);

    return 1;
}

int sterge_element(MateriiPrime* materii_prime, int index_stergere)
{
    if (index_stergere >= materii_prime->used || index_stergere < 0) return 0;
    sterge_materie_prima(materii_prime, index_stergere);
    return 1;
}

MateriePrima* sorteaza_materii_prime(MateriiPrime* materii_prime, int (*cmp)(MateriePrima, MateriePrima), int descrescator)
{
    MateriePrima* tmp = malloc(sizeof(MateriePrima) * materii_prime->used);
    if (tmp == NULL) return NULL;

    for (int i = 0; i < materii_prime->used; i++)
    {
        tmp[i] = *((MateriePrima*)materii_prime->array[i]);
    }

    for (int i = 0; i < materii_prime->used; i++)
    {
        for (int j = i + 1; j < materii_prime->used; j++)
        {
            if ((descrescator && !(*cmp)(tmp[i], tmp[j])) || (!descrescator && (*cmp)(tmp[i], tmp[j])))
            {
                MateriePrima aux = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = aux;
            }

        }
    }
    return tmp;
}

MateriePrima* sorteaza_materii_prime_insertion(MateriiPrime* materii_prime, int (*cmp)(MateriePrima, MateriePrima), int descrescator)
{
    MateriePrima* tmp = malloc(sizeof(MateriePrima) * materii_prime->used);
    if (tmp == NULL) return NULL;

    for (int i = 0; i < materii_prime->used; i++)
    {
        tmp[i] = *((MateriePrima*)materii_prime->array[i]);
    }

    for (int i = 1; i < materii_prime->used; i++)
    {
        MateriePrima val = tmp[i];
        int j = i - 1;
        while (j >= 0 && ((!descrescator && (*cmp)(tmp[j], val)) || (descrescator && !(*cmp)(tmp[j], val))))
        {
            tmp[j + 1] = tmp[j];
            j = j - 1;
        }
        tmp[j + 1] = val;
    }

    return tmp;
}



int compara_dupa_nume(MateriePrima a, MateriePrima b)
{
    return strcmp(a.nume, b.nume) > 0;
}

int compara_dupa_cantitate(MateriePrima a, MateriePrima b)
{
    return a.cantitate > b.cantitate;
}

MateriePrima* get_materii_prime_cu_cantitate_maxima(MateriiPrime* materii_prime, int cantitate_maxima, int* total)
{
    MateriePrima* tmp = (MateriePrima*)malloc(sizeof(MateriePrima) * (materii_prime->used));
    if (tmp == NULL) return NULL;
    (*total) = 0;
    for (int i = 0; i < materii_prime->used; i++)
    {
        if (((MateriePrima*)materii_prime->array[i])->cantitate <= cantitate_maxima)
        {
            tmp[(*total)++] = *((MateriePrima*)materii_prime->array[i]);
        }
    }
    return tmp;
}

MateriePrima* get_materii_prime_cu_nume(MateriiPrime* materii_prime, const char* nume, int* total)
{
    MateriePrima* tmp = (MateriePrima*)malloc(sizeof(MateriePrima) * materii_prime->used);
    if (tmp == NULL) return NULL;
    (*total) = 0;
    for (int i = 0; i < materii_prime->used; i++)
    {
        if (strcmp(((MateriePrima*)materii_prime->array[i])->nume, nume) == 0)
        {
            tmp[(*total)++] = *((MateriePrima*)materii_prime->array[i]);
        }
    }
    return tmp;
}

