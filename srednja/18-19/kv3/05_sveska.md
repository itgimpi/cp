---
hide:
  - toc
---

# 5 - Sveska

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Nakon što je saznao da se porodica Vatrenić odselila iz Niša, gospodin Blažić može da prestane da brine o svojim optičkim kablovima i može da se posveti svojoj omiljenoj igri sa brojevima. On je na poklon dobio svesku sa $N$ prirodnih brojeva, i svakog od narednih $Q$ dana planira da uradi jednu od dve stvari:

1. Da zameni $p$-ti broj u svesci (tj. $a_p$) brojem $x$.
2. Da za neka dva broja $l, r$ uzme brojeve $a_l, a_{l+1}, \ldots, a_r$ i sa njima igra sledeću igru:

Prvo Blažić briše tablu a zatim zapisuje brojeve $a_l, a_{l+1}, \ldots, a_r$ na tu tablu. Zatim, ako je na tabli jedan od zapisanih brojeva broj $x$, on u jednom potezu može da napiše na tablu broj $2x$. Može da napiše i broj $\frac x 2$ pod uslovom da je $x$ deljivo sa $2$. Takođe, ako su na tabli napisani **različiti** brojevi $x, y$, on može da napiše broj $x \text{ xor } y$ (za definiciju operacije $\text{ xor }$ videti napomenu). Pritom, prethodno zapisani brojevi se ne brišu. Vaš zadatak je da, svaki put kada gospodin Blažić igra igru, otkrijete koji je najmanji prirodan broj koji može biti zapisan na tabli nakon konačno mnogo poteza.

## Opis ulaza

Prva linija standardnog ulaza sadrži jedan prirodan broj $N$ - broj brojeva u svesci. Naredna linija sadrži $N$ prirodnih brojeva $a_1, a_2 \ldots, a_N$, brojeve u svesci. Naredna linija sadrži jedan prirodan broj $Q$ - broj dana. Zatim, $j$-ta od narednih $Q$ linija počinje brojem $t_j$ - tipom akcije koju će gospodin Blažić preduzeti $j$-tog dana. Ukoliko je $t_j = 1$, slede dva prirodna broja $p_j, x_j$, koji označavaju da će Blažić $p_j$-ti broj u svesci zameniti brojem $x_j$. Ukoliko je $t_j = 2$, slede dva prirodna broja $l_j, r_j$ i to znači da će tog dana gospodin Blažić igrati igru počevši od trenutnih vrednosti brojeva $a_{l_j}, a_{l_j + 1}, \ldots, a_{r_j}$.

## Opis izlaza

Za svaki dan kada je $t_j = 2$ u posebnu liniju standardnog izlaza ispisati jedan prirodan broj - najmanji moguć broj koji se može dobiti na tabli nakon konačno mnogo poteza ako se igra sa brojevima iz segmenta $[l_j, t_j]$.

## Primer 1

### Ulaz

~~~
3
3 5 15
3
2 1 3
1 2 11
2 1 2
~~~

### Izlaz

~~~
3
1
~~~

### Objašnjenje primera

Kada gospodin Blažić prvi put igra igru, igra počinje sa brojevima $[3, 5, 15]$. Neki od brojeva koje Blažić može da napiše na tabli su $6 = 3 \text{ xor } 5$, $30 = 2 \cdot 15$, ali, ne postoji način da zapiše broj manji od $3$. Zatim, Blažić zameni broj $a_2 = 5$ brojem $11$. Narednog dana on igra igru sa brojevima $[3, 11]$. On može dobiti broj $1$ na sledeći način: Prvo napravi $8 = 3 \text{ xor } 11$ a zatim deljenjem sa dva dobija redom brojeve $4, 2, 1$.

### Ograničenja

U svim test primerima važi: $N, Q \leq 100000$, $0 < a_i, x_j < 2^{62}$, $t_j \in \{1, 2\}$, $1 \leq l_j \leq r_j \leq N$, $1 \leq p_j \leq N$, za svako $1 \leq i \leq N, 1 \leq j \leq Q$.

