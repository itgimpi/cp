# B1 - Kuvar

	| Vremensko ograničenje 1000ms | Memorijsko ograničenje 64MB |
	
Poznati TV kuvar Epirka planira sledeću sezonu svoje emisije, u kojoj će snimiti $N$ emisija o jelima $X_1, X_2, \dots, X_N$ (ne neophodno različitim -- moguće je da snima više emisija o istom jelu). Radi jednostavnosti, predstavićemo ova jela brojevima (isto od $1$ do $N$): ako je $X_i = x$, $i$-ta emisija će biti o jelu $x$.

Na raspolaganju mu je $N$ recepata $Y_1, Y_2, \dots, Y_N$, isto predstavljeni brojevima. Pošto emisija mora biti zanimljiva, nisu dovoljni recepti, već i scenario: smislio je (isto) $N$ scenarija $Z_1, Z_2, \dots, Z_K$, gde $Z_i = z$ znači da se $i$-ti scenario može koristiti za emisiju u kojoj će praviti jelo $Y_{z}$.

Nakon što je popisao emisije, jela i recepte, interesuje ga na koliko načina može da počne snimanje, odnosno na koliko načina može da izabere emisiju $i$ i scenario $j$ o receptu za odgovarajuće jelo. Drugim rečima, interesuje ga broj uređenih parova $(i, j)$, za koje važi $X_i = Y_{Z_j}$.
	
## Opis ulaza
Prvi red standardnog ulaza sadrži jedan prirodan broj $N$: broj emisija, recepata i scenarija.
	
Drugi red sadrži $N$ prirodnih brojeva $X_1, X_2, \dots, X_N$, gde je $X_i$ jelo o kom će snimiti $i$-tu emisiju.
	
Treći red sadrži $N$ prirodnih brojeva $Y_1, Y_2, \dots, Y_N$, gde je $Y_j$ jelo koje se pravi po $j$-tom receptu.
	
Četvrti red sadrži $N$ prirodnih brojeva $Z_1, Z_2, \dots, Z_N$, gde je $Z_k$ recept koji se koristi u $k$-tom scenariju. Scenariji su indeksirani počev od 1.
	
## Opis izlaza
Na standardni izlaz je potrebno ispisati jedan ceo broj: broj načina na koje je moguće izabrati emisiju i scenario, tako da recept koji odgovara tom scenariju pravi jelo o kom će emisija biti.
	
## Primer 1
### Ulaz
```
4
1 1 4 3
3 1 3 4
1 3 2 2
```
	
### Izlaz
```
6
```
	
## Primer 2
### Ulaz
```
5
1 1 1 1 1
2 1 5 5 5
2 1 2 3 3
```
	
### Izlaz
```
10
```
	
## Objašnjenje primera

## Primer 1

4       <- N = 4, 4 emisije, 4 recepta i 4 scenarija<br>
1 2 3 4 <- redni brojevi<br>
slede emisije po jelu:<br>
1 1 4 3 <- emisija 1 je o jelu 1, i druga, treća o jelu 4, četvrta o jelu 3<br>
onda jela po receptu:<br>
3 1 3 4 <- jelo 3 se pravi po receptu 1, jelo 1 po receptu 2, jelo 3 po 3, jelo 4 po 4<br>
na kraju recepti po scenariju:<br>
1 3 2 2 <- recept 1 je po scenariju 1, recept 3 po scenariju 2, 2 je po 3 i 2 je po 4<br>

Ako se odluči za prvu epizodu, praviće jelo $1$, koje se pravi samo po drugom receptu. Za taj recept postoje dva moguća scenarija: treći i četvrti.

Slično, drugoj epizodi odgovaraju treći i četvrti scenario.

Treća epizoda je o jelu $4$, za koje nema na raspolaganju nijedan scenario.

Četvrta epizoda je o jelu $3$, koje se pravi po prvom i trećem receptu. Za prvi recept ima spreman scenario $1$, a za drugi scenario $2$, tako da i za ovu epizodu ima na raspolaganju dva scenarija.

