---
hide:
  - toc
---

# 2 - Uooaah

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 64MB |


Pre oko dvadeset hiljada godina, kada nisu bili u pećinama, praistorijski ljudi (pećinci) su voleli da provode vreme na svežem vazduhu i izvode fizičke eksperimente. Jedan od omiljenijih im je bio sledeći: pećinci Pera, Mika i Laza bi se postavili na različitim pozicijama na jednom pravcu (možemo ih zamisliti kao tačke na realnoj pravoj) i svako od njih bi poneo svoj digitalni ručni peščani sat.

U trenutku 0 svako od njih uzvikne "Aaaa!!"(standardni pozdrav pećinaca) - ovaj pozdrav se širi u svim smerovima brzinom od 1 m/s (gustina vazduha je tada bila drugačija pa je brzina zvuka bila manja). U trenutku kada pećinac prvi put čuje pozdrav (od nekog od preostale dvojice) on se razdere standardnim pećinskim otpozdravom - "Uooaah?!"koji se širi na isti način i istom brzinom. Na kraju, u trenutku kada svaki pećinac prvi put čuje otpozdrav "Uooaah?!"on zapamti to vreme na svom digitalnom peščanom satu i eksperiment je završen.

Na kraju eksperimenta, Pera, Mika i Laza se vrate u pećinu i saopšte svoja zabeležena vremena pećinskom vraču Kljovku koji koristeći ove podatke, šestar, znanje fizike i osvećene kljove mamuta pokušava da impresionira pećinske ljude tako što određuje početne položaje naša tri pećinca (tj. tri pozicije na realnoj pravoj). Pomozite Kljovku da se ne obruka! Obratiti pažnju
da se ponead može desiti da rešenje ne postoji (tj. da Perini, Mikini i/ili Lazini podaci nisu dobri zbog nepreciznosti praistorijskih digitalnih peščanih satova). Dodatno, te tri pozicije moraju biti različiti realni brojevi koji po apsolutnoj vrednosti nisu veći od 109 (Kljovko ne zna mnogo velike brojeve).

## Opis ulaza
Svaki test primer će se sastojati od 3 različita eksperimenta tj. standardni
ulaz se sastoji od 3 reda i u svakom redu (koji predstavlja jedan eksperiment) se nalaze po tri realna broja $t_1, t_2$ i $t_3$, zadata se preciznošću od jedne decimale, koji predstavljaju vremena kada su Pera, Mika i Laza, redom, čuli otpozdrav "Uooaah?!".

## Opis izlaza
Za svaki od 3 eksperimenta treba uraditi sledeće: ukoliko postoji rešenje (tj. početne pozicije koje zadovoljavaju sve uslove) u jednom redu treba ispisati "UGA"(bez navodnika, znači "DA"na pećinskom) a u narednom redu tri realna broja $x_1$, $x_2$ i $x_3$ sa preciznošću na dve decimale koja, redom, predstavljaju početne pozicije Pere, Mike i Laze i koja zadovoljavaju
pomenuta dodatna ograničenja. Sa druge strane, ukoliko ne postoji rešenje u jednom redu samo ispisati "UHUH"(bez navodnika, znači "Nažalost, eksperiment nije uspeo"na pećinskom). Ukoliko ima više rešenja, ispisati bilo koje.

## Primer 1
### Ulaz
```
7.0 8.0 7.0
2.0 4.0 6.0
1.5 1.5 1.5
```

### Izlaz
```
UGA
2.00 10.00 5.50
UHUH
UGA
-0.75 0.00 0.75
```

## Objašnjenje
U prvom eksperimentu jedno moguće rešenje je da se Pera nalazi na poziciji 2, Mika na poziciji 10 i Laza na poziciji 5.5. Tada Pera prvi put čuje pozdrav od Laze posle 3.5 sekun di i tada otpozdravlja; slično, Mika otpozdravlja posle 4.5 sekundi (kada čuje pozdrav od Laze) a Laza otpozdravlja posle 3.5 sekundi kada čuje pozdrav od Pere. Pera prvi put čuje otpozdrav "Uooaah?!"od Laze i to posle 7 sekundi, Mika prvi put čuje otpozdrav posle 8 sekundi (od Laze) i Laza prvi put posle 7 sekundi od Pere. Za drugi eksperiment ne postoji rešenje a lako se može proveriti da su pozicije u trećem eksperimentu zaista jedno od rešenja.

