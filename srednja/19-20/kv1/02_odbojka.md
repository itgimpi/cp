---
hide:
  - toc
---

# 2 - Odbojka

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Pavle i Živko su dva drugara koja mnogo vole da igraju odbojku. Pošto ne mogu da igraju sami, napravili su dva tima. Kapiten prvog tima je Pavle, a kapiten drugog tima je Živko. 

Organizovali su veliki odbojkaški meč. Odbojkaški meč se igra po pravilu "u tri dobijena seta", odnosno prvi tim koji osvoji tri seta je pobednik i meč se tada završava. Da bi se osvojio jedan set potrebno je osvojiti bar $A$ poena u tom setu. Igra se "na razliku", pa se set ne može završiti ukoliko je razlika u poenima manja od $2$. Set se završava čim neki od timova ima $A$ ili više poena, pri čemu je razlika bar $2$. Broj poena u jednom setu nije ograničen.

Na primer, za $A=50$ neki od mogućih rezultata na kraju seta su: $50:45$, $48:50$, $125:123$, $49:51$, $50:0$, dok neki od rezultata koji nisu mogući na kraju seta su: $50:49$, $61:60$, $50:50$, $45:43$, $60:50$, $50:53$, $63:20$. 

Novinar jednog dnevnog lista je došao na stadion baš na kraju meča i nije znao koji je bio krajnji rezultat. Pitao je kapitene za rezultat kako bi mogao da napiše članak o ovom nesvakidašnjem meču. Pavle i Živko nisu hteli da mu kažu tačan rezultat, jer su bili ljuti na novinara zbog kašnjenja, ali su mu ipak rekli koliki je bio ukupan broj poena tokom celog meča. Novinaru je jako važno da napiše vest o meču, čak i po cenu da ona nije tačna. Jedino mu je bitno da se ukupan broj poena poklapa sa onim brojem koji su mu rekli kapiteni i da je meč bio validan. Pomozite novinaru i napišite program koji će za ukupan broj poena na meču i minimalan broj poena koji je potreban da se osvoji jedan set odrediti da li postoji takav meč i naći rezultat na kraju meča. Ukoliko ima više mogućih rešenja, ispisati bilo koje.

## Opis ulaza

Na stadnardnom ulazu su data dva prirodna broja $N$ i $A$. Broj $N$ predstavlja ukupan broj poena na meču. Broj $A$ predstavlja minimalan broj poena koji je potreban da bi se osvojio jedan set. 

## Opis izlaza

Ukoliko traženi meč ne postoji, na izlazu samo ispisati `-1`. Ako takav meč postoji, ispisati bilo koji mogući meč tako što se ispišu rezultati po setovima u redosledu u kom su setovi igrani. Rezultat svakog seta prikazati u zasebnom redu, ispisivanjem dva broja koja predstavljaju poene koje su u tom setu osvojili timovi Pavla i Živka, tim redom.

Voditi računa da se igra na $3$ dobijena seta, pa je najmanji mogući broj setova $3$, a najveći $5$.

## Primer 1

### Ulaz

```
92 10
```

### Izlaz

```
10 7
3 10
12 10
13 15
10 2
```

## Primer 2

### Ulaz

```
20 20
```

### Izlaz

```
-1
```

## Primer 3

### Ulaz

```
163 25
```

### Izlaz

```
25 17
12 25
25 23
25 11
```

## Ograničenja
* $2 \leq N,A \leq 10^{9}$

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim 30 poena: $N,A \leq 20$.
* U test primerima vrednim 40 poena: $A=25$.
* U test primerima vrednim 30 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Filip Ćosović | Nikola Jovanović | Marko Savić |

## Analiza
Postoje dva slučaja u kojima traženi meč ne postoji: ukoliko važi $N < 3A$ (jer moramo imati barem $3$ seta sa barem $A$ poena u svakom), ili ukoliko važi $A=2$ i $2 \nmid n$ (jer se tada svaki set završava razlikom tačno $2$, pa ukupan broj poena mora biti paran).

U svim ostalim slučajevima, možemo pronaći rešenje u tačno $3$ seta. Pretpostavimo, bez umanjenja opštosti, da je prvi tim (čiji je kapiten Pavle) pobedio $3:0$ u setovima. Neka su prva dva seta završena rezultatom $A:0$. Dakle, u trećem setu je odigrano tačno $N' = N-2A$ poena. Imamo dva slučaja:

- Ako važi $N' \leq 2A-2$ tj. $N'-A \leq A-2$, treći set se ne igra ,,na razliku'' i završava se rezultatom $A : (N'-A)$.
- U suprotnom, $N' > 2A-2$ tj. $\frac{N'}{2}+1 > A$, i treći set se igra ,,na razliku'', tj. prvi tim osvaja više od $A$ poena i razlika je tačno $2$.
    - Ako je $N'$ parno, treći set se završava rezultatom $\frac{N'}{2}+1 : \frac{N'}{2}-1$. Po uslovu za ovaj slučaj, rezultat je validan.
    - Ako je $N'$ neparno, treći set se završava rezultatom $\frac{N'-1}{2}+1 : \frac{N'-1}{2}-1$. Ponovo, iz uslova za ovaj slučaj sledi $\frac{N'-1}{2}+1 > A$ (jer je $A$ prirodan broj), pa je ovaj rezultat validan. Sada nam preostaje $1$ poen koji prosto prebacujemo u drugi set, tako da rezultat u njemu postaje $A:1$ (ovo nije moguće uraditi jedino u slučaju $A=2$, ali taj slučaj smo za neparno $N'$, dakle neparno $N$, već obradili). 

``` cpp title="02_odbojka.cpp" linenums="1"
/* kod koji prolazi sve test primere */

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n,a;
    cin >> n >> a;
    if (n/3<a || (a==2 && n%2))
    {
        printf("-1\n");
        return 0;
    }

    int x1,y1,x2,y2,x3,y3;

    x1 = x2 = a;

    y1 = y2 = 0;

    n -= 2*a;

    if (n<=a+a-2)
    {
        x3 = a;
        y3 = n-a;
    }
    else
    {
        if (n%2==1)
            y2++;
        x3 = n/2 + 1;
        y3 = n/2 - 1;
    }

    printf("%d %d\n%d %d\n%d %d\n",x1,y1,x2,y2,x3,y3);

    return 0;
}

```
