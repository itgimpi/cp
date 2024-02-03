---
hide:
  - toc
---

# A3 - Žetoni

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Buba u svom laptopu ima igricu koja sadrži beskonačnu tablu čije su vrste i kolone indeksirane prirodnim brojevima. U početku, kada se igrica pokrene, na polju $(1, 1)$ nalazi se jedan žeton. Svakog dana, kad nema šta drugo da radi, ona klikne na polje na kojem se nalazi bar jedan žeton, recimo, polje $(x, y)$, i nakon toga se jedan žeton skloni sa tog polja a po jedan žeton se dodaje na polja $(x+1, y)$ i $(x, y+1)$. Ali avaj! Zli kosmički zrak (po svojoj prirodi gama foton energije nekoliko desetina megaelektronvolti) je udario u ćeliju RAM memorije i time izbrisao sve žetone sa table.

Bubu je ovo jako potreslo pa je njen drug odlučio da joj pomogne. Oni su pronašli i skinuli izvorni kod igrice i pokrenuli je u _debug_ modu. U ovom modu igrač može kliknuti na bilo koje polje table i na to polje se dodaje jedan žeton. Ako se u nekom trenutku tabla nalazi u stanju do kojeg je moguće doći normalnim igranjem igre, Buba će uzviknuti "Stop!" a zatim će izdiktirati niz poteza koji bi pri normalnom igranju igre doveo tablu u to stanje.

Vaš zadatak je da pomognete Bubinom drugu da, za dati niz klikova u _debug_ modu predvidi u kom trenutku će ona uzviknuti "Stop!", kao i koji niz poteza bi ona tada mogla da izdiktira.

## Opis ulaza

Prva linija standardnog ulaza sadrži jedan prirodan broj $N$ - dužinu niza klikova. Narednih $N$ linija sadrži po dva prirodna broja $x_i, y_i$, odvojena razmakom - koordinate polja na koja će kliknuti Bubin drug.

## Opis izlaza

Ukoliko će Buba u nekom trenutku uzviknuti "Stop!", ispisati trenutak u kojem će se to desiti. Preciznije, ukoliko će ona uzviknuti "Stop!" nakon $k$ klikova, u prvu liniju standardnog izlaza ispisati broj $k$. U narednih $k-1$ linija ispisati redom poteze, tačnije, koordinate polja odvojene razmakom, koji bi pri normalnoj igri doveli tablu u taj položaj. Ako postoji više takvih nizova poteza, štampati bilo koji. U suprotnom, ako Buba neće ni u jednom trenutku uzviknuti "Stop!", u prvu i jedinu liniju standardnog izlaza ispisati broj $-1$.

## Primer 1

### Ulaz

~~~
4
2 2
1 2
3 1
2 3
~~~

### Izlaz

~~~
3
1 1
2 1
~~~

## Primer 2

### Ulaz

~~~
4
4 1
3 2
2 3
1 4
~~~

### Izlaz

~~~
-1
~~~

### Objašnjenje primera

U prvom primeru, Buba će uzviknuti "Stop!" nakon što njen drug doda tri žetona na polja $(2, 2), (1, 2), (3, 1)$. Buba može do istog izgleda table doći normalnom igrom tako što prvo klikne na polje $(1, 1)$, pri čemu će se taj žeton obrisati sa tog polja a pojaviće se po jedan žeton na poljima $(2, 1)$ i $(1, 2)$. Nakon toga ona može da klikne na polje $(2, 1)$. Sa tog polja se žeton briše a dodaje se po jedan žeton na polja $(3, 1)$ i $(2, 2)$. Sada se na tabli nalaze tri žetona na pozicijama: $(3, 1), (2, 2), (1, 2)$, odnosno, dobija se isti izgled table kao onaj koji je njen drug napravio nakon tri klika u _debug_ modu.

U drugom primeru ni u jednom trenutku se ne dobija tabla koju Buba može da napravi normalnom igrom.

## Ograničenja

U svim test primerima važi: $N, x_i, y_i \leq 500.000$. Test primeri su podeljeni u 4 disjunktne grupe:

* U test primerima vrednim 8 poena: $N, x_i, y_i \leq 4$.
* U test primerima vrednim 28 poena: $N, x_i, y_i \leq 10$.
* U test primerima vrednim 18 poena: $N, x_i, y_i \leq 100$.
* U test primerima vrednim 54 poena: Nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Ivan Stošić | Momčilo Topalović |

## Analiza

