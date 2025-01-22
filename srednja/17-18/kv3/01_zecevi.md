---
hide:
  - toc
---

# 1 - Zečevi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 200ms | 64MB |

Anja ima tri zeca, čije su visine prirodni brojevi. Anja obožava aritmetičke progresije, i želi da za rođendan nabavi još jednog zeca čija je visina prirodan broj, tako da može da poređa ta četiri zeca a da njihove visine čine aritmetičku progresiju. Pomozite Anji tako što ćete joj reći koje visine da bude novi zec. Ukoliko nije moguće nabaviti jednog novog zeca tako da ovo važi ispišite $-1$.

## Opis ulaza
U prvoj i jedinoj liniji standardnog ulaza nalaze se tri prirodna broja $a_1, a_2, a_3$, odvojena razmacima - visine zečeva koje Anja trenutno ima.

## Opis izlaza
Na prvu liniju standardnog izlaza ispisati visinu novog zeca, ili $-1$ ukoliko nije moguće nabaviti takvog zeca. Ukoliko ima više rešenja, štampati bilo koje.

## Primer 1
### Ulaz
```
3 7 5
```

### Izlaz
```
1
```

## Primer 2
### Ulaz
```
10 6 2
```

### Izlaz
```
14
```

## Primer 3
### Ulaz
```
999999 999997 999998
```

### Izlaz
```
999996
```

## Primer 4
### Ulaz

```
2 2 3
```

### Izlaz
```
-1
```

## Objašnjenja primera
U prvom primeru, drugo moguće tačno rešenje je $9$.

Visina novog zeca takođe mora biti prirodan broj.

U trećem primeru, nije moguće naći zeca tako da se zajedno preurede u aritmetičku progresiju.

## Ograničenja

* $1 \leq a_1, a_2, a_3 \leq 10^9$.
* U $50\%$ primera važi $1 \leq a_1, a_2, a_3 \leq 1000$.

## Napomena

Za niz brojeva $a_1, a_2, \ldots, a_n$ kažemo da čini aritmetičku progresiju ukoliko postoje brojevi $b, c$ tako da je $a_i = b + c \cdot i$ za svako $i \in \{ 1, \ldots, n \}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Ivan Stošić | Dušan Zdravković |

Učitamo visine tri zeca i uredimo ih u neopadajući redosled. Dobijamo tri broja $b_1 \leq b_2 \leq b_3$. Posmatrajmo razlike $d_1 = b_2 - b_1$ i $d_2 = b_3 - b_2$. Ukoliko su ove razlike jednake, moguće je naći rešenje, to je broj $b_3 + d_2$ i on zajedno sa ostala tri čini aritmetičku progresiju. I broj $b_1 - d_1$ takođe čini aritmetičku progresiju sa ostala tri broja ali ovaj broj može biti manji ili jednak nuli, dok prethodno navedeni $b_3 + d_2$ ne može, jer je veći ili jednak od $b_3$ koji je prirodan broj. Dalje, ukoliko je $d_1 = 2 d_2$, odnosno, ukoliko je razlika drugog i prvog broja duplo veća od razlike trećeg i drugog broja, možemo dodati novi broj između prva dva, a to je broj $b_1 + d_2$, i on sa ostalima čini aritmetičku progresiju. Ako je pak $d_2 = 2 d_1$ možemo dodati broj $b_2 + d_1$ i on će sa preostala tri činiti aritmetičku progresiju. Ako nijedan od ovih uslova nije ispunjen, takav broj ne postoji.

``` cpp title="01_zecevi.cpp" linenums="1"
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a[3], t;
	cin >> a[0] >> a[1] >> a[2];
	sort(a, a+3);
	int d1 = a[1] - a[0];
	int d2 = a[2] - a[1];
	if (d1 == d2) {
		t = a[2] + d2;
	} else if (d1 == 2*d2) {
		t = a[1] - d2;
	} else if (d2 == 2*d1) {
		t = a[1] + d1;
	} else {
		t = -1;
	}
	cout << t << '\n';
}
```
