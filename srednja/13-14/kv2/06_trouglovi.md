---
hide:
  - toc
---

# 6 - Trouglovi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Srba pravi novu verziju igrice “Flappy Bird”. Odlučio je da prepreke više ne budu cevi, već trouglovi koji će lebdedi u vazduhu.

Odlučio je da će trouglove crtati tako što će na početku izabrati $N$ različitih tačaka u ravni. Svaka prepreka će biti trougao koji ima temena u neke tri od izabranih tačaka. Nakon što se prepreka pređe, pravi se nova prepreka koja nije ista kao ni jedna prethodna (dve prepreke su  različite ako odgovarajući trouglovi imaju bar jedno različito teme).

Da bi igra izgledala lepše, on će birati **samo trouglove čiji su svi uglovi oštri**.

Malog Srbu zanima kada odabere početne tačke, koliko će igra biti duga, odnosno, koliko će najviše prepreka postojati u igri?

## Ulaz
U prvom redu standardnog ulaza se nalazi jedan ceo broj $N$ koji predstavlja broj tačaka koje je mali Srba izabrao. U sledećih $N$ redova se nalaze po dva realna broja $X_i$ i $Y_i$ koji predstavljaju koordinate tačaka. Koordinate će biti zapisane sa najviše $3$ decimale.

## Izlaz
U prvom i jedinom redu standardnog izlaza ispisati broj različitih prepreka koje će postojati u novoj igri.

## Primer 1
### Ulaz
```
5
0.0 0.0
1.1 0.0
3.0 0.0
1.1 2.0
2.1 2.0
```

### Izlaz
```
3
```

## Objašnjenje primera
Mali Srba može napraviti $3$ različita oštrougla trougla, i to su trouglovi koje čine tačke:

* $(0.0, 0.0)$, $(3.0, 0.0)$ i $(1.1, 2.0)$;
* $(0.0, 0.0)$, $(3.0, 0.0)$ i $(2.1, 2.0)$;
* $(1.0, 0.0)$, $(3.0, 0.0)$ i $(2.1, 2.0)$.

## Ograničenja

* $1\leq N \leq 1000$.
* $-10^6 \leq X_i, Y_i \leq 10^6$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim $50$ poena važi $1\leq N\leq 100$.
* U test primerima vrednim $50$ poena nema dodatnih ograničenja.



#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | Aleksandar Višnjić | Nikola Stojiljković |

## Prvi podzadatak:
Potrebno je prebrojati broj oštrouglih trouglova sa temenima u datim tačkama. To je moguće uraditi grubom silom: za svake tri tačke odredimo dužine stranica $a$, $b$ i $c$. Trougao je oštrougli ako važi $a^2+b^2>c^2$, $b^2+c^2>a^2$ i $c^2+a^2>b^2$. Vremenska složenost je $O(N^3)$.

## Drugi podzadatak:
Pokušajmo da prebrojimo sve tupougle, pravougle i degenerisane trouglove. Fiksirajmo neku duž $AB$. Posmatrajmo normale na tu duž u tačkama $A$ i $B$. Sve tačke koje se **ne nalaze** strogo između njih spadaju u jednu od tri kategorije koju želimo prebrojati. Kada za svaku fiksiranu duž prebrojimo traženo, dobićemo dvostruku traženu vrednost pošto smo svaki takav trougao prebrojali dvaput (po jednom za svaku "manju" stranicu kojih ima dve). Nakon što nađemo tu vrednost, znamo i broj oštrouglih trouglova.

Preostalo je odrediti koliko se tačaka nalazi između dve paralelne prave, odnosno, za svaku takvu pravu odrediti koliko se tačaka nalazi sa njene "leve" strane (nakon što se prava usmeri i tada je moguće izvršiti orijentaciju trouglova). Ovo radi pošto je razlika tih rezultata upravo broj tačaka između dve paralelne prave.

Fiksirajmo sad jednu tačku i sortirajmo ostale po uglu u odnosu na nju. Primetimo da ako fiksiramo duži sa krajem u toj tački i drugim krajem redom po ostalim dobijamo to da naše normale na duž u toj našoj centralnoj tački budu sortirane po uglu. To znači da možemo preko dva pokazivača za svaku normalu izbrojati koliko tačaka ima "levo" od nje.

