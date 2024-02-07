---
hide:
  - toc
---

# B3 - Marsovci

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |

Nakon mnogo godina istraživanja i rada, kao i bezbroj bezuspešnih pokušaja prouzrokovanih nepažljivim programerima koji u kodu koji pokreće svemirski brod greškom ostave komandu `system("PAUSE")`, a neretko i `readln()`, prva ljudska ekspedicija je uspešno sletela na Mars! Čim su sleteli, mala Marina, vođa ekspedicije, je primetila da se ispred njih nalazi nepomična kolona u kojoj stoji $n$ Marsovaca. Na njeno veliko iznenađenje, Marsovci nisu bili zeleni, već metalik roze boje.

Nakon nekoliko dana proteklih u zbunjujućim pokušajima komunikacije, Marina je saznala visine svih Marsovaca ($H_1 \dots H_N$) i konačno je shvatila da oni nepomično stoje jer testiraju inteligenciju novih posetilaca i žele da provere da li će Zemljani uspeti da naću **podniz uzastopnih Marsovaca iz kolone, takav da je razlika najvišeg i najnižeg Marsovca najveća moguća**.

Kako je ovaj problem Marini previše jednostavan, odlučila je da dodatno impresionira nove poznanike tako što će im reći **koliko takvih podnizova postoji**. Pomozite Marini da obori Marsovce s nogu i započne jedno novo prijateljstvo.

## Opis ulaza
U prvoj liniji standardnog ulaza nalazi se jedan prirodan broj $N$ - broj Marsovaca u koloni. U drugoj liniji standardnog ulaza nalazi se $N$ prirodnih brojeva, $H_1 \dots H_N$ - visine Marsovaca (u metrima) redom, od prvog do poslednjeg u koloni.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan nenegativan ceo broj koji predstavlja broj načina da se odabere podniz uzastopnih Marsovaca takav da je razlika najvišeg i najnižeg među njima najveća moguća.

## Primeri
<div class="col-md-12">
    <div class="panel panel-default">
        <div class="panel-heading">
            <span class="pull-left" style="width: 48%;">Ulaz</span>
            <span style="padding-left: 15px;">Izlaz</span>
        </div>
        <div class="panel-body">
            <span class="pull-left exampleinput">
                5<br/>
                3 5 2 1 4
            </span>
            <span class="exampleoutput">
                4
            </span>
        </div>
    </div>
</div>

<div class="col-md-12">
    <div class="panel panel-default">
        <div class="panel-heading">
            <span class="pull-left" style="width: 48%;">Ulaz</span>
            <span style="padding-left: 15px;">Izlaz</span>
        </div>
        <div class="panel-body">
            <span class="pull-left exampleinput">
                2<br/>
                21 8
            </span>
            <span class="exampleoutput">
                1
            </span>
        </div>
    </div>
</div>

## Objašnjenje primera
U prvom primeru najveća moguća razlika između najvišeg i najnižeg Marsovca u nekom podnizu je 4 metra i može se dobiti na 4 različita načina, i to ako odaberemo neki od narednih podnizova:

* od prvog do četvrtog Marsovca, tj. $[3, 5, 2, 1]$
* od drugog do petog Marsovca, tj. $[5, 2, 1, 4]$
* od prvog do petog Marsovca, tj. $[3, 5, 2, 1, 4]$
* od drugog do četvrtog Marsovca, tj. $[5, 2, 1]$

U drugom primeru najveća moguća razlika je 13 metara i može se dobiti samo ako u podniz uključimo oba Marsovca.

## Ograničenja
* $1 \leq Hi \leq 10^9$.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima koji vrede 15 poena važi $1 \leq N \leq 100$.
* U test primerima koji vrede 20 poena važi $1 \leq N \leq 3000$.
* U test primerima koji vrede 15 poena ne postoje dva Marsovca iste visine i važi $1 \leq N \leq 10^5$.
* U test primerima koji vrede 50 poena važi $1 \leq N \leq 10^5$.

## Napomena
Obratite pažnju da je za rešenje potrebno koristiti $64$-bitni tip podataka.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Nikola Jovanović | Nikola Jovanović | Dimitrije Erdeljan |

## Podzadatak $1$
U prvom podzadatku, dovoljno dobro je i *bruteforce* rešenje. Prolaskom kroz svaki mogući podniz uzastopnih Marsovaca određujemo maksimalnu i minimalnu visinu u njemu, njihovu razliku, i brojimo podnizove gde je ta razlika maksimalna. Ovaj pristup ima vremensku složenost $O(N^3)$.

## Podzadatak $2$
Mala modifikacija prethodnog pristupa može dovesti do vremenske složenosti $O(N^2)$. Ako prolazak kroz sve podnizove vršimo tako što fiksiramo levu granicu $L$, a zatim pomeramo desnu granicu $R$, možemo u $O(1)$ naći maksimum i minimum u svakom podnizu na osnovu prethodno izračunatih rešenja. Konkretno, imamo da je $max(H_L, H_{L+1}, \dots, H_{R+1}) = max(max(H_{L}, H_{L+1}, \dots, H_{R}), H_{R+1})$. Slično važi i za minimum.

