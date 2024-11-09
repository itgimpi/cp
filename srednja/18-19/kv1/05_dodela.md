---
hide:
  - toc
---

# 5 - Dodela vrednosti

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 512MB |

Jaca je pametna maca i za vas ima veoma jednostavan zadatak. Ona će vam dati prirodne brojeve $N$ i $Q$, nakon čega vi treba da napravite niz $a = [1,2,\ldots,N]$ (niz se indeksira od $1$) i da izvršite $Q$ njenih naredbi. Svaka naredba ima jedan od sledeća dva oblika:

- $1$ $u$ $v$ $l$ - Za svako $i \in \{0,1,\ldots,l-1\}$ (tim redom), izvršiti naredbu dodele $a_{u+i} \leftarrow a_{v+i}$ ($a_{u+i}$ dobija vrednost koju u tom trenutku ima $a_{v+i}$)
- $2$ $x$ - Recite Jaci trenutnu vrednost $a_x$

## Opis ulaza

U prvoj liniji standardnog ulaza nalaze se prirodni brojevi $N$ - veličina niza i $Q$ - broj upita. Narednih $Q$ linija mogu biti oblika $1$ $u$ $v$ $l$ ili $2$ $x$. U prvom slučaju važi $u,v \geq 1$ i $u+l-1,v+l-1\leq N$, a u drugom $1 \leq x \leq N$.

## Opis izlaza

Za svaki upit tipa $2$ u poseban red standardnog izlaza ispisati traženi broj.

## Primer 1

### Ulaz

~~~
6 4
1 1 5 1
2 1
1 3 1 4
2 6
~~~

### Izlaz

~~~
5
2
~~~

## Objašnjenje primera

Nakon prve izmene niz će izgledati ovako: $[5,2,3,4,5,6]$, u drugom upitu Jaca nam traži da joj kažemo $a_1$, što iznosi $5$. Nakon druge izmene (treći upit) niz će izgledati ovako: $[5,2,5,2,5,2]$. U četvrtom upitu Jaca nas pita za $a_6$, što iznosi $2$.

## Ograničenja

- $N \leq 1.000.000, Q \leq 100.000$

Test primeri su podeljeni u 4 disjunktne grupe:

- U test primerima vrednim 10 poena: $N, Q \leq 5.000$
- U test primerima vrednim 30 poena: Svi upiti tipa $2$ se nalaze posle svih upita tipa $1$
- U test primerima vrednim 30 poena: U upitima tipa $1$ važi $|u-v| \geq l$
- U test primerima vrednim 30 poena: Nema dodatnih ograničenja

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Ivan Stošić | Vladimir Milenković |

Održavajmo u svakom trenutku graf sa sledećim osobinama:

- Postoje tri vrste čvorova, "unutrašnji", "listovi" i jedan specijalan "prazan" čvor. Unutrašnji čvorovi imaju tačno dve izlazne grane, koje ćemo zvati "levom" i "desnom". Listovi nemaju izlazne grane i čuvaju jednu celobrojnu vrednost, koju ćemo zvati "labela".
- Graf je "nepromenljiv", odnosno, nije moguće izmeniti osobine postojećih čvorova. Moguće je samo dodavati nove čvorove.
- Svaki čvor čuva veličinu iz njega dostižnog dela grafa. Za listove, ova veličina iznosi $1$. Za unutrašnje čvorove, ova veličina jednaka je zbiru veličina čvorova do kojih se stiže pomoću leve i desne grane. Za prazan čvor ova veličina je $0$.
- Analogno definišemo dostižni niz labela za neki čvor. Za listove, to je niz od jednog elementa - njegova labela. Za unutrašnje čvorove niz se dobija konkatenacijom nizova levog i desnog čvora. Za prazan čvor je prazan niz.

Pored grafa, održavajmo i pokazivač $R$ na čvor čiji će dostižni niz labela biti jednak trenutnoj vrednosti niza $a$. Upite tipa $2$ rešavamo veoma jednostavno, krećemo iz čvora $R$ i spuštamo se levo ili desno u zavisnosti od toga kom elementu niza želimo da pristupimo, sve dok ne dođemo do lista. 

Upite prvog tipa rešavamo pomoću sledećih operacija nad grafom:

