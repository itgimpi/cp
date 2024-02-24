
# Generišu se svi moguci kandidati za traženi broj X. 
# Prvo se na sve moguce nacine bira prefiks zajednickih cifara brojeva N i X, tj.
# koliko ce se vodecih cifara (izmedju 0 i 18) broja X podudarati s brojem N. Za svaki taj odabir,
# na sve moguce nacine biramo iducu cifru broja X (izmedju 0 i 9) koja se razlikuje od odgovarajuce cifre broja N. 
# Ovisno o odabranoj cifri, tj. o tome je li ona veca ili manja od odgovarajuce cifre broja N, 
# znamo hoce li promatrani kandidat X biti manji ili veci od N.
# Kako odrediti ostale cifre broja X? Ako je X < N, preostali deo broja X treba biti što veci da bi se maksimalno približili broju N, 
# pa stavljamo što vece cifre (99...) dok ne dosegnemo zbroj cifara K, nakon cega broj X dopunimo nulama. 
# S druge strane, ako je X > N, preostali deo broja X treba biti što manji da bi se približili broju N, 
# X se do kraja dopunjuje nulama i onda povecavaju najmanje znacajne cifre (zdesna nalevo) dok je zbir cifara manji od K.
# Posle dopune nulama, traži prvu cifru s desne strane koja je manja od 9 i povecava se za jedan, dok zbir cifara ne postane K.
# Na kraju od svih uspešno generisanih kandidata za X se bira najbliži broju N.

import sys
n = int(input())
k = int(input())

s = [int(z) for z in str(n)]
if sum(s) == k:
    print(n)
    sys.exit(0)
# Broj N se dopuni vodecim nulama do 19 cifara, što je maksimum, s obzirom na ogranicenje K ~ 170. 
M = 19
while len(s) < M:
    s = [0] + s
naj = float('inf')

for m in range(M):
    for z in range(10):
        if z == s[m]:
            continue
        preostalo = M - m - 1
        broj = s[:m] + [z] + [0 for i in range(preostalo)]
        if sum(broj) > k or sum(broj) + 9 * preostalo < k:
            continue
        if z > s[m]:
            while sum(broj) < k:
                for i in range(-1, -M, -1):
                    if broj[i] < 9:
                        broj[i] += 1
                        break
        else:
            while sum(broj) < k:
                for i in range(m + 1, M):
                    if broj[i] < 9:
                        broj[i] += 1
                        break
        x = int(''.join(map(str, broj)))
        if abs(x - n) < abs(naj - n) or\
                abs(x - n) == abs(naj - n) and x < naj:
            naj = x
print(naj)