---
hide:
  - toc
---

# A3 - Mingo

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 256MB |

Sada, kada je odradio takmičenje, Miroslav je shvatio koliko je programiranje naporno, te je odlučio da pobegne na Mars. On je na internetu naišao na nagradnu igru Mingo u kojoj je glavna nagrada put na Mars.

Nagradna igra se sastoji u tome da svaki takmičar na listiću izabere tačno $K$ različitih prirodnih brojeva, gde je svaki broj iz skupa ${1, 2, 3, ..., M}$. Nakon toga se vrši $Q$ izvlačenja, gde svako izvlačenje podrazumeva nasumičan odabir tačno $K$ različitih brojeva iz prethodno pomenutog skupa. Svaki listić važi za svih $Q$ izvlačenja, i takmičar koji ima listić sa svim izvučenim brojevima u bilo kom od $Q$ izvlačenja dobija put na Mars.

Kako bi povećao svoje šanse, Miroslav je popunio $N$ listića. Kako je sada teško pratiti sve te listiće, on je zamolio vas da mu pomognete.

On želi da za svako izvlačenje u svakom trenutku zna koliko listića ima svaki do tada izvučen broj, tj. za svako izvlačenje posebno, nakon izvučenog $i$-tog broja on želi da zna koliko njegovih listića sadrži svaki od izvučenih $i$ brojeva u tom izvlačenju.

## Opis ulaza
U prvoj liniji standardnog ulaza se nalaze brojevi $N, K$ i $M$, koji redom označavaju broj listića koje je Miroslav popunio, broj razlitih brojeva koje je potrebno obeležiti na listiću i najveći broj koji je moguće obeležiti.
Sledećih $N$ redova opisije listiće koje je popunio Miroslav, gde se u $i$-tom redu nalazi $K$ brojeva koji označavaju izabrane brojeve na $i$-tom listiću.
Nakon toga se nalazi jedan red sa brojem $Q$ koji predstavlja broj izvlačenja.
U narednih $Q$ redova se nalazi opis svih izvlačenja. U $i$-tom redu se nalazi $K$ brojeva koji predstavljaju brojeve u redosledu u kojem su bili izvlačeni.

## Opis izlaza
Na standarni izlaz je potrebno ispisati $Q$ redova, gde $i$-ti red odgovara rešenju za $i$-to izvlačenje, tj. $j$-ti broj u $i$-tom redu predstavlja broj listića koji sadrže svaki od izvučenih $j$ brojeva u $i$-tom izvlačenju.

## Primer 1
### Ulaz
```
3 3 15
2 1 3
1 10 4
4 11 1
2
1 4 11 
4 3 11
```

### Izlaz
```
3 2 1
2 0 0
```

## Primer 2
### Ulaz
```
2 7 39
7 6 5 4 3 2 1
1 2 3 4 5 6 8
2
4 3 5 1 2 6 7
6 5 4 3 2 8 39
```

### Izlaz
```
2 2 2 2 2 2 1
2 2 2 2 2 1 0
```

## Objašnjenje primera
U prvom test primeru kod prvog izvlačenja rešenje je "3 2 1" zato što broj 1 Miroslav ima na sva 3 listića. Nakon drugog izvučenog broja imamo kombinaciju "1 4" koja se pojavljuje na 2 listića. Na kraju trećeg izvlačenja imamo kombinaciju brojeva "1 4 11" i jedini listić koji ima sva 3 broja iz kombinacije jeste treći listić te je odgovor 1.
U drugom izvlačenju prvog test primera, broj 4 sadrže listići 2 i 3. Dok ne postoje listići koji sadrže sve brojeve iz kombinacija "4 3" i "4 3 13".

## Ograničenja
* $1 \leq N \leq 10000$
* $1 \leq K \leq 8$
* $K \leq M \leq 500$
* $1 \leq Q \leq 20000$

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima koji vrede 15 poena važi $Q \leq 10$.
* U test primerima koji vrede 15 poena važi $K = 3, M < 100$.
* U test primerima koji vrede 30 poena važi $K \leq 5, M < 100$.
* U test primerima koji vrede 40 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Demjan Grubić | Demjan Grubić | Nepoznato | Dušan Zdravković |

##Podzadatak $1$
Jasno da svaki listić možemo posmatrati kao $K$-točlani podskup skupa $\{1, 2, 3, …., M\}$, te tako imamo ukupno $N$  podskupova sa po $K$ elemenata ($K$-točlanih). Označimo te podskupove sa $S_1, S_2, …, S_N$. Za svako pojedinačno izvlačenje i svaki broj $j$ između 1 i $K$ potrebno je odrediti koliko ima skupova u nizu $S_1, S_2, …, S_N$ koji sadrže kao poskup skup sastavljen od prvih $j$ brojeva izvučenih u tom izvlačenju.

