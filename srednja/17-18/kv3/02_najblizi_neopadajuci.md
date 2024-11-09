---
hide:
  - toc
---

# 2 - Najbliži neopadajući

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 64MB |

Danici je na zimskom raspustu postalo malo dosadno pa je obećala da će za svaki prirodan broj $N$ koji joj drugari pošalju, pronaći njemu najbliži ceo broj čije su cifre gledane s leva ka desno poređane u neopadajućem redosledu, a ako ima više takvih brojeva, pronaći će ih sve i ispisati, očekivano, u neopadajućem redosledu.

> Za $m$-tocifren prirodan broj $N$ u dekadnom zapisu $N=c_{m-1}\cdot10^{m-1}+c_{m-2}\cdot10^{m-2}+\dots+c_{2}\cdot10^{2}+c_{1}\cdot10^{1}+c_{0}\cdot10^{0}$ kažemo da je neopadajući ako mu broj jedinica $c_0$ nije manji od broja desetica $c_1$, broj desetica $c_1$ nije manji od broja stotina $c_2$, broj stotina $c_2$ nije manji od broja hiljada $c_3$, itd. Drugim rečima prirodan broj je neopadajući ako i samo ako za svaki par susednih cifara $c_{i}$ i $c_{i-1}$ važi $c_{i} \le c_{i-1}$, pri čemu $0<i<m$ i $c_{i}\in\{0,1,2,3,4,5,6,7,8,9\}$.

Kako je i njenim drugarima ta igra postala zanimljiva, nakon početnog zagrevanja sa dvocifrenim i trocifrenim, počeli su da joj šalju sve veće i veće brojeve. Pomozite maloj Danici da uprkos tome održi svoje obećanje.

## Opis ulaza
U jedinom redu standardnog ulaza nalazi se zadati prirodan broj $N$ u dekadnom zapisu.

## Opis izlaza
U jednom redu standardnog izlaza ispisati najbliži neopadajući ceo broj, odnosno sve takve brojeve odvojene razmakom ukoliko ih ima više od jednog.

## Primer 1
### Ulaz
```
53
```

### Izlaz
```
55
```

## Primer 2
### Ulaz
```
82
```

### Izlaz
```
79
```

## Primer 3
### Ulaz
```
105
```

### Izlaz
```
99 111
```

## Primer 4
### Ulaz
```
357
```

### Izlaz
```
357
```

## Objašnjenje primera
Najbliži neopadajući broj može biti veći od zadatog broja. Najbliži neopadajući broj može biti i manji od zadatog broja. Postoji mogućnost i da više neopadajućih brojeva budu podjednako blizu zadatom broju. Najzad, najbliži neopadajući broj može biti i sam zadati broj.

## Ograničenja

* $1 \le N \le 10^{18}$.

Test primeri su podeljeni u četiri disjunktne grupe:

* U $15\%$ test primera važi ograničenje $1 \le N \le 10^{2}$.
* U $30\%$ test primera važi ograničenje $1 \le N \le 10^{3}$.
* U $50\%$ test primera važi ograničenje $1 \le N \le 10^{9}$.
* U ostalim test primerima nema dodatnih ograničenja.

## Napomena
Zadati i ispisani brojevi su uvek u dekadnom zapisu bez vodećih nula.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Vladimir Milovanović | Vladimir Milovanović | Vladimir Milovanović | Ivan Stošić |

Potrebno je primetiti da provera da li je određeni broj neopadajući ne zavisi linearno od vrednosti tog broja, već od broja njegovih cifara koji je za prirodne brojeve u dekadnom zapisu proporcionalan $\log_{10}N$.

Idejno najjednostavnije rešenje najverovatnije je da se krene od zadatog broja $N$ i redom proverava da li je neopadajući ili ne, tako što će se najpre ispitati sam zadati broj $N$, zatim $N\pm1$, pa $N\pm2$ i tako dalje.

Međutim, svakako elegantnije rešenje je da se za uneti broj $N$ na efikasan način pronađe najbliži neopadajući broj veći i najbliži neopadajući broj manji od zadatog broja, a potom vrati onaj koji se nalazi na manjoj razlici od $N$, odnosno da se ispišu oba, ukoliko se ispostavi da su podjednako udaljena.

Da bi se odredio najbliži neopadajući broj veći od zadatog broja, najpre u nizu cifara unetog broja počevši od cifre najvećeg značaja treba pronaći prvo mesto gde niz postaje opadajući, odnosno dve susedne cifre za koje važi $c_{i} > c_{i-1}$, a zatim sve cifre u opsegu od $c_{0}$ do $c_{i-1}$ promeniti u $c_{i}$. Tako će na primer broj $N=12321$ biti prepravljen u $12333$, a samim tim i određen najbliži neopadajući broj veći od zadatog broja.

Slično tome, kako bi se odredio najbliži neopadajući broj manji od zadatog broja, prvo se na isti način pronađe monotono neopadajući prefiks broja $N$, potom $c_{i}$ umanji za jedan, a cifre u opsegu od $c_{0}$ do $c_{i-1}$ promene u $9$. Za gornji primer $N=12321$ to znači da će najbliži neopadajući broj manji od zadatog broja biti $12299$. Treba obratiti pažnju da dekrementiranje poslednje cifre prefiksa može prouzrokovati promenu njegove monotonosti, kao na primer kod $N=12345554321$, pa najbliži neopadajući broj neće biti $12345549999$, ni $12345499999$, već $12344999999$. Uzimajući i taj slučaj u obzir dolazi se do najbližeg neopadajućeg broja koji je manji od zadatog.

Uz napomenu da je vremenska složenost pronalaska najbližeg neopadajućeg broja linearna po dužini niza cifara, odnosno logaritamska po vrednosti zadatog broja $N$, preostaje samo da se proveri koji je od dva neopadajuća broja bliži, i da se isti ispiše, čime je zadatak urađen u $\mathcal{O}(\log{N})$ vremenskoj složenosti.

``` cpp title="02_najblizi_neopadajuci.cpp" linenums="1"
#include <string>
#include <iostream>
using namespace std;

typedef long long ll;

ll od_stringa(string s) {
	ll x = 0;
	for (char c : s) {
		x = 10 * x + (c - '0');
	}
	return x;
}

string veci_jednak(string s) {
	int i = 1;
	while (i < (int)s.size() && s[i] >= s[i-1]) {
		i++;
	}
	for (int j=i; j<(int)s.size(); j++) {
		s[j] = s[i-1];
	}
	return s;
}

string manji_jednak(string s) {
	int i = 1;
	while (i < (int)s.size() && s[i] >= s[i-1]) {
		i++;
	}
	while (0 < i && i < (int)s.size() && s[i] < s[i-1]) {
		s[i-1]--;
		i--;
	}
	for (int j=i+1; j<(int)s.size(); j++) {
		s[j] = '9';
	}
	return s;
}

int main() {
	ll n;
	cin >> n;
	ll l = od_stringa(manji_jednak(to_string(n)));
	ll h = od_stringa(veci_jednak(to_string(n)));

	ll dl = n-l;
	ll dh = h-n;

	if (dl < dh) {
		cout << l << '\n';
	} else if (dh < dl) {
		cout << h << '\n';
	} else if (l == h) {
		cout << l << '\n';
	} else {
		cout << l << ' ' << h << '\n';
	}
}
```
