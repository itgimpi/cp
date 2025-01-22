---
hide:
  - toc
---

# 3 - Retrovirus

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |

Mali Perica, haker i bioinformatičar, je uspešno izveo svoj najveći hakerski poduhvat do sada – uspešno je pristupio strogo čuvanoj bazi podataka ZBO-a (Zavoda za Biotehnološko Oružje), za koji se sumnja da je kreator mnogobrojnih virusa koji su izazivali pandemije u prošlosti. U ovoj bazi je našao, među brojnim tajnim projektima, i prototip nove vrste retrovirusa koji bi potencijalno mogao izazvati novu, neizlečivu, bolest.

Retrovirusi sve svoje genetske informacije pomoću kojih napadaju ćelije domaćina čuvaju u jednoj niti ribonukleinske kiseline (RNK). RNK nit se sastoji iz niza nukleotida, koji mogu biti adenin (A), uracil (U), citozin (C) ili guanin (G).

Perica je saznao da je prototip zapravo mutirana verzija poznatog retrovirusa – samim tim, očekuje se da postoje regioni (podnizovi) u kojima su ova dva virusa izrazito ”slična”. Sličnost dva regiona iste dužine ćemo definisati kao broj mesta na kojima im se nukleotidi poklapaju; na primer, sličnost regiona "ACAGU" sa regionom "AGAGA" je 3 (nukleotidi se poklapaju na prvoj, trećoj i četvrtoj poziciji u regionima). 

Perica je identifikovao potencijalne slične regione; na vama je da napišete program koji će izračunati vrednost sličnosti za sve njih.

## Opis ulaza
U prvom redu standardnog ulaza nalazi se prirodan broj $N$, koji predstavlja dužinu RNK niti starog i novog retrovirusa. U drugom i trećem redu nalaze se dva stringa, $RV_1$ i $RV_2$, koji predstavljaju strukturu ovih niti.

U četvrtom redu nalazi se prirodan broj $Q$, koji predstavlja broj parova regiona koje treba ispitati; zatim, u $Q$ narednih redova nalaze se opisi tih parova u obliku tri cela broja, $X$, $Y$ i $L$, odvojenih razmakom, redom; treba ispitati sličnost regiona dužine $L$ koji počinje na poziciji $X$ u RNK niti prvog retrovirusa sa regionom dužine $L$ koji počinje na poziciji $Y$ u RNK niti drugog.

## Opis izlaza
Na standardni izlaz potrebno je ispisati $Q$ celih brojeva, svaki u zasebnom redu, tako da se u $k$-tom redu nalazi sličnost $k$-tog para regiona iz ulaza.

## Primer 1
### Ulaz
```
7
AUGCAAG
GGAUGCG
2
1 3 4
6 1 2
```

### Izlaz
```
4
1
```

## Objašnjenje primera
Označimo sa $A[i..j]$ podstring stringa $A$ od $i$-tog do $j$-tog člana.

Prvi upit koji imamo je između regiona $RV_1[1..4]$="AUGC" i $RV_2[3..6]$="AUGC". Ova dva regiona se potpuno poklapaju, tako da je sličnost jednaka dužini regiona, tj. 4.

Drugi upit je između regiona $RV_1 [6..7]$="AG" i $RV_2 [1..2]$="GG". Ovi regioni se poklapaju samo na drugoj poziciji, tako da je traženi odgovor 1.

## Ograničenja
* $1\leq N\leq 1000$.
* $|RV_1| = |RV_2| = N$.
* $RV_1$ i $RV_2$ su sastavljeni samo od slova iz skupa {'A','U','C','G'}.
* $1\leq Q \leq 10^6$.
* $1\leq X,Y,L \leq N$.
* $X+L-1 \leq N$.
* $Y+L-1 \leq N$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim 50 poena važi $Q≤1000$.
* U test primerima vrednim 50 poena nema dodatnih ograničenja.



#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Nemanja Majski | Aleksandar Ivanović |

## Rešenje za $Q \le 1000$:
Za svai upit ćemo proći petljom kroz oba intervala i proveriti koliko se elemenata poklapa. Vremenska složenost ovog pristupa je $O(NQ)$.

## Glavno rešenje:

Zadatak ćemo rešiti tehnikom korenske dekompozicije (Square Root Decomposition). Neka je $D= \lceil \sqrt N \ \rceil$. Sada oba stringa delimo na $N-D+1$  blokova tako da svaki blok čini $D$ uzastopnih elemenata. Definišemo početak bloka kao najmanji indeks $i$ tako da element stringa na $i$-toj poziciji pripada bloku. Svi blokovi istog stringa imaju različite početke.

Nakon što smo podelili oba stringa u blokove prolazimo kroz sve parove blokova $(a,b)$, gde je $a$ blok napravljen iz prvog stringa, a $b$ blok napravljen od drugog stringa. Za svaki par ćemo izračunati sličnost blokova prolaskom kroz oba bloka. Vremenska složenost ove prekalkulacije je $O(N^2 \sqrt N)$.

Recimo da treba da ispitamo sličnost intervala $[L_1, R_1]$ iz prvog stringa i intervala $[L_2, R_2]$ iz drugog stringa. Razlikujemo dva slučaja:

 - $L_1+D-1>R_1$ - U ovom slučaju možemo da prođemo petljom kroz oba intervala i izračunamo sličnost.
 - $L_1+D-1\le R_1$ - Neka je $a$ blok od prvog stringa čiji je početak $L_1$, a $b$ blok od drugog stringa čiji je početak $L_2$. Njihovu sličnost znamo zbog ranije prekalkulacije i pristupamo joj u $O(1)$ vremenu. Da dobijemo sličnost celog intervala rezultat sabiramo sa slišnošću intervala $[L_1+D,R_1]$ i $[L_2+D,R_2]$, za čije računanje koristimo isti postupak.

Vremenska složenost ovakvog pristupa je $O(\sqrt N)$ po upitu pošto u prvom koraku proverimo najviše $\sqrt N$ indeksa, a drugi korak se izvrši najviše $O(\sqrt N)$ puta. 

Ukupna vremenska složenost je $O(N^2\sqrt N + Q\sqrt N$) , a memorijska $O(N^2)$.

Napomena: Postoji i slično rešenje koje umesto korenske dekompozicije koristi strukturu *Sparse Table* da napravi blokove veličine $1, 2, 4, 8 ...$ Vremenska složenost tog rešenja je $O(N^2logN + Qlog N)$, a memorijska $O(N^2 \log N)$.

``` cpp title="03_retrovirus.cpp" linenums="1"
/*
 Author: Petar 'PetarV' Velickovic
 Task: Retrovirus
*/

#include <stdio.h>

#define MAX_N 1001

int n, q;
char A[MAX_N], B[MAX_N];

int dp[MAX_N][MAX_N];

int x, y, l;

int main()
{
    scanf("%d", &n);
    scanf("%s%s", A, B);
    
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=n;j++)
        {
            dp[i][j] = dp[i-1][j-1] + (A[i-1] == B[j-1]);
        }
    }
    
    scanf("%d", &q);
    
    while (q--)
    {
        scanf("%d%d%d", &x, &y, &l);
        printf("%d\n", dp[x+l-1][y+l-1] - dp[x-1][y-1]);
    }
    
    return 0;
}
```
