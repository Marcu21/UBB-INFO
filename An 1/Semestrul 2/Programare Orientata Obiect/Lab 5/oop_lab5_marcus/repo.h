#pragma once

#ifndef REPO_H
#define REPO_H
#include "domain.h"

typedef void* ElemType;
typedef void (*DestroyFunction)(ElemType);
typedef struct {
    ElemType* array;
    int used;
    int capacity;
} MateriiPrime;





MateriiPrime* creeaza_vid();
/// @brief adauga o noua materie prima
/// @param materii_prime array de materii prime
/// @param numar_materii_prime int*, numarul materilor prime existente deja, este modificat de functie
/// @param materie_prima_adaugata materia prima adaugata
void adauga_materie_prima(MateriiPrime* materii_destinatie, ElemType materii_sursa);
/// @brief modifica o materie prima
/// @param materii_prime array de materii prime
/// @param numar_materii_prime int*, numarul materilor prime existente deja, este modificat de functie
/// @param index_modificare indexul materiei prime modificate
/// @param materie_noua materia prima cu care se inlocuieste materia prima modificata
void modifica_materie_prima(MateriiPrime* materii_prime, int index_modificare, MateriePrima materie_noua);

/// @brief sterge o materie prima
/// @param materii_prime array de materii prime
/// @param numar_materii_prime int*, numarul materilor prime existente deja, este modificat de functie
/// @param index_stergere indexul de pe care se sterge materia prima
void sterge_materie_prima(MateriiPrime* materii_prime, int index_stergere);
/// <summary>
/// distruge lista de materii prime
/// </summary>
/*
void delete_last_element(MateriiPrime* list);
*/
///Copiaza lista
MateriiPrime* copy_list(MateriiPrime* materii_prime);
///Distruge materiile prime
void distruge_materii_prime(MateriiPrime* materii_prime, DestroyFunction destFct);
///Distruge lista de materii prime
void distruge_lista_materii(MateriiPrime* materii_prime);
#endif