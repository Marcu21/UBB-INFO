def merge_sort(lista, key = lambda x:x, cmp = lambda x,y:x <= y, reverse = False):
    if reverse == True:
        cmp = lambda x,y:x >= y
    if len(lista) > 1:
        mij = len(lista) // 2
        stanga = lista[:mij]
        dreapta = lista[mij:]
        merge_sort(stanga, key = key, cmp = cmp, reverse= reverse)
        merge_sort(dreapta, key = key, cmp = cmp, reverse= reverse)
        i = 0
        j = 0
        k = 0
        while i < len(stanga) and j < len(dreapta):
            if cmp(key(stanga[i]),key(dreapta[j])):
                lista[k] = stanga[i]
                i += 1
                k += 1
            else:
                lista[k] = dreapta[j]
                j += 1
                k += 1
        while i < len(stanga):
            lista[k] = stanga[i]
            i += 1
            k += 1
        while j < len(dreapta):
            lista[k] = dreapta[j]
            j += 1
            k += 1
    return lista



def lista_maxima(lista, key):
    maxim = key(lista[0])
    for el in lista:
        if key(el) > maxim:
            maxim = key(el)
    return maxim

def lista_minima(lista, key):
    minim = key(lista[0])
    for el in lista:
        if key(el) < minim:
            minim = key(el)
    return minim

def bingo_sort(lista, key = lambda x:x, cmp = lambda x,y:x < y, reverse = False):
    if reverse == True:
        cmp = lambda x,y:x > y
        bingo = lista_maxima(lista, key)
        maxx = lista_minima(lista, key)
        bingo_urm = maxx
        poz_urm = 0
    else:
        bingo = lista_minima(lista, key)
        maxx = lista_maxima(lista, key)
        bingo_urm = maxx
        poz_urm = 0
    while cmp(bingo,bingo_urm):

        start = poz_urm
        for i in range(start, len(lista)):
            if key(lista[i]) == bingo:
                lista[i], lista[poz_urm] = lista[poz_urm], lista[i]
                poz_urm += 1

            elif cmp(key(lista[i]),bingo_urm):
                bingo_urm = key(lista[i])
        bingo = bingo_urm
        bingo_urm = maxx
    return lista