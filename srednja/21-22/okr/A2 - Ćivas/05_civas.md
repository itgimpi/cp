---
hide:
  - toc
---

# A2 - Ćivas

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |


Prethodnih godina, duologija o velikom šefu mafije ekskluzivne disjunkcije *Okram Ćivas* postali su neki od najpopularnijih i najvoljenijih filmova na tržištu. Duologija se sastoji od, kao što ime kaže, dva filma, koji se zovu *Okram* i *Ćivas*. U ovom zadatku bavićemo se drugim delom duologije - *Ćivasom*.

U najnovijoj avanturi našeg heroja, on se našao na tajanstvenoj kružnoj traci. Ova traka je podeljena na $N$ delova, koji su redom numerisani brojevima od $1$ do $N$, a u svakom delu trake se nalazio po jedan nenegativan ceo broj. Broj u $i$-tom delu kruga označavamo sa $A_i$. Nije ni stigao da se pribere kad su krenuli da se menjaju brojevi po traci. Desilo se $Q$ promena, gde se u $i$-toj promeni, broj u delu trake sa oznakom $p_i$ promenio u novu vrednost $v_i$. Svi ozbiljniji filmofili mogli su da uoče da važi nešto interesantno: **ni u jednom trenutku nije postojao broj $D<N$ tako da je kružni niz $A_i$ bio $D$-periodičan** (to jest ne postoji $D$ tako da svaka dva dela na distanci $D$ imaju isti broj napisan na sebi, tj. $A_i=A_{(i+D) \text{mod }N}$). Iz nekog razloga je između svaka dva dela trake $i$ i $i+1$ pisao broj $B_i$ koji je bio jednak ekskluzivnoj disjunkciji (poznatoj i kao `xor`)  dva broja napisana na ta dva dela (preciznije $B_i=A_i\text{ xor }A_{i+1}$). Promenama vrednosti $A_i$ su se, naravno, meljale i vrednosti $B_i$.

Kako je Okram Ćivas poznat po svojoj majstoriji sa ekskluzivnom disjunkcijom, on je sebi zadao sledeći zadatak: Pre svih promena, kao i posle svake promene, želeo je da nađe periodu kružnog niza $B$, to jest najmanji prirodan broj $D$ tako da važi $B_i=B_{(i+D)\text{ mod }N}$.

## Opis ulaza
Prva linija standardnog ulaza sadrži dva broja, broj delova trake $N$ i broj upita $Q$. U narednoj liniji nalazi se $N$ prirodnih brojeva: gde $i$-ti broj predstavlja broj $S_i$, koji označava početnu vrednost broja u $i$-tom delu trake. Narednih $Q$ linija sadrže po dva broja: $p_i,v_i$, koji predstavljaju promenu vrednosti u nizu $A$ iz teksta.

## Opis izlaza
Na standardni izlaz je potrebno ispisati $Q+1$ linija: u prvoj liniji treba naći periodu pre ikakvih upita, a u $i+1$-oj liniji treba naći periodu posle $i$-te promene.

## Primer 1

### Ulaz

```
6 1
0 1 3 1 0 1
6 2
```

### Izlaz

```
6
3
```
## Primer 2

### Ulaz

```
5 2
2 3 4 1 2
3 3
4 4
```

### Izlaz

```
5
5
5
```

## Objašnjenja primera
U prvom primeru je niz $B$ na početku `1 2 2 1 1 1`, čija je najmanja perioda očito ceo niz, dok posle promene niz je `1 2 2 1 2 2`, kada je $3$ periodično.

U drugom primeru kako je $5$ prost, a period deli dužinu niza, važi da je period uvek $1$ ili $5$, a kako ovde nikad nije $1$ onda je odgovor $5$ posle svake promene.
## Ograničenja
-   $2 \leq N,M \leq 200.000$
-   $1\leq Q\leq 200.000$
-   $0\leq A_i,v_i<2^{30}$
-   $1\leq p_i\leq N$

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $N\leq500$ i $Q\leq 500$
-   U test primerima vrednim $20$ poena: $Q\leq25$
-   U test primerima vrednim $30$ poena: $Q\leq3.000$
-   U test primerima vrednim $40$ poena: Bez dodatnih ograničenja
## Napomena

