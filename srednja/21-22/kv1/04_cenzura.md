---
hide:
  - toc
---

# 4 - Cen*ura

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Sloboda govora je divna stvar, ali neke ideje su prosto previše loše da bi se širile! Zato je oformljena Kontrolna Organizacija Štetnih Ideja (KOŠI), koja treba da pomogne ljudima da se "ne zanesu" previše u tekstovima koje pišu. Međutim, oni nisu  baš najsigurniji kako to da rade još uvek, pa su odlučili da ako nešto urade, urade jednu stvar kako treba!

KOŠI je odredio najgoru reč koju mogu da smisle: zabranjenu reč $S$ dužine $M$. Da niko ne mora nikad da bude izložen ovako strašnoj reči, odlučili su da je obrišu svuda gde mogu. Pred sobom imaju tekst $T$ dužine $N$ i cilj im je da neka slova zamene sa `*` (ASCII vrednost $42$) tako da se reč $S$ ne pojavljuje kao **podsekvenca** teksta  $T$. Podsećamo da je reč $S$ podsekvenca teksta $T$ ako je moguće obrisati neka slova iz $T$ tako ostane upravo $S$.

Međutim, nije poenta uređivanja promeniti suštinu teksta, stoga moraju da promene **što manje slova u tekstu $T$**. Ovo im ne ide za rukom, pa su pitali vas za pomoć.
## Opis ulaza
U prvom redu standardnog ulaza se nalazi tekst $T$ koji se sastoji od malih slova latinskog alfabeta. U drugom redu se nalazi zabranjena reč $S$ koji se sastoji od malih slova latinskog alfabeta.
## Opis izlaza
U prvom redu standardnog izlaza napisati jedan prirodan broj koji predstavlja najmanji broj slova koje treba da zamenimo sa  `*` da bi ostvarili cilj. U drugom redu standardnog izlaza ispisati uređenu verziju teksta $T$ u kojoj se reč $S$ ne pojavljuje kao podsekvenca.
## Primer

### Ulaz

```
ttaakkprroogg
takprog
```

### Izlaz

```
1
ttaakk*rroogg
```
## Objašnjenja primera
Kada slovo `p` cenzurišemo, ono se više ni ne pojavljuje u tekstu, pa $S$ nikako ne može biti podsekvenca.
## Ograničenja
-   $1 \leq N \leq 200.000$
-   $1 \leq M \leq 10$

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: zabranjena reč je `a`
-   U test primerima vrednim $10$ poena: sva slova zabranjene reči su `a`
-   U test primerima vrednim $15$ poena: zabranjena reč je `ab`
-   U test primerima vrednim $15$ poena: $N \leq 5.000$, a zabranjena reč je `abc`
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja
## Bodovanje
Moguće je dobiti i parcijalne poene po test primeru: ako nađete pravilan najmanji broj cenzurisanih slova, ali ne i pravilnu cenzuru teksta, dobijate 80% bodova na tom primeru.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Pavle Martinović | Aleksa Plavšić |


## Zabranjena reč je 'a'
U ovom podzadatku je očito dovoljno samo cenzurisati sva pojavljivanja slova 'a', što možemo da uradimo tako što linearno prođemo kroz $T$ i nađemo svuda gde se pojavljuje to slovo, zamenimo sa *, i izbrojimo koliko se puta pojavio.
##  Sva slova zabranjene reči su 'a'
Isto je rešenje kao u prethodnom podzadatku, samo preskočimo prvih $M-1$ pojavljivanja slova 'a'.

## Da li je jedna reč podsekvenca druge?
Da bismo umeli da pristupimo ovom problemu potrebno je analizirati algoritam kako proveravamo da li je jedna reč podsekvenca druge. 
Ovo se vrši pohlepnim algoritmom. Naime, neka proveravamo da li je reč $S$ podsekvenca reči $T$. Onda prolazimo linearno kroz reč $T$ dok pamtimo najduži prefiks $S$ koji nam se pojavljuje do sad kao podsekvenca.  Sada, kada sledeći put naiđemo na sledeće slovo koje bi nam trebalo da bismo povećali dužinu tog najvećeg prefiksa (to jest sledeće slovo u $S$), znamo da nam je optimalno da  ga iskoristimo u konstrukiciji $S$ kao podsekvence. To znači da u tom slučaju možemo da povećamo dužinu tog najdužeg prefiksa, dok on u suprotnom ostaje isti. Na kraju vidimo da li je najduži prefiks $S$ koji je podsekvenca $T$ upravo ceo $S$ u tom slučaju je odgovor "DA", a u suprotnom "NE".

## Puno rešenje
Sada kada smo proučili taj algoritam, možemo da rešimo ceo zadatak.
Rešenje ćemo vršiti dinamičkim programiranjem, najsličnije DP rešenju za najdužu zajedničku podsekvencu dve niske. Naime neka je $DP[n][k]$ vrednost "koliko najmanje karaktera treba cenzurisati u prvih $n$ slova $T$ da bi najduži prefiks $S$ koji je podsekvenca tih prvih $n$ karaktera dužine tačno $k$". Sada ove vrednosti u dinamičkom programiranju se lako računaju: ako ne želimo da povećamo vrednost $k$, onda kad naiđemo na slovo koje bi nam ga povećalo, moramo da cenzurišemo, a u suprotnom samo povećamo vrednost $k$. Kako stanja ima $MN$ i svako ima konstantno prelaza, dobijamo ukupno vremensku i memorijsku složenost $O(MN)$. 



``` cpp title="04_cenzura.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
int dp[200007][15];
pair<int,int> prv[200007][15];
int main()
{
    string a,b;
    cin>>a>>b;
    int n=a.size(),m=b.size();
    for(int i=0;i<n;i++) for(int j=0;j<m;j++)
    {
        dp[i+1][j]=dp[i][j]+((a[i]==b[j])?1:0); prv[i+1][j]={i,j};
        if(a[i]==b[j] && j && dp[i+1][j]>dp[i][j-1]) {dp[i+1][j]=dp[i][j-1]; prv[i+1][j]={i,j-1};}
        if(j && dp[i+1][j-1]<dp[i+1][j]) {dp[i+1][j]=dp[i+1][j-1]; prv[i+1][j]={i+1,j-1};}
    }
    int sol=n,nd=0;
    for(int i=0;i<m;i++) if(dp[n][i]<sol) {sol=dp[n][i]; nd=i;}
    pair<int,int> p=make_pair(n,nd);
    while(true)
    {
        if(p.first==0) break;
        pair<int,int> pr=prv[p.first][p.second];
        if(pr.second==p.second && a[pr.first]==b[p.second]) a[pr.first]='*';
        p=pr;
    }
    cout<<sol<<endl<<a;
}

```
