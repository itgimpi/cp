---
hide:
  - toc
---

# B2 - Komande1D

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Danas je loše vreme napolju i student Srba je odlučio da neće izlaziti iz kuće, pa tako neće otići ni na fakultet. Ipak, onda bi izgubio bitne bodove na predavanjima, pa je smislio novi način kako će prisustvovati njima. Napravio je robota koji će otići umesto njega, čak i zapisivati ono što priča profesor.

Selo u kome živi Srba se može zamisliti kao velika brojevna prava. Srbina kuća se nalazi na koordinati $0$, dok se njegov fakultet nalazi na koordinati $X$.

Robotu, koji je mali Srba napravio, se mogu zadati sledeće komande:

*  `L` – Idi levo (ukoliko je bio na koordinati $x$ pomeriće se na $x-1$);
* `R` – Idi desno (ukoliko je bio na koordinati $x$ pomeriće se na $x+1$).

Student Srba je robotu već zadao $N$ komandi. Međutim, pošto on odavno nije išao na fakultet, zaboravio je tačan put do njega, a robot je završio u pivnici. Sada robotu treba promeniti komande, i Srba vas moli da mu pomognete. Pošto se već dovoljno namučio praveći robota i pišući ove komande, on želi samo da **obriše tačno $K$ komandi**. Nađite bilo kojih $K$ komandi koje Srba može da obriše tako da na kraju stigne u koordinatu $X$ ili ispišite $-1$ ukoliko to nije moguće.

## Ulaz
Svaki test primer se sastoji od $3$ posebna potprimera.

Prvi red svakog potprimera sadrži $3$ broja odvojena po jednim znakom razmaka – $N$, $X$ i $K$ koji redom predstavljaju broj komandi koje je Srba zadao robotu, koordinatu fakulteta i broj komadi koje Srba treba da izbriše. Drugi red potprimera sadrži $N$ karaktera koji predstavljaju komande koje je Srba zadao robotu.

## Izlaz
Za svaki potprimer u posebnom redu ispisati po $K$ brojeva odvojenih po jednim znakom razmaka, koji predstavljaju indekse komandi koje treba obrisati (komande su indeksirane od $1$). Ukoliko ne postoji $K$ komandi koje se mogu obrisati i stići u traženu koordinatu, ispisati $-1$. Ukoliko postoji više mogućih rešenja, ispisati bilo koje.

## Primer 1
### Ulaz
```
5 -2 3
RLLLL
4 3 2
RRRL
6 2 2
RRLRLR
```

### Izlaz
```
1 2 5
-1
6 5
```

## Objašnjenje primera
U prvom potprimeru je moguće obrisati $1.$ $2.$ i $5.$ komandu, i tako će ostati samo `LL` što će robota odvesti na koordinatu fakulteta. Druga rešenja bi se takođe priznala, kao npr. `1 2 3`. U drugom potprimeru nije moguće obrisati nijedne dve komande tako da robot na kraju stigne na koordinatu $3$, pa zato treba ispisati $-1$.

## Ograničenja

* $1 \leq N \leq 10^5$.
* $0 \leq K \leq N$.
* $-10^9 \leq X \leq 10^9$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim $40$ poena važi $N\leq 1000$.
* U test primerima vrednim $60$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | Milica Mićić | Boris Grubić |

## Rešenje za $N \leq 1000$
Možemo, na primer, fiksirati koliko desnih komandi ćemo obrisati. Onda znamo i koliko levih komandi moramo obrisati ($l = K-d$, gde je $d$ broj desnih komandi koje obrišemo, slično za $l$). Uvek možemo obrisati prvih $l$ levih komandi i prvih $d$ desnih komandi (naravno, moramo paziti da ih imamo dovoljno). Nakon toga, možemo proveriti da li dati niz komandi zaista dovodi do koordinate $X$. Vremenska složenost: $O(N\cdot K)$, memorijska složenost: $O(N)$.

## Glavno rešenje
Za svaki od tri potprimera pojedinačno  u prvom prolazu kroz komande je potrebno odrediti broj levih i desnih komandi. Tako određujemo koordinatu pivnice (neka bude označena sa $P$) kao razliku broja desnih i levih kretanja. Neophodno je obrisati $X-P$ pomeranja nalevo u slučaju da je $X>P$ ili $P-X$ pomeranja nadesno, u  suprotnom. U tom trenutku smo već doveli robota do pozicije fakulteta, ali pošto moramo obrisati tačno $K$ komandi, možda nam preostane još komandi koje treba obrisati. Kako se ne bi poremetila pozicija na kojoj će se robot nalaziti potrebno je obrisati jednaku količinu desnih i levih koraka preostalim brisanjima.  Doći od pozicije pivnice do mesta fakulteta je moguće jedino ako su zadovoljeni uslovi da je $K-|P-X|\ge 0$,  da je $K-|P-X|$ deljiv sa $2$ (da bismo mogli da podelimo preostala brisanja ravnomerno na leve i desne komande), a potrebno je i imati dovoljan broj levih i desnih komandi od preostalih komandi kako bismo ih obrisali. Ako su svi ovi uslovi zadovoljeni dovoljno je još samo proći ponovo kroz niz komandi i ispisati mesta gde se prvo nalazi određeni broj komandi nalevo i nadesno. Vremenska složenost: $O(N)$, memorijska složenost: $O(N)$.

``` cpp title="02_komande1d.cpp" linenums="1"
#include <stdio.h>

char s[500555];

int main() {

    int n,x,k,i,R,L,P,oL,oR,tt;

    for(tt=0; tt<3; tt++) {
        scanf("%d%d%d", &n, &x, &k);
        scanf("%s", &s);

        R = 0; L = 0;
        for(i=0; i<n; i++) {
            if (s[i] == 'R') R++;
            else L++;
        }

        P = R - L;
        oL = 0; oR = 0;
        if (P < x) {
            oL = x - P;
            k -= oL;
        } else {
            oR = P - x;
            k -= oR;
        }

        if (k < 0 || k%2 == 1) {
            printf("-1\n");
            continue;
        }

        oL += k/2;
        oR += k/2;

        if (oL > L || oR > R) {
            printf("-1\n");
            continue;
        }

        for(i=0; i<n; i++) {
            if (s[i] == 'R' && oR > 0) {
                printf("%d ", i+1);
                oR--;
            }

            if (s[i] == 'L' && oL > 0) {
                printf("%d ", i+1);
                oL--;
            }
        }
    }

    return 0;
}

```