Operator ekskluzivne disjunkcije u Pascal-u je označen sa  `xor`, dok u C++ ga zapisujemo pomoću simbola  `^`. Ova operacija $x\ \text{xor} \ y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način. Prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots b_k$. Zatim se za svaku poziciju $i \in {1, \ldots, k }$ računa $c_i$ pomoću sledećih pravila:

-   Za $a_{i} = 0, b_{i} = 0$ važi $c_{i} = 0$
-   Za $a_{i} = 0, b_{i} = 1$ važi $c_{i} = 1$
-   Za $a_{i} = 1, b_{i} = 0$ važi $c_{i} = 1$
-   Za $a_{i} = 1, b_{i} = 1$ važi $c_{i} = 0$

Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \ \text{xor} \ y$.

Ako želite da saznate priču o poreklu našeg heroja, pogledajte treći zadatak za $B$ kategoriju: *Okram*

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Mladen Puzić | Tadija Šebez |

## Rešenje kada $N, Q \leq 500$
Za svaku promenu niza, izračunamo niz $b$ i na njemu probamo svaku moguću periodu, od kojih uzimamo najmanju. 

Vremenska složenost je $O(QN^2)$,  a memorijska složenost $O(N)$.  

## Rešenje kada $Q \leq 25$
Primetimo da su jedine moguće periode delioci broja $N$. Sada primenjujemo prethodno rešenje, samo što isprobavamo samo te delioce.

Vremenska složenost je $O(QNd(N))$, gde je $d(N)$ broj delioca $N$, a memorijska složenost $O(N)$.

## Rešenje kada $Q \leq 3000$ 
Možemo primetiti da za svako $d$ i $x$ važi: 

$$
a_i \text{ xor } a_{i+d} = b_i \text{ xor } b_{i+1} \text{ xor } \ldots b_{i+d-1}
$$

Analogno, važi i:

$$
a_{i+d} \text{ xor } a_{i+2d} = b_{i+d} \text{ xor } b_{i+d+1} \text{ xor } \ldots b_{i+2d-1}
$$

Ako za $d$ uzmemo periodu niza $b$, važi da su desne strane ovih jednačina jednake, pa važi i da su leve strane jednake. Odatle zaključujemo, da za takvo $d$ i proizvoljno $x$ važi $a_i = a_{i+2d}$,  što nam govori da je $2d$ perioda niza $a$. 

Pošto nam je poznato da je perioda niza $a$ baš $n$, onda imamo dva slučaja. Ukoliko je $n$ neparno, perioda niza $b$ je uvek $n$, u suprotnom, perioda može biti i $\frac{N}{2}$, a ako nije, onda mora biti $n$. Zato, nakon svake promene, dovoljno je proveriti da li je u novom nizu $\frac{N}{2}$ perioda. 

Vremenska složenost $O(NQ)$, a memorijska složenost $O(N)$.

## Glavno rešenje
Poput prethodnog rešenja, dovoljno je proveriti periodu $\frac{N}{2}$, samo ćemo ovde to uraditi na brži način. Pre svih promena, odradimo proveru u $O(N)$, pamteći u koliko odgovarajućih parova su isti elementi. Nakon svake promene, dovoljno je proveriti samo da li se neki od dva para na koje promena utiče *popravio* ili *pokvario*, tj. ažurirati broj parova u kojima su elementi isti. Kad god je broj takvih parova tačno $\frac{N}{2}$, perioda je $\frac{N}{2}$, u suprotnom, perioda je $N$. 

Vremenska složenost je $O(N+Q)$, a memorijska složenost $O(N)$.


``` cpp title="05_civas.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
int a[200007],b[200007],n,q,cnt;
bool bad[200007];
void check(int x)
{
    if(x>=n/2) {check(x-n/2); return;}
    if(bad[x]) cnt--;
    if(b[x]==b[x+n/2]) bad[x]=false;
    else bad[x]=true;
    if(bad[x]) cnt++;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    for(int i=0;i<n;i++) b[i]=a[i]^a[(i+1)%n];
    for(int i=0;i<n;i++) check(i);
    if(cnt==0) printf("%d\n",n/2);
    else printf("%d\n",n);
    while(q--)
    {
        int p,v;
        scanf("%d%d",&p,&v);
        p--;
        a[p]=v;
        b[(p+n-1)%n]=a[(p+n-1)%n]^a[p];
        b[p]=a[p]^a[(p+1)%n];
        check(p); check((p+n-1)%n);
        if(cnt==0) printf("%d\n",n/2);
        else printf("%d\n",n);
    }
}

```
