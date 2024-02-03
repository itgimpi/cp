---
hide:
  - toc
---

# B1 - Premeštanja

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Na okružnom takmičenju iz informatike učestvuje $N$ takmičara. Njihova imena su $1, 2, \ldots, N$. Svi takmičari rade u velikoj prostoriji u kojoj se nalazi $N$ računara u nizu. Imena računara su $1, 2, \ldots, N$. Na početku, takmičar $1$ sedi za računarom $1$, takmičar $2$ za računarom $2$, itd., takmičar $N$ za računarom $N$.

Kako su takmičari generalno nepripremljeni i fragilni, oni se stalno žale na računare, podzemne vode i promaju i traže da se premeste za neki drugi računar. Preciznije, tokom takmičenja se desilo tačno $M$ premeštanja, redom. U $i$-tom premeštanju ($1 \leq i \leq M$) tačno dva takmičara menjaju mesta: takmičar koji je u tom trenutku radio na računaru $A_i$ sada prelazi na računar $B_i$ a takmičar koji je u tom trenutku radio na računaru $B_i$ prelazi na računar $A_i$. Moguće je da se tokom takmičenja neki takmičar premesti više puta (možda i nekoliko puta na isti računar).

Organizator Programer Pera vodi evidenciju o premeštanju takmičara i svaki put kada postoji bar jedan takmičar čiji se redni broj razlikuje za više od $K$ od rednog broja računara za kojim taj takmičar trenutno radi, Pera se namršti jer se takmičar baš udaljio od svog početnog računara, što je sumnjivo! Vaš zadatak je da nakon svakog premeštanja odredite da li se Pera namrštio.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se nenegativni celi brojevi $N$, $M$ i $K$, redom, koji predstavljaju broj takmičara, broj premeštanja i Perin parametar za sumnju. U narednih $M$ redova nalaze se po dva različita prirodna broja $A_i$ i $B_i$: redni brojevi računara sa kojih se takmičari međusobno premeštaju.

## Opis izlaza
Ispisati $M$ brojeva, svaki u posebnom redu, gde je $i$-ti broj $1$ ukoliko se nakon $i$-tog premeštanja Pera namrštio a $0$ ukoliko nije.

## Primer 1

### Ulaz

```
8 5 3
4 6
8 2
2 5
5 8
1 2
```

### Izlaz

```
0
1
1
0
1
```

## Primer 2

### Ulaz

```
10 2 0
1 10
1 10
```

### Izlaz

```
1
0
```

## Objašnjenje primera
Za prvi primer je $N = 8$, $M = 5$, $K= 3$. Raspored učenika po računarima je na početku 1 2 3 4 5 6 7 8 a nakon svakog premeštanja je
- 1 2 3 6 5 4 7 8 (raspored je dobar jer $|1-1|<K, |2-2| < K, \ldots, |4 - 6| < K$ itd.)
- 1 8 3 6 5 4 7 2 (raspored je sumnjiv jer npr. učenik $8$ sedi za računarom $2$ a $|8 - 2| > K$)
- 1 5 3 6 8 4 7 2 (raspored je sumnjiv jer učenik $2$ sedi za računarom $8$ a $|2 - 8| > K$)
- 1 5 3 6 2 4 7 8 (raspored je dobar)
- 5 1 3 6 2 4 7 8 (raspored je sumnjiv jer učenik $5$ sedi za računarom $1$ a $|5 - 1| > K$)

## Ograničenja
-   $2 \leq N,M \leq 3 \cdot 10^5$
-   $0 \leq K \leq 3 \cdot 10^5$
-   $1 \leq A_i, B_i \leq N$ i $A_i \neq B_i$

Test primeri su podeljeni u 5 disjunktnih grupa:

- U test primerima vrednim $20$ poena važi $N,M \leq 10^3$.
- U test primerima vrednim $20$ poena važi $M\leq 10^4$.
- U test primerima vrednim $20$ poena važi $K = N - 3$.
- U test primerima vrednim $20$ poena važi $K = 0$.
- U test primerima vrednim $20$ poena nema dodatnih ograničenja.



