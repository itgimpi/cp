---
hide:
  - toc
---

# 1 - Mala matrica

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Data je matrica $A$ koja ima dve vrste i tri kolone (tj. dimenzija $2\times 3$). Elementi matrice su celi brojevi koji su veći od nule ili jednaki nuli. Zameniti sve elemente matrice koji su jednaki nuli pozitivnim celim brojevima (prirodnim brojevima), tako da zbir svih elemenata u prve dve kolone bude jednak zbiru elemenata u poslednje dve kolone. Ako ima više mogućih načina da se to izvede, odrediti onu zamenu kod koje je zbir svih elemenata matrice minimalan. Ako postoji više različitih matrica sa minimalnim zbirom, odštampati bilo koju.

## Opis ulaza
U dva reda standardnog ulaza se nalaze po tri cela broja koji predstavljaju dve vrste date matrice.

## Opis izlaza
Ako ne postoji matrica sa traženim osobinama ispisati $-1$ u prvom redu standardnog izlaza. Ako postoji matrica sa traženim osobinama, ispisati elemente te matrice, u svakom od dva reda po jednu vrstu matrice.

## Primer 1
### Ulaz
```
1 5 6
0 5 2
```
### Izlaz
```
1 5 6
7 5 2
```

## Primer 2
### Ulaz
```
3 0 2
1 5 0
```

### Izlaz
```
3 1 2
1 5 2
```

## Objašnjenje primera
U prvom primeru, samo je element u preseku druge vrste i prve kolone jednak nuli. Ako njega izjednačimo sa $7$, zbirovi podmatrica će biti jednaki. Ako zamenimo bilo kojim drugim brojem, zbirovi podmatrica će se razlikovati.

## Ograničenja i podzadaci

* Elementi ulazne matrice imaju vrednosti između $0$ i $10^9$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede $50$ poena, elementi matrice nisu veći od $10$.
* U test primerima koji vrede $20$ poena, tačno jedan element matrice je jednak nuli.
* U test primerima koji vrede $30$ poena nema dodatnih ograničenja. 

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Dragan Urošević | Dragan Urošević | Aleksa Plavšić i Ivan Stošić |

Primetimo da ako su zbirovi podmatrice koju čine prve dve kolone i podmatrice koju čine poslednje dve kolone jednaki, onda su jednaki zbir elemenata u prvoj koloni i zbir elemenata u trećoj koloni. Prema tome, proveravaćemo da li možemo da podesimo vrednosti nula-elemenata tako da zbir prve i zbir treće kolone budu jednaki. Elementi koji se nalaze u drugoj (srednjoj) koloni ne utiču na zbir i zbog toga je dovoljno one koji su jednaki nuli postaviti na jedan.

Neka je $nz$ ukupan broj nula u prvoj i trećoj koloni.

Ako je $nz=0$, onda u tim dvema kolonama nema niti jedan element koji se može promeniti. Ako su zbirovi tih kolona jednaki, onda problem ima rešenje i to je matrica u kojoj je samo srednja kolona ažurirana tako što su elementi koji su jednaki nuli zamenjeni jedinicom.

Ako je $nz=1$, onda je samo jedan element jednak nuli i on može promeniti vrednost. Njegova vrednost se odredi tako da zbirovi prve i treće kolone budu jednaki. Ako je ta vrednost veća od nule, onda problem ima rešenje.

Ako je $nz=3$, onda je samo jedan od $4$ elementa u prvoj i trećoj koloni različit od nule. Neka je $k$ redni broj kolone u kojoj se nalazi taj ne-nula element. Jedno od rešenja se dobija tako što se drugi element u koloni  $k$ izjednači sa jedan, a elementi u koloni $4-k$ (kolone numerisane brojevima $1$, $2$ i $3$) izjednače sa odgovarajućim elementima (ista vrsta) u koloni  $k$.

Ako je $nz=4$, onda su sva četiri elementa jednaki nuli i treba ih promeniti u jedan.

