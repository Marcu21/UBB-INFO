//Descompune un numar natural par, mai mare strict ca 2, intr-o suma de doua numere prime (verificarea ipotezei lui Goldbach).

#include <stdio.h>

int prim(int n)
//Returneaza 1 daca numarul este prim, altfel returneaza 0
//input: n (int)
//output: 0/1 in functie de primalitatea numarului
{
    if (n<2) return 0;
    for(int i=2;i<=n/2;i++)
        if (n%i==0) return 0;
    return 1;
}

void goldbach(int x)
//Afiseaza toate descompunerile un numar natural par, mai mare strict ca 2, intr-o suma de doua numere prime
//In caz ca numarul este mai mic sau egal decat 2 sau nu este par, tipareste un mesaj corespunzator
//input: x (int)
{
    if ((x<=2) || (x%2)!=0)
    {
        printf("Numarul nu corespunde principiului lui Goldbach\n");
        return ;
    }
    for(int i=2;i<=x/2;i++) {
        if ((prim(i) == 1) && (prim(x - i) == 1)) {
            printf("%d = %d + %d\n", x, i, x - i);
        }
    }
}

void exponent(int x, int p)
//Afiseaza puterea la care apare un numar prim p in descompunerea in factori primi a unui numar
//input: x (numarul principal) (int)
//input: y (numarul prim care apare in descompunerea numarului anterior) (int)
{
    if (prim(p)==0)
    {
        printf("Numarul nu este prim!\n");
        return ;
    }
    int cnt = 0;
    while (x%p==0){
        cnt++;
        x/=p;
    }
    printf("Exponentul la care apare numarul %d este %d \n", p,cnt);
}

int main() {
    int loop = 1;
    while (loop == 1) {
        printf("1. Problema 14 \n2. Problema 8 \n");
        int x;
        printf("Alege optiunea ta: ");
        scanf("%d", &x);
        if (x == 1) {
            int nr;
            scanf("%d", &nr);
            goldbach(nr);
        } else if (x == 2) {
            {
                int nr;
                scanf("%d", &nr);
                int p;
                scanf("%d", &p);
                exponent(nr, p);
            }
        } else printf("Optiunea nu este corecta!");
    }
}