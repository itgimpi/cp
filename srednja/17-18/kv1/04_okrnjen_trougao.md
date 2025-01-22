---
hide:
  - toc
---

# 4 - Okrnjen trougao

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Dok je prenosio veliki stakleni trougao Cimi je za trenutak izgubio ravnotežu te je treće teme trougla udarilo o pod (primetiti da kako Cimi ima samo dve ruke mogao je u jedinici vremena da drži samo $2$ temena velikog staklenog trougla). Od nekada velikog staklenog trougla ostao je jedan stakleni mnogougao koji je Cimiju ostao u rukama dok se ostatak stakla pri kontaktu sa tlom razbio u neupotrebljivo male komadiće.
Cimiju je ovaj događaj bio izuzetno zanimljiv i želi da o njemu razgovara sa ostalim radnicima ali razmišlja da malo izmeni priču kako bi umanjio štetu koju je napravio, koja se izražava u površini stakla koja je sada neupotrebljiva.
Pomozite Cimiju time što ćete mu za dati prost mnogougao (ne obavezno konveksan) reći kolika je minimalna razlika u površinama između njega i trougla koji ga sadrži a sa njim deli bar jednu stranicu.

## Opis ulaza
U prvoj liniji standardnog ulaza nalazi se ceo broj $n$ koji predstavlja broj temena mnogougla.
U narednih $n$ linija standardnog ulaza nalaze se po dva cela broja $x_i, y_i$ koji predstavljaju koordinate temena mnogougla. (Uzastupna temena kao i prvo i poslednje dele stranicu)

## Opis izlaza
U jedinom redu standardnog izlaza napisati realan broj koji predstavlja minimalnu razliku definisanu u tekstu zadatka.
Ukoliko ne postoji ni jedan trougao koji odgovara opisu ispisati $-1$.

## Primer 1
### Ulaz
```
4
2 0
0 2
0 5
5 0
```

### Izlaz
```
2
```

## Primer 2
### Ulaz
```
4
0 0
1 1
2 0
1 7
```

### Izlaz
```
1
```

## Objašnjenje primera

U $1$. primeru optimalno je odabrati trougao sa koordinatama temena $(0,0)$, $(5,0)$ i $(0,5)$.

U $2$. primeru optimalno je odabrati trougao sa koordinatama temena $(0,0)$, $(2,0)$ i $(1,7)$.

## Ograničenja

* $3 \leq n \leq 10^5$.
* $-10^9 \leq x_i, y_i \leq 10^9$.
* U 50% primera važi $n \leq 1000$.

## Napomena

Ukoliko ne postoji traženi trougao, vaš program mora ispisati ceo broj $-1$. U suprotnom, ako je vaš program ispisao broj $a$, a rešenje komisije je realan broj $b$, vaše rešenje se prihvata kao tačno pod uslovom da važi $\frac{|a-b|}{b} \leq 10^{-6}$ ili važi $|a-b| \leq 10^{-6}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Spasić | Ivan Stošić i Nikola Spasić | Nikola Spasić | Andrej Ivašković |

Posmatrajmo neki trougao $T$ koji zadovoljava uslove zadatka.
Kako trougao $T$ sadrži dati mnogougao $M$, a $T$ je konveksan skup, važiće i $K \subseteq T$, gde je
$K$ konveksni omotač mnogougla $M$, jer je $K$ po definiciji najmanji konveksan skup koji
sadrži $M$. Dakle, u zadatku se traži da za dati mnogougao nađemo trougao najmanje površine
koji sadrži njegov konveksni omotač, sa dodatnim ograničenjem da neka stranica trougla bude
jednaka nekoj stranici datog mnogougla, neka je to stranica $BC$.

Temena $B, C$ moraju biti susedna temena u konveksnom omotaču, jer se u suprotom stranica trougla nalazi u strogoj unutrašnjosti konveksnog omotača pa ga trougao ne može sadržati.
Iz prethodno rečenog proizilazi da konveksni omotač i trougao imaju zajedničku stranicu.
Posmatrajmo sada neku stranicu $BC$ konveksnog omotača. Pretpostavićemo da naš trougao baš
tu stranicu deli sa $K$. Kako nam treba trougao minimalne površine njegove preostale stranice moraju imati isti pravac kao i stranice koje su susedne stranici $BC$, neka su to stranice $AB, CD$.
Stoga za svaku stranicu konveksnog omotača treba proveriti da li se produžeci susednih strana $AB, CD$ seku sa odgovarajuće strane i da li je stranica $BC$ konveksnog omotača ujedno i stranica mnogougla, što nam je dovoljno da zaključimo da postoji trougao sa odgovarajućim svojstvima. Zatim, nalazimo presek pravih $E = AB \cap CD$ i to je treća tačka našeg trougla. Sada znamo sva temena trougla, odredimo površinu a zatim i razliku površina između njega i početnog mnogougla.