## Ograničenja

* $0 \leq t_1, t_2, t_3 \leq 10^9$.
* $-10^9 \leq x_1, x_2, x_3 \leq 10^9$ i sve ove vrednosti moraju biti međusobno različite (ukoliko rešenje postoji, postojaće i ono koje zadovoljava ove dodatne uslove)

## Napomena
Test primeri su podeljeni u dve disjunktne grupe:

* U test primerima vrednim 40 poena važi: ukoliko rešenje postoji, postojaće i rešenje kod
koga su tražene pozicije celi brojevi koje po apsolutnoj vrednosti nisu veće od 100.
* U test primerima vrednim 60 poena nema dodatnih ograničenja.

## Napomena 2
Ukoliko takmičar za svaki eksperiment u test primeru ispravno odredi da li
postoji ili ne postoji rešenje ali same pozicije nisu dobre, dobija 30% poena za dati test primer. Obratiti pažnju da je čak i u tom slučaju posle svakog ispisa "UGA"potrebno ispisati tri realna broja koja zadovoljavaju dodatna ograničenja (npr. "1.00 2.00 3.00").


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Andrej Ivašković | Nikola Milosavljević | Aleksandar Višnjić | Andrej Ivašković |

## Glavno rešenje:
Neka bez umanjenja opštosti važi $x_1\leq x_2\leq x_3$ (možemo pećince permutovati tako). Posmatrajmo slučaj kada važi $x_2-x_1 \leq x_3-x_2$ (drugi slučaj se analogno rešava). Pećinci $1$ i $2$ čuju "Aaaa!!" u istom trenutku $x_2-x_1$, a nakon toga čuju i "Uooaah?!" u istom trenutku $2(x_2-x_1)$ (drugi pećinac će pre to čuti od onog koji je bliži njemu, a to je prvi pećinac). Treći pećinac čuje "Uooaah?!" tek u vremenu $x_3-x_1$. Za data (pravilno permutovana) vremena, pozicije se mogu konstruisati kao $x_1=0$, $x_2=\frac{t_1}{2}$ i $x_3=t_3$, pa se potom odgovarajućim permutovanjem dobija rešenje zadatka. Primetimo da takve pozicije postoje ako i samo ako je $t_1=t_2\leq t_3$ (u nekom poretku).

Dakle, rešenje postoji samo kada su neka dva vremena jednaka, a treće ne manje od ostala dva. Na osnovu tih vremena se potom izračuna formula za poziciju svakog pećinca. Dovoljno je pokriti $4$ slučaja, s tim da je poslednji nemoguć:

 1. $t_1=t_2\leq t_3$, formula je $(0,\frac{t_1}{2},t_3)$
 2. $t_2=t_3\leq t_1$, formula je $(t_1,0,\frac{t_2}{2})$
 3. $t_3=t_1\leq t_2$, formula je $(\frac{t_3}{2},t_2,0)$
 4. ostalo


``` cpp title="02_uooaah.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

double t1, t2, t3;

bool eq(double x, double y)
{
    return ((x - y < 0.000001) && (x - y > -0.000001));
}

int main()
{
    for (int tests = 0; tests < 3; tests++)
    {
        scanf("%lf%lf%lf", &t1, &t2, &t3);

        if (eq(t1, t2) && (eq(t2, t3) || t2 < t3)) // t1 = t2 <= t3
        {
            printf("UGA\n");
            printf("%.2lf %.2lf %.2lf\n", 0.0, t1/2, t3);
        }
        else if (eq(t1, t3) && (eq(t1, t2) || t1 < t2)) // t1 = t3 <= t2
        {
            printf("UGA\n");
            printf("%.2lf %.2lf %.2lf\n", 0.0, t2, t3/2);
        }
        else if (eq(t2, t3) && (eq(t3, t1) || t3 < t1)) // t2 = t3 <= t1
        {
            printf("UGA\n");
            printf("%.2lf %.2lf %.2lf\n", t1, 0.0, t2/2);
        }
        else printf("UHUH\n");
    }

    return 0;
}

```
