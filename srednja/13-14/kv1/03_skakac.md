---
hide:
  - toc
---

# 3 - Skakač

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 16MB |

Na ovogodišnjim Zimskim olimpijskim igrama u ruskom gradu S(k)očiju u disciplini ski-skokovi našu zemlju predstavlja prekaljeni skakač Miške. Teren za skakanje možemo zamisliti kao matricu sa $n$ vrsta i $m$ kolona podeljenu na $nm$ polja pri čemu se Miške na početku nalazi na polju u preseku $r$-te vrste i $c$-te kolone. Međutim, osim što je prekaljeni skakač, Miške je i prekaljeni igrač šaha pa ume da skače samo kao **figura skakač u šahu**.

Pre nego što izabere gde će skakati, Miške želi da zna na koliko **različitih** polja može završiti ako krene sa svog početnog polja i napravi **tačno** $k$ skokova **($k$ će uvek biti $1$ ili $2$)**. Kako Miške nije prekaljeni programer, na vama je da mu date ovu informaciju koja će mu pomoći u borbi za medalju!

## Ulaz
U prvom redu standardnog ulaza nalaze se, redom, pet prirodnih brojeva razdvojenih po jednim razmakom: $n$ (broj vrsta), $m$ (broj kolona), $r$ (redni broj vrste u kojoj se Miške nalazi na početku), $c$ (redni broj kolone u kojoj se Miške nalazi na početku) i $k$ (broj skokova koje planira da napravi). Vrste i kolone su numerisane počevši od broja $1$.

## Izlaz
U prvom i jedinom redu standardnog izlaza ispisati broj različitih polja na koje Miške može završiti posle tačno $k$ poteza ako krene sa svog početnog polja.

## Primer 1
### Ulaz
```
8 8 1 2 1
```

### Izlaz
```
3
```

## Objašnjenje primera
Teren je dimenzija $8\times 8$, Miške se nalazi u preseku prve vrste i druge kolone, tj. na polju $(1, 2)$. Posle jednog skoka on može završiti samo na poljima $(3, 1)$, $(3, 3)$ i $(2, 4)$, pa je rešenje $3$.

## Ograničenja

* $1 \leq r \leq n \leq 2\cdot 10^9$.
* $1 \leq c \leq m \leq 2\cdot 10^9$.
* $1 \leq k \leq 2$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim $60$ poena je $k=1$.
* U test primerima vrednim $40$ poena je $k=2$.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Duško Obradović | Nikola Milosavljević | Nikola Milosavljević | Nikola Stojiljković |

Za kompletno rešenje zadatka, dovoljno je ispitati sva polja na koje skakač može doći u jednom, odnosno u dva poteza.  Za ovo je najjednostavnije napraviti dva konstantna niza: $dx[1\ldots 8] = \{-2, -2, -1, -1, 1, 1, 2, 2\}$ i $dy[1\ldots 8] = \{-1, 1, -2, 2, -2, 2, -1, 1\}$; tada skakač sa polja $(x, y)$ može skočiti na polja oblika $(x+dx[i], y+dy[i])$, za svako $1\leq i \leq 8$, koja su unutar table.

Za $K=2$, takođe generišemo sve moguće (dvo)poteze (njih $64$) pri čemu proveravamo da li je skakač unutar table i posle prvog i posle drugog poteza. Primetimo da je moguće da smo na neko polje stigli na $2$ načina ali to polje treba računati samo jednom u rešenju. Jedan od načina za izbacivanje duplikata je da u nizu pamtimo sva različita polja do kojih smo do tada mogli doći u dva poteza i, ukoliko se trenutno polje ne nalazi u nizu, dodajemo ga i povećavamo rešenje za $1$.

Računanje nekog polja $2$ puta smo mogli izbeći i koristeći činjenicu da skakač posle $2$ poteza može otići najviše 4 polja u svakom smeru – dovoljno je “odseći” odgovarajući deo table dimenzije ne veće od 5×5 i jednostavno markirati odgovarajuća polja u dobijenoj maloj matrici.

Vremenska i memorijska složenost algoritma je u svakom slučaju $O(1)$.

``` cpp title="03_skakac.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

const int dx[] = {-2, -2, -1, -1, +1, +1, +2, +2};
const int dy[] = {-1, +1, -2, +2, -2, +2, -1, +1};

int X[100], Y[100];
int n, m, r, c, k, sol;

bool ok(int x, int y)
{
	return (x >= 1 && x <= n && y >= 1 && y <= m);
}

int solveK1()
{
	int sol = 0;
	for (int i = 0; i < 8; i++)
		if (ok(r + dx[i], c + dy[i])) sol++;
	return sol;
}

int solveK2()
{
	int num = 0;
	for (int i = 0; i < 8; i++)
	{
		if (ok(r + dx[i], c + dy[i]))
		{
			for (int j = 0; j < 8; j++)
			{
				if (ok(r + dx[i] + dx[j], c + dy[i] + dy[j]))
				{
					num++;
					X[num] = r + dx[i] + dx[j];
					Y[num] = c + dy[i] + dy[j];
				}
			}
		}
	}

	int sol = 0;
	for (int i = 1; i <= num; i++)
	{
		bool moveExists = false;
		for (int j = 1; j < i; j++)
		{
			if (X[i] == X[j] && Y[i] == Y[j])
				moveExists = true;
		}
		if (!moveExists) sol++;
	}

	return sol;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &r, &c, &k);
		
	if (k == 1)
		printf("%d\n", solveK1());
	else
		printf("%d\n", solveK2());

	return 0;
}
```
