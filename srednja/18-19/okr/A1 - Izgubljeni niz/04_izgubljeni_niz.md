---
hide:
  - toc
---

# A1 - Izgubljeni niz

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Profesor Feđa, strastveni ribolovac i obožavalac ronjenja na dah, pronašao je svoj 14. omiljeni hobi - zaboravljanje nizova. Ova novootkrivena disciplina teče na sledeći način: 

Na početku, Feđa zamisli niz $A$ sa $N$ prirodnih brojeva. Nakon toga on na papiru zapiše niz $B$ sa tačno $\frac{N (N+1)}{2}$ brojeva. Članovi niza $B$ su dobijeni primenom bitovne operacije $\ \text{or} \ $ (videti napomenu) na sve parove brojeva iz niza $A$, preciznije:

Za svaki uređeni par indeksa ($i, j$), ($1 \leq i \leq j \leq N$) iz niza $A$ u nizu $B$ je zapisana vrednost $A_i \ \text{or} \  A_j$. Ako je neka vrednost ista za više parova, ona se u nizu $B$ pojaljuje tačno onoliko puta koliko ima parova sa tom vrednošću. Ove vrednosti se u nizu $B$ mogu javiti u proizvoljnom redosledu.

Naravno, profesor se umorio nakon zapisivanja svih ovih brojeva i u potpunosti zaboravio prvobitno zamišljeni niz $A$. Srećom na papiru mu je ostao zapisan niz $B$. Da li možete da pomognete našem dragom profesoru i pronađete izgubljeni niz $A$?
  
## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se jedan prirodan broj $N$, dužina izgubljenog niza $A$.
U drugoj liniji standardnog ulaza nalazi se $\frac{N (N+1)}{2}$ prirodnih brojeva, elementi niza $B$ opisanog u tekstu zadatka.

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati $N$ prirodnih brojeva, elemente izgubljenog niza $A$. Garantuje se da su ulazni podaci takvi da postoji bar jedan odgovarajući niz. Ako postoje više mogućih nizova, ispisati bilo koje rešenje.

## Primer 1

### Ulaz

~~~
3
5 4 2 3 1 6
~~~


### Izlaz

~~~
1 4 2
~~~

### Objašnjenje primera

Izgubljeni niz $A$ ima $N=3$ člana i treba ga pronaći koristeći niz $B=[5, 4, 2, 3, 1, 6]$. Jedan od mogućih nizova je $A = [1, 4, 2]$. Ako primenimo bitovnu operaciju $or$ na sve parove brojeva u nizu $A$ dobijamo:
 
* $A_1 \ \text{or} \ A_2 = 5 = B_1$
* $A_2 \ \text{or} \  A_2 = 4 = B_2$
* $A_3 \ \text{or} \  A_3 = 2 = B_3$
* $A_1 \ \text{or} \  A_3 = 3 = B_4$
* $A_1 \ \text{or} \ A_1 = 1 = B_5$
* $A_2 \ \text{or} \  A_3 = 6 = B_6$

## Ograničenja

U svim test primerima važe ograničenja 

* $1 \leq N \leq 1268$
* $1 \leq B_i < 2^{20}$

Test primeri su podeljeni u $3$ disjunktne grupe:

* U test primerima vrednim $20$ poena važe ograničenja $1 \leq N \leq 7$ i $1 \leq B_i \leq 7$ .
* U test primerima vrednim $40$ poena važi ograničenje $1 \leq N \leq 91$.
* U test primerima vrednim $40$ poena nema dodatnih ograničenja.

## Napomena

Operator disjunkcije u Pascal-u je označen sa `or`, dok u C++ ga zapisujemo pomoću simbola `|`. Ova operacija $x\ \text{or} \ y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način. Prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots b_k$. Zatim se za svaku poziciju $i \in \{1, \ldots, k \}$ računa $c_i$ pomoću sledećih pravila:

* Za $a_i = 0, b_i = 0$ važi $c_i = 0$
* Za $a_i = 0, b_i = 1$ važi $c_i = 1$
* Za $a_i = 1, b_i = 0$ važi $c_i = 1$
* Za $a_i = 1, b_i = 1$ važi $c_i = 1$

Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \ \text{or} \  y$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Vladimir Milovanović | Momčilo Topalović |

## Analiza