## Smernice za algoritam

Zbog načina na koji su data temena mnogougla možemo u linearnom vremenu naći konveksni omotač. (videti [članak na Vikipediji](https://en.wikipedia.org/wiki/Convex_hull_algorithms)).
Površina trougla kome znamo koordinate može se dobiti kao polovina intenziteta vektorskog proizvoda dve njegove stranice (odnosno odgovarajućih vektora).
Označena površina nekonveksnog mnogougla može se naći kao zbir označenih površina proizvoljnog razbijanja tog mnogougla na trouglove - videti [link](https://web.archive.org/web/20100405070507/http://valis.cs.uiuc.edu/~sariel/research/CG/compgeom/msg00831.html).
Dalje, potrebno je naći površinu trougla $BCE$ gde je $E$ presek pravih $AB$ i $CD$. U teoriji, ovo se može uraditi nalaženjem jednačina te dve prave i rešavanjem sistema od dve jednačine sa dve nepoznate, a zatim primenom gore pomenute formule za površinu trougla. Međutim, problem nastaje zbog upotrebe tipa *double* za predstavljanje koeficijenata i rešenja ove jednačine. Srećom, postoji daleko jednostavniji način za nalaženje površine trougla $BCE$. Važi sledeća jednakost: $P(BCE) = \frac{P(ABC) P(BCD)}{P(BCF)}$, gde je $F$ tačka dobijena pomeranjem tačke $D$ za vektor $CB$, što se može relativno lako dokazati alatima elementarne geometrije. 

``` cpp title="04_okrnjen_trougao.cpp" linenums="1"
#include <cstdio>
#include <algorithm>
#include <set>
#include <iostream>
using namespace std;

const int MAXN = 200050;

typedef long long ll;
typedef double real_t;

struct pt {
	ll x, y;

	pt operator- (const pt& other) const {
		return {x - other.x, y - other.y};
	}

	bool operator< (const pt& other) const {
		return x < other.x || (x == other.x && y < other.y);
	}
};

ll det(pt a, pt b) {
	return a.x * b.y - b.x * a.y;
}

ll det(pt a, pt b, pt c) {
	return det(a-c, b-c);
}

set<pair<pt, pt>> s;

int n;
pt a[MAXN], h[MAXN];
int n1, n2, m;

void scan(int dir, pt* b, int& num) {
	int s = dir > 0 ? 0 : n-1;
	int e = dir > 0 ? n : -1;

	num = 0;

	for (int i=s; i!=e; i+=dir) {
		while (num >= 2 && det(b[num-2], b[num-1], a[i]) <= 0) {
			num--;
		}
		b[num++] = a[i];
	}

	num--;
}

real_t sol = 0.0;
bool sol_found = false;

void process_sol(pt a, pt b, pt c, pt d, ll cross_det) {
	// naci povrsinu trougla cije su dve tacke b, c
	// a treca nastala presekom polupravih b->a i c->d
	// 
	real_t area = det(a, b, c);
	area *= det(b, c, d);
	area /= cross_det;
	area /= 2;

	if (area < 0) {
		area *= -1;
	}

	if (!sol_found || area < sol) {
		sol_found = true;
		sol = area;
	}
}

int main() {
	scanf("%d", &n);
	for (int i=0; i<n; i++) {
		scanf("%lld%lld", &a[i].x, &a[i].y);
	}

	a[n] = a[0];
	real_t poly_area = 0.0;
	for (int i=0; i<n; i++) {
		s.insert({a[i], a[i+1]});
		poly_area += det(a[i], a[i+1]);
	}

	poly_area /= 2;

	if (poly_area < 0) {
		poly_area *= -1;
	}

	sort(a, a+n);
	scan(+1, h, n1);
	scan(-1, h+n1, n2);
	m = n1 + n2;

	h[m] = h[0];
	h[m+1] = h[1];
	h[m+2] = h[2];
	
	for (int i=0; i<m; i++) {
		pt a = h[i];
		pt b = h[i+1];
		pt c = h[i+2];
		pt d = h[i+3];

		// Ne nalazimo duz u skupu originalnih duzi
		if (s.count({b, c}) + s.count({c, b}) == 0) {
			continue;
		}

		// proverimo da li je zbir spoljnjih uglova abc i bcd > 180
		// ako jeste imamo resenje

		ll cross_det = det(b-a, d-c);

		if (cross_det < 0) {
			// imamo levo skretanje
			process_sol(a, b, c, d, cross_det);
		}
	}

	// fprintf(stderr, "%.9f\n", poly_area);
	// fprintf(stderr, "%.9f\n", sol);

	// odstampaj povrsinu
	if (sol_found) {
		cout.precision(20);
		cout << fixed << (sol - poly_area) * 1.000002 << '\n';
	} else {
		cout << "-1\n";
	}
}

```