Naivna varijanta se sastoji baš od brojanja koliko ima listića (tj. skupova) kojima je  skup sastavljen od prvih $j$ izvučenih brojeva podskup (tj. koliko ima skupova-listića koji sadrže svih $j$ prvih izvučenih brojeva). Zavisno od implementacije, složenost ovog rešenja može biti $O(QNK)$ ili $O(QNK^2)$.

Svaka od naprednijih varijanti podrazumeva preprocesiranje listića tako da se za svako $j\in \{1, 2, ..., K\}$ formiraju svi podskupovi sa tačno $j$ od $K$ izvučenih brojeva. Zatim se podskupovi iste kardinalnosti (sa istim brojem elemenata) smeštaju u kolekciju koja će omogućiti efikasno određivanje koliko se puta neki podskup (sa istim brojem elemenata) pojavljuje u datoj kolekciji. Primetimo da je broj podskupova sa $j$ elemenata skupa koji ima $K$ elemenata jednak $\binom{K}{j}$. Tako će ukupan broj poskupova sa $j$ elemenata skupova $S_1, S_2, …, S_N$ biti $N\times\binom{K}{j}$. Ukupan broj svih podskupova (za sve vrednosti $j$) će biti $N\times (2^K-1)$.

##Podzadatak $2$
Elementi skupova (tj. izvučeni brojevi) su brojevi manji od 100. Podskupovi koje izdvajamo imaju najviše 3 elementa i elementi svakog podskupa se mogu sortirati, a zatim posmatrati kao cifre nekog broja u sistemu sa osnovom 100 (budući da su elementi manji od 100). Tako će svaki podskup biti predstavljen kao najviše trocifren broj u sistemu sa osnovom 100, odnosno svaki skup može biti predstavljen pomoću broja koji je manji od milion. Zahvaljujući tome mogu se izbrojati pojavljivanja svakog podskupa i zapamititi u nizu dužine 1000000 (tj. sa milion elemenata).

##Podzadatak $3$
U podzadatku tri se skupovi opet mogu predstaviti pomoću brojeva u sistemu sa osnovom 100 ali kako u podzadatku 3 broj $K$ može imati vrednost 5, to će biti najviše potocifreni brojevi i njihova vrednost je ograničena sa 10 milijardi. Ovaj put ne možemo primeniti obično brojanje, već formiramo nizove sa brojevima koji predstavljaju skupove. Nizove možemo sortirati i na kraju jednim prolazom izbrojati broj pojavljivanja svake vrednosti (tj. svakog podskupa). Pri odgovaranju na upite podskup koji se sastoji od $j$ prvih izvučenih brojeva predstavimo kao broj (na isti način kao i podskupove oformljene od listića) i binarnom pretragom pronalazimo u nizu brojeva koji predstavljaju podskupove listića. 

##Podzadatak $4$
U podzadatku četiri maksimalni broj izvučenih brojeva, kao i maksimalna vrednost izvučenih brojeva su takvi da se podskupovi sa više elemenata ne mogu reprezentovati pomoću celobrojnih tipova podržanih u jezicima koji se koriste za takmičenje. Zbog toga je potrebno podskupove predstaviti na neki drugi način. Jedan od načina je struktura koja sadrži broj elemenata u podskupu i elemente podskupa smeštene u niz koji je sortiran. Nad tako reprezentovanim podskupovima možemo definisati poređenje (uobičajeno leksikografsko poređenje). Koristeći to poređenje možemo sorirati nizove koji sadrže sve podskupove sa istim brojem elemenata. Nakon toga brojanje koliko puta se neki podskup $P$ pojavljuje u nizu obavljamo varijacijom binarne pretrage u kojoj prvo određujemo deo niza sa podskupovima u kome se prvi element poklapa sa prvim elementom podskupa $P$, zatim u tako izdvojenom podnizu (određen je početnim i krajnjim elementom podniza) deo u kome se drugi element poklapa sa drugim elementom podskupa $P$, itd. Postupak prekidamo kada iscrpimo sve elemente podskupa $P$, nakon čega je broj podskupova jednak dužini izdvojenog podniza, ili kada podniz u kome se elementi mogu poklapati sa podskupom $P$ postane prazan (tada je odgovor nula).

