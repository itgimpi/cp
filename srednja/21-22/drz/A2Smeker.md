# A1 - Šmeker (tačka s)

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

U grid (celobrojni koordinatni sistem) se dodaju tačke. Posle svake dodate tačke $t$ treba da se odredi da li postoji tačka $t_s$, tako da važi da je broj tačaka sa većim koordinatama jednak broju tačaka sa manjim koordinatama i da je broj tačaka gde je x veći od y isti sa brojem tačaka gde je x manji od y.
```
                |
                |
	S2          |    S1 - veći x-ovi i y-i
x-ovi manji     |
y-i veći        |
                |
----------------ts----------
                |
                |
	S3          |    S4 - x-ovi veći, 
x-ovi manji     |         y-i manji
y-i manji       |
```
broj elemenata S1 + broj elemenata S3 = broj elemenata S2 + broj elemenata S4

## Opis ulaza
U prvom redu je n, broj tačaka. U svakom sledećem redu su koordinate tačke $(x_i, y_i)$ koja se dodaje.
## Opis izlaza
Za svaku dodatu tačku odredi tačku ts, ako postoji. Inače -1.
## Primer1

### Ulaz

```
3
1 1
2 2
3 3
```

### Izlaz

```
1
-1
2
```
## Objašnjenja primera
Posle dodavanja prve tačke (t1) u gridu je samo jedna tačka, u 4 skupa je po 0 tačaka, t1 je ts. 
Posle t2 nijedna ne može da bude ts.
Posle t3, t2 je ts jer je po jedna tačka u S1 i S3 a 0 tačaka u S2 i S4.

## Primer2

### Ulaz

```
5
1 1
2 5
3 3
4 2
5 4
```

### Izlaz

```
1
-1
-1
-1
3
```
## Objašnjenja primera
Posle t5, za t3 sva 4 skupa su veličine 1, t3 je ts. 

## Ograničenja
-   $1 \leq n \leq 2\cdot10^5$
-   $1 \leq x_i,y_i \leq 10^9$
-   ne postoje iste $x$ koordinate
-   ne postoje iste $y$ koordinate

Test primeri su podeljeni u 4 disjunktne grupe:

-   U test primerima vrednim $12$ poena: $N \leq 500$
-   U test primerima vrednim $22$ poena: $x_i=y_i$
-   U test primerima vrednim $23$ poena: $N \leq 4.000$
-   U test primerima vrednim $43$ poena: Bez dodatnih ograničenja

#  Rešenje

 
## Rešenje kad je $n \leq 500$
Za svaku novu tačku se izbroje tačke u sva 4 skupa, $O(n^3)$.

## Rešenje kad je $x_i=y_i$
Zbog ponavljanja koordinata, drugi uslov je sigurno ispunjen, ostaje provera za gore desno i dole levo.
Drugim rečima, gleda se samo x koordinata i određuje medijana (samo za neparan broj tačaka).

Brzo određivanje medijane je moguće sa dva hipa, oba čuvaju otprilike po pola (eventualno prvi 1 više) i medijana je uvek najveći element u prvom.

**Hip** je binarna struktura, gde je dodavanje u hip $O(logn)$ a određivanje maksimuma ili minimuma $O(logn)$.

Npr. elementi $1, 12, 54, 72 \ i\  100$ u hipu bi bili: $100$, redosled ostalih nije uređen.

U hipu sa minimumom bi bili: $1$, ostali neuređeni.

Trik sa 2 hipa je:

**hip 1** sadrži $1, 12 \ i\  54$, **hip2** sadrži $100 \ i\  72$.

Brzo se pristupa **najvećem u hipu 1 (54)**, koji je i $medijana$ i **najmanjem u hipu 2**, koji se koristi za $određivanje$ u koji hip ide novi elemenat.

Treba da se održava i $balansiranost$ hipova, da bi medijana uvek bila u hipu 1.

### Brza medijana sa 2 hipa:
#### ako su hipovi prazni (dodaje se prvi el.), ide u prvi hip
#### hip1 čuva manje, hip2 veće elemente
#### Za paran broj elemenata (dodaje se el. sa neparnim rednim brojem) dimenzije hipova su iste
#### neka je hip1: 10, 20, 30 a hip2: 50, 60, 70
Posle dodavanja hip1 treba da bude za 1 veći a njegov najveći el. medijana.

Novi element se poredi sa najmanjim iz hipa2, može da bude manji ili veći.

Neka je novi element **40**, onda je **40 < 50**. Njemu je mesto u **hipu 1**, tamo se i dodaje. Isto bi bilo da je novi element bio i npr. 5, koji je manji od dosadašnje medijane. Dodavanje u hip je $O(logn)$ 

Neka je novi element **70**, onda je **70 > 50**. Njemu je mesto u **hipu 2**, tamo se i dodaje. Isto bi bilo da je novi element bio i npr. 55, koji bi bio novi min u hipu 2.

