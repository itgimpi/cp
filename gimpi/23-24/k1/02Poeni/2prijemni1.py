n = int(input())

poeni = 0

for i in range(n): # za svaki unos
    pokusaj = input()
    resenje = input()

    poz1 = -1
    poz2 = -1

    for j in range(5): # odredi poziciju pokusaja kandidata od 0 do 4
        if pokusaj[j] == 'x':
            poz1 = j

    for j in range(5): # odredi poziciju resenja
        if resenje[j] == 'x':
            poz2 = j

    if poz1 == poz2: # tacno!
        poeni += 4
    elif poz1 != -1 and poz1 != poz2: # ne
        poeni -= 1
    #else: # bez pokusaja
        #poeni += 0

najvise = n * 4
najmanje = n * -1

print(poeni)
print(najvise)
print(najmanje)
