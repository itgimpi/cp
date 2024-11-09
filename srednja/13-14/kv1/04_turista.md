---
hide:
  - toc
---

# 4 - Turista

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 700ms | 256MB |

Gazda Srba i njegova deca su veliki ljubitelji Zimskih olimpijskih igara. Gazda Srba je dve godine prodavao šljive sa svog voćnjaka šljiva u srcu Šumadije i skupio je dovoljno para da jedno od svoje N dece pošalje turistički na ovogodišnje Zimske olimpijske igre u Sočiju.

On je u dogovoru sa svojom decom organizovao izbore na kojima bi se odlučio koje dete ide na Zimske olimpijske igre. Svako dete je napisalo na svom glasačkom listiću jedno ime i ubacilo u glasačku kutiju. Gazda Srba je na glasanju bio uzdržan, predao je prazan listić.

Pravila ovog glasanja nisu uobičajena. Gazda Srba je veliki ljubitelj palindroma (palindrom je reč koja se čita isto i sa leve i sa desne strane, npr. Ana) i imena sve njegove dece su palindromi. Neka deca su na glasanju bila nestašna i predala su nevažeće listiće, listiće na kojima pišu imena koja nisu palindromi. Neka deca su međutim napisala imena koja su palindromi, ali nisu vodili računa o malim i velikim slovima pa su pisala imena kao što su ANA, BoB, LoL, HaNNAh, … Gazda Srba je doneo odluku da uvaži takve glasačke listiće i zbog toga će on sve listiće prepraviti da sadrže samo mala slova. (ANA -> ana, BoB -> bob, LoL -> lol, HaNNAh -> hannah, … )

Pobednik ovog glasanja je ono dete  koje ima najviše glasova, a u slučaju da više dece ima najviše glasova onda je pobednik ono dete  koje ima najviše glasova i čije je ime leksikografski najmanje.

Odredite koje dete je Gazda Srba poslao na Zimske olimpijske igre u Sočiju.

## Ulaz
U prvom redu standardnog ulaza se nalazi broj $N$ koji predstavlja broj dece Gazda Srbe. U sledećih $N$ redova se nalaze imena koja su Gazda Srbina deca napisala na svojim glasačkim listićima, u svakom redu po jedno ime.

## Izlaz
U prvom i jedinom redu standardnog izlaza treba ispisati ime deteta koje je Gazda Srba poslao na Zimske olimpijske igre u Sočiju.

## Primer 1
### Ulaz
```
7
Anna
anA
aNNNa
IcHaBoD
AbbiE
KatRINa
JEREMY
```

### Izlaz
```
ana
```

## Objašnjenje primera
Ichabod, Abbie, Katrina i Jeremy nisu validna imena jer nisu palindromi. Ana, Anna i Annna su palindromi i svako ime ima tačno jedan glas pa je pobednik ana kao leksikografski najmanje ime.

## Ograničenja

* $1 \leq N \leq 10^6$.
* Dužina najdužeg imena nije veća od 10.
* Imena Gazda Srbine dece će se sastojati samo od malih i velikih slova latinične abecede.
* Garantuje se da će barem jedan glasački listić biti validan.

Test primeri su podeljeni u tri disjunktne grupe:
* U test primerima vrednim $20$ poena važi $N \leq 1.000$.
* U test primerima vrednim $60$ poena važi $N \leq 500.000$.
* U test primerima vrednim $20$ poena nema dodatnih ograničenja.

## Napomena
String $A$ je leksikografski manji od stringa $B$ ukoliko postoji indeks $j$ takav da za svaki indeks $i < j$ važi $A[i] = B[i]$ i važi $A[j] < B[j]$ ili ukoliko je string $A$ prefiks stringa $B$.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksandar Ivanović | Aleksandar Ivanović | Aleksandar Ivanović | Dušan Zdravković |

U ovom zadatku se od takmičara zahtevalo da u listi reči pronađe od svih palindroma koji se najviše pojavljuju u listi od svih reči onaj koji je leksikografski najmanji. Zadatak se pokazao kao jedan od težih iz ovog seta i samo je devetoro takmičara osvojilo maksimalan broj poena.

Prva stvar koju treba uraditi u svakom rešenju ovog zadatka je izdvojiti palindrome u posebnu listu jer nam reči koje nisu palindromi ne utiču na rešenje i samo nam povećavaju vremensku složenost.

