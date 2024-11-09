---
hide:
  - toc
---

# 1 - Nadovezivanje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 128MB |

Ove godine, Komisija je odlučila da svim takmičarima pokloni nešto
lepo, tako da ste na poklon dobili tri broja $A$, $B$ i
$C$. Iznenađeni ovim pre svega korisnim poklonom, odlučili ste da vam
je i jedan broj dovoljan, tako da ćete ova tri broja spojiti u jedan
nadovezivanjem (na primer, ako ste dobili brojeve $50$, $2$ i $7$,
možete ih spojiti u $7502$).

Naravno, postoji više načina da spojite tri broja, i odlučili ste da
odaberete onaj koji će vam dati **najveći** broj. Vaš zadatak je da
napišete program koji će, za data tri broja, pronaći najveći broj koji
je moguće dobiti njihovim nadovezivanjem.

## Opis ulaza

U prvom i jedinom redu standardnog ulaza nalaze se tri cela broja $A$,
$B$ i $C$: brojevi koje ste dobili na poklon.

## Opis izlaza

U jedinoj liniji ispisati najveći broj koji je moguće dobiti
nadovezivanjem data tri broja.

## Primer 1

### Ulaz

~~~
15 9 12
~~~

### Izlaz

~~~
91512
~~~

## Primer 2

### Ulaz

~~~
10 102 10
~~~

### Izlaz

~~~
1021010
~~~

## Objašnjenje primera

Brojevi koje možemo dobiti spajanjem $15$, $9$ i $12$ u prvom primeru
su: $15|9|12$, $15|12|9$, $9|15|12$, $9|12|15$, $12|15|9$ i
$12|9|15$. Najveći od ovih brojeva je $91512$.

U drugom primeru možemo dobiti $10|10|102$, $10|102|10$ i $102|10|10$,
tako da je rešenje $1021010$.

## Ograničenja

* $1 \leq A, B, C$

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 20 poena: $A, B < 10$ i $C < 100$.
* U test primerima vrednim 40 poena: $A, B, C \leq 1000$.
* U test primerima vrednim 20 poena: $A, B, C \leq 10^9$.
* U test primerima vrednim 20 poena: $A, B, C \leq 10^{18}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dimitrije Erdeljan | Aleksa Milisavljević | Aleksa Milisavljević |

## Analiza
Zadatak rešavamo jednostavnom proverom slučajeva, napravimo svih 6 permutacija i proverimo koja ima najveću vrednost. Primetimo da su brojevi preveliki da bi stali u tip ```int``` u C++, ali možemo koristiti tip ```long long```. Međutim, najpogodnije je da brojeve učitamo kao ```string```. Tada se operacija spajanja tri broja u nekom redosledu svodi na konkateniranje stringova. U C++ konkateniranje dva stringa ```A``` i ```B``` realizujemo sa ```A+B```. Funkcija ```max``` u C++ vraća leksikografski veći string, ako su joj argumenti stringovi. U našem slučaju, pošto će svih 6 permutacija (```A+B+C```, ```A+C+B```, ```B+A+C```, ```B+C+A```, ```C+A+B``` i ```C+B+A```) imati istu dužinu, leksikografski najveća permutacija je i najveći broj koji možemo dobiti pri spajanju brojeva $A$, $B$ i $C$.

``` cpp title="01_nadovezivanje.cpp" linenums="1"
#include <iostream>
#include <string>

int main()
{
    std::string a, b, c;
    std::cin >> a >> b >> c;

    std::string res = a + b + c;
    res = std::max(res, a + c + b);
    res = std::max(res, b + a + c);
    res = std::max(res, b + c + a);
    res = std::max(res, c + a + b);
    res = std::max(res, c + b + a);

    std::cout << res << std::endl;
    return 0;
}

```