##glavno rešenje
Poslednji podzadatak može biti rešen i tako što se podskupovi smeštaju u heš tabelu, pri čemu u toku dodavanja istovremeno brojimo koliko se puta pojavljuju podskupovi. Nakon toga odgovaranje na upite se svodi na pronalaženje odgovarajućih skupova u heš tabeli i izdvajanju informacije koliko puta se taj podskup nalazi u heš tabeli.

Pokazalo se da maksimum poena može biti osvojen i tako što se svakim izvučenim brojem u jednom konkretnom izvlačenju izdvoje samo listići koji sadrže sve do tog trenutka izvučene brojeve. Broj izdvojenih listića je odgovor za konkretno izvlačenje i konkretan broj izvučenih brojeva. Kada se nakon toga obrađuje sledeći izvučeni broj, analiziraju se samo listići koji su izdvojeni i od njih izdvajaju samo oni koji sadrže izvučeni broj. Uz pažljivu implementaciju dobija se rešenje koje se izvršava u predviđenom vremenu.

``` cpp title="06_mingo.cpp" linenums="1"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

const int MaxN = 10000;
const int MaxK = 8;
const int MaxM = 500;
const int MaxKombZaIgracaZaILoptica = 70; // binom(MaxK, MaxK/2)

int N; // broj ljudi
int K; // broj kuglica koje se izvlace
int M; // kuglice imaju brojeve {1, 2, 3, ..., M}
int Q; // broj izvlacenja

int kombIgraca[MaxN][MaxK];

int trenutnoElemenata[MaxK+1];
int sveMoguceKombinacije[MaxK+1][MaxN*MaxKombZaIgracaZaILoptica][MaxK];
int komb[MaxK];

int firstElement[2][MaxM+1];
int lastElement[2][MaxM+1];
int nextElement[2][MaxN*MaxKombZaIgracaZaILoptica];

int sortiranRaspored[MaxK+1][MaxN*MaxKombZaIgracaZaILoptica];

/*
O(N*K*logK) ili O(N*K^2)
*/
void UlazIgraci()
{
	scanf("%d%d%d", &N, &K, &M);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < K; ++j) {
			scanf("%d",&kombIgraca[i][j]);
		}

		// nije bitno koji sort
		// posto sortiramo K elemenata
		sort(kombIgraca[i], kombIgraca[i]+K);
	}
}

/*
O(N*K*2^K)
*/
void UbaciUNizove()
{
	memset(trenutnoElemenata, 0, sizeof(trenutnoElemenata));

	for (int i = 0; i < N; ++i) {
		int bitmaskEnd = (1 << K);
		for (int bitmask = 1; bitmask < bitmaskEnd; ++bitmask) {
			int cntBit = 0;
			for (int bit = 0; bit < K; ++bit) {
				if ((bitmask >> bit) & 1) {
					komb[cntBit++] = kombIgraca[i][bit];
				}
			}

			for (int j = 0; j < cntBit; ++j) {
				sveMoguceKombinacije[cntBit][trenutnoElemenata[cntBit]][j] = komb[j];
			}
			trenutnoElemenata[cntBit]++;
		}
	}
}

/*
O(SUM_{i=1..K} i*(binom(K, i)*N+M)) ~ O(K*N*2^K + K^2*M)
*/
void SortSveNizove()
{
	for (int brojLoptica = 1; brojLoptica <= K; ++brojLoptica) {

		int now = 0;
		int prev = 1;

		memset(firstElement, -1, sizeof(firstElement));
		memset(lastElement, -1, sizeof(lastElement));
		for (int i = 0; i < trenutnoElemenata[brojLoptica]; ++i) {
			if (lastElement[prev][1] == -1) {
				firstElement[prev][1] = lastElement[prev][1] = i;
			}
			else {
				nextElement[prev][ lastElement[prev][1] ] = i;
				lastElement[prev][1] = i;
			}

			nextElement[prev][i] = -1;
		}

		for (int trenIdx = brojLoptica-1; trenIdx >= 0; --trenIdx) {
			for (int i = 1; i <= M; ++i) {
				for (int j = firstElement[prev][i]; j != -1; j = nextElement[prev][j]) {
					int idxNiza = j;
					int vrednost = sveMoguceKombinacije[brojLoptica][idxNiza][trenIdx];

					if (lastElement[now][vrednost] == -1) {
						firstElement[now][vrednost] = lastElement[now][vrednost] = idxNiza;
					}
					else {
						nextElement[now][ lastElement[now][vrednost] ] = idxNiza;
						lastElement[now][vrednost] = idxNiza;
					}

					nextElement[now][idxNiza] = -1;
				}
			}

			memset(firstElement[prev], -1, sizeof(firstElement[prev]));
			memset(lastElement[prev], -1, sizeof(lastElement[prev]));

			now = 1 - now;
			prev = 1 - prev;
		}

		int trenElement = 0;
		for (int i = 1; i <= M; ++i) {
			for (int j = firstElement[prev][i]; j != -1; j = nextElement[prev][j]) {
				int idxNiza = j;
				sortiranRaspored[brojLoptica][trenElement++] = idxNiza;
			}
		}
	}
}

/*
O(log(binom(K, K/2) * N)) ~ O(N*logN)
*/
int BinarySearch(int vrednostTrazeneKuglice, int idxKuglice, int donjaGranica, int gornjaGranica, bool prvi, int brojKuglica)
{
	int left = donjaGranica;
	int right = gornjaGranica;

	while (right - left) {
		int mid = (left + right) / 2;
		int idxUNesortitanomNizu = sortiranRaspored[brojKuglica][mid];
		int vrednostKugliceUNizu = sveMoguceKombinacije[brojKuglica][idxUNesortitanomNizu][idxKuglice];

		if (prvi) {
			if (vrednostKugliceUNizu >= vrednostTrazeneKuglice) right = mid;
			else 												left = mid + 1;
		}
		else {
			if (vrednostKugliceUNizu > vrednostTrazeneKuglice) right = mid;
			else 											   left = mid + 1;
		}
	}

	// ako trazimo poslednji
	// onda moramo smanjiti pokazivac za 1
	if (donjaGranica != gornjaGranica) {
		int idxUNesortitanomNizu = sortiranRaspored[brojKuglica][left];
		int vrednostKugliceUNizu = sveMoguceKombinacije[brojKuglica][idxUNesortitanomNizu][idxKuglice];
		if (!prvi && (vrednostKugliceUNizu != vrednostTrazeneKuglice)) {
			left--;
		}
	}

	if (left == -1) return -1;

	int idxUNesortitanomNizu = sortiranRaspored[brojKuglica][left];
	int vrednostKugliceUNizu = sveMoguceKombinacije[brojKuglica][idxUNesortitanomNizu][idxKuglice];

	if (vrednostTrazeneKuglice != vrednostKugliceUNizu) return -1;
	return left;
}

/*
O(K*log(binom(K, K/2) * N)) ~ O(K*K*logN) (gubi se dosta na uproscavanju verovatno)
*/
int BinarySearchNiz(int brojKuglica, int *trazenNiz)
{
	int donjaGranica = 0;
	int gornjaGranica = trenutnoElemenata[brojKuglica] - 1;

	for (int trenutnoPoredimKuglicu = 0; trenutnoPoredimKuglicu < brojKuglica; ++trenutnoPoredimKuglicu) {
		int trenutnaKuglicaKojaSeTrazi = trazenNiz[trenutnoPoredimKuglicu];

		int tmp_donjaGranica  = BinarySearch(trenutnaKuglicaKojaSeTrazi, trenutnoPoredimKuglicu, donjaGranica, gornjaGranica, true, brojKuglica);
		int tmp_gornjaGranica = BinarySearch(trenutnaKuglicaKojaSeTrazi, trenutnoPoredimKuglicu, donjaGranica, gornjaGranica, false, brojKuglica);

		donjaGranica = tmp_donjaGranica;
		gornjaGranica = tmp_gornjaGranica;

		if (donjaGranica == -1) return 0;
	}

	return gornjaGranica - donjaGranica + 1;
}

/*
O(Q*K*log(binom(K, K/2) * N)) ~ O(Q*K*K*logN)
*/
void UcitajIOdradiUpite()
{
	scanf("%d", &Q);
	for (int q = 0; q < Q; ++q) {
		for (int i = 1; i <= K; ++i) {
			scanf("%d", &komb[i-1]);

			// nije bitno kako cemo sortirati
			sort(komb, komb+i);
			int resenje = BinarySearchNiz(i, komb);

			if (i > 1) {
				printf(" ");
			}
			printf("%d", resenje);
		}
		printf("\n");
	}
}

/*
O(SUM_{i=1..K] i*(binom(K, i)*N+M)) ~ O(K*N*2^K + K^2*M)
+
O(Q*K*log(binom(K, K/2) * N)) ~ O(Q*K*K*logN)
````````````~~
O(K*N*2^K + K^2*M + Q*K^2*logN)

ukoliko se koristi sort()
~ O(K*N*2^K*(K*logN) + Q*K^2*logN)
*/
int main()
{
	UlazIgraci();
	UbaciUNizove();
	SortSveNizove();
	UcitajIOdradiUpite();

	return 0;
}

```
