---
hide:
  - toc
---

# 1 - Vatra

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 64MB |


Pre oko dvadeset hiljada godina, praistorijski ljudi su dosta vremena provodili u pećinama.
Tokom noći, da ih životinje ne bi napale, zapalili bi vatru. Jedno veče, pre spavanja, primetili su da im vatra neće izdržati do ujutru, te su našli tri predmeta koja su hteli da ubace u vatru i time produže vreme trajanja vatre. Međutim, ubacivanje nekih od tih predmeta bi moglo da dovede do skraćivanja vremena trajanja vatre, te nije isplativo ubaciti te predmete.
Za svaki od tri predmeta vama je dato za koliko bi se promenilo vreme trajanja vatre (ovaj broj
može da bude i negativan) ukoliko bi se taj predmet ubacio u vatru. Vaš zadatak je da odredite
maksimalno vreme za koje je moguće produžiti trajanje vatre.

## Opis ulaza
U prvom i jedinom redu standardnog ulaza se nalaze tri cela broja $x_1$, $x_2$ i $x_3$, gde $x_i$ predstavlja vreme za koje bi se promenilo trajanje vatre ukoliko bi se i-ti predmet ubacio u vatru.

## Opis izlaza
U prvi red standardnog izlaza ispisati jedan ceo broj koji predstavlja maksimalno vreme
za koje je moguće produžiti vreme trajanja vatre.

## Primer 1
### Ulaz
```
5 -3 7
```

### Izlaz
```
12
```

## Primer 2
### Ulaz
```
-4 -4 5
```

### Izlaz
```
5
```

## Ograničenja

* $-1000 \leq x_1,x_2,x_3\leq 1000$.
* Bar jedan od brojeva u ulazu će uvek biti nenegativan.

## Napomena
Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim 30 poena važi $x_1$, $x_2$, $x_3$ $\geq 0$.
* U test primerima vrednim 70 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Boris Grubić | Boris Grubić | Milica Mićić | Lazar Milenković |

## Rešenje za $x_1, x_2, x_3 \geq 0$ :
Kada bi se bilo koji od predmeta ubacio u vatru dužina njenog gorenja bi se povećala. Vatra bi onda najduže gorela ako bi se svaki od tih predmeta ubacio i zato je potrebno samo ispisati zbir sve tri date vrednosti.

## Glavno rešenje:
Želimo da odaberemo samo predmete koji imaju nenegativnu vrednost produžavanja trajanja vatre i njihove vrednosti sabiramo kao krajnje rešenje. Ako bi se uzeo i neki od predmeta sa negativnim brojem konačno vreme gorenja bi se samo smanjilo.



``` cpp title="01_vatra.cpp" linenums="1"
#include <iostream>

using namespace std;

int main() {
    int x1, x2, x3;
    cin >> x1 >> x2 >> x3;
    cout << max(0, x1) + max(0, x2) + max(0, x3) << endl;
    return 0;
}

```