Pre početka ključno je uvideti da pošto za svako $x$ važi $x\ \text{or}\ x = x$, a kako niz $B$ između ostalih sadrži i rezultate operacije *ili* primenjene nad istim članom izvornog niza, zaključuje se da je traženi niz $A$ zapravo podskup zadatog niza. Nameće se naivno rešenje da se formiraju svi podskupovi niza $B$ koji sadrže tačno $N$ članova, a zatim ispita koji tačno od njih daje zadati niz $B$, međutim, ovo rešenje pati od izuzetno visoke vremenske složenosti.

Nije teško dalje zaključiti da rezultat *ili* operacije nad bitovima dva prirodna broja (operandi) nikada nije manji, već isključivo broj veći ili jednak većem operandu. Iz prethodnog lako se izvodi da su dva po vrednosti najmanja člana datog niza $B$, označimo ih sa $B_{S1}$ i $B_{S2}$, sigurno i članovi izvornog niza $A$, odnosno $A_1 = B_{S1}$ i $A_2 = B_{S2}$. Sledeći član izvornog niza $A_3$ biće ili treći po vrednosti član niza $B$, to jest $B_{S3}$, ili pak četvrti, $B_{S4}$, ukoliko je $A_1\ \text{or}\ A_2 = B_{S3}$. Ponavljanjem ovog postupka, može se doći do svih članova izvornog niza, na mnogo efikasniji način od prethodno pomenutog.

Naime, u svakom koraku algoritma iz niza $B$ treba eliminisati ili na neki način označiti sve članove koje je moguće formirati pomoću članova niza $A$ koji su već određeni, a zatim u niz $A$ dodati prvi sledeći po vrednosti član zadatog niza.

## Smernice za algoritam

Po učitavanju članova niza $B$ najpre je zadati niz neophodno sortirati u neopadajućem redosledu koristeći se nekim efikasnim algoritmom. Pošto niz $B$ ne sadrži jedinstvene vrednosti, već se jedna vrednost može ponavljati više puta, u jednom prolasku kroz dobijeni sortiran niz označiti indekse kada se svaka vrednost pojavljuje prvi put. Zatim, u glavnoj petlji, prolaziti kroz sortiran zadati niz $B$ i dodavati članove u niz $A$, ali samo pod uslovom da taj član već nije moguće dobiti nekom kombinacijom članova koji su već dodati u niz $A$. Da bi se ovo izvelo na efikasan način, prilikom svakog novog dodavanja u niz $A$ proveriti i označiti sve indekse članova niza $B$ koje je moguće formirati uparivanjem poslednje dodatog člana sa svim prethodnim koji se već nalaze u nizu $A$. Drugim rečima moguće je koristeći se već označenim indeksima pojedinih vrednosti i njihovim inkrementiranjem znati do kog indeksa niza $B$ je izvodljivo generisati sve članove, a zatim dodati prvi sledeći kada se do njega dođe. Ovaj proces nastaviti dok se ne prođe kroz čitav zadati niz. Kako niz $B$ sadrži $\frac{N(N+1)}{2}$ članova, glavna petlja ima zapravo kvadratnu složenost, odnosno $\mathcal{O}(N^2)$. Međutim, kako je zadati niz prethodno sortiran, to će ova operacija dominirati, te je zapravo $\mathcal{O}(N^2\log N)$ ukupna vremenska složenost ovog algoritma.

``` cpp title="04_izgubljeni_niz.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

const int maxA=1<<20;
int vis[maxA], a[maxA], b[maxA], cnt[maxA];
int n,m;
int main()
{
    cin>>n;
    m = (n*(n+1))/2;

    for (int i=1; i<=m; i++)
        scanf("%d",&b[i]);

    sort(b+1,b+m+1);

    for (int i=1; i<=m; i++)
        if (!cnt[b[i]])
            cnt[b[i]]=i;

    int cur = 0;
    for (int i = 1; i <= m; i++)
        if (!vis[i])
        {
            a[++cur] = b[i];

            for (int j=1; j<=cur; j++)
            {
                vis[cnt[a[j]|a[cur]]] = 1;
                cnt[a[j]|a[cur]]++;
            }
        }

    for (int i = 1; i <= n; i++)
        printf("%d ",a[i]);
    printf("\n");

    return 0;
}

```
