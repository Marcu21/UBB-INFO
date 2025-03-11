#include <vector>
#include <list>

typedef int TElem;

#define NULL_TELEMENT 0


class Matrice {
private:
    struct Node {
        int linie;
        int coloana;
        TElem valoare;
        Node* next;

        Node(int l, int c, TElem v, Node* n = nullptr) : linie(l), coloana(c), valoare(v), next(n) {}
    };

    Node** tabela; // Array de pointeri la Node pentru reprezentarea listelor înlanțuite
    int nrLin, nrCol;
    int capacitate;

    int hash(int i, int j) const {
        return (i * 31 + j) % capacitate;
    }

public:
    Matrice(int nrLinii, int nrColoane);

    ~Matrice();

    TElem element(int i, int j) const;

    TElem modifica(int i, int j, TElem e);

    int nrLinii() const;

    int nrColoane() const;

    int numarElementeNenule(int linie) const;

    int valoareMaxima() const;
};