Ako je $nz=2$, imamo dva podslučaja:

Ne-nula elementi su u istoj koloni (neka je to kolona $k$). Tada elemente u koloni $4-k$ treba izjednačiti sa odgovarajućim u koloni $k$ (to je jedno od mogućih rešenja).

Ne-nula elementi su u različitim kolonama. Neka su vrednosti tih elemenata $a$ i $b$ (obeleženi tako da je $a\leq b$). Jedno od mogućih rešenja se dobija tako što se nula-element u koloni u kojoj je $b$ izjednači sa $1$, a nula-element u koloni u kojoj je $a$ izjednači sa $b-a+1$. Lako se proverava da ovo rešenje zadovoljava sve uslove zadatka.




 


``` cpp title="01_mala_matrica.cpp" linenums="1"
# include <stdio.h>

long long a[2][3];

int resi4() {
  a[0][0] = a[0][2] = a[1][0] = a[1][2] = 1;
  return 1;
}

int resi0() {
  if (a[0][0] + a[1][0] == a[0][2] + a[1][2]) return 1;
  return 0;
}

int resi1() {
  int i, j;
  i = 0; j = 0;
  while (i < 2) {
    if (a[i][j] == 0) break;
    j += 2;
    if (j > 2) {
      i++; j = 0;
    }
  }
  if (i >= 2) return 0;
  a[i][j] = a[i][2-j] + a[1-i][2-j] - a[1-i][j];
  if (a[i][j] <= 0) return 0; else return 1;
}

int resi3() {
  int i, j;
  i = 0; j = 0;
  while (i < 2) {
    if (a[i][j] != 0) break;
    j += 2;
    if (j > 2) {
      i++; j = 0;
    }
  }
  if (i >= 2) return 0;
  a[i][2-j] = a[i][j];
  a[1-i][j] = a[1-i][2-j] = 1;
  return 1;
}

int resi2() {
  int i1, j1, i2, j2;
  if ((a[0][0] != 0) && (a[1][0] != 0)) {
    a[0][2] = a[0][0];
    a[1][2] = a[1][0];
    return 1;
  }
  if ((a[0][2] != 0) && (a[1][2] != 0)) {
    a[0][0] = a[0][2];
    a[1][0] = a[1][2];
    return 1;
  }
  if (a[0][0] != 0) {
    i1 = j1 = 0;
  } else {
    i1 = 1; j1 = 0;
  }
  if (a[0][2] != 0) {
    i2 = 0; j2 = 2;
  } else {
    i2 = 1; j2 = 2;
  }
  if (a[i1][j1] >= a[i2][j2]) {
    a[1-i1][j1] = 1;
    a[1-i2][j2] = 1 + a[i1][j1] - a[i2][j2];
    return 1;
  } else {
    a[1-i2][j2] = 1;
    a[1-i1][j1] = 1 + a[i2][j2] - a[i1][j1];
    return 1;
  } 
  return 0;
}

main() {
  int nz;
  int i, j, k;
  for (i = 0; i < 2; i++)
    for (j = 0; j <= 2; j++)
      scanf("%lld", &a[i][j]);
  if (a[0][1] == 0) a[0][1] = 1;
  if (a[1][1] == 0) a[1][1] = 1;
  nz = 0;
  if (a[0][0] == 0) nz++;
  if (a[0][2] == 0) nz++;
  if (a[1][0] == 0) nz++;
  if (a[1][2] == 0) nz++;
  switch (nz) {
    case 0:
      k = resi0();
      break;
    case 1:
      k = resi1();
      break;
    case 2:
      k = resi2();
      break;
    case 3:
      k = resi3();
      break;
    case 4:
      k = resi4();
      break;
  }
  if (k == 1) {
    for (i = 0; i < 2; i++) {
      for (j = 0; j < 3; j++) 
        printf("%lld ", a[i][j]);
      printf("\n");
    }
  } else {
    printf("-1\n");
  }
  return 0;
}


```
