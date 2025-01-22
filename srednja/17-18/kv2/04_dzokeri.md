---
hide:
  - toc
---

# 4 - Džokeri

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 5000ms | 256MB |

Mali Perica je napravio početničku grešku: šifrirao je celokupan sadržaj svog hard diska koristeći neki string (sastavljen od malih slova engleske abecede) kao ključ, koji je zatim izgubio! Uspeo je, doduše, da pronađe dva stringa, $A$ i $B$, koja su ”slični” traženom. Perica sada želi da konstruiše najverovatniju moguću šifru koristeći ova dva stringa.

Peričin cilj je da učini da ova dva stringa budu potpuno isti. Dozvoljen mu je samo jedan tip poteza: ubacivanje određenog broja ”džoker” karaktera između dva susedna karaktera u jednom od ova dva stringa. Na primer, u jednom potezu od stringa `abcdef` možemo napraviti string `abc???def`, ili `abcdef??` (tj. dozvoljeno je ubacivati džokere i na početak ili kraj stringa). Džoker karakteri se podudaraju sa bilo kojim karakterom!

Naravno, ovo bi bio jednostavan zadatak da ne postoje dodatni uslovi: kada se stringovi $A$ i $B$ izjednače na ovaj način, obračunava se ”kvalitet” rešenja, na sledeći način:
- Za svaku poziciju na kojoj ne postoji džoker ni u stringu $A$ ni u stringu $B$, dodaje se 1 poen.
- Za svaki potez, oduzima se $X$ poena.
- Za svaki džoker, oduzima se $Y$ poena.

Vaš zadatak je da odredite **maksimalan kvalitet** koji je moguće postići na ovaj način.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se četiri cela broja, $N$, $M$, $X$ i $Y$, koji predstavljaju dužine stringova $A$ i $B$, cenu jednog poteza, i cenu jednog džokera, redom.
U drugom redu standardnog ulaza nalazi se string $A$, sastavljen od $N$ malih slova engleske abecede.
U trećem redu standardnog ulaza nalazi se string $B$, sastavljen od $M$ malih slova engleske abecede.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza potrebno je ispisati jedan ceo broj, koji predstavlja maksimalan kvalitet šifre koji je moguće postići koristeći stringove $A$ i $B$ (ovaj broj može biti **negativan**).

## Primer 1
### Ulaz
```
5 4 1 1
abcef
acde
```

### Izlaz
```
-3
```

## Primer 2
### Ulaz
```
7 7 5 5
abcdefj
befghij
```

### Izlaz
```
-41
```

## Objašnjenje primera
U prvom primeru, možemo ubaciti jedan džoker između karaktera `c` i `e` u stringu $A$, jedan džoker između karaktera `a` i `c` u stringu $B$, i jedan džoker na kraj stringa $B$. Ovim dobijamo ”iste” stringove:

`abc?ef`

`a?cde?`

Ukupni kvalitet ovog rešenja je $3 - 1 \times 3 - 1 \times 3 = -3$ (tri podudaranja bez džokera, tri poteza, tri džokera). Nije moguće postići rešenje sa većim kvalitetom.

U drugom primeru, jedno od mogućih optimalnih rešenja će uraditi sledeće poteze:
- Ubaciti jedan džoker na početak stringa $B$;
- Ubaciti dva džokera između karaktera `b` i `e` u stringu $B$;
- Ubaciti tri džokera između karaktera `f` i `j` u stringu $A$.

Ovim dobijamo ”iste” stringove:

`abcdef???j`

`?b??efghij`

Ukupni kvalitet ovog rešenja je $4 - 5 \times 3 - 5 \times 6 = -41$ (četiri podudaranja bez džokera, tri poteza, šest džokera). Nije moguće postići rešenje sa većim kvalitetom.

## Ograničenja

* $1 \leq N, M \leq 1000$.
* $0 \leq X, Y \leq 10^8$.
* Stringovi $A$ i $B$ će sadržati samo mala slova engleske abecede.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 20 poena važiće $N, M \leq 100$, $X, Y \leq 1000$.
* U test primerima vrednim 10 poena važiće $X = Y = 0$.
* U test primerima vrednim 10 poena važiće $X = 0$.
* U test primerima vrednim 20 poena važiće $X, Y \leq 1000$.
* U test primerima vrednim 40 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Slobodan Mitrović | Slobodan Mitrović |

Primetimo najpre da je zadatak za slučaj $x = y = 0$ jednak problemu Najduži Zajedniči Podniz (engl. *Longest Common Subsequence*; skr. *LCS*). Uz vrlo jednostavnu izmenu, algoritam za *LCS* može takođe rešiti varijantu ovog zadatka za slučaj $x = 0$. Dakle, prava težina zadatka leži u slučaju kada $x \neq 0$. U nastavku ćemo se najpre ukratko podsetiti algoritma za *LCS* i pokazati kako se jednostavnom izmenom može iskoristiti da reši ovaj zadatak za slučaj $x = 0$. Potom ćemo opisati kako se taj algoritam može proširiti tako da reši ovaj zadatak u opštem slučaju, tj. čak i kada $x \neq 0$.