Dakle, ukupno ima $2 + 2 + 0 + 2 = 6$ opcija.
	
## Ograničenja
	
- $1 \leq N \leq 10^5$.
- $1 \leq X_i, Y_i, Z_i \leq N$.
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
- U testovima vrednim 20 poena: $N \leq 1000$ i $Z_i = i$ za sve $1 \leq i \leq N$.
- U testovima vrednim 20 poena: $N \leq 1000$.
- U testovima vrednim 10 poena: svi $Z_i$ su isti.
- U testovima vrednim 20 poena: $Z_i = i$ za sve $1 \leq i \leq N$.
- U testovima vrednim 30 poena: nema dodatnih ograničenja.

## Rešenje

Prva dva podzadatka mogu lako da se reše sa dve ugnježdene petlje koje isprobavaju svaki par $(i, j)$ i broje za koliko takvih parova je $X_i = Z_{Y_j}$. Vremenska složenost ovog algoritma je $\mathcal{O}(N^2)$, što nije dovoljno za preostale podzadatke.

## Rešenje za test primer 1 ( klasične petlje )

``` cpp title="kuvar1.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;	
	
int main() {
    int n = 4;
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // test primer 1

    long long res = 0;
    for (int i = 0; i < n; i++)  // za svaku emisiju...
        for (int j = 0; j < n; j++)   // za svaki scenario...
            if (x[i] == y[z[j]-1])   // -1 zbog prebacivanja sa 1, 2, 3, ... na 0, 1, 2, ...
                res++; 
                
    cout << res;
    return 0; }
```
Rešenje preko pokazivača. Ako se kod postavi na https://pythontutor.com/ lako se uočavaju preslikavanja.
## Rešenje za test primer 1 ( pokazivači )

``` cpp title="kuvar2.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;    

int main() {
    int n = 4;
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // test primer 1
    int *px, *py, *pz;
	
    int res = 0;
    for (int i = 0; i < n; i++) {  
        px = x + i;
        for (int j = 0; j < n; j++) {
            //if (x[i] == y[z[j]-1])    res++; 
            pz = z + j;
            py = y + *pz - 1;
            if ( *px == *py ) res++;    } }
                
    cout << res;
    return 0; }
```

## Rešenje za 40 poena

``` cpp title="kuvar3.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;	

int x[100010], y[100010], z[100010]; // ako se koriste statički nizovi, deklaracija je pre main-a
int cnt[100010];                     // za brojanje emisija, inicijalno sve na 0
	
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); // bez sinhronizacije
    int n; cin >> n; // unos
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> y[i];
    for (int i = 0; i < n; i++) cin >> z[i];
	
    long long res = 0;
    for (int i = 0; i < n; i++)  // za svaku emisiju...
        for (int j = 0; j < n; j++)   // za svaki scenario...
            if (x[i] == y[z[j]-1])   // -1 zbog prebacivanja sa 1, 2, 3, ... na 0, 1, 2, ...
                res++;               // ako je isto jelo...
                
    cout << res;
    return 0; }
```


	
## Glavno rešenje
	
Algoritam se poboljšava tehnikom brojanja, koja omogućava razdvajanje petlji. Prvo se prebroje emisije za svako jelo, i to smesti u niz $cnt$, gde je $cnt_i$ broj indeksa $j$ gde $X_j = i$. Pošto su sve vrednosti $X_i$ najviše $N$, nema problema sa memorijom i određuje se jednim prolazom kroz $X$.
	
Sada je dovoljno da prođemo kroz $Z$, i za svako $Z_i$ ukupnom broju dodamo $cnt_{Z_i}$ (broj elemenata u $X$ koji bi bili odgovarajući par). Vremenska složenost je sada $\mathcal{O}(N)$, dovoljno za $N \leq 10^5$.

## Rešenje za test primer 1 ( klasične petlje )

