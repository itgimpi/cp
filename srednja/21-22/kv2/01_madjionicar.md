---
hide:
  - toc
---

# 1 - Mađioničar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Saznali ste da su vam drugari kupili knjigu mađioničarskih trikova kao novogodišnji poklon. Međutim, zbog ovog saznanja, krenuli ste da nestrpljivo iščekujete početak vaše buduće karijere  mađioničara. Toliko ste nestrpljivi, da ste odlučili da ne možete sačekati Novu godinu, pa ste izmislili svoj mađioničarski trik!

Na raspolaganju imate špil od $N$ karata, gde na svakoj karti piše po jedan broj od $1$ do $N$. Na svakoj karti napisan je različit broj. Kao prvi korak trika uzećete taj špil i promešati ga na takav način da tačno znate kojim redosledom idu karte u špilu. Zatim ćete pozvati iz publike jednog gledaoca, koji će vam pomoći u izvođenju vašeg trika. Prvo ćete mu dati mogućnost da preseče špil: uzme nekoliko karata sa vrha i stavi ih na dno u istom poretku. **Primetiti da on ne mora da preseče špil ukoliko to ne želi**. Dalje, taj gledalac će uzeti neku kartu iz špila, **ali ne onu sa vrhu špila**, i zatim ćete lupiti petama tri puta, uraditi kolut unapred, pokloniti se i najaviti publici da ste otkrili koju je kartu uzeo gledalac! Kada, posle toga, pogodite njegovu kartu svi će biti oduševljeni vašom magijom.

Ono što publika ne zna je da kada je gledalac izvlačio kartu iz špila, vi ste virnuli i videli kartu $K$ koja se nalazila **direktno iznad nje u špilu** i na osnovu nje pogodili izvučenu kartu. Kako niste još sigurni u vaše izvršavanje ovog trika, želite da proverite da radi na računaru.

## Opis ulaza

U prvom redu standardnog ulaza nalaze se dva pozitivna cela broja $N$ i $K$: broj karata u špilu i broj na karti iznad izvučene karte.

U drugom redu standardnog ulaza, nalaze se $N$ pozitivnih celih brojeva, $i$-ti od njih je $p_i$ i on predstavlja broj napisan na $i$-toj karti sa vrha špila.

## Opis izlaza

U prvom i jedinom redu standardnog izlaza treba ispisati jedan pozitivan ceo broj, koji predstavlja broj na karti koju je izvukao gledalac.

## Primer 1

### Ulaz

```
2 2
2 1
```

### Izlaz

```
1
```

### Objašnjenje

Videli ste kartu sa brojem $2$, što znači da on mora da je izvukao kartu sa brojem $1$, što i uspešno pogodite.

## Primer 2
### Ulaz
```
5 3
5 4 1 2 3
```

### Izlaz
```
5
```

### Objašnjenje
Kako god gledalac preseče špil, karta sa brojem $3$ će se nalaziti iznad karte sa brojem $5$. Na primer: ako uzme $3$ karte sa vrha (karte $5,4,1$) i stavi ih na dno u istom poretku, onda će špil sa vrha na dole biti $2,3,5,4,1$, stoga je karta koja je ispod karte sa brojem $3$ upravo karta sa brojem $5$. Primetite da ovde nije moguće da gledalac nije presekao špil, jer u tom slučaju niste mogli da vidite broj $3$ iznad izvučene karte.

## Ograničenja

-   $2 \leq N \leq 20.000$
-   $1\leq K \leq N$
-   $1 \leq p_i \leq N$, za svako $1 \leq i \leq N$
-   $p_i\neq p_j$ za sve $1\leq i < j\leq N$

Test primeri su podeljeni u četiri disjunktne grupe:

-   U test primerima vrednim $15$ poena: $N=2$.
-   U test primerima vrednim $20$ poena: važi $p_i=i$ za svako $1\leq i\leq N$.
-   U test primerima vrednim $20$ poena: $N=5$.
-   U test primerima vrednim $45$ poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Vladimir Milovanović | Vladimir Milovanović |

## Glavno rešenje
Pošto je u zadatku poznata karta (odnosno njena vrednost $K$) koja se nalazi direktno iznad tražene karte, ako se špil karata posmatra kao niz pozitivnih celobrojnih vrednosti, to će drugim rečima značiti, da je postavkom zadatka data vrednost u nizu pod indeksom za jedan manjim u odnosu na indeks zahtevane vrednosti. Stoga je u prvom koraku potrebno pronaći indeks $i$ u nizu pod kojim je zapisana data vrednost $K$, a zatim u narednim koraku ispisati vrednost pod indeksom $i+1$. Kako bi se osvojili svi poeni, neophodno je obratiti pažnju na jedan specijalan slučaj, koji je objašnjen u drugom javnom primeru u postavci zadatka, a to je kada je $i=N$. U ovom slučaju indeks tražene karte nije $i+1$, odnosno $N+1$, iz razloga što on ne postoji, već je to prva karta u špilu, odnosno vrednost pod indeksom $i=1$, uz pretpostavku da indekse računamo počevši od jedinice, a ne od nule. Elegantan način da se pokrije ovaj izuzetak jeste uzeti $i+1$ i pronaći ostatak pri deljenju sa $N$, to jest indeks tražene vrednosti će biti $(i+1) \mod N$ i sve što treba uraditi u zadatku nakon učitavanja odgovarajućih podataka je ispis vrednosti pod pomenutim indeksom.

Kako se u najgorem slučaju vrednost niza $K$ može nalaziti pod indeksom $N$, neophodno je u gore opisanom prvom koraku proći kroz čitav niz da bi se to utvrdilo, pa je asimptotska vremenska složenost algoritma $\mathcal{O}(N)$, odnosno linearna po dužini niza.

``` cpp title="01_madjionicar.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 20007
using namespace std;
int p[MAXN];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=0;i<n;i++) cin>>p[i];
    for(int i=0;i<n;i++) if(p[i]==k) printf("%d",p[(i+1)%n]);
}

```
