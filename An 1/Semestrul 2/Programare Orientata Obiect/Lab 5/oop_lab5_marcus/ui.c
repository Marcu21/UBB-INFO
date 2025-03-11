#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void print_materie_prima(MateriePrima materie_prima)
{
    printf("Nume: %s, Producator: %s, Cantitate: %d\n", materie_prima.nume, materie_prima.producator, materie_prima.cantitate);
}

int read_int(int* val)
{
    if (scanf("%d", val) == 1) return 1;
    int c;
    while (((c = fgetc(stdin)) != '\n') && (c != EOF));
    return 0;
}

MateriePrima* citeste_materie_prima()
{
    printf("Introduceti numele materiei prime: ");
    char nume[MAX_CHAR];
    scanf_s(MAX_CHAR_FORMAT, nume, MAX_CHAR);

    printf("Introduceti producatorul materiei prime: ");
    char producator[MAX_CHAR];
    scanf_s(MAX_CHAR_FORMAT, producator, MAX_CHAR);

    int cantitate = -1;
    printf("Introduceti cantitatea materiei prime: ");
    read_int(&cantitate);

    return creeaza_materie_prima(nume, producator, cantitate);
}


void main_ui()
{
    MateriiPrime* materii_prime;
    materii_prime = creeaza_vid();
    MateriiPrime* undoL;
    undoL = creeaza_vid();
    while (1)
    {
        printf("Alegeti optiunea:\n1. Adaugare materie prima\n2. Modificare materie prima\n3. Stergere materie prima\n");
        printf("4. Vizualizare materii prime pentru care cantitatea disponibila e mai mica decat un numar dat \n");
        printf("5. Vizualizare materii prime din stoc ordonat dupa nume sau cantitate disponibila(crescator / descrescator)\n");
        printf("6. Undo\n");
        printf("0. Exit\n");

        int optiune = -1;
        if (read_int(&optiune) == 0)
        {
            printf("Optiunea aleasa nu exista!\n");
        }

        if (optiune == 1)
        {
            if (adauga_element(materii_prime, citeste_materie_prima()) == 1)
            {
                adauga_materie_prima(undoL, copy_list(materii_prime));
                printf("Elementul a fost adaugat!\n");
            }
            else
            {
                printf("Elementul nu este valid!\n");
            }
        }
        else if (optiune == 2)
        {
            int index_modificare = -1;
            printf("Introduceti numarul elementului modificat: ");
            read_int(&index_modificare);
            if (modifica_element(materii_prime, index_modificare - 1, citeste_materie_prima()))
            {
                adauga_materie_prima(undoL, copy_list(materii_prime));
                printf("Elementul a fost modificat!\n");
            }
            else
            {
                printf("Nu exista element pe pozitia introdusa sau elementul nou este invalid!\n");
            }
        }
        else if (optiune == 3)
        {
            int index_stergere = -1;
            printf("Introduceti numarul elementului sters: ");
            read_int(&index_stergere);
            if (sterge_element(materii_prime, index_stergere - 1) == 1)
            {
                adauga_materie_prima(undoL, copy_list(materii_prime));
                printf("Elementul a fost sters!\n");
            }
            else
            {
                printf("Nu exista element pe pozitia introdusa!\n");
            }
        }
        else if (optiune == 4)
        {
            printf("1. Filtrare dupa cantitate maxima\n2. Filtrare dupa nume\n");
            int optiune_filtrare;
            scanf("%d", &optiune_filtrare);
            if (optiune_filtrare == 1) {
                int cantitate_maxima = -1;
                printf("Introdu cantitatea maxima: ");
                if (!read_int(&cantitate_maxima) || cantitate_maxima < 0) {
                    printf("Input invalid\n");
                    continue;
                }

                int total = 0;
                MateriePrima* filtered = get_materii_prime_cu_cantitate_maxima(materii_prime, cantitate_maxima, &total);
                for (int i = 0; i < total; i++) {
                    printf("%d. ", i + 1);
                    print_materie_prima(filtered[i]);
                }
                free(filtered);
            }
            else if (optiune_filtrare == 2) {
                char nume[MAX_CHAR];
                printf("Introdu numele materiei prime: ");
                scanf_s(MAX_CHAR_FORMAT, nume, MAX_CHAR);
                int total = 0;
                MateriePrima* filtered = get_materii_prime_cu_nume(materii_prime, nume, &total);
                for (int i = 0; i < total; i++) {
                    printf("%d. ", i + 1);
                    print_materie_prima(filtered[i]);
                }
                free(filtered);
            }
            else {
                printf("Input invalid\n");
            }
        }
        else if (optiune == 5)
        {
            int dupa_nume = -1;
            int descrescator = -1;
            printf("Introdu 1 daca vrei sa fie bubble sort, 0 daca vrei sa fie selection sort ");
            int opt;
            scanf("%d", &opt);
            if (opt == 1) {
                printf("Introdu 1 daca sortarea este dupa nume, 0 daca este dupa cantitate: ");
                if (!read_int(&dupa_nume)) {
                    printf("Input invalid\n");
                    continue;
                }
                printf("Introdu 1 daca sortarea este descrescatoare, 0 daca este crescatoare: ");
                if (!read_int(&descrescator)) {
                    printf("Input invalid\n");
                    continue;
                }
                int (*cmp)(MateriePrima, MateriePrima) = NULL;
                if (dupa_nume == 1) {
                    cmp = &compara_dupa_nume;
                }
                if (dupa_nume == 0) {
                    cmp = &compara_dupa_cantitate;
                }
                if (cmp == NULL) {
                    printf("Input invalid\n");
                    continue;
                }
                MateriePrima* sorted = sorteaza_materii_prime(materii_prime, cmp, descrescator);
                for (int i = 0; i < materii_prime->used; i++) {
                    printf("%d. ", i + 1);
                    print_materie_prima(sorted[i]);
                }
                free(sorted);
            }
            else if (opt == 0) {
                printf("Introdu 1 daca sortarea este dupa nume, 0 daca este dupa cantitate: ");
                if (!read_int(&dupa_nume)) {
                    printf("Input invalid\n");
                    continue;
                }
                printf("Introdu 1 daca sortarea este descrescatoare, 0 daca este crescatoare: ");
                if (!read_int(&descrescator)) {
                    printf("Input invalid\n");
                    continue;
                }
                int (*cmp)(MateriePrima, MateriePrima) = NULL;
                if (dupa_nume == 1) {
                    cmp = &compara_dupa_nume;
                }
                if (dupa_nume == 0) {
                    cmp = &compara_dupa_cantitate;
                }
                if (cmp == NULL) {
                    printf("Input invalid\n");
                    continue;
                }
                MateriePrima* sorted = sorteaza_materii_prime_insertion(materii_prime, cmp, descrescator);
                for (int i = 0; i < materii_prime->used; i++) {
                    printf("%d. ", i + 1);
                    print_materie_prima(sorted[i]);
                }
                free(sorted);
            }
            else {
                printf("Input invalid\n");
                continue;
            }

        }
        else if (optiune == 6)
        {
            if (undoL->used == 0)
            {
                printf("Nu exista operatii de undo!\n");
            }
            else {
                if (undoL->used == 1) {
                    distruge_materii_prime(materii_prime, (DestroyFunction)distruge_materie_prima);
                    materii_prime = creeaza_vid();
                    undoL->used--;
                    printf("Undo efectuat cu succes!\n");
                }
                else {
                    distruge_materii_prime(materii_prime, (DestroyFunction)distruge_materie_prima);
                    materii_prime = copy_list(undoL->array[undoL->used - 2]);

                    distruge_lista_materii(undoL->array[undoL->used - 1]);
                    undoL->used--;

                    printf("Undo efectuat cu succes!\n");
                }
            }
        }
        else if (optiune == 0)
        {
            distruge_materii_prime(materii_prime, (DestroyFunction)distruge_materie_prima);
            return;
        }
        else
        {
            printf("Optiunea aleasa nu exista!\n");
        }
    }
}