Test primeri su bili podeljeni u tri disjunktne grupe.

U prvoj grupi se nalazilo $20\%$ test primera i za test primere iz prve grupe je važilo da je broj reči u ulaznoj listi $N \leq 1.000$. Za rešavanje ovog podzadatka je bilo dovoljno proveriti sa dve petlje za fiksiran indeks $1 \leq i \leq N_{pal}$ koliko postoji indeksa $i \leq j \leq N_{pal}$ takvih da je $Pal[i]=Pal[j]$, gde je $Pal$ lista palindromskih reči.  Složenost ovog rešenja je $O(N_{pal}^2 \cdot L)$, gde je $L$ dužina reči sa ulaza. $L$ po uslovima zadatka nije veće od $10$.

U drugoj se nalazilo $60\%$ test primera i za te test primere je važilo $N \leq 50.000$. Za rešavanje ove grupe test primera je bilo potrebno da se zaključi da se ulazne reči mogu sortirati i da će se onda jednake reči pojavljivati jedna za drugom u listi. Nakon sortiranja reči rešenje se može pronaći jednim prolazom kroz niz tako što se sve reči u uzastopnom bloku jednakih reči obrađuju odjednom. Ukoliko se koristi efikasan algoritam za sortiranje, rešenje ima složenost $O(N_{pal}\cdot \log(N_{pal}) \cdot L)$.

U poslednjoj grupi test primera se nalazilo $20\%$ test primera i za rešavanje ove grupe test primera je bilo potrebno primeniti tehniku heširanja. Možemo primetiti da je u prethodnim rešenjima u složenosti figurisala dužina reči $L$. Iako je ta dužina mala možemo je izostaviti tako što ćemo ulazne reči heširati, odnosno pretvoriti u brojeve. Heširanje reči u brojeve je injektivno preslikavanje skupa reči u skup integera. Pošto su ulazne reči kratke možemo izbeći koliziju (pojavu da dve različite reči imaju istu heš vrednost, koja se dešava pri heširanju velikih stringova jer se heširanje mora raditi po nekom modulu) tako što ćemo koristiti sledeću heš funkciju:
$$
h(s)=(s_0-'a'+1)\cdot 27^{l-1}+(s_1-'a'+1)\cdot 27^{l-2}+\ldots+(s_{n-1}-'a'+1)\cdot 27^0.
$$
Primetimo da je dovoljno da heširamo samo polovinu stringa odnosno prvih $(l+1)/2$ karaktera i podatak o tome da li je palindrom parne ili neparne dužine pošto su palindromi simetrični. Nakon heširanja dovoljno je da koristimo matricu od $275$ redova i $2$ kolone kako bi smo prebrojali sve palindrome i pronašli rešenje.

## Generalizacija
Ukoliko ne bi postojalo ograničenje za dužinu ulaznih reči ali bi postojalo ograničenje za njihovu sumu $1 \leq L_i \leq 10^6$ zadatak bi se mogao rešiti koristeći strukturu *Trie* koja je veoma korisna u zadacima sa stringovima. Više o strukturi *Trie* možete pročitati na [linku.](http://www.dms.rs/agogeit/data/tekstovi/Trie.pdf)

``` cpp title="04_turista.cpp" linenums="1"
#include <stdio.h>
#include <ctype.h>
#include <cstring>
#include <string>
using namespace std;

int cnt[27*27*27*27*27][2];

int main() {

    int n,l,k,i,j,t1,t2,bb,resbr;
    string ps,res;
    char s[15];

    res = "";
    resbr = 0;

    scanf("%d", &n);
    for(i=0; i<n; i++) {
        scanf("%s", &s);
        l=strlen(s);
        k=(l+1)/2;
        t2=l&1;
        t1=0;
        bb=1;
        for(j=0; j<k; j++) {
            t1 = t1*27 + (tolower(s[j]) - 'a' + 1);
            s[j] = tolower(s[j]);
            s[l-1-j] = tolower(s[l-1-j]);
            if (s[j] != s[l-1-j]) bb=0;
        }

        if (bb) {
            if( ++cnt[t1][t2] > resbr ) {
                resbr = cnt[t1][t2];
                res = string(s);
            } else if (cnt[t1][t2] == resbr) {
                ps = string(s);
                if (ps < res) {
                    res = ps;
                }
            }
        }
    }

    printf("%s\n", res.c_str());

    return 0;
}

```
