---
hide:
  - toc
---

# 4 - Carina

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 16MB |

Mali Perica, igrajući igru ”Flappy Bird”, je primetio da ptica uvek ujednačeno skakuće, bez obzira na to u kojoj je fazi padanja kao i da se nikad ne umara. Ovo je Perici bilo jako neprirodno, tako da je rešio da napravi novu verziju igrice, TheBird™. Međutim, komisija ga je odmah prijavila policiji za krađu autorskih prava, tako da su mu mogućnosti za distribuciju igrice u inostranstvo sada jako ograničene.

Perica je napravio određen broj kopija igrice, i namerava da ih prenese od firme (mesto A) do distributera za strano tržište (mesto B). Da bi to uradio, na raspolaganju mu je jedan šleper koji može da prenese ograničen broj igrica odjednom. Na putu od mesta A do mesta B nalazi se određen broj kontrolnih punktova carine: ukoliko Perica prevozi bar jednu kopiju igrice u momentu ulaska na punkt, mora pokloniti carinicima jednu kopiju kao mito. Na punktu se kopije mogu istovariti, pa ponovo pokupiti kasnije. Perica takođe ne želi da se vraća nazad u mesto A više od $X$ puta (da ne bi ispao sumnjiv saobraćajcima).

Pericu interesuje koliki je najveći broj kopija igrice TheBird™ koji se mogu dopremiti do mesta B.

## Ulaz
U prvom i jedinom redu standardnog ulaza nalaze se četiri cela broja, $N$, $C$, $L$ i $X$, koji predstavljaju broj kopija igrice, kapacitet šlepera, broj punktova i maksimalan broj vraćanja u mesto A, redom.

## Izlaz
U prvom i jedinom redu standardnog izlaza ispisati najveći broj kopija igrice koje se mogu dopremiti.

## Primer 1
### Ulaz
```
4000 1000 1000 1
```

### Izlaz
```
500
```

## Objašnjenje primera
Perica može najpre da napuni šleper sa $1000$ igrica, da ga doveze do $500$-tog punkta, i da tu istovari $500$ kopija koje su mu ostale u šleperu. Zatim se vraća u mesto A i na isti način dovozi još $500$ kopija na $500$-ti punkt. Tada ponovo puni šleper sa prethodno ostavljenih $500$ kopija, i tako dolazi do mesta B, sa $500$ dopremljenih kopija. Nije moguće napraviti strategiju koja donosi više kopija do mesta B.

## Ograničenja

* $1 \leq N, C, L \leq 10^{18}$.
* $0 \leq X \leq 10^6$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim $40$ poena važi $N, C, L \leq 10^6$.
* U test primerima vrednim 60 poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Petar Veličković | Dušan Zdravković |

Zadatak Carina spada u probleme srednje težine na drugim Kvalifikacijama, i odlikuje se izuzetno kratkim rešenjem; ideja je da rešavaoci mnogo više vremena potroše na smišljanje pravilnog rešenja nego na samu implementaciju.

Pre svega, primetimo da je jedini efekat broja $X$ ograničavanje koliko igrica možemo izneti iz mesta A; ovo je ekvivalentno tome da je $N=\min⁡(N, C\cdot (X+1))$. Pošto je broj $X$ ograničen sa $10^6$, ovo samo po sebi treba da sugeriše da je traženi algoritam reda veličine $O(X)$; međutim da bismo došli do ovog algoritma neophodno je najpre napraviti nekoliko zapažanja.

Najpre primetimo da je jedna od optimalnih strategija vrlo jednostavna: svaki put punimo šleper do vrha, i donosimo igrice na prvi sledeći punkt, gde gubimo jednu i istovaramo ostale; ovo ponavljamo dok ne prenesemo sve igrice na prvi punkt. Ovim smo izgubili $\lceil \frac{N}{C}\rceil$ igrica, tj. najmanji ceo broj veći ili jednak $\frac{N}{C}$. Ako ovako nastavimo, preneli smo maksimalan moguć broj igrica u mesto B; ovo možemo naivno predstaviti sledećim C++ kodom:

```cpp
long long carina(long long n, long long c, long long l)
{
for (long long i=0;i<l;i++)
{
long long lost = n/c;
if (c * lost != n) lost++;
n -= lost;
}
return n;
}
```

Ovo rešenje je očigledno složenosti $O(L)$, i donosi oko $50$ bodova. Zapažanje koje nam pomaže da dođemo do bržeg rešenja je da primetimo da se više koraka mogu ”spakovati” u jedan, tj. često će postojati više od jednog koraka tokom ove strategije gde ćemo izgubiti isti broj igrica; ako efikasno odredimo broj koraka koji smemo napraviti tako da u svakom koraku gubimo isti broj igrica, onda možemo šleper odmah nositi do te pozicije; tj. ne moramo prelaziti jedan po jedan punkt.