#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Aleksa Milojević |


## Analiza

Označimo sa $R_i$ redni broj učenika koji sedi za računarom $i$. Na početku je $R_i = i$ za svako $i = 1, 2, \ldots, N$. U svakom premeštanju mi praktično menjamo mesta dva elementa niza $R$ i nakon svakog premeštanja želimo da proverimo da li postoji neki indeks $i$ za koji važi $|i - R_i| > K$.

Pomenutu proveru možemo uraditi pravolinijski: u svakom od $M$ koraka zamenimo dva elementa niza a zatim prođemo kroz ceo niz i uporedimo $|i - R_i|$ i $K$. Složenost ovog algoritma je $O(NM)$ i rešava podzadatak 1 ($20$-$30$ poena) ali je previše spor za ostale podzadatke.

Primetimo da kada vršimo proveru nakon $i$ premeštanja, za sve indekse $j$ koji nisu učestvovali u prvih $i$ premeštanja važi $R_j = j$; dakle, ne moramo proveravati ceo niz već (u $i$-tom koraku) samo indekse iz prvih $i$ premeštanja ($A_1, B_1, A_2, B_2, \ldots, A_i, B_i$; među njima može biti istih). Ovo daje algoritam složenosti $O(M^2)$ što je dovoljno za prva dva podzadatka ($40$-$50$ poena).

U trećem podzadatku važi $K = N - 3$. Međutim, jedini indeksi $i$ za koje je moguće da važi $|i - R_i| < N - 3$ su $1, 2, N-1$ i $N$ (ostali se ne mogu dovoljno "udaljiti"; proveriti!) pa je nakon svake zamene dovoljno proveriti vrednosti $R_1, R_2, R_{N-1}$ i $R_N$ što nam daje ukupnu složenost $O(N+M)$ i rešava ovaj podzadatak ($20$ poena).

Da bismo rešili ceo zadatak, primetimo da nije neophodno stalno proveravati puno indeksa već je dovoljno da u svakom trenutku pamtimo koliko ima indeksa $i$ za koje važi $|i - R_i| > K$; označimo tu količinu sa $x$ (na početku je $x = 0$). Pomenuti indeks postoji akko je $x > 0$.  Zamenom dva elementa niza vrednost $x$ se može promeniti najviše za $2$ i razlikovanjem nekoliko slučajeva lako "update"-ujemo $x$ (npr. ako je $|A_i - R_{A_i}| \leq K$ i $|B_i - R_{B_i}| > K$, a $|A_i - R_{B_i}| > K$ i $|B_i - R_{A_i}| > K$, tada se nakon $i$-tog premeštanja $x$ povećava za $1$, itd.) . Složenost ovog rešenja je $O(N+M)$ i osvaja svih $100$ poena.

``` cpp title="01_premestanja.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

const int MAX_N = 300100;

int n, m, k;
int r[MAX_N]; // r[i] - redni broj takmicara koji sedi za racunarom i

int main()
{
	scanf("%d%d%d", &n, &m, &k);

	int num_suspicious = 0; // trenutni broj sumnjivih takmicara
	
	for (int i = 1; i <= n; i++)
		r[i] = i;

	for (int i = 1; i <= m; i++)
	{
		int a, b, tmp;
		scanf("%d%d", &a, &b);

		if (abs(a - r[a]) > k) num_suspicious--;
		if (abs(b - r[b]) > k) num_suspicious--;
		if (abs(a - r[b]) > k) num_suspicious++;
		if (abs(b - r[a]) > k) num_suspicious++;

		tmp = r[a]; 
		r[a] = r[b]; 
		r[b] = tmp;

		if (num_suspicious > 0)
			printf("1\n");
		else
			printf("0\n");
	}

	return 0;
} // O(n + m)
```
