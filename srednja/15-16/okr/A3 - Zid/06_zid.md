---
hide:
  - toc
---

# A3 - Zid

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 64MB |

Nalazimo se u godini 80. pre nove ere. Cela Galija je pod vlašću Rimljana... Osim $N$ sela, koja se još uvek uspešno odupiru. Posle puno pokušaja, Rimljani su odustali od osvajanja svih sela. Odlučili su da će napraviti veliki zid, koji će odvojiti neka sela od njihove teritorije, a zatim osvojiti preostala.

Za svako selo je poznata njegova pozicija $(X_i, Y_i)$ (u kilometrima) i cena opremanja vojske (u zlatnicima) dovoljne da ga osvoji $W_i$. Rimska vojna taktika je toliko dobra da pri ovome ne očekuju gubitke – za osvajanje više sela cena opremanja vojske jednaka je najvećoj ceni za pojedinačna sela.

Na primer, ukoliko van zida ostanu tri sela, sa $W_i$ = 50, 20, 30, neophodna vojska će koštati 50 zlatnika. Zid mora biti pravougaonog oblika, sa stranicama paralelnim koordinatnim osama i centrom u $(0, 0)$ (niko nije rekao zašto, ali sigurno postoji dobar razlog). Jedan kilometar zida košta $C$ zlatnika. Moguće je napraviti zid koji je po jednoj ili obe dimenzije veoma kratak i ograđuje samo sela na odgovarajućoj osi – u tom slučaju, smatra se da je dužina “kratke” stranice zida 0 (npr. da bi se ogradila sela na $(0, 1)$ i $(0, 1)$, dovoljan je zid sa stranicama dužine 2 i “zanemarljivo malo”, sa ukupnom dužinom 4). Vaše zaduženje je da odredite najmanju cenu za koju je moguće ostvariti ovaj plan (sagraditi zid i osvojiti sva sela van zida).

## Opis ulaza
U prvom redu standardnog ulaza će se nalaziti dva cela broja $N$ i $C$, koji označavaju
redom broj sela i cenu kilometra zida.

U narednih $N$ redova će se nalaziti po tri cela broja $X_i$, $Y_i$, $W_i$, koji označavaju redom koordinate i cenu osvajanja sela (u redu $i$ + 1 će se nalaziti podaci za $i$-to selo).

## Opis izlaza
Na standardni izlaz ispisati jedan broj – minimalan broj zlatnika koje je neophodno
potrošiti da bi se plan ostvario.

## Primer 1
### Ulaz
```
4 2
2 -1 12
3 2 60
-5 -5 6
562
```

### Izlaz
```
46
```

## Primer 2
### Ulaz
```
2 10
005
111
```

### Izlaz
```
1
```

## Ograničenja

* $1 \leq N \leq 10^6$
* $1 \leq C \leq 200$
* $106 \leq X_i, Y_i \leq 10^6$
* $0 \leq W_i \leq 10^6$

## Napomena
Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 20 poena važi $N \leq  100, 100 \leq  X_i, Y_i \leq  100$.
* U test primerima vrednim 20 poena važi $N \leq  10^3$ i sva sela su na $x$-osi $(Y_i = 0)$.
* U test primerima vrednim 30 poena važi $N \leq  10^3$.
* U test primerima vrednim 30 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Jovanović | Ivan Stošić | Aleksandar Višnjić | Nikola Milosavljević |

## Obzervacija:
Ako jedno teme pravougaonog zida ima koordinate $(x,y)$, onda ostala imaju $(x,-y)$, $(-x,y)$ i $(-x,-y)$. Zbog simetrije, zadatak možemo rešavati samo u prvom kvadrantu: uzećemo **apsolutnu vrednost** koordinata svih sela, a zid će pokrivati sva sela u pravougaoniku sa temenima $(0,0)$, $(x,0)$, $(0,y)$ i $(x,y)$ i njegova cena će biti $4C\cdot (x+y)$. Selo $i$ pripada zidu akko $X_i\leq x$ i $Y_i\leq y$.

## Podzadatak 1:

U ovom podzadatku možemo izgraditi svaki mogući zid jer ih ima dovoljno malo i proveriti za svako selo da li je u njemu, i na osnovu toga da izračunamo cenu izgradnje zida i osvajanja svih ostalih.
Ako je $M=max(max|X_i|,max|Y_i|)$, zidova koje proveravamo ima najviše $(M+1)^2$, a ukupna složenost je $O(M^2\cdot N)$.

## Podzadatak 2:
$X$ koordinate sela se mogu poređati u **sortiran** niz i potrebno je izgraditi "prefiks" čija cena linearno zavisi od njegove dužine i na tu cenu dodati sufiksni maksimum (najskuplje selo za osvojiti van tog prefiksa)  koji smo ranije izračunali za svako selo. Primetimo da je u ovom slučaju optimalno graditi zid sa krajem u selu. Složenost je $O(NlogN)$ ili $O(N+M)$ zbog sortiranja.

## Podzadatak 3:

Selo sa koordinatama $(X_i,Y_i)$ možemo razložiti na dva sela sa $(X_i,0)$ i $(0,Y_i)$. Nije teško videti da se oba "razložena" sela moraju osvojiti kako se njegova cena ne bi uračunala u maksimum, samim tim je ovo ekvivalentan zadatak. Sada imamo dva  soritrana niza ("horizontalna" i "vertikalna" sela). Gradimo zid koji ima koordinate među ovim razloženim selima, njih ima $O(N^2)$ i u cenu osvajanja računamo sufiksne maksimume ova dva niza za efikasno rešenje.

## Podzadatak 4

Pretpostavimo da plaćamo $Z$ zlatnika za osvajanje sela van zida. Preostaje nam samo da ogradimo sela sa većom cenom. To možemo raditi jednim opadajućim prolaskom po svim vrednostima $Z$ tako što nakon izgradnje zida za određenu vrednost i nakon računanja cene dodamo sva sela sa tom istom cenom u zid (kako bismo garantovali da više ne plaćamo za njih); ako je ono van, onda jednostavno promenimo dimenzije zida najmanje što možemo tako da ono bude unutar (drugim rečima, postavljamo $x=max(x,X_i)$ i $y=max(y,Y_i)$). Koristeći *counting sort* dobijamo složenost $O(N+max(W_i))$.

``` cpp title="06_zid.cpp" linenums="1"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Selo {
    int x, y, w;
};

vector<Selo> sela[1000002];
int C; // cena kilometra zida

void ucitaj(){
    int N;
    cin >> N >> C;
    while (N--){
        Selo novo;
        cin >> novo.x >> novo.y >> novo.w;
        sela[novo.w].push_back(novo);
    }
}

int aps(int x){
    return x > 0 ? x : -x;
}

int resi(){
    int xmax = 0, ymax = 0, obim = 0, resenje = 1e9;

    for (int d=1000000; d>=0; d--){
        for (unsigned i=0; i<sela[d+1].size(); i++){
            xmax = max(xmax, aps(sela[d+1][i].x));
            ymax = max(ymax, aps(sela[d+1][i].y));
            obim = 4*(xmax+ymax);
        }
        resenje = min(resenje, C*obim + d);
    }
    return resenje;
}

int main(){
    ios_base::sync_with_stdio(0);
    ucitaj();
    cout << resi() << endl;
    return 0;
}


```