Ali, treba da se vodi računa o **balansiranosti** hipova. **Najmanji iz hipa 2 se prebacuje u hip1 a novi ide u hip2**.

#### Za neparan broj elemenata (dodaje se parni indeks), hip1 ima 1 el. više 
#### neka je hip1: 10, 20, 30, 40 a hip2: 50, 60, 70

Opet se **novi** el. poredi sa **najmanjim iz hipa 2**. Ako je **veći**, jednostavno ide u **hip2**.

Inače je za **hip 1**. Najveći iz **hipa 1** se prebaci u **hip2** a novi ide u **hip 1**.

## Rešenje kad je $N \leq 4.000$
Tačka t je rešenje ako je njena x-koordinata medijana za sve x-koordinate i y-koordinata medijana za sve y-koordinate. 

Dokaz. Ako je gore desno s1, gore levo s2, dole levo s3 i dole desno s4  tačaka, uslov za medijanu je da je zbir gornjih isti sa zbirom donjih, s2+s1=s4+s3 i da je zbir levih isti sa zbirom desnih, s2+s3=s1+s4, sabiranjem 2 jednačine se dobija 2s2+s1+s3=s1+2s4+s3 to jest s2=s4, i s1=s3, tako da ako je tačka po obe koordinate medijana, onda je ts. 

Rešenje u $O(n^2logn)$ je da se posle svakog dodavanja odredi medijana u $O(nlogn)$, i ako je ista tačka onda je ts.

## Glavno rešenje

Medijana se održava sa dva hipa u $O(logn)$. Tačnije, dve medijane u po dva hipa. Posle svake nove tačke se proveravaju indeksi medijana. $O(n logn)$

``` cpp title="a2_smeker.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
// za brzo odredjivanje nedijane se koriste 2 hipa
// 2 za x i 2 za y koordinate
priority_queue<pair<int,int>> hipx1; priority_queue<pair<int,int>> hipy1;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> hipx2;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> hipy2;

void uhipx(int vrednost, int i) { // u hip idu 
    pair<int, int> nova = {vrednost, i};
    if (i == 1) // prva tacka ide u prvi hip1, njegov max je medijana
        {hipx1.push(nova); return;} // i to je to
    if (i & 1) {  // tacke sa neparnim indeksima, hipovi su pre dodavanja iste dimenzije
        if(nova < hipx2.top()) // nije veca od najmanjeg iz hipa2, 
            hipx1.push(nova); // ide u hip1, hip1 je za 1 veci od hipa 2
        else { // ipak je veca od najmanjeg iz hipa2, onda je za hip2, ali...
            // treba da se odrzava balansiranost hipova!
            pair<int,int> tmp = hipx2.top(); // zapamti najmanji iz hipa2
            hipx2.pop(); // izbaci najmanji iz hipa2
            hipx2.push(nova); // dodaj novi u hip2
            hipx1.push(tmp); } // dodaj prethodno najmanji iz hipa2 u hip1
            //  opet je hip1 za 1 veci od hipa 2
        return; } // i to je to
    // tacke sa parnim indeksima, hip1 je pre dodavanja veci za 1
    if (nova > hipx1.top()) // ako je nova tacka za hip2
        hipx2.push(nova); // ide u hip2
    else { // ipak je za hip1
        pair<int,int> tmp = hipx1.top(); // zapamti najveci iz hipa1
        hipx1.pop(); // izbaci ga iz hipa1
        hipx1.push(nova); // dodaj novu u hip1
        hipx2.push(tmp); } } // zapamcenu u hip2

void uhipy(int vrednost, int i) {
    pair<int,int> nova = {vrednost, i};
    if(i == 1) 
        {hipy1.push(nova); return;}
    if(i & 1) { 
        if(nova < hipy2.top()) hipy1.push(nova);
        else {
            pair<int,int> r=hipy2.top();
            hipy2.pop(); hipy2.push(nova);
            hipy1.push(r); }
        return; }
    if(nova>hipy1.top()) hipy2.push(nova);
    else { 
        pair<int,int> r=hipy1.top();
        hipy1.pop(); hipy1.push(nova);
        hipy2.push(r); } }

int medijanax() {
    if(hipx1.size()!=hipx2.size()) // ako su dimenzije hipova razlicite
        return hipx1.top().second; // vrati indeks najvece iz prvog hipa
    return -1; }

int medijanay() {
    if(hipy1.size()!=hipy2.size()) 
        return hipy1.top().second;
    return -1; }

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); // zbog IO preplitanja 
    int n; cin >> n;
    for(int i = 1; i <= n; i++) { // tacke od 1 do n...
        int x, y; cin >> x >> y;
        uhipx(x, i); // na hip idu koordinata i redni broj / indeks tacke
        uhipy(y, i);
        int mx = medijanax(); // odredi medijanu po x
        int my = medijanay(); // i po y
        if (mx == my) cout << mx << '\n'; // ako je to isti indeks, medijana postoji
        else cout << -1 << '\n'; } } // inace ne
```
