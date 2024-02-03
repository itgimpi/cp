---
hide:
  - toc
---

# B1 - Pangram

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Moreplovac Brle je u jednoj od svojih pustolovina nabasao na novo, neotkriveno ostrvo. Kada je pokušao da priđe ostrvu ugledao je rečenicu ispisanu ogromnim slovima u pesku. Nažalost, palmini listovi prekrivaju delove plaže, pa neki delovi rečenice nisu vidljivi. Poznato je da je ispisana rečenica savršen pangram (sadrži svako slovo engleske abecede **tačno jednom**) i sastoji se isključivo od slova engleske abecede i razmaka. Pritom, ne postoje dva susedna razmaka, i rečenica ne počinje niti se završava razmakom. Vaš zadatak je da pomognete Brletu da rekonstruiše ispisanu rečenicu, ukoliko je to moguće. 

## Opis ulaza
U prvoj liniji standardnog ulaza nalazi se broj $N$. U drugoj liniji standardnog ulaza nalazi se string $A$ dužine $N$, koji predstavlja ispisanu rečenicu iz Brletove perspektive. Pritom važi: 

 - $A$ se sastoji isključivo od slova engleske abecede (slova iz skupa $\{a \dots z\}$), karaktera **_** koji označavaju razmake, i karaktera $?$ koji označavaju palmine listove tj. karaktere (slova ili razmake) koji nisu vidljivi.
 - U $A$ ne postoje dva susedna razmaka, a ni prvi i poslednji karakter $A$ nisu razmaci.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati string $B$, koji predstavlja rekonstruisanu rečenicu. Pritom mora da važi: 

 - $B$ se sastoji isključivo od slova engleske abecede i karaktera **_** koji označavaju razmake.
 - U $B$ ne postoje dva susedna razmaka, a ni prvi i poslednji karakter $B$ nisu razmaci.
 - $B$ je savršen pangram.
 - Moguće je dobiti $B$ od $A$ isključivo nizom zamena karaktera $?$ slovima engleske abecede ili razmacima.

Ukoliko ima više rešenja, ispisati bilo koje. Ukoliko takvo $B$ ne postoji (tj. rekonstrukcija nije moguća) Brle sanja i potrebno je ispisati string `SAN` (velikim slovima).

## Primer 1
### Ulaz
```
29
abc????ghijklm_nopqrst???xyz?
```

### Izlaz
```
abcdfe_ghijklm_nopqrstu_vxyzw
```

## Primer 2
### Ulaz
```
28
abcdefghijklmnopqrstuvwxy???
```

### Izlaz
```
SAN
```

## Objašnjenje primera
U prvom primeru možemo pretpostaviti da prva serija palminih listova prekriva karaktere $dfe\_$, druga $u\_v$, a treća $w$. Ovako dobijamo savršen pangram koji ispunjava sve uslove.

U drugom primeru je nemoguće zameniti tri palmina lista karakterima tako da se dobije savršen pangram koji ispunjava sve uslove, pa je u pitanju san.

## Ograničenja

* $1 \leq N \leq 250$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima koji vrede 15 poena važi $1 \leq N \leq 26$.
* U test primerima koji vrede 15 poena nema palminih listova.
* U test primerima koji vrede 15 poena postoji najviše jedan karakter prekriven palminim listom.
* U test primerima koji vrede 15 poena cela rečenica je prekrivena palminim listovima.
* U test primerima koji vrede 40 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Nikola Jovanović | Nikola Jovanović | Dimitrije Erdeljan |

Označimo broj pojavljivanja karaktera **?** u stringu $A$ sa $U$, a skup slova engleske abecede koja se ne pojavljuju u stringu $A$ sa $S$. Jednim prolaskom kroz string možemo lako naći ove vrednosti. Ukoliko se neko slovo pojavljuje više od jednom možemo odmah zaključiti da rekonstrukcija nije moguća i prekinuti izvršavanje programa.

Sada znamo da treba zameniti tačno $|S|$ karaktera **?** slovima engleske abecede kako bi dobijena rečenica bila savršen pangram. Kako moramo zameniti sve karaktere **?**, sledi da treba zameniti tačno $R=U-|S|$  njih razmacima. Pritom, ako važi  $U < |S|$ nije moguće dodati sva nedostajuća slova, pa je ovo još jedan slučaj u kom zaključujemo da rekonstrukcija nije moguća.

Ostalo je još izvršiti samu rekonstrukciju tj. rasporediti slova i razmake. Treba imati u vidu da nije svejedno na koji način ovo radimo. Na primer, ako prvo dodamo svih $|S|$ slova  (tj. zamenimo prvih $|S|$  karaktera **?** slovima) možda neće biti moguće postaviti svih $R$ razmaka (npr. zbog uslova da dva razmaka ne smeju biti susedi). Primetimo da je uvek moguće dodati slovo, ali nije uvek moguće dodati razmak. Stoga, vršićemo rekonstrukciju tako da *greedy* dodajemo razmake dok ne dodamo svih $R$. Drugim rečima, krećemo se kroz string $A$ sa leva na desno, i na svakoj poziciji postavljamo razmak ukoliko su svi uslovi ispunjeni: na toj poziciji je karakter **?**, nismo na početku/kraju stringa, nijedan od dva susedna karaktera nije razmak. U suprotnom, dodajemo jedno od nedostajućih slova iz skupa $S$. Kada na ovaj način dodamo svih $R$ razmaka, sve preostale karaktere **?** menjamo preostalim nedostajućim slovima iz skupa $S$ i ispisujemo dobijeni string kao rešenje zadatka. Nije teško pokazati da se na ovaj način može dodati maksimalan broj razmaka, te da ukoliko ovakva procedura nije u stanju da doda svih $R$, došli smo do trećeg i poslednjeg slučaja u kom je nemoguće izvršiti rekonstrukciju. 

``` cpp title="01_pangram.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 255

using namespace std;

int N;
char A[MAXN];
unordered_map<char, int> cnt;

int main() {
	scanf("%d", &N);
	scanf("%s", A);
	for (int i = 0; i < N; i++) {
		cnt[A[i]]++;
		if (A[i] >= 'a' && A[i] <= 'z' && cnt[A[i]] == 2) {
			// neko slovo se pojavilo dvaput
			// nemoguce napraviti pangram
			printf("SAN\n");
			return 0;
		}
	}
	// skupimo slova koja fale
	vector<char> missing;
	for (int c = 'a'; c <= 'z'; c++) {
		if (cnt[c] == 0) {
			missing.push_back(c);
		}
	}
	// ne mora, naravno
	reverse(missing.begin(), missing.end()); 
	if (missing.size() > cnt['?']) {
		// nema dovoljno '?' da dodamo sva slova
		printf("SAN\n");
		return 0;
	}
	// koliko razmaka treba dodati?
	int spaces = cnt['?'] - missing.size();
	for (int i = 0; i < N; i++) {
		if (A[i] == '?') {
			if (i > 0 && i < N-1 && spaces > 0 && A[i-1] != '_' & A[i+1] != '_') {
				// treba i moze razmak
				A[i] = '_';
				spaces--;
			} else {
				// ne treba razmaka vise ili ne moze razmaka vise
				if (missing.empty()) {
					// nemoguce staviti dovoljno razmaka
					printf("SAN\n");
					return 0;
				} else {
					A[i] = missing.back();
					missing.pop_back();
				}
			}
		}
	}
	printf("%s\n", A);
	return 0;
}

```
