---
hide:
  - toc
---

# 1 - Misterija

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 64MB |

Trenutno se vodi veliki sajber-rat između dve najveće hakerske grupe; ”Anonimni” i ”Hakerinati”. Mali Perica, član Anonimnih, je dobio naizgled težak zadatak: da probije ”Misteriju”, mašinu preko koje se šifriraju sve poruke unutar Hakerinata. Algoritam koji ova mašina koristi je nepoznat, ali se zna da se za šifrovanje i deš ifrovanje koriste celobrojni ključevi $A$ i $B$, koji se povremeno menjaju.

Perica je, međutim, saznao da vođa Hakerinata obaveštava celu grupu o promeni ključa na jako nesiguran način - tako što objavi fajl koji u sebi sadrži dva cela broja koja predstavljaju zbir i razliku novih ključeva. Fajl se samouništava posle 50 sekundi, a Perici treba tačno 49.9 da bi probio na mrežu i pristupio mu; samim tim, nema dovoljno vremena da prepiše ove brojeve. Na vama je da napišete program koji će mu pomoći da otkrije nove klj učeve

## Opis ulaza
U prvom i jedinom redu standardnog ulaza nalaze se dva cela broja, $Z$ i $R$, odvojena razmakom, koji predstavljaju zbir i razliku ključeva $A$ i $B$, redom.

## Opis izlaza
U prvi i jedini red standardnog izlaza ispisati tražene ključeve $A$ i $B$, odvojene razmakom.

## Primer 1
### Ulaz
```
11 1
```

### Izlaz 
```
6 5
```

### Objašnjenje primera
Za $A=6$ i $B=5$ važi:

$$
Z = A+B = 11;
$$

$$
R = A-B = 1.
$$

## Ograničenja
* $-15000 \leq A, B \leq 15000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Petar Veličković | Boris Grubić |

Problem Misterija bio je ubedljivo najlakši zadatak na ovogodišnjim Kvalifikacijama, i predstavlja školski tip problema. Svi takmičari su pokušali ovaj zadatak ove godine, od čega je 564 takmičara uspešno osvojilo 100 bodova; prosečan broj osvojenih poena je 92.072, što čini ovaj problem definitivno najlakšim na svim Kvalifikacijama do sada.

Problem se jednostavno formuliše na sledeći način:

Za data dva cela broja $Z$ i $R$, odrediti cele brojeve $A$ i $B$ tako da važi: $A+B=Z$, $A-B=R$.

Do tačnog rešenja dolazimo jednostavnim premeštanjem ovog sistema jednačina:

$$
Z=A+B \rightarrow B=Z-A
$$

$$
R=A-B \rightarrow R=A-(Z-A) \rightarrow A=(Z+R)/2
$$

$$
B=Z-\frac{Z+R}{2} \rightarrow B=\frac{Z-R}{2}
$$

## Uobičajene greške
Takmičari uglavnom nisu imali problema sa implementacijom rešenja za ovaj zadatak. Jedna zanimljiva greška potkrala se kod takmičara koji su ispitivali da li su ulazni podaci u intervalu [-15000,15000], i odbijali da reše test primer ukoliko to ne bi bio slučaj. Međutim, u tekstu zadatka je jasno rečeno da su ova ograničenja data za izlazne promenljive $A$ i $B$, a ne za ulazne promenljive $Z$ i $R$, tako da je određen broj test primera pao ovim takmičarima.

Određeni takmičari su pokušavali da promenljive $A$ i $B$ nađu dvostrukom for petljom po njima; ovo rešenje na većini primera prekoračuje vremensko ograničenje. Takođe je bilo takmičara koji su promenljive $A$ i $B$ čuvali u realnim tipovima i ispisivali ih sa decimalnim zarezom i određenim brojem nula iza zareza (iako je naglašeno da će uvek biti celi); međutim, ocenjivač je u tom slučaju odmah obaveštavao takmičare da im je netačan izlaz na primeru iz teksta zadatka, te se nadamo da su ovu ”grešku” uspeli da isprave.

``` cpp title="01_misterija.cpp" linenums="1"
#include <stdio.h>

int pl, mi;

int main()
{
    scanf("%d%d", &pl, &mi);
    printf("%d %d\n", (pl + mi) / 2, (pl - mi) / 2);
    return 0;
}
```
