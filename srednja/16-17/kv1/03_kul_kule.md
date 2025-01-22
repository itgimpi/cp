---
hide:
  - toc
---

# 3 - Kul kule

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Kao što je većini đaka poznato, draga profesorka robotike Katarina mnogo voli da se igra lego robotima i kockicama. Ovaj put na čas je donela specijalnog robota i $n$ kula kockica. Na svakoj kuli se nalazi određen broj naslaganih kockica koje predstavljaju visinu te kule, tačnije $i$-ta kula ima visinu $A_i$ (sastavljena je od tačno $A_i$ kockica). Đaci su primetili da ne sadrže sve kule podjednak broj kockica i žele to da promene pomoću profesorkinog specijalnog robota. Naime, ovaj robot može izvršiti sledeću operaciju:

* Robot može da uzme **dve** ili **tri** kockice sa **beskonačne gomile** koja se nalazi pored datih kula (Katarina toliko voli   kockice da ih ima u neograničenim količinama) i da te kockice stavi na jednu od $n$ kula. Tako se u jednoj operaciji povećava visina određene kule za $2$ ili $3$ kockice.

Kako su đaci i sama profesroka malo nestrpljivi, molimo vas pomozite im da što pre izračunaju **minimalan broj operacija** potrebnih robotu da izjednači visine svih $n$ kula.

## Opis ulaza
U prvom redu standardnog ulaza nalazi se prirodan broj $n$, broj kula koje je donela profesorka. U drugom redu nalazi se niz $A$ od $n$ prirodnih brojeva razdvojenih razmakom, gde $A_i$ predstavlja visinu $i$-te kule.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati ceo broj koji predstavlja minimalan broj operacija navedenih u tekstu zadatka potrebnih robotu da izjednači visine svih kula.

## Primer 1
### Ulaz
```
3
7 10 5
```

### Izlaz
```
3
```

## Primer 2
### Ulaz
```
5
1 5 1 5 2
```

### Izlaz
```
5
```

## Objašnjenje primera
U prvom primeru ukupno imamo $3$ kule sa kockicama. Prva kula je visine $7$, druga kula je visine $10$, dok je treća kula visine $5$.  Robot može izjednačiti visine kula u $3$ operacije :

1.  Robot dodaje $3$ kockice na prvu kulu.  Sada su visine kula { $10$, $10$, $5$}.
2.  Robot dodaje $3$ kockice na treću kulu.  Trenutne visine kula su { $10$, $10$, $8$}.
3.  Robot dodaje $2$ kockice na treću kulu.  Konačne visine kula su { $10$, $10$, $10$}.

Pokazali smo kako robot može da izjednači visine kula u $3$ operacije, može se pokazati da je nemoguće izjednačiti pomenute kule u manje poteza. Minimalan broj potrebnih operacija je $3$.

## Ograničenja
Test primeri su podeljeni u dve disjunktne gurpe:

* U test primerima koji vrede $40$ poena važiće $1 \leq n \leq 100$ i $1 \leq A_i \leq 1000$.
* U test primerima koji vrede $60$ poena važiće $1 \leq n \leq 10^5$ i $1 \leq A_i \leq 10^9$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Dimitrije Erdeljan | Dušan Zdravković |

##Glavno rešenje
Da bismo mogli da nađemo minimalan broj operacija za izjednačavanje
svih kula, prvo nam je potreban način da odredimo minimalan broj
operacija potreban da bi se jednoj kuli dodalo $K$ kockica. Ovo nije
moguće ako $K = 1$, jer je svaka operacija dodaje barem dve
kockice. Ako $K \leq 2$, optimalan algoritam je:

* dok $K$ nije deljivo sa $3$, dodaj dve kockice (i samim time smanji
  $K$ za $2$)
* dodaj $K/3$ grupa od po tri kockice

Jasno je da je ovaj algoritam optimalan u slučaju u kom je $K$ deljivo
sa $3$. Ako $K$ nije deljivo sa $3$, sigurno moramo da iskoristimo
barem jednu grupu od dve kockice, a ako pretpostavimo da je naš
algoritam optimalan za $K-2$ kockice, po indukciji je optimalan za
svako $K$ (gde su bazni slučajevi $K=2$ i $K=3$, za koje je potrebna
jedna grupa).

Primetimo da ove vrednosti (minimalni brojevi operacija) rastu sa K
(počev od $K=2$, vrednosti su: $1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
\dots$ -- svaka posle $1$ se ponavlja tri puta). Dakle, minimalan
ukupan broj operacija se postiže tako što odaberemo najmanju "ciljnu
visinu" $T$ na koju možemo dovesti visine svih kula.

Pošto ne možemo "smanjivati" kule, ovo $T$ mora biti veće ili jednako
od svih vrednosti $A_i$. Takođe ne sme biti jednako sa $A_i$ ni za
jedno $i$, pošto kule ne možemo povećati za samo jednu kockicu. Ako je
$M$ maksimalna vrednost u nizu $A_i$, imamo dve mogućnosti:

* $M-1$ se ne javlja u $A$ -- optimalno je $T=M$
* u suprotnom, ne možemo koristiti $T=M$ (zbog $M-1$) ni $T=M+1$ (zbog
  $M$) -- optimalno je $T=M+2$

Nakon što odredimo optimalnu vrednost za $T$, potrebno je samo da
saberemo broj potrebnih kockica za svaku kulu na osnovu opisanog
algoritma. Kako $T$ možemo odrediti jednim prolazom kroz niz (gde
pamtimo najveći i drugi najveći element), a broj dodatih kockica u
$\mathcal{O}(1)$ po kuli (jer ćemo najviše dvaput dodati dve kockice),
ukupna složenost algoritma je $\mathcal{O}(N)$.

``` cpp title="03_kul_kule.cpp" linenums="1"
#include<stdio.h>
#include<math.h>
#include<algorithm>


using namespace std;

int n;
long long a[1000000];

long long calc(long long x)
{
    if (x%3==0) return(x/3); else
    if (x%3==1) return((x-4)/3+2); else
    return(x/3+1);
}

int main()
{
    scanf("%d",&n);

    long long res=0;
    long long maxi=0;
    for (int i=0;i<n;i++)
    {
        scanf("%lld",&a[i]);
        maxi=max(maxi,a[i]);
    }

    int cnt=0;

    for (int i=0;i<n;i++)
        if (maxi-a[i]==1) cnt++;

    if (cnt==0)
    {
        for (int i=0;i<n;i++)
            res+=calc(maxi-a[i]);

        printf("%lld\n",res);
    } else
    {
        for (int i=0;i<n;i++)
            res+=calc(maxi-a[i]+2);

        printf("%lld\n",res);
    }

    return 0;
}


```