Standardni *LCS* algoritam definiše niz $dp[i][j]$ koji predstavlja *LCS* za stringove $A^i$ i $B^j$, gde $A^i$ ($B^j$) označava sufiks stringa $A$ ($B$) od pozicije $i$ ($j$). Tada, $dp[i][j]$ definišemo kao: $dp[i][j] = \max\{dp[i + 1][j], dp[i][j + 1], eq_{i, j}\}$, gde u slučaju da $A[i] = B[j]$ imamo $eq_{i, j} = dp[i + 1][j + 1] + 1$, a inače $eq_{i, j} = -\infty$.

Da bismo rešili ovaj zadatak u slučaju kada $x = 0$, dovoljno je da definišemo $dp[i][j]$ na samo malo drugačiji način, naime $dp[i][j] = \max\{dp[i + 1][j] - y, dp[i][j + 1] - y, eq_{i, j}\}$, gde je $eq_{i, j}$ definisano kao i pre.

Posmatrajmo sada slučaj $x \neq 0$. Prvo, u definiciji $dp[i][j]$ imamo, između ostalog, vrednost $dp[i + 1][j] - y$ koja se može intepretirati na sledeći način: ubacimo džoker ispod karaktera $A[i]$, što ima cenu $y$, i pronađimo *LCS* za $A^{i + 1}$ i $B^j$. Kada $x \neq 0$, treba li cena i dalje da bude samo $y$ ili ipak treba da bude $x + y$? To zavisi od toga da li je i ispod $A[i - 1]$ bio džoker ili nije. Ako je ispod bio džoker, onda je cena samo $y$ (jer ne počinjemo novu operaciju), a ako nije bio džoker onda je cena $x + y$ (jer počinjemo novu operaciju). Sada je jasno kako proširiti algoritam za *LCS* da reši ovaj zadatak -- pored indeksa $i$ i $j$, trebalo bi pamtiti još dva indikatora (tj. dve promennjive gde svaka ima vrednost $0$ ili $1$) koje označavaju da li je ispod $A[i - 1]$, tj. iznad $B[j - 1]$, bio umetnut džoker ili nije.

## Smernice za algoritam
Recimo da želimo da izračunamo $dp[i][j][ind1][ind2]$, gde su $ind1$ i $ind2$ kao što je opisano iznad. U smernicama datim ispod, pretpostavljamo da su stringovi $A$ i $B$ indeksirani od $0$. Radi jednostavnosti, neka $ret$ predstavlja vrednost koju želimo da izračunamo. Tada imamo

```
Ako ako i == length(A) i j == length(B):
  ret = 0
Inače, ako je i == length(A):
  ret = -x * (1 - ind2) - y * (length(B) - j)
Inače, ako je j == length(B):
  ret = -x * (1 - ind1) - y * (length(A) - i)
Inače:
  Ako je A[i] == B[j]:
    ret = max{dp[i][j + 1][0][1] - x * (1 - ind2) - y, dp[i + 1][j][1][0] - x * (1 - ind1) - y, dp[i + 1][j + 1][0][0] + 1}
  Inače:
    ret = max{dp[i][j + 1][0][1] - x * (1 - ind2) - y, dp[i + 1][j][1][0] - x * (1 - ind1) - y}
```

``` cpp title="04_dzokeri.cpp" linenums="1"
/*
 Author: Petar 'PetarV' Velickovic
 Task: Dzokeri 
*/

#include <iostream>
#include <string>

#define MAX_N 1005
#define NEGINF -99999999999999999LL

using namespace std;

typedef long long lld;

int n, m;
lld x, y;
string A, B;

lld dn[MAX_N][MAX_N];
lld rt[MAX_N][MAX_N];
lld md[MAX_N][MAX_N];

int main(int argc, char **argv)
{
    cin >> n >> m >> x >> y;
    cin >> A >> B;
    
    // Simple base case: zero-cost to begin with
    dn[0][0] = rt[0][0] = md[0][0] = 0LL;
    
    // Base case: extending an initial wildcard-gap downwards only
    for (int i=1;i<=n;i++)
    {
        dn[i][0] = md[i][0] = -x - i * y;
        rt[i][0] = NEGINF;
    }

    // Base case: extending an initial wildcard-gap rightwards only
    for (int j=1;j<=m;j++)
    {
        rt[0][j] = md[0][j] = -x - j * y;
        dn[0][j] = NEGINF;
    }

    // Recurrence relation
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            dn[i][j] = max(dn[i - 1][j] - y, md[i - 1][j] - x - y);
            rt[i][j] = max(rt[i][j - 1] - y, md[i][j - 1] - x - y);
            md[i][j] = max(dn[i][j], rt[i][j]);
            if (A[i - 1] == B[j - 1])
            {
                md[i][j] = max(md[i][j], md[i - 1][j - 1] + 1);
            }
        }
    }

    cout << md[n][m] << endl;
    return 0;
}

```
