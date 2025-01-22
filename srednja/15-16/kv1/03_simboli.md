---
hide:
  - toc
---

# 3 - Simboli

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 64MB |


U praistorijskom dobu, iako nisu postojala jasno definisana pisma, jezici i udžbenici, ljudi su i dalje nalazili načina da pripišu prirodne pojave nekim simbolima—tako stvarajući preteče današnjih jezika. 

Poznato je da su u jednoj staroj civilizaciji na prostorima gde je vladala Tajna Komisija ljudi komunicirali koristeći 26 simbola (koje ćemo, radi lakše postavke, zapisivati koristeći velika slova engleske abecede). Takođe je ustanovljeno da se ti simboli mogu podeliti u “suprotne parove”. Ponovo, radi pojednostavljenja, smatraćemo da su slova koja su sa suprotnih strana engleske abecede međusobno suprotna. ($A$ i $Z$, $B$ i $Y$, $C$ i $X$, itd.)

Hiljadama godina kasnije, naslednici stare Tajne Komisije su iskopali jedan niz od n simbola, zajedno sa opisom pravila igre koja se igrala u to doba. Prvi igrač bira jedan simbol, nakon čega drugi igrač menja $k$ uzastopnih simbola iz niza u njima suprotne simbole. Na kraju, prvi igrač dobija poen za svako pojavljivanje simbola koji je odabrao u nizu, dok drugi igrač dobija
poen za svako pojavljivanje njemu suprotnog simbola.

Mali Perica i njegov kolega mali Nikolaj odlučili su da odigraju jednu partiju ove igre. Pericu zanima koliku najveću prednost može ostvariti kao prvi igrač, ukoliko Nikolaj bude igrao optimalno. Kao i ranije, zamolio vas je za pomoć.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva cela broja, $n$ i $k$, koji predstavljaju dužinu niza simbola i broj uzastopnih simbola koje Nikolaj treba pretvoriti u suprotne, redom.

U drugom redu nalazi se niz od $n$ velikih slova engleske abecede, koji predstavlja početno stanje niza simbola.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza potrebno je ispisati jedan ceo broj koji označava maksimalnu prednost koju Perica može ostvariti.


## Primer 1
### Ulaz
```
7 2
AAABBAA
```

### Izlaz
```
1
```

## Objašnjenja primera
Perica će steći najveću prednost ukoliko na početku odabere simbol $A$. Nikolaj tada može da promeni dva uzastopna simbola $A$ u simbole $Z$, čime u nizu na kraju postoje tri simbola $A$ i dva simbola $Z$, što predstavlja prednost od jednog poena za Pericu.

## Ograničenja.

* $1 ≤ n ≤ 10^6$.
* $0 ≤ k ≤ n$.

## Napomena. 
Test primeri su podeljeni u pet disjunktnih grupa:

*  U test primerima vrednim 20 poena važiće $n ≤ 50$.
*  U test primerima vrednim 20 poena važiće $n ≤ 1000$.
*  U test primerima vrednim 20 poena važiće $n ≤ 10^4$.
*  U test primerima vrednim 20 poena važiće $n ≤ 10^5$.
*  U test primerima vrednim 20 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Petar Veličković | Dragan Urošević |


Zadatak Simboli predstavlja problem srednje težine na ovogodišnjim Kvalifikacijama. Na njemu je bilo relativno jednostavno osvojiti značajnu količinu bodova, dok je za pune bodove bilo potrebno primeniti vrstu ideje koja nije momentalno intuitivna, ali se često "provlači'' u takmičarskim zadacima, i zato iskusniji takmičari uglavnom nisu imali problema sa ovim zadatkom. Autor je originalno smislio ovaj zadatak 2013. godine, inspirisan zadacima "Menjanje stringa'' i "Menjanje stringa v2'' koji su se pojavili na tadašnjim Kvalifikacijama, i predstavljaju slične primere prednosti pametnih optimizacija nad direktnom simulacijom.