Dodelimo žetonu na poziciji $(x, y)$ vrednost $2^{2-x-y}$. Primetimo da se nakon jednog poteza pri normalnoj igri zbir vrednosti svih žetona neće promeniti, što znači da je potreban (ali ne i dovoljan) uslov da Buba kaže "Stop!" da zbir vrednosti svih žetona bude tačno $1$. Pošto se dodavanjem novog žetona u _debug_ modu ova vrednost povećava, ovo znači da će u najviše jednom trenutku zbir vrednosti svih žetona na tabli biti jednak $1$. Ako vrednost table "preskoči" $1$ ili nikad ne dostigne $1$, znamo da nema rešenja.

U trenutku kada vrednost dostigne $1$, pokušaćemo da rekonstruišemo niz poteza koji tablu dovodi u to stanje. Ovo ćemo raditi grabljivim algoritmom odnazad. Posmatrajmo sve žetone u poslednjoj nepraznoj dijagonali (pod dijagonalom podrazumevamo skup polja sa konstantnom vrednošću $x+y$). Rešenje postoji ako i samo ako se oni mogu upariti tako da svaki par čine dva žetona koji se nalaze na poljima koja imaju zajedničko teme.

Ovo uparivanje se može uraditi na jedinstven način, ako je uopšte moguće, ponovo grabljivim algoritmom redom od žetona sa najmanjom $x$-koordinatom. Ako smo uspešno uparili sve žetone iz ove dijagonale, za svaki par uparenih žetona na pozicijama $(x, y+1), (x+1, y)$ kreiramo jedan žeton na poziciji $(x, y)$. Ovaj postupak ponavljamo sve dok ne dođemo do prve dijagonale ili ne dođemo u situaciju da ne možemo da uparimo žetone.

Ako dođemo do stanja gde je samo jedan žeton u prvoj dijagonali, rešenje štampamo kao obrnuti niz žetona koje smo kreirali tokom obilaska dijagonala.
 
##  Smernice za algoritam

Trenutak kada zbir vrednosti svih žetona postane jednak $1$ možemo pronaći tako što održavamo binarni zapis razlomka koji sadrži trenutni zbir vrednosti. Kada dodajemo žeton na poziciju $(x,y)$, u pomoćnom nizu $c$ treba povećati broj $c_{x+y-2}$ za $1$. Ako njegova vrednost postane $2$, onda je postavljamo na $0$ i isti postupak ponavljamo za cifru na poziciji $x+y-3$, i tako dalje, do zaustavljanja.

Amortizovanom analizom složenosti se može pokazati da ovaj postupak ima vremensku složenost $O(N)$. U rešenju dominira vremenska složenost za sortiranje svake dijagonale, pošto će sve one ukupno sadržati $O(N)$ žetona vremenska složenost je $O(N \log N)$ dok je memorijska složenost $O(N)$.

``` cpp title="06_zetoni.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;

int c[1000005], cp, n, x[500005], y[500005];

void dodaj(int x) {
	if (++c[x] == 2) {
		c[x] = 0;
		cp--;
		dodaj(x-1);
	} else {
		cp++;
	}
}

basic_string<int> e[1000005];

void nema() {
	cout << "-1\n";
	exit(0);
}

void resi(int k) {
	for (int i=1; i<=k; i++)
		e[x[i] + y[i]] += x[i] - y[i];
	basic_string<pair<int, int>> sol;
	for (int i=1000000; i>=3; i--) {
		sort(e[i].begin(), e[i].end());
		basic_string<pair<int, int>> freqs;
		{
			int last = -123123123, cnt = 0;
			for (int x : e[i])
				if (x == last)
					cnt++;
				else {
					if (cnt)
						freqs += {last, cnt};
					cnt = 1;
					last = x;
				}
			if (cnt)
				freqs += {last, cnt};
		}
		
		int last_g = 0, last_c = 0;
		for (int j=0; j<(int)freqs.size(); j++) {
			if (last_c > 0) {
				if (freqs[j].first != last_g + 2)
					nema();
				if (freqs[j].second < last_c)
					nema();
				freqs[j].second -= last_c;
				while (last_c--) {
					sol += {(last_g + i) / 2, (i - last_g) / 2 - 1};
					e[i-1] += last_g + 1;
				}
			}
			last_c = freqs[j].second;
			last_g = freqs[j].first;
		}
	}

	if (e[2].size() != 1 || e[2][0] != 0)
		nema();

	cout << k << '\n';
	reverse(sol.begin(), sol.end());
	for (auto p : sol)
		cout << p.first << ' ' << p.second << '\n';
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n;
	for (int i=1; i<=n; i++)
		cin >> x[i] >> y[i];

	for (int i=1; i<=n; i++) {
		dodaj(x[i] + y[i]);
		if (c[2] == 1) {
			if (cp == 1)
				resi(i);
			else
				nema();
		}
	}
	nema();
}
```