- `seci(x, s)`, vraća dva pokazivača na čvorove, gde je prvi čvor takav da je njegov dostižni niz jednak prefiksu dostižnog niza za čvor $x$ dužine $s$, a dostižni niz drugog čvora je jednak ostatku dostižnog niza za čvor $x$.
- `spoji(x, y)` vraća čvor čiji je dostižni niz jednak konkatenaciji dostižnih nizova za čvorove $x$ i $y$. Ova operacija se može izvesti na dva načina o čemu će biti više reči kasnije.
- `pomnozi(x, k)` vraća čvor čiji je dostižni niz jednak konkatenaciji $k$ dostižnih nizova za čvor $x$. 

Naš cilj je da sve tri operacije rade brzo. Tačnije, sve tri operacije radiće u složenosti linearnoj po dubini grafa počev od datog čvora ili čvorova, zato će nama biti cilj da se ova dubina ne povećava previše u toku rada.

Slede skice mogućih realizacija ove tri operacije:

- `seci(x, s)`, ukoliko je $s$ manje od veličine levog čvora od $x$, pravimo kopiju $y$ čvora $x$ čiji levi čvor sečemo rekurzivno. Prvi čvor rezultata rekurzivnog poziva vratimo kao prvi čvor, dok drugi čvor rezultata rekurzivnog poziva zakačimo kao levi čvor čvora $y$ i kao drugi čvor vratimo upravo $y$. U suprotnom, analogno sečemo desni čvor.
- `spoji(x, y)`, nasumično izaberemo jedan od ta dva čvora (recimo da je to čvor $x$), napravimo njegovu kopiju $z$, rekurzivno spojimo desni čvor čvora $z$ i čvor $y$ i rezultat zakačimo kao desni čvor $z$, zatim vratimo $z$.
- `pomnozi(x, k)`, kako će važiti $k \leq n < 2^{20}$, napravimo čvorove $y_0, y_1, \ldots, y_{19}$, gde je $y_0$ kopija čvora $x$, a za $i > 0$ je $y_i$ čvor koji se dobija "prostim" (nerekurzivnim) spajanjem čvora $y_{i-1}$ sa samim sobom. Tačnije, čvoru $y_i$ će i leva i desna grana pokazivati na čvor $y_{i-1}$. Sada je jasno da je niz čvora $y_i$ jednak konkatenaciji $2^i$ nizova čvora $x$. Zatim samo izaberemo stepene dvojke u binarnom zapisu broja $k$ i ponovo prostim spajanjem napravimo rezultujući čvor, vodeći računa da spajamo od manjih ka većim stepenima.

Sada, zadatak rešavamo na sledeći način. Graf inicijalizujemo kao binarno stablo čiji listovi redom imaju labele od $1$ do $N$ i $R$ postavljamo za koren tog stabla. U većini slučajeva samo sečemo delove niza za čvor $R$ i sastavljamo ih u nekom drugom redosledu. Jedini nezgodan slučaj jeste taj kada je $u > v$ i $l > u-v$. Tada se jedno parče originalnog niza ciklično ponavlja određen broj puta, i tu nam je potrebna efikasna operacija `pomnozi`.

Jedna moguća optimizacija jeste da, kada broj čvorova prebaci neku unapred zadatu granicu (recimo par miliona), izračunamo ceo dostižan niz iz čvora $R$, obrišemo sve čvorove i "počnemo ispočetka" sa tim nizom.

Vremenska i memorijska složenost: $N + Q \log N$.

