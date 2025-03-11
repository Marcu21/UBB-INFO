def este_prim(nr):
    if nr<2:
        return False
    for i in range(2,nr//2+1):
        if nr%i==0:
            return False
    return True
k=0
n=int(input("n="))
for p1 in range(2,n-1):
    p2=n-p1
    if este_prim(p1) and este_prim(p2):
        k=1
        pp1=p1
        pp2=p2
if(k==1): print(pp1,pp2)
else: print("nu exista")
5