---
hide:
  - toc
---

# A1 - Standardan zadatak

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Osoba T je dobila niz $A$ dužine $N$. Jedina dozvoljena operacija nad nizom je:

* Izabrati tri proizvoljna različita indeksa $(i, j, k)$, $1 \leq i < j < k \leq N$ i postaviti članove niza $A_i, A_j$ i $A_k$ na srednji po vrednosti od ta tri elementa.

Naći minimalan broj operacija koji osoba T mora napraviti tako da svi elementi niza $A$ budu jednaki po vrednosti.

## Opis ulaza
* U prvom redu ulaza se nalazi pozitivan ceo broj $N$ - broj elemenata u nizu $A$. 

* U drugom redu ulaza se nalazi $N$ pozitivnih celih brojeva, elementi niza $A$.

## Opis izlaza
Na izlazu ispisati minimalan broj operacija potreban da niz $A$ sadrži sve jednake elemente po vrednosti.

## Ograničenja
-   $3 \leq N \leq 2\cdot10^5$
-   $1 \leq A_i\leq 10^6$

Test primeri su podeljeni u $4$ disjunktne grupe:

-   U test primerima vrednim $10$ poena: Svi elementi niza $A$ su različiti.
-   U test primerima vrednim $10$ poena: U nizu $A$ se pojavljuje najviše dve različite vrednosti.
-   U test primerima vrednim $20$ poena: $N\leq 2000$.
-   U test primerima vrednim $60$ poena: Bez dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
5
1 2 3 2 5
```

#### Izlaz
```
2
```

#### Objašnjenje
Osoba T prvu operaciju može primeniti nad indeksima $(2, 3, 4)$, niz se transformiše u $A = [1, 2, 2, 2, 5]$. U drugom operaciji može izabrati indekse $(1, 2, 5)$ nakon čega svaki element niza $A$ ima vrednost $2$. 

### Primer 2
#### Ulaz
```
3
1 1 1
```

#### Izlaz
```
0
```

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Vladimir Milenković | Vladimir Milenković |

Pretpostavimo da će nam na kraju svi elementi niza biti jednaki nekom broju $x$, koji već postoji u ovom nizu. Ono što treba da uradimo je da pretvorimo sve brojeve koji nisu isprva jednaki $x$ u $x$-eve. 

Neka imamo $l$ brojeva strogo manjih od $x$ u početnom nizu, i $r$ brojeva koji su strogo veći. Ukoliko su oba broja veća od $0$, možemo izvršiti operaciju koja će umanjiti brojeve $l$ i $r$ za jedan, tako što ćemo uraditi operaciju na jednom broju manjem od $x$, jednom jednakom i jednom većem od njega. Ovo možemo ponavljati dok god su i $l$ i $r$ pozitivni, dakle $\min(l, r)$ puta. Kada jedan od njih postane jednak nuli, bez umanjenja opštosti, neka je to $r$ -- možemo iskoristiti još $l$ operacija u kojima stavljamo dva broja $x$ i jedan manji broj, dok god svi brojevi ne budu jednaki broju $x$.

Broj operacija kojima smo smanjili zbir $l + r$ za $2$ je $\min(l, r)$, svim ostalim operacijama smo smanjivali zbir za 1, pa je ukupan broj operacija $l + r - \min(l, r) = max(l, r)$. 

Dakle, primetimo da nam je rešenje zadatka jednako $\min_{i = 1}^{n} \max(l(a_i), r(a_i)$, gde funkcije $l(\cdot)$ i $r(\cdot)$ vraćaju broj manjih, odnosno većih brojeva od $a_i$ u početnom nizu a $LIM$ je maksimalni broj koji se može pojaviti u nizu.

## Podzadatak 1
U ovom podzadatku, nakon sortiranja niza trivijalno imamo vrednosti funkcija $l(\cdot)$ i $r(\cdot)$ za sve vrednosti. Složenost: $\mathcal{O}(N\log N)$.

## Podzadatak 2
U ovom podzadatku, imamo samo dve moguće vrednosti za naš $x$. Složenost: $\mathcal{O}(N)$.

## Podzadatak 3
U ovom podzadatku možemo, za svaki kandidat za rešenje, ”ručno” izbrojati odgovarajući broj većih odnosno manjih brojeva. Složenost: $\mathcal{O}(N^2)$.

## Celo rešenje
Možemo iterirati po vrednostima od najmanje do najveće, pamteći koliko manjih brojeva smo prošli do sad. Znajući koliko ima manjih i koliko brojeva jednakih trenutnom broju, možemo izračunati i koliko ima većih i samim tim dobiti rešenje u linearnoj složenosti. Složenost: $\mathcal{O}(N)$ ili $\mathcal{O}(N\log N)$, zavisno od implementacije.

``` cpp title="04_standardan_zadatak.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

const int maxN = 2e5;
const int maxA = 1e6;

int a[maxN], cnt[maxA + 10];
int n;

int main()
{
    scanf("%d",&n);

    assert(n > 0 && n <= maxN);

    for (int i = 1; i<=n;i++)
    {
    	scanf("%d",&a[i]);
    	assert(a[i] > 0 && a[i]<=maxA);
    	cnt[a[i]]++;
    }
   
   int ans = n;
   int bigger = 0;
   for (int i = maxA; i>0; i--) 
   if (cnt[i])
   {   
       ans = min(ans, max(bigger, n - bigger - cnt[i]));
       bigger+=cnt[i];
   }

   printf("%d\n", ans);
}
```
