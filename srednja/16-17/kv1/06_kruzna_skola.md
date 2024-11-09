---
hide:
  - toc
---

# 6 - Kružna škola

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Škola se sastoji od $n$ učionica raspoređenih u krug. U nekim učionicama nalaze se profesori koji drže čas, tako da je u svakoj učionici ili jedan ili nijedan profesor. Profesori su poznati po tome da ih mrzi da mnogo hodaju i da umeju da hodaju samo u smeru kazaljke na satu. Nakon što zvono označi kraj časa, svaki profesor pogleda da li se u sledećoj učionici (u smeru kazaljke na satu) nalazi profesor koji je upravo završio čas. Ako se ne nalazi, on će sledeći čas održati u toj sledećoj učionici, dok ako je nekog bilo tamo on odlučuje da ostane u istoj učionici u kojoj je malopre održao čas, i ponovi čas istim đacima (jadni oni).

Na slici je dat primer kako se menja raspored profesora pri prelasku iz jednog školskog časa u naredni. Crna polja označavaju učionice sa profesorom, bela polja su učionice bez profesora.

![Slika primera](06_kruzna_skola-sl1.png)

Ako je poznat raspored profesora po učionicama na prvom času, odrediti raspored na $k$-tom času.

## Opis ulaza
U prvoj liniji ulaza nalaze se prirodni brojevi $n$, broj učionica u školi, i $k$, redni broj časa za koji treba odrediti raspored. U drugoj liniji ulaza nalazi se opis učionica na prvom času dat kao $n$ karaktera. Učionice su navedene u smeru kazaljke na satu, i za svaku učionicu zapisan je karakter $1$ ako se u učionici nalazi profesor, odnosno $0$ ako se ne nalazi.

## Opis izlaza
Neka je $S$ niz od $n$ elemenata koji predstavlja stanja učionica na $k$-tom času. $S[i] = 0$ ako je $i$-ta učionica na času $k$ prazna, odnosno $S[i] = 1$ ako je u njoj profesor.

U jedinu liniju izlaza ispisati opis učionica na $k$-tom času, na sledeći način. Ako je $n \leq 10^5$, ispisati niz $S$ (bez razmaka).
Ako je $n > 10^5$, ispisati $10^5$ brojeva, svaki ili $0$ ili $1$, gde $i$-ti broj predstavlja XOR svih brojeva niza $S$ na pozicijama čiji je indeks kongruentan sa $i$ po modulu $10^5$.

Ovakav način ispisivanja se traži da bi se uštedelo vreme potrebno za ispis, i ne menja suštinu zadatka. Ukoliko već imate izračunat niz $S$, možete iskoristiti sledeći C++ kod za ispis.

```cpp
int M = 100000;
int l = min(n, M);
for (int i = 0; i < l; i++) {
    int a = 0;
    for (int j = i; j < n; j += M) {
        a ^= S[j];
    }
    printf("%i", a);
}
```

U programskom jeziku Pascal, pod pretpostavkom da ste deklarisali ove promenljive,
```pascal
l, i, j, a : Longint;
S : array[1..n] of Integer;
```
za ispis možete koristiti sledeći kod.
```pascal
l := Min(n, M);
for i := 1 to l do
begin
    a := 0;
    j := i;
    while (j <= n) do
    begin
        a := a xor S[j];
        j := j + M;
    end;
    Write(a);
end;
```

## Primer 1
### Ulaz
```
16 2
1011101100110100
```

### Izlaz
```
0111011010101010
```

## Primer 2
### Ulaz
```
10 4
1110010110
```

### Izlaz
```
0101010111
```

## Objašnjenje primera
Prvi test primer je prikazan na slici u zadatku.
U drugom test primeru raspored po časovima je:

1. 1110010110
2. 1101001101
3. 1010101011
4. 0101010111

## Ograničenja
Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima koji vrede 20 poena važiće $1 \leq n \leq 10^5$ i $1 \leq k \leq 10^5$.
* U test primerima koji vrede 12 poena važiće $1 \leq n \leq 10^5$ i $10^5 < k \leq 10^9$.
* U test primerima koji vrede  8 poena važiće $10^5 < n \leq 10^7$,  $1 \leq k \leq 10^5$ i broj profesora nije veći od $10^5$.
* U test primerima koji vrede 60 poena važiće $10^5 < n \leq 10^7$,  $10^5 < k \leq 10^9$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Savić | Marko Savić | Aleksandar Višnjić | Nikola Spasić |

Zadatak rešavamo u složenosti $O(n)$, te se odmah osvrćemo na glavno rešenje. Sporije implementacije mogu rešiti podzadatke.

## Glavno rešenje:
Možemo posmatrati prelaženje profesora u sledeću slobodnu učionicu kao pretvaranje svakog pojavljivanja podniske $10$ u $01$. Štaviše, možemo posmatrati i kao "prelaženje keca udesno" ili "prelaženje nule ulevo". Ova dva zadatka su analogna, te možemo unapred odrediti onaj koji rešavamo. Ispostavlja se da je jednostavnije rešavati zadatak za karakter ($0$ ili $1$) koji se manje puta pojavljuje u zadatoj niski (ako se oba pojavljuju isti broj puta, uzimamo bilo koji).