* U test primerima vrednim 16 poena: $N, Q \leq 100, a_i, x_j \leq 7$.
* U test primerima vrednim 28 poena: $N, Q \leq 500$.
* U test primerima vrednim 56 poena: Nema dodatnih ograničenja.

### Napomena

Operator $\text{ xor }$ (ekskluzivna disjunkcija) u Pascal-u je označen sa `xor`, dok u C++ ga zapisujemo pomoću simbola `^`. Ova operacija $x \text{ xor } y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način: prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots, b_k$. Zatim se za svaku poziciju $i \in \{1, \ldots, k\}$ računa $c_i$ pomoću sledećih pravila:

- Za $a_i=0, b_i=0$ važi $c_i=0$
- Za $a_i=0, b_i=1$ važi $c_i=1$
- Za $a_i=1, b_i=0$ važi $c_i=1$
- Za $a_i=1, b_i=1$ važi $c_i=0$

Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \text{ xor } y$.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Slobodan Mitrović | Slobodan Mitrović |

## Analiza


Ukratko, rešenje zadatka će izgledati ovako. Koristićemo segmentno stablo da odgovorimo na upite. Listovi u segmentnom stablu će biti jednaki nizu $a$. Čvor u stablu koji je otac listova $a_i, \ldots, a_j$ će sadržati najmanji broj koji može biti zapisan na tabli nakon konačno mnogo poteza igre sa brojevima $a_i, \ldots, a_j$. Ovaj pristup nameće dva glavna pitanja:
- Zašto je za svaki čvor dovoljno čuvati samo najmanji broj koji se može dobiti igrajući se njegovim sinovima?
- Ako je čvor $v$ otac čvorova $L$ i $R$, kako iskombinovati vrednosti sačuvane u $L$ i $R$ da se dobije vrednost za čvor $v$?

Da bismo odgovorili na ova pitanja, posmatraćemo ovaj problem kao zadatak sa polinomima nad $\mathbb{Z}_2$.

### Polinomi nad $\mathbb{Z}_2$ umesto brojeva

Za broj $a$ definišemo polinom $P_a(x)$ nad $\mathbb{Z}_2$ na sledeći način: $P_a(x)$ sadrži $x^i$ akko je $i$-ti bit broja $a$ jednak $1$. Primetimo da ako $P_a(x)$ sadrži $x^i$, onda je koeficijent ispred $x^i$ tačno $1$. Na primer, $P_5(x) = x^2 + 1$, jer u binarnom zapisu broj $5$ je jednak $101$.

Tada broj $a\text{ xor }b$ odgovara polinomu $P_a(x) + P_b(x)$. Broj $2 \cdot a$ odgovara polinomu $x \cdot P_a(x)$, i broj $\frac a 2$ odgovara polinomu $\frac {P_a(x)} x$ (pod uslovom da je $a$ deljivo sa $2$).

### Zadatak bez operacije deljenja

Prvo ćemo posmatrati zadatak u slučaju da opcija deljenja nije na raspolaganju, tj. možemo da koristimo samo xor i množenje (ili, u svetu polinoma, ako koristimo sabiranje i množenje sa $x$).

Primetimo da za bilo koji polinom $Q(x)$ nad $\mathbb{Z}_2$, ako počnemo od polinoma $P_a(x)$ možemo dobiti polinom $P_a(x) \cdot Q(x)$ primenom samo ove dve operacije. Na primer, da bismo dobili $P_a(x) \cdot Q(x)$ počevši od $P_a(x)$, prvo za svako $x^i$ koje ima pozitivan koeficijent u $Q(x)$ napravimo polinom $x^i \cdot P_a(x)$. Potom saberemo sve te polinome.

Neka je $A$ skup polinoma. Iz Bezuovog stava sada sledi da se primenom ove dve operacije na skup polinoma iz $A$ može dobiti $NZD(A)$ (najveći zajednički delilac polinoma iz $A$). Pošto se sabiranjem dva (različita) polinoma koji su deljivi sa $NZD(A)$ dobija polinom deljiv sa $NZD(A)$ (koji je jednak ili veći od $NZD(A)$), i takođe pošto se množenjem polinoma sa $x$ dobija polinom deljiv sa $NZD(A)$, to znači da je $NZD(A)$ najmanji polinom koji možemo dobiti primenom ove dve operacije.

