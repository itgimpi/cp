---
hide:
  - toc
---

# 1 - Nesusedni

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 200ms | 256MB |

Programer Pera ima omiljeno slovo $c_1$ (jedno od malih slova engleskog alfabeta) i poseduje $a_1$ komada ovog slova. Programerka Petra takođe ima svoje omiljeno slovo $c_2$ (jedno od malih slova enegleskog alfabeta, različito od Petrovog) i $a_2$ komada svog slova. 

Pera i Petra su rešili da naprave string u kome će se naći **svih** $a_1+a_2$ njihovih slova ali takav da u njemu **ne postoje dva ista susedna slova**. Odredite bilo koji string koji zadovoljava ove uslove ili konstatujte da takav string ne postoji.

## Opis ulaza
U prvom redu standardnog ulaza se nalaze Perino i Petrino slovo $c_1$ i $c_2$, redom, **bez razmaka**. U narednom redu se nalaze dva prirodna broja $a_1$ i $a_2$, razdvojena razmakom, koja predstavljaju broj komada slova koje poseduju Pera i Petra, redom.

## Opis izlaza
U prvom redu ispisati string koji zadovoljava sve uslove iz zadatka. **Ukoliko ima više rešenja, ispisati bilo koje**. Ukoliko rešenje ne postoji, ispisati 'nemoguce' (bez navodnika).

## Primer 1

### Ulaz

```
ab
2 2
```

### Izlaz

```
baba
```

## Primer 2

### Ulaz

```
nm
4 10
```

### Izlaz

```
nemoguce
```

## Objašnjenja primera
U prvom primeru su iskorišćena 2 slova 'a' i 2 slova 'b' i ne postoje dva ista susedna slova - dakle, string je validan. String 'abab' je takođe validno rešenje za ovaj primer. U drugom primeru, ma kako rasporedili 4 slova 'n' i 10 slova 'm', uvek će postojati dva susedna ista slova pa traženi string ne postoji.

## Ograničenja
- $c_1$ i $c_2$  su međusobno različita mala slova engleskog alfabeta
-   $1 \leq a_1, a_2 \leq 50.000$

Test primeri su podeljeni u 3 disjunkne grupe:

-   U test primerima vrednim $20$ poena važi $c_1 =$ '$a$',  $c_2 =$ '$b$' i $1 \leq a_1, a_2 \leq 3$.
-   U test primerima vrednim $40$ poena važi $1 \leq a_1, a_2 \leq 1.000$
-   U test primerima vrednim $40$ poena nema dodatnih ograničenja.





#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Vladimir Milovanović |

Kako imamo tačno 2 različita slova, jedini način da string ne sadrži dva ista susedna slova je da se slova pojavljuju naizmenično u stringu tj. $c_1c_2c_1c_2\ldots$ ili $c_2c_1c_2c_1\ldots$. Ovo je moguće ako i samo ako je $|a_1 - a_2| \leq 1$. Zaista, ako je $|a_1 - a_2| > 1$, "istrošićemo" jedno slovo u naizmeničnom pojavljivanju pre kraja stringa. Sa druge strane, ako je $a_1 = a_2$, imamo 2 moguća rešenja (bilo koje slovo može biti prvo), a ako je $|a_1 - a_2|=1$, rešenje je jedinstveno jer moramo početi (i završiti) slovom koje se pojavljuje više puta.

Složenost algoritma je $O(a_1 + a_2)$, zbog ispisa.

``` cpp title="01_nesusedni.cpp" linenums="1"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); // uvek dodati ovu liniju ako se radi sa cin/cout umesto sa scanf/printf (iako nije neophodna za ovaj zadatak)

	char c1, c2;
	int a1, a2;

	cin >> c1 >> c2;
	cin >> a1 >> a2;

	if (abs(a1 - a2) > 1)
	{
		cout << "nemoguce" << "\n";
		return 0;
	}

	if (a1 < a2)
	{
		char tmp = c1;
		c1 = c2;
		c2 = tmp;
	}

	for (int i = 0; i < a1 + a2; i++)
	{
		if (i % 2 == 0)
			cout << c1;
		else
			cout << c2;
	}

	cout << "\n";
	return 0;
}

```
