---
hide:
  - toc
---

# B3 - Čarobnjak iz Voza

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Čarobnjak Kiki, nakon boravka u Sankt Peterburgu, se uputio na prelepo putovanje vozom Transsibirskom železnicom kroz Rusiju. Na njegovo zaprepašćenje, u istom kupeu sa njim je sedela i poznata muzičarka Danijela Bajaga. Dok su prolazili pored planine Ural, Danijela je baš u tom trenutku pevala njenu poznatu pesmu ”Ruski voz”, i tako je izuzetno visokim tonovima uspela da probudi Jetija iz zimskog sna, koji je odmah, vidno iznerviran, pojurio ka vozu. Tu je bio red na Kikija da pokaže svoj čarobnjački talenat i spasi voz i putnike od besnog Jetija.

Kiki je brzo reagovao, prvo je Jetiju očitao energiju i uvideo da je ona tačno $E$, a zatim je, da bi ga što pre opet uspavao, stvorio **$N$ malih čarobnjaka**. Svakom je od njih je na početku kreiranja odredio i njihovu početnu snagu obične čarolije $S_i$, kao i jačinu specijalne magije $M_i$. Mali čarobnjak u jednoj sekundi može baciti ili običnu čaroliju na Jetija ili njegovu specijalnu magiju.

Ukoliko baci običnu čaroliju, Jetiju skida onoliko energije koliko je njegova trenutna snaga čarolije, ali se nakon bacanja čarolije **njena snaga smanjuje za duplo**, i to uvek na manji ceo broj (Npr. ako je početna snaga čarolije nekog malog čarobnjaka 14, u prvom bacanju čarolije on može Jetiju skinuti 14 energije, drugi put kada baca čaroliju može mu skinuti 7, treći put 3, četvrti put 1, a naon čega bi mu se snaga smanjila na 0 i ne bi mogao više ovom čarolijom da skine energiju Jetiju).

Ukoliko baci specijalnu magiju, Jetiju će skinuti onoliko energije kolika je njegova jačina specijalne magije, ali on će se time previše umoriti, i **neće moći više da baca čini na Jetija (ni običnu čaroliju, kao ni specijalnu magiju).**

Kada se Jetiju energija smanji na 0 ili manje, on će se ponovo uspavati i voz će biti spašen. Ipak, Kiki nije uspeo da uvidi jednu stvar, a to je da **na Jetija može da deluje samo jedno bacanje čini u jednoj sekundi** (odnosno, u svakoj sekundi, samo jedan mali čarobnjak može baciti čaroliju ili magiju na njega), te više čarobnjaka ništa ne znači ukoliko ne naprave dobar plan kojim redosledom će bacati čini. 

Mali čarobnjaci čekaju da im Kiki prenese plan, a Kiki vas je zamolio da mu pomognete u planiranju, i **odredite minimalno vreme u sekundama** za koje mali čarobnjaci mogu da uspavaju Jetija (snage magija i čarolija će uvek biti takve da je to moguće).

## Opis ulaza

Prva linija standardnog ulaza sadrži dva prirodna broja $N$, $E$ odvojena razmakom. Druga linija sadrži $N$ prirodnih brojeva odvojenih razmakom - niz $S$. Treća linija sadrži $N$ prirodnih brojeva odvojenih razmakom - niz $M$.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati minimalno vreme u sekundama za koje mali čarobnjaci mogu da uspavaju Jetija.

## Primer 1

### Ulaz

```
4 53
10 3 7 12
4 5 15 8
```

### Izlaz

```
6
```

## Primer 2

### Ulaz

```
2 35
10 2
10 10
```

### Izlaz

```
4
```

### Objašnjenje primera

U prvom primeru imamo 4 mala čarobnjaka i Jetija koji ima energiju 53. Jedan od načina na koji mali čarobnjaci mogu uspavati jetija za 6 sekundi je:

- u prvoj sekundi prvi čarobnjak baca običnu čaroliju i tako skida Jetiju 10 energije
- u drugoj sekundi četvrti čarobnjak baca običnu čaroliju i tako skida Jetiju 12 energije
- u trećoj sekundi četvrti čarobnjak opet baca običnu čaroliju i tako skida Jetiju 6 energije
- u četvrtoj sekundi treći čarobnjak baca specijalnu magiju i tako skida Jetiju 15 energije
- u petoj sekundi četvrti čarobnjak baca specijalnu magiju i skida Jetiju 8 energije
- u šestoj sekundi prvi čarobnjak baca običnu magiju i tako skida Jetiju još 5 energije, i time ga uspavljuje.

