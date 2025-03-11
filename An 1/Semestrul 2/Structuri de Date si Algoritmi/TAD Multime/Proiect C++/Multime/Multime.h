#pragma once

#define NULL_TELEM -1
typedef int TElem;

typedef bool(*Conditie)(TElem);

class IteratorMultime;



class Multime {
    friend class IteratorMultime;

private:
    struct Node {
        TElem elemente;
        Node* urm;
        Node* pred;

        Node(TElem elemente, Node* urm=nullptr, Node* pred =nullptr) : elemente(elemente), urm(urm), pred(pred) {}
    };

    Node* prim;
    Node* ultim;
    int dimensiune;


public:
    //constructorul implicit
    Multime();

    //adauga un element in multime
    //returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
    bool adauga(TElem e);

    //sterge un element din multime
    //returneaza adevarat daca elementul a existat si a fost sters
    bool sterge(TElem e);

    //verifica daca un element se afla in multime
    bool cauta(TElem elem) const;


    //intoarce numarul de elemente din multime;
    int dim() const;

    //verifica daca multimea e vida;
    bool vida() const;

    //returneaza un iterator pe multime
    IteratorMultime iterator() const;


    void filtreaza(Conditie cond);

    // destructorul multimii
    ~Multime();
};




