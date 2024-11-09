---
hide:
  - toc
---

# 4 - Konjugacija

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Jednom, mudri Čar TakMi opazi segmente neke na $x$-osi. I bi mu jasno da neki segment $[l,r]$ sadrži neku tačku sa koordinatom $c$ samo ako i ako je $l \leq c \leq r$, jer tako je zapisano u knjigama geometarskim. I znade da je *centar* nekog segmenta zapravo tačka u središtu segmenta toga, jer drugačije ne može biti. I, najbitnije od svega, shvati da su dva segmenta *konjugovana* ako svaki od njih sadrži centar onog drugog, jer konji su plemenite životinje.

Za datih $N$ segmenata $[a_i, b_i]$ na $x$-osi, odredite koliko je (neuređenih) parova konjugovanih segmenata među njima, jer drugačije poene ne možete osvojiti.

## Opis ulaza
U prvom redu standardnog ulaza nalazi se prirodan broj $N$ - broj segmenata.

U narednih $N$ redova nalaze se po dva cela broja $a_i$ i $b_i$, redom, koji predstavljaju krajeve $i$-tog segmenta.

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati ceo broj koji predstavlja broj (neuređenih) parova konjugovanih segmenata među datim segmentima.

## Primer 1
### Ulaz
```
5
7 12
4 10
1 21
20 24
22 26
```

### Izlaz
```
3
```

### Objašnjenje
Centar segmenta $[7,12]$ je $9.5$ a centar segmenta $[4,10]$ je $7$.  Kako segment $[7,12]$ sadrži $7$ a segment $[4,10]$ sadrži $9.5$, ova dva segmenta su konjugovana. Slično, segmenti $[7,12]$ i $[1,21]$ su konjugovani kao i segmenti $[20,24]$ i $[22,26]$. Kako nema drugih parova konjugovanih segmenata, rešenje je $3$.

## Primer 2
### Ulaz
```
4
3 8 
3 8
3 8
4 8
```

### Izlaz
```
6
```

### Objašnjenje
Svaka dva segmenta iz ulaza su konjugovana.

## Ograničenja

- $1 \leq N \leq 150.000$
- $0 \leq a_i \leq b_i \leq 10^9$

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 10 poena: $N \leq 1000$.
- U testovima vrednim 15 poena: $0 \leq a_i, b_i \leq 100$ za $1 \leq i \leq N$.
- U testovima vrednim 20 poena: $a_i < a_{i+1}$ i $b_i < b_{i+1}$ za $1 \leq i <N$ .
- U testovima vrednim 25 poena: $N \leq 50.000$, $0 \leq a_i \leq b_i \leq 10^6$ za $1 \leq i \leq N$
- U testovima vrednim 30 poena: Bez dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Momčilo Tošić |

Možemo za svaki par segmenata proveriti u konstantnoj složenosti da li su konjugovani - složenost ovog algoritma je $O(N^2)$, što je dovoljno za **Podzadatak 1**

Ako su koordinate krajeva segmenata brojevi ne veći od $MaxVal$, tada postoji $O(MaxVal^2)$ mogućih pozicija za segmenate. Možemo u nekoj pomoćnoj matrici $m$ pamtiti $m[i][j] =$ broj segmenata sa krajevima u $i$ i $j$. Zatim, slično kao i u prethodnom slučaju, za svake dve moguće pozicije segmenata proverimo da li su oni konjugovani i koliko je to ukupno parova na osnovu matrice $m$. Ukupna složenost je $O(N + MaxVal^4)$ što je dovoljno za **Podzadatak 2**

Jedna od ideja je sortirati segmente neopadajuće na osnovu koordinate centra $c_i = \frac{a_i+b_i}{2}$ i za svaki segment $i$ odrediti koliko ima segmenata levo od njega koji su konjugovani sa njim; konačno rešenje dobijamo kada saberemo ove količine za svaki segment. Broj takvih segemenata je jednak broju indeksa $j$ za koje važi $1 \leq j < i$ i $a_i \leq c_j$ i $c_i \leq b_j$.