## Podzadatak $3$
U ovom momentu, neophodno je napraviti par bitnih opservacija koje predstavljaju prvi korak ka kompletnom rešenju zadatka.

Označimo sa $H_{min}$ i $H_{max}$ visinu najnižeg, odnosno najvišeg Marsovca. Sada primećujemo da je najveća moguća razlika najvišeg i najnižeg Marsovca u nekom podnizu uzastopnih Marsovaca jednaka $H_{max} - H_{min}$. Veću razliku nije moguće dobiti, a upravo ova razlika se dobija u bilo kom podnizu u kom je $H_{max}$ maksimum a $H_{min}$ minimum - npr. ceo niz. Takođe, važi da je maksimum u nekom podnizu jednak $H_{max}$ ako i samo ako se u njemu nalazi bar jedna vrednost $H_{max}$ (slično važi i za minimum). Sada se zadatak može svesti na brojanje podnizova koji sadrže barem jednog Marsovca visine $H_{max}$ i barem jednog Marsovca visine $H_{min}$. 

Dodatni uslov koji ovaj podzadatak unosi je da se vrednosti $H_{min}$ i $H_{max}$ pojavljuju tačno jednom u nizu visina. Označimo indeks (jedinstvenog) najvišeg Marsovca sa $i_{max}$ a najnižeg sa $i_{min}$ i uzmimo da je (ne umanjujući opštost) $i_{max} < i_{min}$. Sada do rešenja dolazimo u konstantnom vremenu, uz malo računa. Kako leva granica podniza ne sme biti veća od $i_{max}$ (inače se $H_{max}$ ne nalazi u tom podnizu), a desna manja od $i_{min}$ (inače se $H_{min}$ ne nalazi u tom podnizu) broj podnizova koji sadrže i $H_{min}$ i $H_{max}$ je jednak $(i_{max} + 1) * (N - i_{min})$. Vremenska složenost ovog pristupa je $O(n)$.

## Podzadatak $4$
Ovde je potrebno malo komplikovanije rešenje, budući da dodatni uslov iz prethodnog podzadatka ne važi, pa najviši (tj. najniži) Marsovac ne mora biti jedinstven. Brojanju podnizova pristupamo tako što pomeramo brojač $L$ od početka do kraja niza i u svakom koraku računamo koliko ima podnizova čija je leva granica $L$ a da sadrže barem jednog Marsovca visine $H_{max}$ i barem jednog Marsovca visine $H_{min}$. Kako bismo ovo efikasno izračunali u toku cele procedure održavamo dva pokazivača $firstMax$ i $firstMin$ koji, za trenutno $L$, pokazuju na prvo pojavljivanje Marsovca visine $H_{max}$ (odnosno $H_{min}$)  od pozicije $L$ pa do kraja niza (uključujući i $L$). Kako je leva granica podniza fiksirana na $L$, a desna granica ne sme biti manja od $max(firstMax, firstMin)$, u svakom koraky na konačno rešenje dodajemo $N - max(firstMax, firstMin)$. 

Ostalo je još da prodiskutujemo kako se ovi pokazivači efikasno održavaju: ako nakon inkrementovanja $L$ važi $firstMax>=L$ nije potrebna korekcija, a u suprotnom uvećavamo $firstMax$ za jedan sve do prvog narednog pojavljivanja $H_{max}$ (ako naredno pojavljivanje ne postoji, možemo odmah prestati sa brojanjem i ispisati trenutno rešenje). Analogno održavamo i drugi pokazivač.

Iako se u jednom koraku uvećanje pomenutih pokazivača može dogoditi i do $N$ puta, u toku cele procedure će oni, kao i $L$, preći put od početka do kraja niza, pa je ukupna vremenska složenost rešenja $O(n)$.

``` cpp title="03_marsovci.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 1000005
#define MAXH 1000000005

using namespace std;

int N, H[MAXN];
int minh = MAXH, maxh = -1;
int main()
{
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &H[i]);
        minh = min(minh, H[i]);
        maxh = max(maxh, H[i]);
    }
    int first_min = -1;
    int first_max = -1;
    long long sol = 0;
    for(int L = 0; L < N; L++)
    {
        if(first_min < L)
        {
            do
            {
                first_min++;
            }
            while(first_min < N && H[first_min] != minh);
        }
        if(first_max < L)
        {
            do
            {
                first_max++;
            }
            while(first_max < N && H[first_max] != maxh);
        }
        if(first_min == N || first_max == N)
        {
            break;
        }
        int R = max(first_max, first_min);
        sol += N - R;
    }
    printf("%lld\n", sol);
    return 0;
}

```
