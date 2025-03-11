#pragma once

#ifndef SERVICE_H
#define SERVICE_H
#include "repo.h"

/// @brief adauga o noua materie prima
/// @param materii_prime array de materii prime
/// @param numar_materii_prime int*, numarul materilor prime existente deja, este modificat de functie
/// @param materie_prima_adaugata materia prima adaugata
/// @return 1 daca operatia a fost efectuata cu succes, 0 altfel
int adauga_element(MateriiPrime* materii_prime, MateriePrima*materie_prima_adaugata);

/// @brief modifica o materie prima
/// @param materii_prime array de materii prime
/// @param numar_materii_prime int*, numarul materilor prime existente deja, este modificat de functie
/// @param index_modificare indexul materiei prime modificate
/// @param materie_noua materia prima cu care se inlocuieste materia prima modificata
/// @return 1 daca operatia a fost efectuata cu succes, 0 altfel
int modifica_element(MateriiPrime* materii_prime, int index_modificare, MateriePrima* materie_noua);

/// @brief sterge o materie prima
/// @param materii_prime array de materii prime
/// @param numar_materii_prime int*, numarul materilor prime existente deja, este modificat de functie
/// @param index_stergere indexul de pe care se sterge materia prima
/// @return 1 daca operatia a fost efectuata cu succes, 0 altfel
int sterge_element(MateriiPrime* materii_prime, int index_stergere);

/// <summary>
/// Sorteaza materiile prime cu bubble sort
/// </summary>
/// <param name="materii_prime"></param>
/// <param name="cmp">functia de comparare</param>
/// <param name="descrescator"> 1 daca se ordoneaza descrescator, 0 daca se ordoneaza crescator</param>
/// <returns>array MateriePrima*</returns>
MateriePrima* sorteaza_materii_prime(MateriiPrime* materii_prime, int (*cmp)(MateriePrima, MateriePrima), int descrescator);

/// <summary>
/// compara doua materii prime dupa nume
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>1 daca numele lui a este mai mare decat numele lui b, 0 altfel</returns>
int compara_dupa_nume(MateriePrima a, MateriePrima b);

/// <summary>
/// compara doua materii prime dupa nume
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>1 daca cantitatea lui a este mai mare decat a lui b, 0 altfel</returns>
int compara_dupa_cantitate(MateriePrima a, MateriePrima b);

/// <summary>
/// gaseste materiile prime cu cantitate mai mica de o cantitate
/// </summary>
/// <param name="materii_prime"></param>
/// <param name="cantitate_maxima">cantitate dupa care se face cautarea</param>
/// <param name="total">numarul de materii prime gasite</param>
/// <returns>array MateriePrima*</returns>
MateriePrima* get_materii_prime_cu_cantitate_maxima(MateriiPrime* materii_prime, int cantitate_maxima, int *total);

/// <summary>
/// Sorteaza materiile prime cu insertion sort
/// </summary>
/// <param name="materii_prime"></param>
/// <param name="cmp">functia de comparare</param>
/// <param name="descrescator"> 1 daca se ordoneaza descrescator, 0 daca se ordoneaza crescator</param>
/// <returns>array MateriePrima*</returns>
MateriePrima* sorteaza_materii_prime_insertion(MateriiPrime* materii_prime, int (*cmp)(MateriePrima, MateriePrima), int descrescator);

/// <summary>
/// gaseste materiile prime cu un anumit nume
/// </summary>
/// <param name="materii_prime"></param>
/// <param name="nume">numele dupa care se face cautarea</param>
/// <param name="total">numarul de materii prime gasite</param>
/// <returns>array MateriePrima*</returns>
MateriePrima* get_materii_prime_cu_nume(MateriiPrime* materii_prime, const char* nume, int* total);
#endif