Rešenje koje se odmah nameće, s obzirom na mali broj simbola (26), je da se pronađe rešenje za svaki mogući Peričin odabir simbola, uzimajući maksimalno od tih rešenja kao konačno rešenje. Samim tim, naše rešenje se onda svodi na rešavanje potproblema u kome je unapred poznato koji simbol je odabrao Perica.

Direktna simulacija procesa u tekstu zadatka (tj. direktno obrtanje svakog mogućeg stringa dužine $k$) može doneti bilo koji broj bodova u intervalu od 20 do 60, u zavisnosti od nivoa "optimizovanosti'' rešenja; evo nekoliko takvih rešenja: 

* Rešenje koje za svaki podstring dužine $k$ obrće sve simbole u njemu, a zatim broji pojavljivanja simola dodatnim prolazom kroz ceo niz; ovo rešenje ima ukupnu složenost $O(n^2 \cdot k)$.
* Modifikovano prethodno rešenje u kome nemamo dodatni prolaz kroz ceo niz na kraju; iskorišćavamo činjenicu da, ukoliko prethodno zapamtimo koliko ima kog simbola u celom nizu, treba direktno ažurirati ove sume samo nad intervalom koji trenutno obrćemo da bismo prebrojali sva pojavljivanja simbola. Ovo rešenje ima ukupnu složenost $O(n\cdot k)$.
* Možemo dodatno optimizovati prethodno rešenje ukoliko iskoristimo činjenicu da će količine svakog simbola uvek biti iste za isto obrtanje (tj. ranije smo 26 puta obrtali string na istom mestu---i svaki put dobijali iste količine simbola). Ukoliko prvo odradimo obrtanje na nekoj poziciji pa tek onda izračunamo relevantne količine za svaki simbol na toj poziciji, i dalje imamo algoritam složenosti $O(n\cdot k)$, ali će ovaj algoritam sveukupno izvršiti znatno manje operacija obrtanja!

Za preostalih 40 poena neophodno je iskočiti iz okvira direktne simulacije zadatka, i smisliti optimalnije rešenje. Jedna od mogućih ideja je da, ukoliko za svaki simbol pamtimo **kumulativnu sumu** njegovih pojavljivanja kroz ceo niz, tj. za svaki simbol $s$ i poziciju $1 \leq x \leq n$, pamtimo vrednost $K_x^s$, tako da važi:
$K_x^s = \sum_{i=1}^x {\mathbb{I}(S_i = s)}$
gde je $S_i$ $i$-ti simbol u početnom stringu, a $\mathbb{I}(S_i = s)$ je definisan kao .
Za svaki simbol $s$, ove vrednosti se mogu izračunati u jednom prolazu kroz niz; za svaki indeks, uzimamo prethodnu vrednost, i dodajemo 1 ukoliko je trenutni simbol jednak simbolu $s$, tj. $K_{x+1}^s = K_{x}^s + \mathbb{I}(S_{x+1} = s)$.

Kada imamo ove vrednosti, moguće je efikasnije izračunati efekat jednog obrtanja bez da se zapravo direktno obrnu vrednosti stringa. Naime, ukupan broj pojavljivanja simbola $s$ između pozicija $a$ i $b$ je:

$$
\sum_{i=a}^{b} {\mathbb{I}(S_i = s)} = \sum_{i=1}^{b} {\mathbb{I}(S_i = s)} - \sum_{i=1}^{a-1} {\mathbb{I}(S_i = s)} = K_b^s - K_{a-1}^s
$$

Takođe, ukupan broj pojavljivanja simbola $s$ je dat kao:

$$
\sum_{i=1}^{n} {\mathbb{I}(S_i = s)} = K_n^s
$$

Označimo sada obrnuti simbol simbolu $s$ sa $\bar{s}$. Prednost za obrtanje na $i$-toj poziciji se onda može izračunati kao:

$$
(K_n^s - (K_{i+k-1}^s - K_{i-1}^s) + (K_{i+k-1}^{\bar{s}} - K_{i-1}^{\bar{s}})) - (K_n^{\bar{s}} - (K_{i+k-1}^{\bar{s}} - K_{i-1}^{\bar{s}}) + (K_{i+k-1}^{s} - K_{i-1}^{s}))
$$

$$
= K_n^s - 2(K_{i+k-1}^s - K_{i-1}^s) + 2(K_{i+k-1}^{\bar{s}} - K_{i-1}^{\bar{s}}) - K_n^{\bar{s}}
$$

Pošto smo već izračunali sve ove vrednosti, za fiksirano obrtanje i Peričin simbol možemo odrediti rešenje u konstantnom vremenu. Ovo nam sveukupno daje algoritam optimalne vremenske složenosti $O(n)$.

Međutim, naivno čuvanje svih vrednosti $K_n^s$ dovodi do probijanja memorijskog ograničenja; ukoliko takmičari koriste statički alocirane nizove, onda će moći ovo odmah da vide i koriguju. Ukoliko korekcija bude korišćenje manje širokog tipa (npr. *short/integer* umesto *int/longint*) ovo će dovesti do prekoračenja opsega na većim primerima i do netačnog rešenja; ovakva rešenja onda donose oko 80 bodova.

Za optimalno rešenje, možemo primetiti da, kada razmatramo jedan simbol $s$, zanimaju nas samo vrednosti $K_{\cdot}^s$ i $K_{\cdot}^{\bar{s}}$, tj. samo dva simbola. Ukoliko u svakom momentu čuvamo ove vrednosti samo za ove simbole, smanjujemo dodatnu memorijsku složenost algoritma sa $O(26n)$ na $O(2n)$, što je dovoljno za osvajanje 100 poena.

Napomenimo na kraju da je moguće dodatno modifikovati optimalno rešenje, tako da je neophodno samo **konstantno mnogo** (tj. $O(1)$) dodatne memorije. Da li možete smisliti ovo rešenje?


``` cpp title="03_simboli.cpp" linenums="1"
/*
 Author: Petar 'PetarV' Velickovic
 Task: Simboli
*/

#include <stdio.h>
#include <iostream>

#define MAX_N 1000001

using namespace std;

int n, k;
char sym[MAX_N];

int s[2][MAX_N];

int sol = -MAX_N;

int total(int left)
{
    int right = left + k - 1;
    
    int cnt1 = s[0][n - 1] - (s[0][right] - (left > 0 ? s[0][left - 1] : 0)) + (s[1][right] - (left > 0 ? s[1][left - 1] : 0));
    int cnt2 = s[1][n - 1] - (s[1][right] - (left > 0 ? s[1][left - 1] : 0)) + (s[0][right] - (left > 0 ? s[0][left - 1] : 0));
    
    return cnt1 - cnt2;
}

int main()
{
    scanf("%d%d", &n, &k);
    scanf("%s", sym);
    
   
    for (int ch=0;ch<26;ch++)
    {
        int opp = 25 - ch;
        
        if (sym[0] - 'A' == ch) s[0][0] = 1;
        else s[0][0] = 0;
        
        if (sym[0] - 'A' == opp) s[1][0] = 1;
        else s[1][0] = 0;
        
        for (int i=1;i<n;i++)
        {
            s[0][i] = s[0][i - 1];
            s[1][i] = s[1][i - 1];
            if (sym[i] - 'A' == ch) s[0][i]++;
            if (sym[i] - 'A' == opp) s[1][i]++;
        }
        if (k == 0)
        {
            sol = max(sol, s[0][n - 1] - s[1][n - 1]);
        }
        else
        {
            int curr_sol = MAX_N;
            for (int l=0;l<n-k+1;l++)
            {
                curr_sol = min(curr_sol, total(l));
            }
            sol = max(sol, curr_sol);
        }
    }
    
    printf("%d\n", sol);
    
    return 0;
}

```
