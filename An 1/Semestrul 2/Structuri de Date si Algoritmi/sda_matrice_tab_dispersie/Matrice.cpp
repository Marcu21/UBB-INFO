#include "Matrice.h"

#include <exception>

#include <stdexcept>

using namespace std;

//0(n), n este capacitatea tabelei
Matrice::Matrice(int nrLinii, int nrColoane) : nrLin(nrLinii), nrCol(nrColoane) {
    capacitate = 101; // Stabilim o capacitate implicită
    tabela = new Node*[capacitate];
    for (int i = 0; i < capacitate; i++) {
        tabela[i] = nullptr;
    }
}

//0(n*m), n este capacitatea tabelei si m este numarul mediu de noduri din fiecare lista
Matrice::~Matrice() {
    for (int i = 0; i < capacitate; i++) {
        Node* current = tabela[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] tabela;
}

//0(1)
int Matrice::nrLinii() const{
    //Returneaza numarul de linii ale matricei
    return nrLin;
}

//0(1)
int Matrice::nrColoane() const{
    //Returneaza numarul de coloane ale matricei
    return nrCol;
}


//Best case: 0(1), cand elementul se afla pe prima pozitie
//Worst case: 0(m), cand elementul se afla pe ultima pozitie, m reprezentand lungimea slotului din tabela
//Total case: O(m)
TElem Matrice::element(int i, int j) const {
    int index = hash(i, j);
    Node* current = tabela[index];
    while (current != nullptr) {
        if (current->linie == i && current->coloana == j)
            return current->valoare;
        current = current->next;
    }
    return NULL_TELEMENT;
}


//Best case: 0(1), cand elementul se afla pe prima pozitie
//Worst case: 0(m), m reprezentand lungimea slotului din tabela
//Total case: O(m)
TElem Matrice::modifica(int i, int j, TElem e) {
    int index = hash(i, j);
    Node* current = tabela[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->linie == i && current->coloana == j) {
            TElem oldVal = current->valoare;
            if (e == NULL_TELEMENT) {
                if (prev == nullptr) {
                    tabela[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
            } else {
                current->valoare = e;
            }
            return oldVal;
        }
        prev = current;
        current = current->next;
    }

    if (e != NULL_TELEMENT) {
        Node* newNode = new Node(i, j, e, tabela[index]);
        tabela[index] = newNode;
    }
    return NULL_TELEMENT;
}



//0(n*m), n este nr sloturilor din tabela si m este media nr tripletelor din slot
int Matrice::numarElementeNenule(int linie) const {
    if (linie < 0 || linie >= nrLin) {
        throw std::runtime_error("Indicele liniei este incorect.");
    }

    int count = 0;
    for (int i = 0; i < capacitate; i++) {
        Node* current = tabela[i];
        while (current != nullptr) {
            if (current->linie == linie && current->valoare != NULL_TELEMENT) {
                count++;
            }
            current = current->next;
        }
    }
    return count;
}


/*
 * Functie numarElementeNenule(linie)
        Daca linie < 0 sau linie >= nrLinii() atunci
            Arunca o exceptie cu mesajul "Linie in afara limitelor!"
        SfarsitDaca

        count <- 0

        Pentru i <-0, capacitate-1 executa
            current <- tabela[i]
            Cat timp current != NULL executa
                Daca [current].linie == linie si [current].valoare != NULL_TELEMENT atunci
                    count <- count + 1
                SfarsitDaca
                current <- [current].next
            SfarsitCatTimp
        SfarsitPentru

        returneaza count
SfFunctie

 */


//total case: 0(n*m)
int Matrice::valoareMaxima() const {
    //gaseste si returneaza valoarea maxima din matrice
    //Daca matricea este vida se returneaza NULL_TVALOARE
    TElem maxVal = NULL_TELEMENT;
    for (int i = 0; i < capacitate; i++) {
        Node* current = tabela[i];
        while (current != nullptr) {
            if (current->valoare > maxVal) {
                maxVal = current->valoare;
            }
            current = current->next;
        }
    }
    return maxVal;
}

/*
Functie valoareMaxima()
        maxVal <- NULL_TELEMENT
        Pentru i <-0, capacitate-1 executa
            current <- tabela[i]
            Cat timp current != NULL executa
                Daca [current].valoare > maxVal atunci
                    maxVal <- [current].valoare
                SfarsitDaca
                current <- [current].next
            SfarsitCatTimp
        SfarsitPentru

        returneaza maxVal
SfFunctie
*/