``` cpp title="05_dodela.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;

const int MAX_LOG = 20;
const int MAX_NODES = 10000000;
const int CRITICAL_NODES = 5000000;

bool odluka() {
	static unsigned x = 0;
	x += 1111111111;
	return x < 0x80000000u;
}

struct cvor {
	int l, r, s;
} a[MAX_NODES]; int z; // a[0] = {0, 0, 0}

int kopija(int c) {
	a[++z] = a[c];
	return z;
}

void fixs(int x) {
	if (a[x].l == -1)
		a[x].s = 1;
	else
		a[x].s = a[a[x].l].s + a[a[x].r].s;
}

pair<int, int> seci(int x, int s) {
	if (!x)
		return {0, 0};
	if (!s)
		return {0, x};
	if (a[x].l == -1)
		return {s ? x : 0, s ? 0 : x};
	int y = kopija(x), p = a[a[x].l].s;
	if (s <= p) {
		auto w = seci(a[y].l, s);
		a[y].l = w.second;
		fixs(y);
		return {w.first, y};
	} else {
		auto w = seci(a[y].r, s - p);
		a[y].r = w.first;
		fixs(y);
		return {y, w.second};
	}
}

int spoji(int x, int y) {
	if (!x) return y;
	if (!y) return x;
	if (a[x].l == -1 && a[y].l == -1) {
		int z = kopija(0);
		a[z] = {x, y, 2};
		return z;
	}
	bool levo = odluka();
	if (a[x].l == -1)
		levo = false;
	else if (a[y].l == -1)
		levo = true;
	if (levo) {
		int z = kopija(x);
		a[z].r = spoji(a[z].r, y);
		fixs(z);
		return z;
	} else {
		int z = kopija(y);
		a[z].l = spoji(x, a[z].l);
		fixs(z);
		return z;
	}
}

int trazi(int x, int s) {
	if (a[x].l == -1)
		return a[x].r;
	int p = a[a[x].l].s;
	if (s < p)
		return trazi(a[x].l, s);
	else
		return trazi(a[x].r, s-p);	
}

int spoji_spolja(int x, int y) {
	int z = kopija(0);
	a[z] = {x, y, a[x].s + a[y].s};
	return z;
}

int dupliraj(int x) {
	return spoji_spolja(x, x);
}

int pomnozi(int x, int k) {
	if (!k) return 0;
	int y[MAX_LOG];
	y[0] = x;
	for (int i=1; i<MAX_LOG; i++)
		y[i] = dupliraj(y[i-1]);
	int z = -2;
	for (int i=0; i<MAX_LOG; i++) {
		if (k & (1 << i)) {
			if (z == -2)
				z = y[i];
			else
				z = spoji_spolja(z, y[i]);
		}
	}
	return z;
}

int napravi(int l, int r, basic_string<int>& v) {
	if (l == r) {
		int z = kopija(0);
		a[z] = {-1, v[l], 1};
		return z;
	} else {
		int m = (l+r) >> 1;
		return spoji_spolja(napravi(l, m, v), napravi(m+1, r, v));
	}
}

void procitaj_rek(int x, basic_string<int>& v) {
	if (!x) return;
	if (a[x].l == -1) {
		v += a[x].r;
		return;
	}
	procitaj_rek(a[x].l, v);
	procitaj_rek(a[x].r, v);
}

void stampaj(int x) {
	basic_string<int> v;
	procitaj_rek(x, v);
	for (int x : v)
		cerr << x << ' ';
	cerr << '\n';
}

basic_string<int> seci(int x, basic_string<int> v) {
	basic_string<int> r;
	for (int s : v) {
		auto p = seci(x, s);
		r += p.first;
		x = p.second;
	}
	return r;
}

int spoji(basic_string<int> v) {
	int x = 0;
	for (int y : v)
		x = spoji(x, y);
	return x;
}

int osvezi(int x) {
	basic_string<int> v;
	procitaj_rek(x, v);
	memset(a, 0, (z + 1) * sizeof(cvor));
	z = 0;
	return napravi(0, v.size()-1, v);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;
	int x;
	{
		basic_string<int> a(n, 0);
		iota(a.begin(), a.end(), 1);
		x = napravi(0, n-1, a);
	}
	for (int _q=0; _q < q; _q++) {
		int t;
		cin >> t;
		if (t == 1) {
			int u, v, l;
			cin >> u >> v >> l;
			u--, v--;
			if (u < v) {
				if (v-u >= l) {
					auto p = seci(x, {u, l, v-u-l, l, n-v-l});
					x = spoji({p[0], p[3], p[2], p[3], p[4]});
				} else {
					auto p = seci(x, {u, v-u, u+l-v, v-u, n-v-l});
					x = spoji({p[0], p[2], p[3], p[3], p[4]});
				}
			} else if (u > v) {
				if (u-v >= l) {
					auto p = seci(x, {v, l, u-v-l, l, n-u-l});
					x = spoji({p[0], p[1], p[2], p[1], p[4]});
				} else {
					int kol = l / (u - v);
					int ost = l % (u - v);
					auto p = seci(x, {v, ost, u-v-ost, l, n-u-l});
					int ponovljeno = pomnozi(spoji(p[1], p[2]), 1 + kol);
					x = spoji({p[0], ponovljeno, p[2], p[4]});
				}
			}
		} else {
			int u;
			cin >> u;
			cout << trazi(x, u-1) << '\n';
		}
		if (z > CRITICAL_NODES)
			x = osvezi(x);
	}
}
```
