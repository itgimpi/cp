---
hide:
  - toc
---

# 5 - Luxor

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 64MB |


U nedavnoj poseti hramu u Luksoru naišli ste na interesantnu, drevnu zagonetku. Naime, staroegipatski mudraci su voleli da množe i da računaju XOR-vrednost parova prirodnih brojeva. Naišli ste na tablu na kojoj je ispisano $T$ parova nenegativnih celih brojeva $A_i, B_i$. Interesantno je da je kod svih ovih parova broj $A_i$ neparan. Vaš zadatak je da za svaki od tih parova pronađete dva prirodna broja $X_i, Y_i$ takva da važi $A_i = X_iY_i$ i $B_i = X_i \text{ xor } Y_i$. Moguće je da takav par ne postoji, ukoliko je to slučaj, ispišite $-1$.

## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se prirodan broj $T$. U narednih $T$ linija nalaze se po dva nenegativna cela broja odvojena razmakom, $A_i$ i $B_i$.

## Opis izlaza

U $T$ redova, po jedan za svaki upit, ispisati traženi par $X_i, Y_i$, odvojen razmakom. Ukoliko takav par ne postoji, ispisati $-1$. Ukoliko ima više rešenja, ispisati bilo koje.

## Primer 1

### Ulaz

```
4
21 4
2795079079011879151 119681854
9 0
9 2
```

### Izlaz

```
3 7
1679133257 1664596343
3 3
-1
```

## Ograničenja

- $1 \leq T \leq 10.000$
- $0 \leq A_i, B_i < 2^{62}$
- $A_i$ je neparan.

Test primeri su podeljeni u 3 disjunktne grupe:

- U test primerima vrednim 20 poena: $T \leq 10$ i $A_i, B_i \leq 10^{13}$.
- U test primerima vrednim 20 poena: $T \leq 500$.
- U test primerima vrednim 60 poena: Bez dodatnih ograničenja.

## Napomena

Operator XOR, odnosno ekskluzivnu disjunkciju u C++ zapisujemo pomoću simbola `^`. Ova operacija $x\ \text{xor} \ y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način. Prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots b_k$. Zatim se za svaku poziciju $i \in \{1, \ldots, k \}$ računa $c_i$ pomoću sledećih pravila:

* Za $a_{i} = 0, b_{i} = 0$ važi $c_{i} = 0$
* Za $a_{i} = 0, b_{i} = 1$ važi $c_{i} = 1$
* Za $a_{i} = 1, b_{i} = 0$ važi $c_{i} = 1$
* Za $a_{i} = 1, b_{i} = 1$ važi $c_{i} = 0$

Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \ \text{xor} \  y$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić i Lazar Korsić | Ivan Stošić | Aleksandar Zlateski |


## Podzadatak 1

Primetimo da je jedan od brojeva $X,Y$ manji ili jednak $\sqrt{A}$, pa je dovoljno izvršiti pretragu po svim brojevima $X$ do $\sqrt{A}$, gde proveravamo da je $Y = \frac{A}{X}$ ceo broj i da je $X \text{ XOR } Y = B$. Vremenska složenost po primeru je $O(\sqrt{A})$.

## Podzadatak 2

Da bi se smanjio broj kandidata za broj $X$ primetimo da $X$ mora biti delilac broja $A$. Može se iskoristiti bilo koji brzi algoritam za faktorizaciju celih brojeva. Jedan takav algoritam je *Pollard-Rho* algoritam, koji se najčešće implementira zajedno sa *Miller-Rabin* algoritmom za proveru da li je broj prost. Ovaj algoritam ima vremensku složenost $O(\sqrt[4]{n})$ za nalaženje jednog faktora broja $n$, ali ima veliku skrivenu konstantu i iz tog razloga nije dovoljno brz.

## Glavno rešenje

Najpre, primetimo da pri računanju XOR vrednosti i proizvoda dva broja, najnižih $n$ bitova rezultata zavise samo od najnižih $n$ bitova operanada. Ako posmatramo fiksne vrednosti $n, a, b$, gde je $0 \leq a, b < 2^n$ i $a$ je neparno, pokazuje se da postoji najviše $2^{\lfloor\frac{n+3}{2}\rfloor}$ rešenja jednačine

$xy \equiv a \mod 2^n, x \text{ XOR } y = b$,

gde su $x,y$ nepoznate, takođe brojevi iz skupa $[0, 2^n)$. Iz tog razloga, ako fiksiramo najnižih $n$ bitova broja $X$, ovakvih validnih parcijalnih rešenja neće biti više od $2^{\lfloor\frac{n+3}{2}\rfloor}$. Ova parcijalna rešenja možemo generisati rekurzivno. U $n$ tom nivou rekurzije imamo ne više od $2^{\lfloor\frac{n+3}{2}\rfloor}$ poziva. Dovoljno je pronaći samo prvih $31$ bitova broja $X$, jer je zbog uslova $XY=A$ bar jedan od brojeva $X,Y$ manji ili jednak $A$, a uvek možemo da pretpostavimo da je to broj $X$. Sumiranjem po $n$ dobijamo da ima $O(\sqrt[4]{A})$ rekurzivnih poziva, pa je upravo ovo vremenska složenost rešavanja jednog test primera.

``` cpp title="05_luxor.cpp" linenums="1"
#include <iostream>
using namespace std;

typedef unsigned long long ull;

bool rek(ull a, ull b, ull x, int i) {
	ull y = b ^ x;
	ull m = (1ull << i) - 1;
	if (((x*y) ^ a) & m)
		return false;
	if (i == 32)
		return false;
	if (x*1.0*y < 5e18 && x*y == a) {
		cout << x << ' ' << y << '\n';
		return true;
	}
	if (rek(a, b, x, i+1))
		return true;
	return rek(a, b, x|(1ull<<i), i+1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t;
	cin >> t;
	while (t--) {
		ull a, b;
		cin >> a >> b;
		if (!rek(a, b, 0, 0))
			cout << "-1\n";
	}
}
```
