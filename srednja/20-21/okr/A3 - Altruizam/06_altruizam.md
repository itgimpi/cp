---
hide:
  - toc
---

# A3 - Altruizam

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Drevni Programer ide od sela do sela pogođenih nestašicom interneta i deli kriptovalute. Zašto? Niko ne zna. Na njegovom putu našlo se $k$ sela, u $i$-tom selu je $a_i$ programera koji se, u nedostatku interneta, dive suncu, drveću i drugim čudesima koja ih okružuju. Drevni Programer je poneo $n$ kilograma kriptovaluta i deli ih prema Zakonu velikih brojeva - selo sa većim rednim brojem dobija veći broj kriptovaluta. 

Formalnije, svaki programer prvog sela dobio je onoliko kilograma kriptovaluta koliki je zbir cifara broja $n$; svaki programer drugog sela dobio je onoliko kilograma kriptovaluta koliki je zbir kvadrata cifara broja $n$; itd.; svaki programer $k$-tog sela dobio je onoliko kilograma kriptovaluta koliki je zbir $k$-tih stepena cifara broja $n$. Nakon što je Drevni Programer obišao sva sela i odjahao u suton, shvatio je da je podelio tačno sve kriptovalute koje je poneo; i bi mu drago i pusti uzdah i dve suze radosnice.

Odrediti koliko je kilograma kriptovaluta poneo Drevni Programer ukoliko je poznato da je taj broj između $x$ i $y$ (uključivo), kao i da omiljena kriptovaluta Drevnog Programera nije kriptonit.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se tri prirodna broja $x$, $y$ i $k$ koji, redom, predstavljaju granice za broj $n$ i broj sela. U narednom redu nalazi se $k$ prirodnih brojeva $a_i$ - broj programera po selima, redom.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan prirodan broj $n$ - broj kilograma kriptovaluta koje je Drevni Programer poneo sa sobom. Ukoliko nema rešenja u zadatom intervalu, ispisati `-1`; ukoliko ima više rešenja (u zadatom intervalu) ispisati bilo koje.

## Ograničenja
-   $1 \leq x \leq y \leq 10^{18}$
-   $1 \leq k \leq 10^5$
-   $1 \leq a_i \leq 10^{18}$ za svako $i \in \{1,2,...,k\}$