Ne postoji način da mali čarobnjaci uspavaju Jetija za manje od 6 sekundi.

U drugom primeru će prvi čarobnjak u prve dve sekunde bacati običnu čaroliju, zatim njegovu specijalnu magiju i time ukupno skinuti 25 energije Jetiju, a zatim će drugi čarobnjak u četvrtoj skundi baciti specijalnu magiju i time skinuti još 10 energije i uspavati Jetija.

### Ograničenja

U svim test primerima važi:

* $1 \leq N \leq 5 \cdot 10^5$
* $0 \leq S_i, M_i \leq 10^6$
* $1 \leq E \leq 10^{15}$

Test primeri su podeljeni u 4 disjunktne grupe:

* U test primerima vrednim 20 poena: za svako $i$ važi $S_i = 0$, odnosno, čarobnjaci mogu da koriste samo specijalnu magiju.
* U test primerima vrednim 25 poena: za svako $i$ važi $M_i = 0$, odnosno, čarobnjaci mogu da koriste samo običnu čaroliju.
* U test primerima vrednim 35 poena: $N \leq 1000$.
* U test primerima vrednim 20 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dušan Zdravković | Dragan Urošević | Nikola Pešić |


Nameće da će čarobnjaci potrošiti manje vremena na uspavljivanje Jetija ako koriste više snage. Pored toga, bez obzira što se specijalna magija koristi na kraju (posle bacanja običnih čarolija), možemo već na početku "uračunati" specijalnu magiju (ako je veća od obične magije).
Zbog toga formiramo niz sa svim mogućim čarolijama i magijama. Naime, ako su $S_i$ i $M_i$ početna jačina obične čarolije i jačina specijalne magije čarobnjaka broj $i$, onda u niz $a$ sa svim (mogućim) magijama dodajemo sledeće jačine:
$$
M_i, S_i, \frac{S_i}{2^1}, \frac{S_i}{2^2}, \frac{S_i}{2^3}, ..., \frac{S_i}{2^k}, 
$$
gde je $k$ broj sa osobinom da je 
$$
\frac{S_i}{2^k}\geqslant 1 \ \ \ \ \text{i}\ \ \ \ \ \frac{S_i}{2^{k+1}} < 1.
$$
Po formiranju niza $a$, soritramo ga u nerastućem poretku, a zatim određujemo najmanji broj $m$ takav da je
$$
a_1 + a_2 + a_3 + \dotsb + a_m \geqslant E.
$$

Kako su sve moći manje od ili jednake broju $10^6$, to će i elementi niza $a$ biti između $1$ i milion, pa se taj niz može sortirati primenom sortiranja prebrajanjem (counting sort). Broj elemenata u nizu je $O(N\log\max\{S_i, M_i|i=1, 2, ..., N\}) = O(N\log N)$. Složenost sortiranja je takođe $O(N\log N)$ . Određivanje broja $m$ koji predstavlja broj dana potrebnih da se uspava Jeti ima složenost $O(\max\{S_i,M_i\})$.


Niz $a$ se može sortirati primenom nekog brzog algoritma za sortiranje (npr. quick sort)  i tada  je složenost samog sortiranja $O(N\log N\log(N\log N))$.

Zadatak možemo rešiti i bez sortiranja niza sa magijama. Naime, magije možemo smestiti u prioritetni red, a zatim iz reda brisati redom magije od najveće smanjijući svaki put Jetijevu moć za iznos te čarolije (magije) sve dok se Jeti ne uspava.

``` cpp title="03_carobnjak_iz_voza.cpp" linenums="1"
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000555
#define MAXSM 1000555

int n;
long long e;
int s[MAXN],m[MAXN],cnt[MAXSM];

int main() {

    scanf("%d%lld", &n, &e);

    for(int i=0; i<n; i++) {
        scanf("%d", &s[i]);
    }

    for(int i=0; i<n; i++) {
        scanf("%d", &m[i]);
    }

    for(int i=0; i<n; i++) {
        cnt[m[i]]++;
        while(s[i] > 0) {
            cnt[s[i]]++;
            s[i] /= 2;
        }
    }

    int res = 0;
    for(int i=MAXSM-1; i>=1; i--) {
        while(e > 0 && cnt[i] > 0) {
            e -= i;
            cnt[i]--;
            res++;
        }
    }

    printf("%d\n", res);

    return 0;
}
```
