---
hide:
  - toc
---

# A1 - Cik-cak

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Mikica se od završetka trećeg kruga kvalifikacija bavi proučavanjem nizova koje je nazvao cik-cak nizovi. To su nizovi celih brojeva sa sledećim osobinama:

* prvi element ima vrednost nula
* svaki sledeći element je za jedan manji ili za jedan veći od prethodnog.

Na primer, cik-cak nizovi su nizovi
$0, -1, -2, -1, 0, 1, 2, 3, 2, 1$ ili $0, 1, 0, -1, -2, -1, 0, 1, 2, 3$ a niz $0, 1, 2, 3, 1, 2, 1, 0, -1$ nije cik-cak jer je peti element za dva manji od četvrtog. Proučavajući cik-cak nizove, Mikica je sebi postavio zadatak da za zadati prirodni broj $n$ i ceo broj $S$ odredi cik-cak niz koji ima $n$ elemenata, ali takav da je zbir tih $n$ elemenata jednak broju $S$. Zapravo, postavio je sebi zadatak da to bude leksikografski najmanji niz, ali kako još uvek nije uspeo da pronađe postupak za određivanje tog niza bio bi zadovoljan ako pronađe bilo koji cik-cak niz sa $n$ elemenata koji ima zbir elemenata jednak broju $S$.

Pomozite Mikici i napišite program koji će za zadate brojeve $n$ i  $S$ odrediti leksikografski najmanji niz sa $n$ elemenata čiji je zbir $S$. **Ako ne uspete da nađete leksikografski najmanji, ali zato pronađete neki drugi niz sa tom osobinom, dobićete $60\%$ predviđenih poena**.

## Opis ulaza
U prvom redu standardnog ulaza se nalaze prirodan broj $n$ i ceo broj $S$ razdvojeni jednim razmakom

## Opis izlaza
Ako ne postoji cik-cak niz sa $n$ elemenata čiji je zbir $S$, onda u prvom redu ispisati broj $-1$. Ako postoji cik-cak niz sa traženim osobinama, ispisati taj niz tako što se u svakom od $n$ redova ispisuje po jedan element niza. Ako ste uspeli da odredite leksikografski najmanji, treba njega ispisati, u suprotnom ispisati bilo koji.

## Primer 1
### Ulaz
```
7 3
```

### Izlaz
```
0
-1
0
1
0
1
2
```

## Primer 2
### Ulaz
```
3 100
```

### Izlaz
```
-1
```

## Objašnjenje primera
Sabiranjem elemenata (prvi primer) se zaključuje da je zbir 3. Lako se proverava da ne postoji leksikografski manji sa istim zbirom.

## Ograničenja i podzadaci

* $1\leq n \leq 50000$.
* $-10^9 \leq S \leq 10^9$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede $20$ poena broj elemenata u nizovima nije veći od $20$.
* U test primerima koji vrede $30$ poena broj $S$ je između $-10$ i $10$.
* U test primerima koji vrede $50$ poena nema dodatnih ograničenja. 

**Napomena**

Niz $(a_1, a_2, a_3, \ldots, a_n)$ je leksikografski manji od niza  $(b_1, b_2, b_3, \ldots, b_n)$ ako postoji indeks $i$ sa osobinom da je $a_1 = b_1, a_2 = b_2, \ldots, a_{i-1} = b_{i-1}$ i $a_{i} < b_{i}$.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dragan Urošević | Dragan Urošević | Dragan Urošević | Aleksa Plavšić |

Primetimo da je najveći zbir koji može imati cik-cak niz sa $n$ elemenata jednak $\frac{n(n-1)}{2}$ i postiže se ako je svaki sledeći element za jedan veći od prethodnog, tj. ako niz ima sledeći izgled:

$$
0, 1, 2, ..., n-1.
$$

Takođe je najmanji zbir koji se može postići jednak $-\frac{n(n-1)}{2}$ i dobija se kada je svaki sledeći element za jedan manji od prethodnog pa su elementi tog niza:

$$
0, -1, -2, ..., -n+1.
$$

Takođe, primetimo da elementi niza zadržavaju parnost, pa su tako prvi, treći, peti, itd. uvek parni, a drugi, četvrti, šesti, itd. su uvek neparni. Zbog toga sume svih cik-cak nizova sa istim brojem elemenata (neka je broj elemenata $n$) uvek iste parnosti. Prema tome, ako su vrednost $\frac{n(n-1)}{2}$ i suma zadata u postavci problema (označimo tu sumu sa $S$) različite parnosti, zadatak nema rešenje. Takođe, ako je tražena suma veća od najveće moguće ili manja od najmanje moguće, zadatak nema rešenje. U ostalim slučajevima zadatak ima rešenje i potrebno je krenuti od cik cak niza $$0, 1, 2, 3, ..., n-1$$ čija je suma $\frac{n(n-1)}{2}$ i smanjivati dok se ne dobije tražena suma. Primetimo da ako se drugi element dobija smanjivanjem prvog za jedan, dok se svi ostali dobijaju dodavanjem broja 1 na prethodni, onda se ukupna suma smanji za $2(n-1)$. To je zato što su se svi elementi osim prvog smanjili za dva. Analogno, ako treći dobijemo smanjivanjem drugog za 1, a ostale računamo nepromenjeno, zbir će se smanjiti za $2(n-2)$. 
Tako dolazmo do pravilnosti kako računamo elemente niza. Neka je 

$$
D = \frac{n(n-1)}{2} - S.
$$

Postavimo da je prvi element jednak nuli (jer je tako i definisan cik-cak niz).
Počev od elementa sa indeksom $k=2$ (elementi su inače indeksirani počev od indeksa 1), proveravamo da li je trenutna vrednost $D$ veća od ili jednaka $2(n-k+1)$. Ako jeste, onda taj element dobijamo umanjivanjem prethodnog za jedan i istovremeno vrednost $D$ smanjimo za $2(n-k+1)$. U suprotnom, taj element dobijamo uvećavanjem prethodnog za jedan, a vrednost $D$ ostaje neporomenjena. Lako se uveravamo da će se na ovaj način uvek dobiti niz čija je suma jednaka traženoj. 

Primetimo da time što početne elemente dobijamo smanjivanjem prethodnih (kada god je to moguće), obezbeđujemo da će biti dobijen leksikografski najmanji cik-cak niz sa zadatom sumom.

``` cpp title="04_cik_cak.cpp" linenums="1"
# include <stdio.h>

# define MAXN 50050

int n;
int a[MAXN];
long long s, s1, s2, s3;

main() {
	int i, j, k;
	scanf("%d%lld", &n, &s1);
	s = (long long)n * (n-1) / 2;
	if (s1 > s) {
		printf("-1\n");
		return 0;
	}
	if (s1 < -s) {
		printf("-1\n");
		return 0;
	}
	if ((s - s1) %2 == 1) {
		printf("-1\n");
		return 0;
	}
	s2 = (s - s1) / 2;
	a[0] = 0;
	for (i = 1, j = n-1; i < n; i++, j--) 
		if (j <= s2) {
			a[i] = a[i-1] - 1;
			s2 -= j;
		} else {
			a[i] = a[i-1] + 1;
		}
	for (i = 0; i < n; i++)
		printf("%d\n", a[i]);
	return 0;
}

```