Test primeri su podeljeni u $5$ disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $|x-y| \leq 10^3$.
-   U test primerima vrednim $10$ poena: $|x-y| \leq 10^7$.
-   U test primerima vrednim $20$ poena: $k \leq 2$.
-   U test primerima vrednim $20$ poena: $k = 2021$.
-   U test primerima vrednim $40$ poena: Bez dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
18000 25000 3
30 65 21
```

#### Izlaz
```
20528
```

#### Objašnjenje
Ukoliko je Drevni Programer poneo $20528$ kilograma kriptovaluta, tada svaki programer iz 1. sela dobija po $2+0+5+2+8=17$ kilograma, svaki programer iz 2. sela dobija po $2^2+0^2+5^2+2^2+8^2=97$ kilograma i svaki programer iz 3. sela dobija po $2^3+0^3+5^3+2^3+8^3=653$ kilograma. Dakle, ukupno je podeljeno $30\cdot17+65\cdot97+21\cdot653=20528$ kilograma, tj. podeljene su sve kriptovalute kao što se i zahtevalo. Obratiti pažnju da iako i broj $29630$ zadovoljava prethodne uslove, on ne pripada opsegu $[18000, 25000]$ pa nije rešenje.

### Primer 2
#### Ulaz
```
45 60 1
7
```

#### Izlaz
```
-1
```

#### Objašnjenje
Iako postoji nekoliko brojeva koji ispunjavaju uslove o podeli (npr. $21$) nijedan od njih ne pripada segmentu $[45,60]$ pa treba ispisati `-1`.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Aleksa Milisavljević |

## Analiza
Označimo sa $S_i(n)$ zbir $i$-tih stepena cifara broja $n$ (npr. $S_3(2021)=2^3+0^3+2^3+1^3=17$). Potrebno je pronaći prirodan broj $n$ iz segmenta $[x,y]$ za koji važi

$$n = a_1 \cdot S_1(n)+a_2\cdot S_2(n) + \ldots + a_k \cdot S_k(n)$$

Najjednostavnije rešenje je proveriti prethodnu jednakost za svaki broj iz $[x,y]$; direktna implementacija radi u složenosti $O(|y-x|\cdot k)$ i rešava **podzadatak 1**. 

Malo bolje rešenje (koje vodi konačnom rešenju) je zapisati prethodnu jednačinu na drugačiji način. Za svaku cifru $i$, $1 \leq i \leq 9$ uvedimo oznaku $c_i = a_1 \cdot i^1 + a_2\cdot i^2 + \ldots + a_k \cdot i^k.$ Takođe, označimo broj pojavljivanja cifre $i$ ($1\leq i \leq 9$) u broju $n$ sa $x_i(n)$. Nije teško uočiti da je polazna jednačina ekvivalentna sa

$$n = c_1 \cdot x_1(n) + c_2 \cdot x_2(n) + \ldots + c_9 \cdot x_9(n)$$ 

Za konkretan broj $n$ prethodnu jednačinu možemo proveriti u $O(\log n)$ (broj cifara broja $n$) pa dolazimo do rešenja složenosti $O(|y-x|\log y)$ koje je dovoljno za **podzadatak 2**.
 
U **podzadatku 3** je $k \leq 2$; kako je $n \leq 10^{18}$, važi $S_1(n) \leq 9\cdot 18 = 162$ i $S_2(n)\leq 9^2 \cdot 18 = 1458$ pa možemo isprobati svih $162 \cdot 1458$ mogućnosti za ove vrednosti i proveriti da li dobijeni broj $n$ zadovoljava jednačinu.

Primetimo da ako $n$ sadrži bar jednu cifru vrednosti $c$, tada važi $n \geq c^1+c^2+\ldots +c^k$. Sada, iz $n \leq 10^{18}$, dobijamo da ako $n$ sadrži bar jednu cifru veću od $1$ mora važiti da je $k \leq 58$. Kako u **podzadatku 4** važi $k = 2021$, sledi da su u ovom podzadatku jedini kandidati za rešenje brojevi koji se sastoje od nula i jedinica. Sada na osnovu druge jednačine imamo $n = c_1 \cdot x_1(n)$ pa jednostavno isprobamo svih $18$ mogućih vrednosti za $x_1(n)$ (ili, malo komplikovanije, generišemo svih $2^{18} - 1$ takvih brojeva i proverimo ih).

Ključno zapažanje, koje direktno sledi iz jednačine sa $c_i$-ovima, je da brojevi sa istim brojem pojavljivanja svake ne-nula cifre daju istu vrednost sa desne strane jednačine (npr. $35502, 2355, 5532, 20305050...$) pa proveru ne moramo vršiti po svim brojevima iz $[x,y]$ već po broju pojavljivanja cifara. Dovoljno je isprobati sve $9$-orke $(x_1, x_2, ..., x_n)$ nenegativnih celih brojeva za koje je $1 \leq x_1 + x_2 + \ldots  +x_9 \leq 18$ (broj cifara je između 1 i 18), izračunati desnu stranu jednačine i proveriti da li je dobijeni broj $n$ iz $[x,y]$ i da li se u njemu svaka cifra $i$ javlja tačno $x_i$ puta.

Za generisanje ovakvih $9$-orki koristimo **backtracking** tehniku. Jedan od načina je zapravo generisati brojeve sa nerastućim nizom cifara: sa $F(a,b)$ označimo poziv rekurzivne funkcije u kome treba fiksirati $a$-tu cifru pri čemu je prethodna cifra $b$; rekurzivni pozivi su $F(a+1, b)$ ($a$-ta cifra je $b$, uz povećanje $x_b$) i $F(a, b-1)$ ($a$-ta cifra je manja od $b$) . Broj pomenutih devetorki se može odrediti pokretanjem ovog algoritma ili koristeći malo kombinatorike; taj broj je $\binom{27}{9}-1=4686825$ tj. dovoljno je mali da ovaj algoritam rešava ceo zadatak u zadatom vremenskom ograničenju.

``` cpp title="06_altruizam.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

const long long MAX_VAL = 1000000000000000000LL;
const int MAX_DIGITS = 18;
const int MAX_K = 100000;

long long X, Y;
int k;
long long a[MAX_K + 10];

long long c[10];
int x[10];
bool found;
long long solution;

void precalc()
{
	for (int val = 1; val <= 9; val++)
	{
		long long curr = 1LL;
		c[val] = 0LL;
		int i = 1;

		while (i <= k)
		{
			curr = curr * val;
			if (curr > MAX_VAL / a[i])
			{
				c[val] = MAX_VAL + 1;
				break;
			}
			c[val] = c[val] + curr * a[i];
			if (c[val] > MAX_VAL)
			{
				c[val] = MAX_VAL + 1;
				break;
			}
			i++;
		}
	}
}

long long calc(int x[])
{
	long long ret = 0LL;
	for (int i = 1; i <= 9; i++)
	{
		if (x[i] > MAX_VAL / c[i])
			return MAX_VAL + 1;
		ret = ret + c[i] * x[i];
		if (ret > MAX_VAL)
			return MAX_VAL + 1;
	}

	return ret;
}

bool check(int x[])
{
	long long n = calc(x);
	if (n < X || n > Y)
		return false;

	int x1[10];
	for (int i = 0; i <= 9; i++)
		x1[i] = 0;

	long long n1 = n;
	while (n > 0)
	{
		x1[n % 10]++;
		n = n / 10;
	}
	for (int i = 1; i <= 9; i++)
		if (x[i] != x1[i])
			return false;

	solution = n1;
	return true;
}

void F(int n, int currDigit)
{
	if (found)
		return;

	if (n > MAX_DIGITS || currDigit == 0)
	{
		found = check(x);
		return;
	}

	x[currDigit]++;
	F(n + 1, currDigit);
	x[currDigit]--;
	F(n, currDigit - 1);
}

int main()
{
	scanf("%lld%lld%d", &X, &Y, &k);
	for (int i = 1; i <= k; i++)
		scanf("%lld", &a[i]);

	precalc();

	for (int i = 0; i <= 9; i++)
		x[i] = 0;
	found = false;
	solution = -1LL;

	F(1, 9);

	printf("%lld\n", solution);
	return 0;
}

```