Takođe, ako imamo dva skupa polinoma $A$ i $B$, tada važi $NZD(NZD(A), NZD(B)) = NZD(A \cup B)$. Ovo opravdava pristup opisan na početku u kojem, da bismo izračunali najmanji zapisan broj u nekom intervalu (za koji smo u slučaju da koristimo samo dve operacije zaključili da odgovara $NZD$ vrednosti odgovarajućih polinoma), smo koristili segmentno stablo.

### Zadatak sa operacijom deljenja
Dosadašnji opis rešenja ovog zadatka je podrazumevao da ne koristimo operaciju deljenja sa $x$. Pošto ova operacija praktično kaže da krajnji polinom ne treba da bude deljiv sa $x$ (inače nije najmanji), deljenje možemo primeniti tek na kraju ili čak u svakom koraku tokom primene $NZD$ operacija. $NZD$ polinomi koje dobijamo u među-koracima bi se u zavisnosti od primene deljenja razlikovali samo u deljivosti sa $x$, što je nebitno za krajnji rezultat. Dakle, deljenje sa $x$ je dovoljno primeniti samo na krajnji rezultat i ignorisati do tada.

## Smernice za algoritam


Implementacija bilo koja od dva upita u segmentom stablu zahteva $O(\log{n})$ $NZD$ operacija.

Da bismo našli $NZD$ dva polinoma $P_a(x)$ i $P_b(x)$ možemo da iskoristimo neki od standardnih algoritama, na primer, Euklidov algoritam. Taj ceo proces u našem slučaju, gde takođe imamo operaciju deljenja, može da se uradi na jednostavan način. Naime, počnemo od $a$ i $b$, i sve dok su oba različita od $0$ radimo sledeće. Neka je $a \leq b$, i neka je $c$ broj dobijen od $a$ množenjem ("shift"-ovanjem) sa $2$ sve dok se $c$ i $b$ razlikuju po dužini u binarnom zapisu. Potom $b$ zamenimo sa $b\text{ xor }c$, i nastavimo proces. Kad jedan od brojeva $a$ ili $b$ postane $0$, vratimo ne-nula među njima na koji je primenjeno deljenje sa $2$ dok je to moguće.

``` cpp title="05_sveska.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll bit_remove_tz(ll x) {
	return x >> __builtin_ctzll(x);
}

ll bit_gcd(ll x, ll y) { // x, y su neparni ili 0
	if (!x) return y;
	if (!y) return x;
	while (1) {
		x = bit_remove_tz(x);
		y = bit_remove_tz(y);
		if (x == y)
			return x;
		auto a = __builtin_clzll(x);
		auto b = __builtin_clzll(y);
		ll t = x;
		x = (x << max(a-b, 0)) ^ y;
		y = t;
	}
}

const int MAXN = 131072;
ll a[2 * MAXN];

ll solve(int l, int r, int x, int xl, int xr) {
	if (r < xl || xr < l)
		return 0;
	if (l <= xl && xr <= r)
		return a[x];
	int xm = (xl + xr) >> 1;
	return bit_gcd(solve(l, r, 2*x, xl, xm), solve(l, r, 2*x+1, xm+1, xr));
}

void change(int p, ll x) {
	p += MAXN;
	a[p] = x;
	while (p > 1) {
		p >>= 1;
		a[p] = bit_gcd(a[2*p], a[2*p+1]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;
	for (int i=1; i<=n; i++) {
		ll x;
		cin >> x;
		change(i, bit_remove_tz(x));
	}

	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 2) {
			int l, r;
			cin >> l >> r;
			cout << solve(l, r, 1, 0, MAXN-1) << '\n';
		} else {
			int p;
			ll x;
			cin >> p >> x;
			change(p, bit_remove_tz(x));
		}
	}
}
```
