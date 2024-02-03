---
hide:
  - toc
---

# A3 - Komande2D

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 64MB |

Danas je loše vreme napolju i student Srba je odlučio da neće izlaziti iz kuće, pa tako neće otići ni na fakultet. Ipak, onda bi izgubio bitne bodove na predavanjima, pa je smislio novi način kako će prisustvovati njima. Napravio je robota koji će otići umesto njega, čak i zapisivati ono što priča profesor.

Selo u kome živi Srba je kvadratnog oblika, i nalazi se na površini koju obuhvata kvadrat koji ima temena u koordinatama $(-K, K)$, $(K, K)$, $(K, -K)$, $(-K, K)$. Srbina kuća se nalazi na koordinatama $(0,0)$, dok se njegov fakultet nalazi na koordinatama $(X_f, Y_f)$.

Robotu, koji je mali Srba napravio, se mogu zadati sledeće komande:

* `U` – Idi gore (ukoliko je bio na koordinatama $(x, y)$ pomeriće se na $(x,  y+1)$);
* `D` – Idi dole (ukoliko je bio na koordinatama $(x, y)$ pomeriće se na $(x,  y-1)$);
* `L` – Idi levo (ukoliko je bio na koordinatama $(x, y)$ pomeriće se na $(x-1,  y)$);
* `R` – Idi desno (ukoliko je bio na koordinatama $(x, y)$ pomeriće se na $(x+1,  y)$).

Student Srba je robotu već zadao $N$ komandi. Međutim, pošto on odavno nije išao na fakultet, zaboravio je tačan put do njega, a robot je završio u pivnici. Sada robotu treba promeniti komande, i Srba vas moli da mu pomognete. Pošto se već dovoljno namučio praveći robota i pišući ove komande, on želi samo da **obriše neki uzastopni niz komandi**, i to po mogućstvu **najkraći**. Nađite najkraći takav niz ukoliko on postoji, ili ispišite $-1$ ukoliko ne postoji.

Obratite pažnju da robot **ni u jednom trenutku ne sme preći granice sela** (ne sme izaći iz kvadrata koji ga predstavlja), jer će se izgubiti. Preciznije, dok se izvršava konačan skup komandi nakon brisanja, robot uvek mora ostati u kvadratu (iako je možda tokom izvršavanja početnog niza komandi, pre brisanja, mogao odlutati van kvadrata).

## Ulaz
U prvom redu standardnog ulaza se nalaze $4$ broja – $N$, $K$, $X_f$, $Y_f$ koji redom predstavljaju broj komandi koje je Srba zadao robotu, granice sela i koordinate fakulteta. U drugom redu se nalazi $N$ karaktera koji predstavljaju komande koje je Srba zadao robotu.

## Izlaz
U prvi i jedini red standardnog izlaza ispisati $2$ broja koji, redom, predstavljaju indeks početne i krajnje komande najkraćeg niza komandi koji se može izbrisati (komande su indeksirane od $1$). Ukoliko ne postoji takav niz, ispisati $-1$. Ukoliko postoji više najkraćih nizova, ispisati bilo koji.

## Primer 1
### Ulaz
```
11 100 2 3
UUURRDRDRUU
```

### Izlaz
```
7 10
```

## Primer 2
### Ulaz
```
8 2 1 2
RRRUULLL
```

### Izlaz
```
-1
```

## Objašnjenje primera
U prvom primeru treba obrisati niz `RDRU` koji se nalazi od $7$. do $10$. komande. Primetimo da se i brisanjem niza `DRDRUU` od $6$. do $11$. pozicije, na kraju stiže u tražene koordinate $(2, 3)$, ali je prethodni niz kraći.

U drugom primeru nije moguće doći u koordinate $(1,2)$ bez izlaska iz sela.

## Ograničenja

* $1\leq N\leq 10^6$.
* $1\leq K\leq 1000$.
* $-K\leq X_f,  Y_f \leq K$.

Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim $40$ poena važi $N\leq 1000$.
* U test primerima vrednim $60$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | - | Boris Grubić |


``` cpp title="06_komande2d.cpp" linenums="1"
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1000005;
const int MAX_K = 1005;

int n, k, x, y;
char s[MAX_N];
int pos[2 * MAX_K][2 * MAX_K];
vector<int> List[2 * MAX_K][2 * MAX_K];

int dx[] = {0,  -1, 1,  0};
int dy[] = {1,   0, 0, -1};

int decode(char ch) {
	if (ch == 'U') return 0;
	if (ch == 'L') return 1;
	if (ch == 'R') return 2;
	return 3;
}

int main() {
	scanf("%d%d%d%d", &n, &k, &x, &y);
	scanf("%s", s);
	int sx = 0;
	int sy = 0;
	for (int i = 0; i < n; ++i) {
		sx += dx[decode(s[i])];
		sy += dy[decode(s[i])];
		if (sx < -k || sx > k) break;
		if (sy < -k || sy > k) break;
		List[sx + k][sy + k].push_back(i);
	}

	for (int i = 0; i < 2 * MAX_K; ++i)
		for (int j = 0; j < 2 * MAX_K; ++j)
			pos[i][j] = List[i][j].size() - 1;

	sx = x;
	sy = y;
	int res = 987654321;
	int sta, end;
	for (int i = n - 1; i >= 0; --i) {
		sx += dx[3 - decode(s[i])];
		sy += dy[3 - decode(s[i])];
		if (sx < -k || sx > k) break;
		if (sy < -k || sy > k) break;
		while (pos[sx + k][sy + k] >= 0 && 
			   List[sx + k][sy + k][pos[sx + k][sy + k]] >= i)
			--pos[sx + k][sy + k];

		if (pos[sx + k][sy + k] >= 0) {
			int tmp = i - List[sx + k][sy + k][pos[sx + k][sy + k]];
			if (res > tmp) {
				res = tmp;
				sta = i - tmp + 1;
				end = i - 1;
			}
		}
	}

	if (res != 987654321) printf("%d %d\n", sta + 1, end + 1);
	else printf("-1\n");

	return 0;
}
```
