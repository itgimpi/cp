---
hide:
  - toc
---

# B2 - Raketa

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 256MB |

Javna je tajna da ukoliko želite da idete na Mars morate imati raketu. Međutim, samo retki znaju da ukoliko želite i da stignete do Marsa, motori na vašoj raketi moraju biti što izbalansiraniji.

Pošto je Mars četvrta planeta Sunčevog sistema, raketa kojom želite da idete na njega mora imati četiri motora, i oni moraju biti raspoređeni u formaciju $2 \times 2$. Prilikom lansiranja, svaki od motora je podešen na neku svoju početnu snagu. Kapetan rakete pomoću sistema poluga može da pojačava snagu motora, i to tako da prilikom svake operacije za 1 pojača snagu tačno dva motora koja su ili u istoj vrsti ili u istoj koloni. U nauci o raketama, klackavost rakete se definiše kao razlika najveće i najmanje snage od snaga njena četiri motora. Pomozite kapetanu da što bolje izbalansira raketu tako što će primenom raspoloživih operacija dovesti klackavost na najmanju moguću vrednost.

## Opis ulaza
Sa standardnog ulaza se učitavaju četiri nenegativna cela broja koji predstavljaju početne snage četiri motora. U prvom redu ulaza zapisane su početne snage levog i desnog motora iz gornjeg reda, a u drugom redu ulaza zapisane su početne snage levog i desnog motora iz donjeg reda.

## Opis izlaza
U jedini red standardnog izlaza zapisati jedan broj koji predstavlja najmanju moguću klackavost rakete koja se može postići.

## Primer 1
### Ulaz
```
1 1
0 3
```

### Izlaz
```
2
```

## Primer 2
### Ulaz
```
9 8
7 0
```

### Izlaz
```
3
```

## Objašnjenje primera
U prvom primeru, ako operaciju pojačavanja snage primenimo jednom na gornju vrstu i dva puta na levu kolonu, dobićemo sledeću konfiguraciju snaga.
```
4 2
2 3
```
Kako nije moguće postići manju klackavost, optimalna klackavost je $4 - 2 = 2$.

## Ograničenja
* U $32%$ test primera početna snaga svakog motora nije veća od $44$.
* U $44%$ test primera početna snaga svakog motora nije veća od $110$.
* U $56%$ test primera početna snaga svakog motora nije veća od $1300$.
* U $68%$ test primera početna snaga svakog motora nije veća od $10^7$.
* U $100%$ test primera početna snaga svakog motora nije veća od $5 \cdot 10^8$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Savić | Marko Savić | Marko Savić | Nikola Spasić |

Rešenje možete pogledati na sledećoj adresi: [Link](https://github.com/olympicode/olympicode-site/blob/main/docs/takprog/2016_2017/okr/02_raketa-sol.pdf)

``` cpp title="02_raketa.cpp" linenums="1"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	cout << (abs(a+d-b-c) + 1) / 2;
	return 0;
}

```
