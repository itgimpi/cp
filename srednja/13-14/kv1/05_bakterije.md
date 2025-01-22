---
hide:
  - toc
---

# 5 - Bakterije

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |

Ruski špijuni otkrili su plan da se onemogući održavanje Zimskih olimpijskih igara. U planu stoji sledeće:

* Soči (mesto održavanja ZOI) je podeljen na kvadratne regione. Svaki region određen je koordinatama $(x, y)$. Susedni regioni regionu $(x, y)$ su: $(x-1,y)$, $(x+1,y)$, $(x,y-1)$, $(x, y+1)$.
* Određeni regioni u određenim trenucima biće zaraženi određenom vrstom bakterije. Svake sekunde, bakterije se šire na sve susedne regione (ali ne nestaju iz regiona u kojima se već nalaze). Grupu bakterija čine svi povezani regioni na kojima živi ta bakterija.

Međutim, plan ima veliki propust koji je organizator uspeo da otkrije. Kada se dve ili više grupa različitih bakterija nađe u istom regionu, obe odnosno sve grupe umiru (nestaju sa svih polja) istog trenutka. Ukoliko se susretnu grupe istih bakterija one se spajaju u jednu grupu. Spajanje grupa se odvija brže od umiranja. Odnosno, ako se u istom trenutku grupa $A$ u nekom regionu susretne (nađe u istom regionu) sa grupom $B$ iste vrste, a u nekom drugom (ili istom) regionu susretne sa grupom $C$ različite vrste, tada se prvo spajaju grupe $A$ i $B$, a potom obe umiru zajedno sa grupom $C$.

Ovo će znatno olakšati borbu protiv bakterija, jer će neke vrste same nestati. Ali neke nikada neće same nestati pa se za njih mora napraviti serum. Organizatoru je neophodna vaša pomoć. Potrebno je da odgovorite na pitanje: Koji je prvi trenutak posle kog nijedna grupa bakterija neće više umrti? Za koliko i kojih vrsta bakterija je potrebno napraviti serum? Garantuje se da će bar jedna grupa bakterija umreti.

## Ulaz
U prvom redu standardnog ulaza nalazi se broj $N$, broj regiona koji napadači planiraju da zaraze. U sledećih $N$ redova nalaze se $4$ cela broja, $X$, $Y$, $T$, $S$, gde je $(X, Y)$ region koji napadači planiraju da zaraze u trenutku $T$ bakterijom vrste $S$. Napadači neće zaraziti isti region dva puta, ali u jednom trenutku mogu zaraziti više regiona.

## Izlaz
Standardni izlaz u prvom redu sadrži ceo broj, odgovor na pitanje: Koji je prvi trenutak posle kog nijedna grupa bakterija neće više umrti? U drugom redu nalazi se broj $K$, broj različitih vrsta bakterija za koje je potrebno napraviti serum ili $0$ ako će sve vrste same nestati. U trećem redu nalaze se $K$ brojeva, vrste bakterija razdvojene razmakom.

## Primer 1
### Ulaz
```
3
1 1 1 2
3 1 1 1
5 1 1 1
```

### Izlaz
```
2
0
```

## Objašnjenje primera
Zaraženo je ukupno $3$ regiona i sva tri su zaražena istovremeno u sekundi $1$. Regioni $(3, 1)$ i $(5, 1)$ su zaraženi bakerijama vrste $1$ a region $(1, 1)$ bakterijom vrste $2$. Posle prve sekunde, bakterije sa regiona $(3, 1)$ i $(1, 1)$  se susreću kao i bakterije sa regiona $(3, 1)$  i $(5, 1)$. Prvo se spajaju bakterije vrste $1$ a zatim vrste $1$ i $2$ umiru. Dakle, posle $2$ sekunde neće ostati nijedna vrsta i neće biti potreban serum.

## Ograničenja

* $1 \leq N \leq 1000$.
* $1 \leq X, Y, T, S \leq 10^9$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim $20$ poena važi $1 \leq N, X, Y, T, S \leq 100$.
* U test primerima vrednim $30$ poena važi $1 \leq N \leq 100$ i $1 \leq X, Y, T, S \leq 10^9$.
* U test primerima vrednim $50$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Baković | Dimitrije Dimić | Nepoznato | Marko Baković |

Najjednostavnije rešenje ovog zadatka bi bila čista simulacija po vremenu. Kratko ćemo opisati to rešenje. Za svako polje na mapi čuvamo koja se bakterija nalazi na tom polju. U svakom trenutku radimo sledeće:

* Proširimo sve grupe bakterija koje se nalaze na mapi, tako što na svako polje koje dodiruje neku vrstu, upišemo tu vrstu.
* Da li se neka bakterija pojavljuje u trenutku u kom se nalazimo? Ako se pojavljuje, ubacimo je na mapu tako što obeležimo da se na polju $(X, Y)$ nalazi bakterija vrste $S$.
* Preostaje nam da uništimo neke bakterije. To možemo da uradimo puštajući *BFS* (ili *DFS*) od svih polja na kojima su se spojile dve grupe različite vrste i uklanjajući te vrste sa mape.

Jedini mogući ishodi su jedna ili nijedna preživela. Trenutak nakon poslednjeg pojavljivanja bakterija, a u kom se na mapi nalazi samo jedna vrsta ili uopšte nema bakterija je rešenje. Pri implementaciji, obratiti pažnju da ako se na dva susedna polja nalazi bakterija iste vrste, ne mora nužno da znači da ta dva polja čine istu grupu. Analizirajmo složenost ovog rešenja:

* Proširivanje bakterija moguće je implementirati u složenosti $O(maxX\cdot maxY)$.
* Pojavljivanje nove bakterije zahteva samo njeno dodavanje na određeno polje, pa je složenost $O(1)$.
* Uništavanje vrsta može se implementirati u $O(maxX\cdot maxY)$.

Takmičari koji su imali ovakvo rešenje osvojili su $20$ poena.

U simulaciji po vremenu, značajna su samo uništavanja i spajanja grupa, što možemo iskoristiti za bolje rešenje. Na početku svakoj bakteriji dodelimo čvor u grafu i obeležimo sve bakterije kao žive. Sve dok postoje dve žive bakterije različite vrste radimo sledeće:

Nađemo dve žive bakterije koje će se prve susresti, ukoliko postoji više takvih prednost dajemo bakterijama iste vrste. Ukoliko su iste vrste povežemo njihove čvorove u grafu. Inače, obeležimo obe vrste kao mrtve i od njihovih čvorova pustimo *DFS* (ili *BFS*) i obeležimo sve bakterije koje su povezane sa njima (ne nužno direktno) kao mrtve. Rešenje je maksimum svih trenutaka u kojima se pojavljuju neke bakterije i svih trenutaka u kojim dolazi do uništavanja nekih bakterija. Ukoliko postoji neka preživela vrsta, lako je naći koja je.

Uništavanja može biti najviše $\frac{N}{2}$, međutim spajanja u najgorem slučaju može biti $\frac{(N-1)\cdot(N-2)}{2}$, pa je složenost ovog rešenja $O(N^4)$ i ono vredi $50$ poena.

Ovo rešenje lako možemo dovesti do složenosti $O(N^2\cdot \log N)$ koja donosi $100$ poena. Napravimo niz svih parova bakterija. Svi parovi će se nekada spojiti (uništiti ili povezati). Sortirajmo ovaj niz po vremenima spajanja svakog para, tako što ćemo dati prednost parovima koji se prvi spajaju, a ukoliko se dva para spajaju u istom trenutku, dajemo prednost onom paru koji sadrži dve bakterije iste vrste (ako takav postoji). Sada prolaskom kroz niz radimo isto što i u prethodno opisanom rešenju, samo što sada nema potrebe da tražimo dve najbliže bakterije svaki put. Ukoliko je bar jedna bakterija iz para mrtva, preskočimo taj par, inače spojimo njihove čvorove ako su iste vrste, odnosno ako su različite vrste uništimo njih i sve bakterije povezane sa njima.

Napomenimo da i umesto pravljenja grafa i puštanja *DFS*-a (ili *BFS*-a) moguće je i koristiti [*disjoint-set union*](http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=disjointDataStructure).

``` cpp title="05_bakterije.cpp" linenums="1"
/*
    Marko Bakovic
    Bakterije
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

const int maxn = 1e3 + 5;

struct node
{
    int x, y, time, type;
} event[ maxn ];

int n, dist[ maxn ][ maxn ], time_sol, all_size, dead[ maxn ];
pair < int, int > all[ maxn * maxn ];
vector < int > adj[ maxn ];

int get_dist( node A, node B )
{
    int temp = abs( A.x - B.x ) + abs( A.y - B.y );
    int diff = max( A.time, B.time ) - min( A.time, B.time );
    return max( A.time, B.time ) + max( 0, ( temp - diff + 1 ) / 2 );
}

bool cmp( pair < int, int > A, pair < int, int > B )
{
    if ( dist[ A.first ][ A.second ] != dist[ B.first ][ B.second ] ) return dist[ A.first ][ A.second ] < dist[ B.first ][ B.second ];
    return ( event[ A.first ].type == event[ A.second ].type );
}

void kill( int curr, int time )
{
    dead[ curr ] = time;
    for ( vector < int > :: iterator it = adj[ curr ].begin(); it != adj[ curr ].end(); it++ )
        if ( dead[ *it ] == -1 ) kill( *it, time );
}

bool one_dead( int A, int B )
{
    if ( dead[ A ] != -1 && dead[ A ] < dist[ A ][ B ] ) return true;
    if ( dead[ B ] != -1 && dead[ B ] < dist[ A ][ B ] ) return true;
    return false;
}

int main()
{
    scanf( "%d", &n );
    for ( int i = 0; i < n; i++ ) scanf( "%d %d %d %d", &event[ i ].x, &event[ i ].y, &event[ i ].time, &event[ i ].type );
    for ( int i = 0; i < n; i++ )
        for ( int j = i + 1; j < n; j++ )
        {
            all[ all_size++ ] = make_pair( i, j );
            dist[ i ][ j ] = get_dist( event[ i ], event[ j ] );
        }
    sort( all, all + all_size, cmp );
    memset( dead, -1, sizeof( dead ) );
    for ( int i = 0; i < all_size; i++ )
    {
        if ( one_dead( all[ i ].first, all[ i ].second ) ) continue;
        if ( event[ all[ i ].first ].type != event[ all[ i ].second ].type )
        {
            kill( all[ i ].first, dist[ all[ i ].first ][ all[ i ].second ] );
            kill( all[ i ].second, dist[ all[ i ].first ][ all[ i ].second ] );
            time_sol = dist[ all[ i ].first ][ all[ i ].second ];
        }
        else
        {
            adj[ all[ i ].first ].push_back( all[ i ].second );
            adj[ all[ i ].second ].push_back( all[ i ].first );
        }
     }
     printf( "%d\n", time_sol );
     int alive = -1;
     for ( int i = 0; i < n; i++ )
        if ( dead[ i ] == -1 )
        {
            alive = event[ i ].type;
            break;
        }
    if ( alive == -1 ) printf( "0\n" );
    else printf( "1\n%d\n", alive );
    return 0;
}

```