Vremenska složenost je $O(N^2\cdot logN)$.

``` cpp title="06_trouglovi.cpp" linenums="1"
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const double EPS = 1e-7;
const double PI = 3.1415926535;

int n, m;

struct Point
{
	double x, y;
	double angle;

	bool operator < (const Point &p) const
	{
		return angle < p.angle;
	}

	Point(){}

	Point(double _x, double _y)
		: x(_x), y(_y)
	{
		angle = atan2(y, x);
		if (angle < -EPS)
		{
			angle += 2.0 * PI;
		}
	}
};

double angleDifference(double angle1, double angle2)
{
	double angle = angle1 - angle2;
	if (angle < -EPS)
	{
		angle += 2.0 * PI;
	}
	return angle;
}

Point points[MAXN];
Point sorted[MAXN];

bool equals(double a, double b)
{
	return fabs(a - b) < EPS;
}

bool UpdateStart(int j, int &start)
{
	while (equals(sorted[start % m].angle, sorted[j].angle)) start++;	// preskocim kolinearne

	while (true)
	{
		double diff = angleDifference(sorted[start % m].angle, sorted[j].angle);

		if (diff > PI / 2.0 - EPS && diff < PI - EPS)	// ako je >= 90 stepeni && < 180 stepeni (nadje start i prekine)
		{
			return true;
		}
		else if (diff >= PI - EPS)	// ako je >= 180 stepeni onda nije naisao na ugao koji je izmedju [90, 180) pa kaze nije nasao start
		{
			return false;
		}
		start++;

		if (equals(sorted[start % m].angle, sorted[j].angle))	// ako sam naisao na neku kolinearnu opet onda znaci da ne postoji nijedan od gore navedenih uglova
		{
			return false;
		}
	}
	return false;
}

// sve isto kao UpdateStart samo sto ovde izlazim kad naidjem na ugao >= 180
bool UpdateEnd(int j, int &end)
{
	while (equals(sorted[end % m].angle, sorted[j].angle)) end++;

	while (true)
	{
		double diff = angleDifference(sorted[end % m].angle, sorted[j].angle);
		if (diff >= PI - EPS)
		{
			return true;
		}

		end++;
		if (equals(sorted[end % m].angle, sorted[j].angle))
		{
			return false;
		}
	}
	return false;
}

int CalculateDegen()
{
	int ans = 0;

	int j = 0;
	for (int i = 0; i < m; j++)
	{
		while (equals(sorted[i].angle, sorted[j].angle))
		{
			j++;
		}
		ans += (j - i) * (j - i - 1) / 2;
		i = j + 1;
	}
	return ans;
}

int main()
{
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%lf%lf", &points[i].x, &points[i].y);
	}

	int total = 0;
	int totalDegen = 0;

	for (int i = 0; i < n; i++)
	{
		m = 0;
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				continue;
			}
			
			sorted[m++] = Point(points[j].x - points[i].x, points[j].y - points[i].y);
		}
		
		sort(sorted, sorted + m);		// sorted sadrzi tacke koje su sortirane u odnosu na fiksiranu tacku p[i]
		totalDegen += CalculateDegen();

		int start = 0, end = 0;	// start je prvi prav ili tup ugao, end je prvi >= 180 (tj. interval [start, end) predstavlja prave/tupe)
		int degenStart = 0, degenEnd = 0;

		for (int j = 0; j < m; j++)
		{
			// fiksiram drugu tacku, updatujem start i end
			bool existsStart = UpdateStart(j, start);
			bool existsEnd = UpdateEnd(j, end);

			// ako start postoji (onda postoji i end sigurno) i updatujem broj tupih/pravih uglova
			if (existsStart)
			{
				total += end - start;
			}
			else if (!existsEnd)	// ako ne postoji ni start ni end onda je pretpostavka da dalje ne postoji nijedan tup/prav ugao
									// za trenutno fiksiranu tacku (mislim da je tacno jer ce se uglovi samo smanjivati 
									// a kako ne postoji >= 90 nijedan onda su svi ostri)
			{
				break;
			}
		}
	}

	int totalTriangles = n * (n - 1) * (n - 2) / 6;
	totalDegen /= 2;
	printf("%d %d\n", total, totalDegen);

	printf("%d\n", totalTriangles - total - totalDegen);

	return 0;
}
```
