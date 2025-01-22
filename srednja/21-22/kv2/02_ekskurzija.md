---
hide:
  - toc
---

# 2 - Ekskurzija

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 256MB |


Nakon uspešno završenog prvog kruga kvalifikacija, profesor Guki je odlučio da odvede svoje učenike na ekskurziju. Iako je spremio ogromnu količinu krem bananica i izabrao premijum destinaciju, Denino brdo, njegovi učenici nisu baš najsrećniji! Oni smatraju da bi mnogo korisnije bilo da ulože dodatno vreme u vežbanje zadataka sa Petlje i poprave svoj skor na bar 490 poena u drugom krugu kvalifikacija. Međutim, kako znaju da profesoru mnogo znači poseta Deninom brdu (čak je spremio i te krem bananice), odlučili su da mu pruže priliku i postave jedan sitan uslov za svoj polazak.

Učenici će poći na ekskurziju ako je moguće raspodeliti ih u tačno $K$ nepraznih grupa, tako da svaki učenik pripada tačno jednoj grupi i svi učenici u okviru jedne grupe dobiju različit ceo pozitivan broj krem bananica.

Pomozite Gukiju da sazna da li ima potrebe da pakuje krem baninice, ili nema dovoljnu količinu za sve učenike (u tom slučaju će morati sam da ih pojede).

## Opis ulaza

Prva linija standardnog ulaza sadrži pozitivan ceo broj $T$, broj različitih testova.

Svaka od narednih $T$ linija sadrži po tri cela pozitivna broja, $N$, $M$, $K$ - broj učenika, broj krem baninica koje je profesor spremio i zahtevani broj grupa.

## Opis izlaza

U svakoj od $T$ linija standardnog izlaza ispisati "Tak" (bez navodnika) ako će za zadate parametre ekskurzija biti održana, u suprotnom ispisati "Nie" (bez navodnika).

## Primer 1
#### Ulaz
```
2
5 100 2
2 2 1
```

#### Izlaz
```
Tak
Nie
```

#### Objašnjenje
U prvom testu moguće je podeliti studente u dve grupe, na primer jednu veličine $4$ i drugu veličine $1$. U prvoj grupi učenici bi dobili redom $10, 15, 20$ i $35$ krem bananica. Učenik iz druge grupe bi u tom slučaju dobio preostalih $20$ krem bananica.

## Ograničenja

- $1 \leq T \leq 10$
- $1 \leq N \leq 10^9$
- $1 \leq M \leq 10^{17}$
- $1 \leq K \leq N$

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 10 poena: $N = 3$.
- U testovima vrednim 10 poena: $K = 1$.
- U testovima vrednim 20 poena: $N, M \leq 10$.
- U testovima vrednim 30 poena: $N \leq 2000$.
- U testovima vrednim 30 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Dragan Urošević | Aleksa Milisavljević |

## Rešenje kad $N = 3$
U ovom slučaju, broj grupa ne može biti veći od $3$. Prema tome, potrebno je samo odrediti minimalni broj bananica za sve tri vrednosti za broj grupa. Ako je $K=1$, onda u toj grupi ima 3 učenika, minimalni broj bananica je $1+2+3=6$. Ako je  $K=2$, onda u jednoj grupi moraju biti dva učenika (i minimalan broj bananica je $1+2=3$), a u drugoj grupi 1 učenik (i minimalan broj bananica je $1$), pa je ukupan minimalan broj bananica $4$. Ako je $K=3$, onda je u svakoj grupi $1$ učenik, pa je ukupan minimalan broj bananica $3$.

## Rešenje kad $K = 1$
U ovom slučaju, svi učenici su u istoj grupi i minimalan broj bananica je
$$
1+2+3+\dotsb + N = \frac{N\cdot(N+1)}{2}.
$$
Potrebno je voditi računa da poslednji proizvod može biti vrlo veliki broj.

## Rešenje kad $N, M \leq 10$
U ovom slučaju, do rešenja se može doći primenom pretrage sa vraćanjem (bektrek).

## Rešenje kad $N \leq 2000$
U ovom slučaju se primenjuje glavno rešenje u kojem ne primetimo sve formule, već primenjujemo neke manje efikasne metode (npr. prolazak kroz sve grupe).

## Glavno rešenje
Potrebno je primetiti da grupe treba da budu približno jednake veličine. Naime, ako je $c_1$ broj učenika u jednoj grupi, $c_2$ broj učenika u drugoj grupi i pri tome važi $c_2 \geq c_1 + 2$, onda je minimalni broj bananica za te dve grupe
$$
B_1 = \frac{c_1\cdot(c_1+1)}{2} + \frac{c_2\cdot (c_2+1)}{2} =
\frac{c_1^2+c_2^2+c_1+c_2}{2}.
$$
Ako jednog učenika prebacimo iz druge grupe u prvu grupu, onda je minimalni broj bananica u te dve grupe
 $$
B_2 = \frac{(c_1+1)\cdot(c_1+2)}{2} + \frac{(c_2-1)\cdot c_2}{2} =
\frac{c_1^2+c_2^2+3c_1-c_2+2}{2}.
$$
Razlika dva poslednja broja je
$$
B_1 - B_2 = \frac{2c_2 - 2c_1 - 2}{2} = c_2 - c_1 -1 > 0,
$$
tj. minimalan broj bananica se smanjio.

Prema tome, sve grupe treba da imaju približno jednako elemenata. Ako je broj učenika deljiv brojem grupa, onda bi svaka grupa imala $N/K$ učenika. Ako broj učenika nije deljiv brojem grupa onda će jedan deo grupa imati $N_1 = \lfloor N/K \rfloor$,  a drugi deo grupa $N_2 = N_1 + 1$. Broj grupa $K_2$ koje imaju $N_2$ učenika je
$$
K_2 = N - K \cdot \lfloor N/K\rfloor = N \text{ mod } K,
$$
gde je $N \text{ mod } K$ ostatak pri deljenju broja $N$ brojem $K$.
Konačno, minimalan ukupan broj bananica je
$$
(K-K_2) \cdot \frac{N_1\cdot (N_1+1)}{2} + K_2 \cdot \frac{N_2\cdot (N_2+1)}{2}.
$$

Složenost algoritma je $O(1)$.

``` cpp title="02_ekskurzija.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;


const int maxN = 1000000000;
const long long maxM = 100000000000000000;
int t;
long long n, m, k;

void solve() {
	cin >> n >> m >> k;
	assert(n > 0 && n <= maxN);
	assert(m > 0 && m <= maxM);
	assert(k > 0 && k <= n);

	long long velicinaGrupe = n / k;
	long long potrebneBannice = velicinaGrupe * (velicinaGrupe + 1) / 2 * k + (velicinaGrupe + 1) * (n % k);

	if (potrebneBannice <= m) {
		cout << "Tak" << endl;
	} else {
		cout<< "Nie" << endl;
	}
}

int main() {

	cin >> t;

	assert(t >0 && t<=10);

	while(t--) {
		solve();
	}
}

```