Neka je bez umanjenja opštosti taj karakter $1$, što znači da se on pojavljuje najviše $\lfloor \frac{n}{2} \rfloor$ puta. Nadalje simuliramo proces u što je manje operacija moguće. Najpre, korisno je particionisati kružnu školu u tri vrste particija:

1. Uzastopni kečevi: $111\ldots 111$
2. Uzastopne nule:  $000\ldots 000$
3. Naizmenični kečevi i nule, s tim da particija uvek počinje kecom i završava se nulom: $1010\ldots 10$

Postavljamo prioritet da se prvo iskoriste particije treće vrste, a tek onda ostale. Ovim se particija druge vrste neće naći nakon particije prve vrste. Dalje posmatramo veličinu svake particije i odnose između particija različitih vrsta tokom procesa. Navodimo sve moguće slučajeve:

1. *prva-treća*: prva se smanjuje za $1$, a treća povećava za $2$.
2. *druga-prva*: druga se smanjuje za $1$, a prva ostaje nepromenjena.
3. *druga-treća*: druga se povećava za $1$, treća ostaje nepromenjena.
4. *treća-prva*: treća se smanjuje za $2$, a prva se povećava za $1$.
5.  *treća-druga*: treća ostaje nepromenjena, a druga se smanjuje za $1$.

Čitav proces je moguće simulirati preko *kružne liste*. To je dvostruko povezana lista u kojoj povezujemo početak i kraj. Za svaki element te liste računamo koliko se u jednom trenutku smanji ili poveća veličina particije koju predstavlja na osnovu odnosa sa susedima, kao i kada će ta veličina pasti na $0$. Kada se to desi brišemo element iz liste što je moguće učiniti u $O(1)$. U stvari, za svaki element pamtimo trenutak u kome će  on biti izbrisan. To je moguće učiniti upotrebom pomoćnog niza veličine $n$, u kome za svaki mogući trenutak pamtimo koje elemente treba obrisati baš tad.

Ispostavlja se da nakon određenog vremena, upravo zato što smo pretpostavili da kečeva ima manje od nula, ostaju samo particije vrste $2$ i $3$, tj. da se cela škola rotira odjednom. U stvari, nakon $n$ trenutaka ovo će biti slučaj. Ukoliko je $k-n>0$, konačno stanje liste računamo jednostavnom modularnom aritmetikom. Zato red veličine vrednosti $k$ nije od važnosti.

Pažljiva implementacija dovodi do rešenja ukupne složenosti $O(n)$. Kao što je ranije napomenuto, sporije implementacije mogu rešiti podzadatke.

``` cpp title="06_kruzna_skola.cpp" linenums="1"
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>


using namespace std;

const int maxN = 10000000;

int state[maxN];
int n, t;


struct Particle {
	int p, dir;
	bool used = false;
	int annihilated = 0;

	Particle(int _p, int _dir):p(_p), dir(_dir) {}
};

vector<Particle> particles;


void solve() {

	for (int i = 0; i < n; i++) {
		int c = state[i];
		int r = state[(i + 1) % n];
		if (c == r) {
			Particle p = Particle(i, c ? -1 : 1);
			particles.push_back(p);
		}
	}

	stack<int> s;
	int last = -1;

	for (int z = 0; z < 2; z++) {
		for (int i = 0; i < particles.size(); i++) {
			Particle *p = &particles[i];
			if (!p->used) {
				if (p->dir == 1) {
					p->used = true;
					s.push(i);
				} else {
					if (!s.empty()) {
						p->used = true;
						Particle *q = &particles[s.top()];
						s.pop();
						int d = (p->p - q->p + n) % n;
						q->annihilated = p->annihilated = (d / 2 <= t ? 2 : 1);
						last = i;
					}
				}
			}
		}
	}

	int j = -1;
	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].annihilated == 0) {
			j = i;
			break;
		}
	}

	int k, st;

	if (j != -1) {
		k = ((particles[j].p + particles[j].dir * t) % n + n) % n;
		st = state[particles[j].p % n];
	} else {
		if (last != -1) {
			k = ((particles[last].p - t + 2) % n + n) % n;
			st = state[(particles[last].p + 2) % n];
		} else {
			k = t % n;
			st = state[0];
		}
	}

	std::fill(state, state + n, 0);

	for (int i = 0; i < particles.size(); i++) {
		if (particles[i].annihilated != 2) {
			state[((particles[i].p + particles[i].dir * t) % n + n) % n] = 1;
		}
	}

	for (int i = 0; i < n; i++) {
		int j = (k + i) % n;
		int nextState = (state[j] == st);
		state[j] = st;
		st = nextState;
	}
}

char ulaz[10000555];

int main() {
    scanf("%i %i\n", &n, &t);
    t--;

    gets(ulaz);
    for (int i = 0; i < n; i++) {
		state[i] = ulaz[i] - '0';
    }

	solve();

	int d = 100000;
	int l = min(n, d);
	for (int i = 0; i < l; i++) {
		int a = 0;
		for (int j = i; j < n; j += d) {
			a ^= state[j];
		}
		printf("%i", a);
	}
    printf("\n");

    return 0;
}

```