``` cpp title="kuvar4.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;	

int cnt[5];           // za brojanje emisija, inicijalno sve na 0
	
int main() {
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // nizovi
    int n = 4;
	
    int res = 0;
    for(int i = 0; i < n; i++)  // broj emisija za svako jelo
        cnt[x[i]]++;   
                
    // za svaki scenario koji vodi ka nekom jelu, dodaj u resenje broj emisija o tom jelu
    for (int i = 0; i < n; i++) res += cnt[y[z[i] - 1]];
	
    cout << res;
    return 0; }
```
Ako se kod postavi na https://pythontutor.com/ lako se uočavaju preslikavanja.
## Rešenje za test primer 1 ( pokazivači )

``` cpp title="kuvar5.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;    

int cnt[5];           // za brojanje emisija, inicijalno sve na 0
    
int main() {
    int n = 4;
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // nizovi
    int *px, *py, *pz, *pcnt;

    long long res = 0;
    for (px = x; px < x + n; px++) {  // broj emisija za svako jelo
        //cnt [ *px ]++;   // nizovski
        //(*(pcnt + *px))++; // pokazivacki kratko
        pcnt = cnt + *px;
        (*pcnt)++; }
                
    px = pcnt = NULL; // ne mora, zbog preglednisti
    //for(int i = 0; i < n; i++) res += cnt[y[z[i] - 1]]; // nizovski
    
    for(int i = 0; i < n; i++) {
        pz = z + i;
        py = y + *pz - 1;
        pcnt = cnt + *py;
        res += *pcnt; }
    
    cout << res;
    return 0; }
```

## Rešenje za 100 poena

``` cpp title="kuvar6.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;	
const int N = 100005; // maks. dimenzija nizova
int x[N], y[N], z[N]; // nizovi
int cnt[N];           // za brojanje emisija, inicijalno sve na 0
	
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> y[i];
    for (int i = 0; i < n; i++) cin >> z[i];
	
    long long res = 0;
    for (int i = 0; i < n; i++)  // broj emisija za svako jelo
        cnt[x[i]]++;   
                
    // za svaki scenario koji vodi ka nekom jelu, dodaj u resenje broj emisija o tom jelu
    for (int i = 0; i < n; i++) res += cnt[y[z[i] - 1]];
	
    cout << res;
    return 0; }
```

## mape za 100 poena

int
``` cpp title="01_kuvar.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);

    int n, tmp1, res = 0;
    vector<int> X; 
    vector<int> Y;
    map<int, int> mY;
    map<int, int> mZ;

    cin >> n;
    X.resize(n);
    Y.resize(n);
    for(int i = 0; i < n; i++) 
        cin >> X.at(i);

    for(int i = 0; i < n; i++) {
        cin >> tmp1;
        Y.at(i) = tmp1;
        mY[tmp1];
        mY[tmp1]++;    }
		
    for(int i = 0; i < n; i++) {
        cin >> tmp1;
        mZ[Y.at(tmp1 - 1)];
        mZ[Y.at(tmp1 - 1)]++;    }
    
    for(int i = 0; i < n; i++)
        res += mZ[X.at(i)];

    cout << res << endl;
    return 0;
}
```

ull
``` cpp title="02_kuvar.cpp" linenums="1"
sing namespace std;

int main()
{
    ios_base::sync_with_stdio(false);

    unsigned long long n, tmp1, res = 0;
    vector<unsigned long long> X; 
    vector<unsigned long long> Y;
    map<unsigned long long, unsigned long long> mY;
    map<unsigned long long, unsigned long long> mZ;

    cin >> n;
    X.resize(n);
    Y.resize(n);
    for(unsigned long long i = 0; i < n; i++) {
        cin >> X.at(i);
    }
    for(unsigned long long i = 0; i < n; i++) {
        cin >> tmp1;
        Y.at(i) = tmp1;
        mY[tmp1];
        mY[tmp1]++;
    }
    for(unsigned long long i = 0; i < n; i++) {
        cin >> tmp1;
        mZ[Y.at(tmp1 - 1)];
        mZ[Y.at(tmp1 - 1)]++;
    }
    
    for(unsigned long long i = 0; i < n; i++) {
        res += mZ[X.at(i)];
    }
    cout << res << endl;
    return 0;
}
```