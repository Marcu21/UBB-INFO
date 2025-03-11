"""
lista_maxima= [1,2,3,4]
            lista_curenta = [6,7,8,9,10,11,12]
            lista_maxima = lista_curenta [:]
"""

"""
Scrieti o aplicatie care are interfata utilizator tip consolă cu un meniu:
1 Citirea unei liste de numere intregi
2,3 Gasirea secventelor de lungime maxima care respectă o proprietatea dată.
 Fiecare student primeste 2 proprietati din lista
de mai jos.
4 Iesire din aplicatie.
Documentatia să contină:
 Scenarii de rulare pentru cele două cerinte primite (vezi curs 1 – scenarii de rulare)
 Cazuri de testare pentru cele doua cerinte în format tabelar (vezi curs 1 – cazuri de testare)
oricare doua elemente consecutive difera printr-un numar prim.
p=1 sau diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1]) au semne contrare,
pentru j=i..i+p-2.
"""

def este_prim(numar: int):
    if numar < 2: return 0
    if numar == 2: return 1
    if numar % 2 == 0: return 0
    for i in range(3,numar//2 + 1,2):
        if numar % i == 0: return 0

    return 1
def  secventa_maxima_interval_0_10(lista: int,dimensiune_lista: int):
    lista_secventa_maxima = []
    lista_secventa_curenta = []
    secventa_curenta = 0
    secventa_maxima = -1


    for i in range(dimensiune_lista):
        if lista[i]>=0 and lista[i]<=10:
            lista_secventa_curenta.append(lista[i])
            secventa_curenta += 1
            if secventa_curenta > secventa_maxima:
                lista_secventa_maxima.clear()
                lista_secventa_maxima = lista_secventa_curenta [:]
                secventa_maxima = secventa_curenta

        else:
            secventa_curenta=0
            lista_secventa_curenta.clear()

    return lista_secventa_maxima
def secventa_maxima_semn_contrar(lista, dimensiune_lista):

    """
        Secventa maxima cu semn contrar are dimensiunea 7 si este:
        [2, 4, 7, 1, 3, 8, 9]
            1  1  0  1  1  1
         0  1  2  3  4  5  6
    """

    lista_secventa_maxima = []
    lista_secventa_curenta = []
    secventa_curenta = 0
    secventa_maxima = -1
    for i in range(dimensiune_lista-2):
        #pentru lista[i+1]-lista[i] >0 => + => semn_a =1
        #pentru lista[i+1]-lista[i] <0 => + => semn_a =0
        "1,4,3,5,2"
        " +  -  +  -"

        if lista[i+1] - lista[i]>= 0 : semn_a = 1
        else: semn_a = 0

        if lista[i+2] - lista[i+1]> 0 : semn_b = 1
        else: semn_b = 0

        if semn_a != semn_b:
            if secventa_curenta == 0:
                lista_secventa_curenta.append(lista[i])
                lista_secventa_curenta.append(lista[i+1])
                secventa_curenta += 2

            lista_secventa_curenta.append(lista[i+2])
            secventa_curenta +=1
            if secventa_curenta > secventa_maxima:
                lista_secventa_maxima.clear()
                lista_secventa_maxima = lista_secventa_curenta [:]
                secventa_maxima = secventa_curenta

        else:
            secventa_curenta=0
            lista_secventa_curenta.clear()

    return lista_secventa_maxima

"""
# Exemplu de utilizare
lista = [2, 4, 7, 1, 3, 8, 9, 6]
secventa = gaseste_secventa_maxima(lista)
print("Secventa de lungime maxima este:", secventa)
"""

def  secventa_maxima_dif_2prime(lista: int,dimensiune_lista: int):

    """
    1 5 8 10 11 20
      + +  +  +  +
    """
    lista_secventa_maxima = []
    lista_secventa_curenta = []
    secventa_curenta = 0
    secventa_maxima = -1


    for i in range(dimensiune_lista-1):
        if este_prim(abs(lista[i]-lista[i+1])):
            if secventa_curenta == 0:
                lista_secventa_curenta.append(lista[i])
                secventa_curenta += 1

            lista_secventa_curenta.append(lista[i+1])
            secventa_curenta +=1

            if secventa_curenta > secventa_maxima:
                lista_secventa_maxima.clear()
                lista_secventa_maxima = lista_secventa_curenta [:]
                secventa_maxima = secventa_curenta

        else:
            secventa_curenta=0
            lista_secventa_curenta.clear()

    return lista_secventa_maxima


def citire_lista(lista :int, dimensiune_lista :int):
    print("Introdu numerele: ")
    for i in range(dimensiune_lista):
        #numar = input() asa se citeste de tipul sir de caractere
        numar = int(input())
        lista.append(numar)

    #print(f"Lista are {dimensiune_lista} elemente")
    print("Lista citita este: ",lista)


Flag = True
lista = []

assert secventa_maxima_dif_2prime([1,2,4,7,12],5)==[2,4,7,12]
assert secventa_maxima_dif_2prime([1,2,3,4,5],5)==[]
assert secventa_maxima_dif_2prime([0,0,1],3)==[]
assert secventa_maxima_dif_2prime([1,5,8,10,11,12],6)==[5,8,10]

assert secventa_maxima_semn_contrar([2, 4, 7, 1, 3, 8, 9, 6 ],8)==[4,7,1,3 ]
assert secventa_maxima_semn_contrar([0,0,1],3)==[]
assert secventa_maxima_semn_contrar([1,5,8,10,11,12],6)==[]
assert secventa_maxima_semn_contrar([1,4,3,5,2],5)==[1,4,3,5,2]

assert secventa_maxima_interval_0_10([-1,0,2,3,-2],5)==[0,2,3]
assert secventa_maxima_interval_0_10([11,1,2,3,10],5)==[1,2,3,10]
assert secventa_maxima_interval_0_10([1,2,3,4],4)==[1,2,3,4]
assert secventa_maxima_interval_0_10([11,-1],2)==[]

while Flag:
    print("1.Citeste lista")
    print("2.Gaseste secventa de lungime maxima in care oricare 2 elemente consecutive difera printr-un numar prim")
    print("3.Gaseste secventa de lungime maxima in care p=1 sau diferentele (x[j+1] - x[j]) si (x[j+2] - x[j+1])"
    "au semne contrare, pentru j=i..i+p-2")
    print("4.Gaseste secventa de lungime maxima care are elemente din intervalul [0,10]")
    print("5.Iesire")
    optiune = int(input("Alegeti optiunea: "))
    if optiune == 1:
        lista.clear()
        dimensiune_lista = int(input("Introdu numarul de numere din lista: "))
        citire_lista(lista, dimensiune_lista)
    elif optiune == 2:
        if len(lista) == 0:
            print("Prima data alegeti optiunea 1 pentru a citi lista")
        else:
            secv_max_dif_2prime=secventa_maxima_dif_2prime(lista,dimensiune_lista)
            if len(secv_max_dif_2prime) > 0:
                print(f"Secventa maxima are dimensiunea {len(secv_max_dif_2prime)} si este:", secv_max_dif_2prime)
            else:
                print("Lista nu respecta conditia")
    elif optiune == 3:
        if len(lista) == 0:
            print("Prima data alegeti optiunea 1 pentru a citi lista")
        else:
            secv_max_semn_contrar=secventa_maxima_semn_contrar(lista,dimensiune_lista)
            if len(secv_max_semn_contrar) <= 0:
                print("Nu exista secventa de semne contrare")
            else:
                print(f"Secventa maxima cu semn contrar are dimensiunea {len(secv_max_semn_contrar)} si este:",
                      secv_max_semn_contrar)
    elif optiune==4:
        if len(lista) == 0:
            print("Prima data alegeti optiunea 1 pentru a citi lista")
        else:
            secv_max_interval_0_10=secventa_maxima_interval_0_10(lista, dimensiune_lista)
            if len(secv_max_interval_0_10) > 0:
                print(f"Secventa maxima are dimensiunea {len(secv_max_interval_0_10)} si este:", secv_max_interval_0_10)
            else:
                print("Lista nu are elemente care corespund intervalului")
    elif optiune == 5:
        print("La revedere !")
        Flag=False