U **Podzadatku 3** su segmenti već sortirani rastuće po oba kraja posebno (pa samim tim i po centru) pa je skup segmenata levo od $i$-tog i koji su konjugovani sa $i$-tim neki uzastopni podniz sortiranog niza segmenata. U svakom koraku se sa početka ovog podniza mogu izbacivati segmenti koji nisu konjugovani sa trenutnim (neće biti konjugovani ni sa "desnijim" segmentima zbog uslova podzadatka) pa tehnika dva pokazivača i/ili binarne pretrage rešava ovaj podzadatak u složenosti $O(N)$ ili $O(N \log N)$.

Pretpostavimo da su sve koordinate centara $c_i$ relativno mali, različiti celi brojevi (možemo se obezbediti da budu celi tako što na početku pomnožimo sve krajeve segemenata sa $2$). Definišimo niz $A$ gde je za svako $i=\overline{1,N}$, $A[c_i] = r_i$ a na ostalim pozicijama su nule. Ako je $c_1 < c_2 < \ldots < c_N$, tada je broj segmenata koji su levo od segmenta $i$ i koji su konjugovani sa njim jednak broju elememenata uzstopnog podniza $A[l_i], A[l_i+1],\ldots, A[c_i - 1]$ koji su veći ili jednaki od $c_i$ (posmatra se samo podniz od $l_i$-te do $(c_i-1)$-te pozicije jer su indeksi - centri segmenata i oni moraju pripadati $i$-tom segmentu; vrednosti elementa su desni krajevi tih segmenata pa moraju biti $\geq c_i$ da bi sadržali centar $i$-tog segmenta). 

Ovim se zadatak svodi na **relativno poznat problem**: *dat je niz $A$ dužine $M$ i $N$ upita oblika $(l, r, k)$ - odrediti koliko ima elemenata u podnizu $A[l..r]$ koji su veći ili jednaki $k$*. Ovaj problem se najlakše rešava *offline* koristeći strukturu *segmentno stablo*. Na početku napunimo pomoćni niz $B$ nulama i sortiramo sve elememente i upite (zajedno) opadajuće po vrednosti elementa odnosno vrednosti $k$ u upitima. Zatim idemo redom po sortiranom nizu i kada naiđemo na neki element $A[i]$, na poziciji $i$ u nizu $B$ postavimo jedinicu; kada naiđemo na upit $(l,r,k)$, samo odredimo broj (ili zbir) svih elemenata u nizu $B$ na pozicijama od $l$ do $r$ jer su u tom trenutku dodati samo elementi iz $A$ koji su veći ili jednaki $k$. Ovo se jednostavno radi segmentnim stablom u ukupnoj složenosti $O(M + N \log M)$.

U **Podzadatku 4** su vrednosti $c_i$ zaista dovoljno male da se njima može direktno indeksirati niz $A$ (tj. ovde je $M \leq 10^6$) a slučajevi se jednakim $c_i$-ovima se rešavaju malom modifikacijom algoritma. Kada su vrednosti $c_i$ velike (npr. do $10^9$) treba koristiti *implicitno segmentno stablo* ili, jednostavnije, kompresovati koordinate na početku, što daje algoritam složenosti $O(N \log MaxVal)$ ili $O(N \log N)$ koji rešava **sve podzadatke**. 

Alternativni pristup (za rešavanje problema na koji smo sveli originalni problem) je korišćenje takozvane $Sqrt$-dekompozicije gde delimo niz na $\sqrt{N}$ delova veličine $\sqrt{N}$ i za svaki od njih pamtimo sortirani niz elemenata iz tog dela. Kada dođe upit $(l,r,k)$, za najviše dva dela u kojima su krajevi upita odradimo pretragu ručno a za ostalih $O(\sqrt{N})$ delova odradimo binarnu pretragu nad odgovarajućim nizom. Ovo daje algoritam složenosti $O(N\sqrt{N}\log N)$ koji bi, uz pristojnu implementaciju, takođe trebalo da osvoji sve poene. Napomenimo da ovaj pristup u istoj složenosti rešava varijantu problema u kome se zahteva da se na upite odgovara u zadatom redosledu (*online*) i gde su dozvoljeni upiti koji modifikuju pojedinačne elemente (inače, ova teža varijanta problema se može rešiti i u složenosti $O(N \log^2 N)$).