Da bismo odredili ovu poziciju, potrebno je posmatrati ostatak pri deljenju $N$ sa $C$.  Nazovimo ovaj ostatak $R$. Neophodan broj povrataka na punkt sa kojeg smo krenuli trenutni korak se smanjuje za bar jedan kada se ovaj ostatak izgubi; kako u svakom jediničnom koraku gubimo $\lceil \frac{N}{C}\rceil$ igrica, broj potrebnih koraka da se ovo desi je $k = \lceil \frac{R}{\lceil \frac{N}{C} \rceil} \rceil$. Ukoliko je $R=0$, onda možemo uzeti $R=C$.

Nakon što odredimo broj potrebnih koraka, možemo odmah otići sa punkta $x$ na punkt $x+k$ i usput oduzeti $k\cdot \lceil \frac{N}{C} \rceil$ od $N$, naravno vodeći računa o tome da li smo prekoračili mesto B.

Primetimo da ovo rešenje u svakom koraku smanjuje broj ”povrataka” šlepera za bar jedan, dakle složenost ovog algoritma je $O(\frac{N}{C})$, što smo na početku ograničili sa $O(X)$. Ovaj algoritam donosi $100$ bodova.

``` cpp title="04_carina.cpp" linenums="1"
/*
 Author: Petar 'PetarV' Velickovic
 Task: Carina
*/

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

#define DPRINTC(C) printf(#C " = %c\n", (C))
#define DPRINTS(S) printf(#S " = %s\n", (S))
#define DPRINTD(D) printf(#D " = %d\n", (D))
#define DPRINTLLD(LLD) printf(#LLD " = %lld\n", (LLD))
#define DPRINTLF(LF) printf(#LF " = %.5lf\n", (LF))

using namespace std;
typedef long long lld;
typedef unsigned long long llu;

lld n, c, l, X;

inline lld max1(lld a, lld b)
{
    if (a > b) return a;
    return b;
}

inline lld min1(lld a, lld b)
{
    if (a < b) return a;
    return b;
}

inline lld moj_ceil(lld A, lld B)
{
    lld ret = A/B;
    if (B * ret != A) ret++;
    return ret;
}

inline lld solve_bruteforce()
{
    for (lld i=0;i<l;i++)
    {
        n -= moj_ceil(n, c);
    }
    return n;
}

inline lld calc_new_n(lld x)
{
    lld V = moj_ceil(n, c);
    lld rem = n % c;
    lld ret;
    
    if (rem == 0 || rem >= x) ret = n - V*x;
    else ret = n - (V-1)*x - rem;
    
    return max1(0, ret);
}

inline lld binsearch(lld initPos)
{
    lld i = initPos + 1, j = l;
    lld V = moj_ceil(n, c);
    
    while (i < j)
    {
        lld mid = (i+j) >> 1;
        lld newN = calc_new_n(mid - initPos);
        if (moj_ceil(newN, c) == V) i = mid+1;
        else j = mid;
    }
    
    return i;
}

inline lld solve()
{
    lld ii = 0;
    while (ii < l && moj_ceil(n, c) > 1)
    {
        lld next_ii = binsearch(ii);
        lld x = next_ii - ii;
        
        lld V = moj_ceil(n, c);
        lld rem = n % c;
        
        if (rem == 0 || rem >= x) n -= V*x;
        else n -= (V-1)*x + rem;
        
        ii = next_ii;
    }
    return max1(0LL, n - (l - ii));
}

inline void debug()
{
    srand(time(NULL));
    for (int i=1;i<=20000;i++)
    {
        n = rand() % 100000 + 1;
        c = rand() % 100000 + 1;
        l = rand() % 100000 + 1;
        X = rand() % 100000 + 1;
        
        lld X1 = moj_ceil(n, c);
        if (X1 > (X+1)) n = c*(X+1);
        
        lld storN = n, storC = c, storL = l;
        lld bf = solve_bruteforce();
        n = storN, c = storC, l = storL;
        lld tt = solve();
        if (i % 1000 == 0) printf("Done %d\n", i);
        assert(bf == tt);
    }
}

int main()
{
    scanf("%lld%lld%lld%lld", &n, &c, &l, &X);
    lld X1 = moj_ceil(n, c);
    if (X1 > (X+1)) n = c*(X+1);
    printf("%lld\n", solve());
    return 0;
}
```
