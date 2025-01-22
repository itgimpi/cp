---
hide:
  - toc
---

# 4 - Požar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

U jednom predgrađu Niša nalazi se velika, takoreći beskonačna njiva u obliku dvodimenzione ravni. Bogata porodica Vatrenić se ne podnosi sa drugom bogatom porodicom Blažić. Porodica Blažić poseduje $N$ optičkih kablova, $i$-ti kabl je u obliku beskonačne prave koja prolazi kroz tačke $(x_i, y_i)$ i $(u_i, v_i)$. Vatrenići su poznati po paljenju njiva, te je vaš zadatak da za svaki od datih $Q$ scenarija širenja požara odredite koliko kablova će se oštetiti. Scenario sa rednim brojem $j$ se odnosi na jedan krug $K_j$ sa centrom u tački $(a_j, b_j)$ i radijusom $r_j$, krug do kojeg će se raširiti požar u tom scenariju. Pritom, za ove krugove važi: $K_j \subset K_{j+1}$ za svako $1 \leq j < Q$, drugim rečima, $j$-ti krug je u potpunosti sadržan u $(j+1)$-om krugu, takođe, granice nikoja dva kruga se ne dodiruju. Kabl koji je u obliku prave $p$ će se oštetiti u scenariju $C$ ako i samo ako je skup $p \cap C$ neprazan, odnosno, ako se krug i prava seku u bar jednoj tački. Kako je vatra nepredvidiva pojava, u svakom scenariju **se garantuje da se rešenje (broj oštećenih kablova) neće promeniti čak ni ako se poluprečnik kruga $r$ poveća ili smanji za $r \cdot 10^{-12}$.**

## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se prirodan broj $N$ - broj kablova koje poseduje porodica Blažić. U narednih $N$ linija nalaze se po četiri cela broja, $x_i, y_i, u_i, v_i$, koordinate dve tačke kroz koje prolazi $i$-ti kabl. Naredna linija sadrži jedan prirodan broj $Q$, broj scenarija. U narednih $Q$ redova nalaze se po tri cela broja $a_i, b_i, r_i$, koordinate centra kruga i poluprečnik kruga kod $i$-tog scenarija.

## Opis izlaza

Za svaki od $Q$ scenarija ispisati po jedan ceo broj - u $j$-ti red ispisati broj kablova koji će se oštetiti u scenariju pod rednim brojem $j$.

## Primer 1

### Ulaz

~~~
4
4 -3 -5 1
6 -2 -4 10
6 11 6 8
6 8 6 11
3
0 5 1
1 4 3
3 5 6
~~~

### Izlaz

~~~
1
1
3
~~~

### Objašnjenje primera

U prva dva scenarija će se oštetiti samo jedan kabl (kabl sa rednim brojem $2$), dok će se u trećem scenariju pored ovog oštetiti i kablovi sa rednim brojevima $3, 4$ (koji su podudarni).

<img src="https://petljamediastorage.blob.core.windows.net/competitions/uNQdMIo.png" />

## Ograničenja

U svim test primerima važi:

* $-10^8 \leq x_i, y_i, u_i, v_i, a_j, b_j \leq 10^8$ za svako $1 \leq i \leq N, 1 \leq j \leq Q$ 
* $1 \leq r_j \leq 10^8$ za svako $1 \leq j \leq Q$
* $N, Q \leq 100000$.
* Za svako $1 \leq i \leq N$ važi da se tačke $(x_i, y_i)$ i $(u_i, v_i)$ ne podudaraju.

Test primeri su podeljeni u sledeće grupe:

* U test primerima vrednim 20 poena: $N, Q \leq 500$.
* U test primerima vrednim 20 poena: $a_i = a_j, b_i = b_j$ za svako $1 \leq i, j \leq Q$.
* U test primerima vrednim 20 poena: $y_i = v_i$ za svako $1 \leq i \leq N$.
* U test primerima vrednim 40 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Ivan Stošić | Aleksa Milisavljević |

## Analiza

Umesto da posmatramo problem "iz perspektive kruga", nađimo za svaku pravu skup krugova imaju presek sa njom. Kako je $i$-ti krug sadržan u narednom, ako prava seče $i$-ti krug, tada sigurno seče i svaki naredni, što znači da ovaj skup krugova čini segment, pritom, sufiks, niza krugova. Nađimo, dakle, za svaku pravu najmanji krug koji se seče sa njom. Iz gore izloženog zaključujemo da se ovaj krug može naći binarnom pretragom po krugovima - ako se neki krug ne seče sa pravom, nastavljamo pretragu po većim krugovima, inače, pamtimo rešenje i tražimo među manjim krugovima. Nakon što smo našli indeks $j$ ovog najmanjeg kruga, u nizu rešenja $z$ treba brojevima $z_j, z_{j+1}, \ldots, z_n$ da dodamo $1$, što možemo uraditi tako što dodamo $1$ broju $z_j$ a nakon što obradimo sve prave izračunamo prefiksnu sumu niza $z$, koju štampamo. 

## Smernice za algoritam

Da bismo ispitali da li se prava određena dvema tačkama $A, B$ seče sa krugom radijusa $r$ sa centrom u tački $C$, najjednostavniji način je da nađemo udaljenost prave $AB$ do tačke $C$ i da taj broj uporedimo sa $r$. Izračunajmo dvostruku površinu trougla $ABC$ kao apsolutnu vrednost vektorskog proizvoda $2P = |CA \times CB|$ i dužinu duži $|AB|$. Kako je udaljenost prave $AB$ od $C$ zapravo visina trougla $h_C$, tu visinu možemo izračunati preko površine: $h_C = \frac{2P}{|AB|}$. Pritom, sve ove operacije se mogu pouzdano izračunati pomoću tipa `double` sa relativnom preciznošću $10^{-14}$ što je dovoljno dobro za ovaj zadatak.

``` cpp title="04_pozar.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

typedef ll niz[100005];

int n, q;
niz a, b, u, v, x, y, r, z;

ll det(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
	return ax*by + bx*cy + cx*ay - ay*bx - by*cx - cy*ax;
}

ll kv(ll x) {
	return x*x;
}

ll dist2(ll a, ll b, ll c, ll d) {
	return kv(a-c) + kv(b-d);
}

bool presek(ll u, ll v, ll x, ll y, ll a, ll b, ll r) {
	ld dc = abs(det(u, v, x, y, a, b)) / sqrt((ld)dist2(u, v, x, y));
	/*
	ld eps = 1.2e-12;
	ld err = abs((dc / r) - 1);
	if (err < eps) {
		cerr << "Upozorenje! Vrednosti su previse blizu! Resenje je nepouzdano!\n";
		exit(1);
	}
	*/
	return dc < r;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n;
	for (int i=0; i<n; i++)
		cin >> x[i] >> y[i] >> u[i] >> v[i];
	cin >> q;
	for (int j=0; j<q; j++)
		cin >> a[j] >> b[j] >> r[j];

	for (int i=0; i<n; i++) {
		int lo = 0, hi = q-1, o = q;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (presek(u[i], v[i], x[i], y[i], a[mid], b[mid], r[mid])) {
				o = mid;
				hi = mid - 1;
			} else {
				lo = mid + 1;
			}
		}
		z[o]++;
	}
	cerr << '\n';

	ll sol = 0;

	for (int i=0; i<q; i++)
		cout << (sol += z[i]) << '\n';
}
```
