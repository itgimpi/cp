---
hide:
  - toc
---

# 3 - Sazvežđa

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |


Nena je sinoć sanjala da gleda u zvezdano nebo, koje se može zamisliti kao dvodimenziona ravan, u kojoj se nalaze zvezde, koje su predstavljene kao tačke. Kada se probudila, pored toga što je shvatila da kasni, zaboravila je skoro sve detalje svog sna. Jedino što je zapamtila je $K$, broj kolinearnih trojki tačaka. Formalno, ako su zvezde bile različite tačke $A_1, A_2, \ldots, A_N$, broj kolinearnih trojki je broj uređenih trojki $(i,j,k)$ takvih da je $1 \leq i < j < k \leq N$ i tačke $A_i, A_j, A_k$ su kolinearne.

Pomozite Neni tako što ćete joj reći jedan skup sa najviše $2000$ različitih tačaka za koji važi da je broj kolinearnih trojki tačno $K$. Nena voli cele brojeve, a ne voli brojeve kojima je apsolutna vrednost veća od $10^9$, pa koordinate vašeg skupa tačaka takođe moraju zadovoljavati ove osobine. **Nije potrebno minimizovati broj tačaka. Garantuje se da pod datim ograničenjima uvek postoji bar jedno rešenje.**

## Opis ulaza

U prvom i jedinom redu standardnog ulaza nalazi se jedan ceo broj $K$, traženi broj kolinearnih trojki.

## Opis izlaza

U prvi red standardnog izlaza ispisati prirodan broj $N$, broj tačaka. U narednih $N$ redova ispisati cele brojeve $x_i, y_i$, koordinate tačke $A_i$. Za ove brojeve mora da važi $-10^9 \leq x_i, y_i \leq 10^9$. Sve odštampane tačke moraju biti različite.

## Primer 1

### Ulaz

```
8
```

### Izlaz

```
9
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
```

## Primer 2

### Ulaz

```
2
```

### Izlaz

```
5
0 2
0 1
0 0
1 0
2 0
```

## Primer 3

### Ulaz

```
4
```

### Izlaz

```
4
0 0
1 1
2 2
3 3
```

## Objašnjenja primera

- U prvom primeru tačke formiraju kvadratnu mrežu formata $3 \times 3$. Postoje $3$ kolinearne trojke po vrstama, $3$ kolinearne trojke po kolonama i $2$ kolinearne trojke po dijagonalama, što je ukupno $8$ kolinearnih trojki.

- U drugom primeru, prve tri tačke čine jednu kolinearnu trojku, a poslednje tri tačke drugu kolinearnu trojku.

- U trećem primeru, svaka trojka je kolinearna, takvih trojki ima $4$.

## Ograničenja

- $1 \leq K \leq 10^8$

Test primeri su podeljeni u 4 disjunktne grupe:

- U test primerima vrednim 20 poena: $K \le 10$.
- U test primerima vrednim 20 poena: $K \leq 2000$.
- U test primerima vrednim 20 poena: $K \leq 10^6$.
- U test primerima vrednim 40 poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Ivan Stošić | Marko Savić |


Ukoliko imamo $x$ tačaka i sve leže na istoj pravoj, svaka trojka je kolinearna, pa je broj takvih trojki jednak $\binom{x}{3}$. Jedno rešenje je da se napravi niz brojeva $b_1, b_2, \ldots, b_m$ takav da važi $\binom{b_1}{3} + \binom{b_1}{3} + \ldots + \binom{b_m}{3} = K$ i da se izgeneriše $m$ pravih, da se na $i$-tu pravu nanese $b_i$ tačaka, i da se sve ovo uradi na takav način da nijedne tri tačke ne budu kolinearne osim ukoliko potiču sa iste prave.

Ovaj niz brojeva se može naći grabljivim postupkom - dokle god je $K > 0$, biramo najveće $x$ takvo da je $\binom{x}{3} \leq K$, dodajemo $x$ na niz i smanjujemo $K$ za $\binom{x}{3}$. Može se pokazati (na primer, primenom grube sile) da ovaj postupak rezultira u ne više od $1049$ tačaka, i to u ne više od $10$ koraka.

Za prave možemo izabrati uzastopne različite prave koje su paralelne $x$-osi, odnosno prave $y=1, y=2, \ldots$. Tačke možemo ređati počev od koordinate $q_i = i^2 \times 10^6$ za $i$-tu pravu, odnosno, na pravoj sa rednim brojem $i$ biće tačke ${(q_i, i)}, {(q_i+1, i)}, \ldots, {(q_i+b_i-1, i)}$. Ova "konveksnost" obezbeđuje da nijedne tri tačke sa različitih pravih ne budu kolinearne.

Podzadaci se mogu rešiti primenom grube sile ili nekog jednostavnijeg postupka postavljanja pravih.

``` cpp title="03_sazvezdja.cpp" linenums="1"
#include <iostream>
using namespace std;

int f(int b) {
	return b*(b-1)*(b-2)/6;
}

int k, l, e, x[2005], y[2005];

int main() {
	cin >> k;
	while (k > 0) {
		int b = 0;
		while (f(b+1) <= k)
			b++;
		k -= f(b);
		for (int i=0; i<b; i++)
			x[e] = l*l*500000+i, y[e++] = l;
		l++;
	}
	cout << e << '\n';
	for (int i=0; i<e; i++)
		cout << x[i] << ' ' << y[i] << '\n';
}
```