``` cpp title="04_konjugacija.cpp" linenums="1"
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX_N = 150000;
const int TREE_SIZE = (1 << 19);

struct point
{
	int type; // 1 - left query, 2 - value, 3 - right query
	int ind;
	int position;

	point(int t, int i, int p)
	{
		type = t; ind = i; position = p;
	}
};

struct point2
{
	int type; // 1 - query, 2 - array element
	int val;
	int ind;

	point2(int t, int v, int i)
	{
		type = t; val = v; ind = i;
	}
};

struct query
{
	int l, r;
	int val;
};

bool cmp(const point& A, const point& B)
{
	if (A.position != B.position)
		return (A.position < B.position);
	return (A.type < B.type); 
}

bool cmp2(const point2& A, const point2& B)
{
	if (A.val != B.val)
		return (A.val > B.val);
	return (A.type > B.type);
}

struct SegmentTree
{
	int sum[TREE_SIZE];

	void init()
	{
		for (int i = 0; i < TREE_SIZE; i++) sum[i] = 0;
	}

	// add 1 at position pos
	void add(int pos)
	{
		pos = pos + (TREE_SIZE >> 1) - 1;
		while (pos > 0)
		{
			sum[pos] = sum[pos] + 1;
			pos = (pos >> 1);
		}
	}

	// calculate sum[l..r]
	long long calc(int node, int node_L, int node_R, int l, int r)
	{
		if (node_R < l || node_L > r)
			return 0;
		if (l <= node_L && node_R <= r)
			return (sum[node]);

		int node_M = (node_L + node_R) >> 1;
		return calc((node << 1), node_L, node_M, l, r) + calc((node << 1) + 1, node_M + 1, node_R, l, r);
	}
};

int N;
long long sol;
int l[MAX_N + 10], r[MAX_N + 10];

vector<point> points;
vector<point2> points2;
int A[MAX_N + 10];
query Q[MAX_N + 10];
SegmentTree tree;

int main()
{
	scanf("%d", &N);
	sol = 0LL;

	for (int i = 1; i <= N; i++)
	{	// dupliramo koordinate da bi centar bio ceo broj
		scanf("%d%d", &l[i], &r[i]);
		int c = l[i] + r[i];
		l[i] = 2 * l[i];
		r[i] = 2 * r[i];
		points.push_back(point(1, i, l[i]));
		points.push_back(point(2, i, c));
		points.push_back(point(3, i, c - 1));
		Q[i].val = c;
	}

	// kompresujemo koordinate
	sort(points.begin(), points.end(), cmp);

	int currInd = 0;
	for (int i = 0; i < (int)points.size(); i++)
	{
		if (points[i].type == 2)
		{
			A[++currInd] = r[points[i].ind];
		}
		else
		{
			if (points[i].type == 1)
			{
				Q[points[i].ind].l = currInd + 1;
			}
			else
			{
				Q[points[i].ind].r = currInd;
			}
		}
	}

	// posebno racunamo kada se centri segmenata poklapaju
	int lastPos = -1, cnt = 0;
	for (int i = 0; i < (int)points.size(); i++)
	{
		if (points[i].type == 2)
		{
			if (points[i].position == lastPos)
				cnt++;
			else
			{
				cnt = 0;
				lastPos = points[i].position;
			}
			sol = sol + cnt;
		}
	}

	// Sada je problem ekvivalentan sa: dat je niz A[1..N] i N upita (l,r,v) sa znacenjem:
	// koliko ima elemenata u podnizu A[l..r] koji su veci ili jednaki od k?
	// Resenje je suma odgovora na sve upite. Ovo radimo offline sortiranjem upita
	// opadajuce po parametru k i dodavanjem odgovarajucih elemenata niza i brojanjem istih
	// koristeci segmentno stablo.

	for (int i = 1; i <= N; i++)
	{
		points2.push_back(point2(1, Q[i].val, i));
		points2.push_back(point2(2, A[i], i));
	}
	sort(points2.begin(), points2.end(), cmp2);
	tree.init();

	for (int i = 0; i < (int)points2.size(); i++)
	{
		if (points2[i].type == 1) // query
		{
			int left = Q[points2[i].ind].l;
			int right = Q[points2[i].ind].r;
			if (left <= right)
				sol = sol + tree.calc(1, 1, (TREE_SIZE >> 1), left, right);
		}
		if (points2[i].type == 2) // add element
		{
			tree.add(points2[i].ind);
		}
	}

	printf("%lld\n", sol);

	return 0;
}
```
