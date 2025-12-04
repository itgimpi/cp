union-find

1. union-find sa pamćenjem podskupova
2. union-find sa pamćenjem roditelja
3. union-find sa rang-om
4. union-find i kompresija putanje
5. union-find babe i dede
6. union-find druge babe i dede

Elementi skupa se razbiju u podskupove sa po jednim elementom, disjunktne podskupove.

Treba da se obezbedi union (unija) i find (nađi koji je podskup ili predstavnik) podskupova.

# 1 union-find sa pamćenjem podskupova

Svaki element se poveže sa skupom kome pripada i lako se dolazi do skupa.

Svaki element se pomoću niza od 0 do n-1 preslika u skup kome pripada.  

Ako elementi nisu brojevi, koristi se mapa. 

Find je trivijalna operacija, samo se pročita oznaka podskupa, O(1). 

Union je spora, jer se prolazi kroz ceo niz, O(n).

```
Sve su posebni skupovi:
0  1  2  3  4  5  6  7 <- id elemenata
0  1  2  3  4  5  6  7 <- elementi
```
```
unija 7 6

posebni: 0, 1, 2, 3, 4 i 5, plus skup {6, 7} u oznaci 6
0  1  2  3  4  5  6  6
0  1  2  3  4  5  6  7
```
```
unija 6 5

posebni: 0, 1, 2, 3 i 4, plus skup {5, 6, 7} u oznaci 5
0  1  2  3  4  5  5  5
0  1  2  3  4  5  6  7
```
```
nadji 5 -> 5
```
```
unija 5 4

posebni: 0, 1, 2 i 3, plus skup {4, 5, 6, 7} u oznaci 4
0  1  2  3  4  4  4  4
0  1  2  3  4  5  6  7
```
```
unija 4 3

posebni: 0, 1 i 2, plus skup {3, 4, 5, 6, 7} u oznaci 3
0  1  2  3  3  3  3  3
0  1  2  3  4  5  6  7
```
```
unija 3 2

posebni: 0 i 1, plus skup {2, 3, 4, 5, 6, 7} u oznaci 2
0  1  2  2  2  2  2  2
0  1  2  3  4  5  6  7
```
```
unija 2 1

posebni: 0, plus skup {1, 2, 3, 4, 5, 6, 7} u oznaci 1
0  1  1  1  1  1  1  1
0  1  2  3  4  5  6  7
```
```
unija 1 0

samo skup {0, 1, 2, 3, 4, 5, 6, 7} u oznaci 0
0  0  0  0  0  0  0  0
0  1  2  3  4  5  6  7
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int id[1000];
int n;

void init() { // 
    for (int i = 0; i < n; i++)
        id[i] = i; } // svaki el. od 0 do n-1 je sam u svom skupu 

int nadji(int x) { // kom skupu pripada? O(1)
   return id[x]; }

int isti(int x, int y) { // da li pripadaju istom skupu?
    return nadji(x) == nadji(y); }

void spoji(int x, int y) { // spoji prvi i drugi skup u drugi O(n)
    int idx = id[x], idy = id[y]; // први и други скуп
    for (int i = 0; i < n; i++) // за све могуће елементе...
        if (id[i] == idx)        // ако је био члан првог...
            id[i] = idy; }        // сада је члан другог.

int main() {
    n = 10;
    init(); // 10 podskupova, od 0 do 9
    cout << nadji(5) << endl;
    cout << nadji(6) << endl;
    isti(5,6) ? (cout << "jesu" << endl) : (cout << "nisu" << endl);
    spoji(5, 6);
    cout << nadji(5) << endl;
    cout << nadji(6) << endl;
    isti(5,6) ? (cout << "jesu" << endl) : (cout << "nisu" << endl);
    return 0;    }
```

# 2 union-find sa pamćenjem roditelja

Elementi se ne preslikavaju u podskupove nego u roditelje. 

Formiraju se stabla, u kojima se koreni na početku preslikavaju sami u sebe. Npr roditelj od 5 je 5.

Podskup nekog elementa se određuje prolaskom kroz roditelje, do korena. Deca pokazuju na roditelje.

```
7   svi elementi ispod su u skupu koji je obeležen 7.
^
|
4   4 je roditelj od 2, 7 je roditelj od 4
^
|
2  
``` 

Unija se dobija usmeravanjem korena jednog skupa prema drugom.

Prvi algoritam predstavlja osobu koja se seli i obaveštava ostale o novoj adresi.

Drugi algoritam na staroj adresi ostavi informaciju o novoj.

Ово, наравно, мало успорава доставу поште, јер се мора прећи кроз низ преусмеравања, 
али ако тај низ није предугачак, може бити значајно ефикаснији од првог приступа.

Složenost zavisi od uravnoteženosti stabla. 
Najgori slučaj je O(n):

```
0  1  2  3  4  5  6  7 <- roditelj elementa
0  1  2  3  4  5  6  7 <- element
```
```
unija 7 6

0  1  2  3  4  5  6
                  7 (potomak od 6)

0  1  2  3  4  5  6  6 <- roditelj el. 7 je sada 6
0  1  2  3  4  5  6  7
```

```
unija 6 5

0  1  2  3  4  5 (predstavnik skupa {5,6,7})
               6 (potomak od 5)
               7

0  1  2  3  4  5  5  6 <- roditelj el. 6 je sada 5
0  1  2  3  4  5  6  7
```
```
unija 5 4

0  1  2  3  4
            5
            6
            7

0  1  2  3  4  4  5  6 <- roditelj el. 5 je sada 4
0  1  2  3  4  5  6  7
```
```
unija 4 3

0  1  2  3  3  4  5  6 <- roditelj el. 4 je sada 3
0  1  2  3  4  5  6  7
```
```
unija 3 2

0  1  2  2  3  4  5  6 <- roditelj el. 3 je sada 2
0  1  2  3  4  5  6  7
```
```
unija 2 1

0  1  1  2  3  4  5  6 <- roditelj el. 2 je sada 1
0  1  2  3  4  5  6  7
```
```
unija 1 0

0  0  1  2  3  4  5  6 <- roditelj el. 1 je sada 0
0  1  2  3  4  5  6  7
```

Kom skupu pripada element 7? Roditelj od 7 je 6, tako da on ukazuje na pripadnost.
Njegov roditelj je 5, onda 4, ... Tako do 0.
Za bilo koji el. da se proveri, dolazi se do 0.

Upit je u O(n).

Ovo je gore od 1. rešenja gde je find bio O(1).

Da je stablo uravnoteženo, bilo bi O(logn). 
Zadatak je efikasna struktura, koja omogućava uravnoteženo stablo.

```cpp
#include <bits/stdc++.h>
using namespace std;

int roditelj[1000];
int n;

void init() {
    for (int i = 0; i < n; i++)
        roditelj[i] = i; }

int nadji(int x) {
    while (roditelj[x] != x) 
        x = roditelj[x];
    return x; }

void spoji(int x, int y) { // spoji prvi i drugi u prvi
    int fx = nadji(x), fy = nadji(y);
    roditelj[fx] = fy; }
     
int main() {
    n = 7;
    init(); // 7 podskupova, od 0 do 6

    spoji(7, 6); spoji(6, 5); //...

    cout << nadji(7) << endl; // 0

    return 0;    }
```

# 3 union-find sa rangom

Kod unije bi bilo dobro da se visina stabla (od korena do najdaljeg lista) što manje povećava.

Koren manjeg stabla treba da pokazuje na veće. Onda se visina ne povećava:

```
1 + 2 -> 1, 1 + 3 -> 1,  1 + 4 -> 1,   1 + 3 -> 1,   1 + 4 -> 1
         2  2       2 3 2 3     2 3 4  2   4   2 3  2 3  5  2 3 4
                                                 4              5
```

Samo ako su visine iste, visina unije se poveća za 1.
 
Visine stabala (disj. skupova) su u nizu rang:
```
0  0  0  0  0  0  0  0, rang je 0, tj. h = 0
1  2  3  4  5  6  7  8, elementi
```
```
spoji 1 2

1  0  0  0  0  0  0, rang
1  3  4  5  6  7  8, samo {1, 2} ima rang 1 (h=1)
2
```
```
spoji 6 7

1  0  0  0  1  0, rang
1  3  4  5  6  8, {1, 2} i {6, 7} imaju rang 1
2           7
```
```
spoji 4 7

1  0  0    1    0, rang
1  3  5    6    8, {1, 2} i {6, 7, 4} imaju rang 1
2        4   7
```
```
spoji 5 8

1  0    1     1, rang
1  3    6     8, {1, 2}, {6, 7, 4} i {8, 5} imaju rang 1
2     4   7   5
```
```
spoji 1 3

  1       1     1, rang
  1       6     8, {1, 2, 3}, {6, 7, 4} i {8, 5} imaju rang 1
2   3   4   7   5
```
```
spoji 5 4

  1        2, rang
  1        6   , {1, 2, 3} ima rang 1, {6, 4, 7, 8, 5} ima rang 2
2   3   4  7  8
              5
```
```             
spoji 3 7

       2, rang
       6    , {1, 2, 3, 4, 5, 6, 7, 8} ima rang rang 2
  1  4  7  8
2   3      5
```

Find je složenosti O(logn), unija (koristi find) takođe.

Ово важи зато што и овај начин прављења уније гарантује да не можемо имати високо дрво са малим бројем чворова. 
Да би се добило дрво висине 1, потребна су најмање два чвора; 
да би се добило дрво висине 2 најмање четири чвора (јер се спајају два дрвета висине 1 која имају бар по два чвора). 
Да би се добило дрво висине h потребно је најмање 2^h чворова. 
Одавде следи да ће висине свих дрвета у овој структури бити висине O(logn).

```cpp
#include <bits/stdc++.h>
using namespace std;

int roditelj[1000];
int n;
int rang[1000];

void init() {
    for (int i = 0; i < n; i++) {
        roditelj[i] = i;
        rang[i] = 0;    } }

int nadji(int x) {
    while (roditelj[x] != x) 
        x = roditelj[x];
    return x; }

void spoji(int x, int y) {
    int fx = nadji(x), fy = nadji(y);
    if (rang[fx] < rang[fy])
        roditelj[fx] = fy;
    else if (rang[fy] < rang[fx])
        roditelj[fy] = fx;
    else {
        roditelj[fx] = fy;
        rang[fy]++;    } }

int main() {

    return 0;    }
```

# 4 union-find i kompresija putanje

Iako složenost nije loša (za n unija је O(n logn)), može da se popravi.

Tehnika je kompresija putanje.

Kad se traže predstavnici, mogu svi čvorovi kroz koje se prolazi da se usmere prema korenu.
Prvim prolaskom se odredi koren, drugim se svi usmere prema korenu.

Svim čvorovima, kroz koje se prođe, je onda visina 1, što nagoveštava O(1).

Ali rangovi se ne menjaju... Doduše i ne moraju... Rangovi više nisu visine, već gornje granice visine, 
tj. koja bi bila visina da se ništa ne menja, i te vrednosti su korektne za uniju. 
 
```cpp
#include <bits/stdc++.h>
using namespace std;

int roditelj[1000];
int n;
int rang[1000];

void init() {
    for (int i = 0; i < n; i++) {
        roditelj[i] = i;
        rang[i] = 0;    } }

int nadji(int x) {
    int koren = x;
    while (koren != roditelj[koren]) // prvi prolaz, odredi koren
        koren = roditelj[koren];

    while (x != koren) { // drugi prolaz, od elementa x
        int tmp = roditelj[x]; // zapamti roditelja
        roditelj[x] = koren;   // roditelj pokazuje na koren
        x = tmp;     }         // nastavi sa roditeljem elementa...
        
    return koren; }

void spoji(int x, int y) {
    int fx = nadji(x), fy = nadji(y);
    if (rang[fx] < rang[fy])
        roditelj[fx] = fy;
    else if (rang[fy] < rang[fx])
        roditelj[fy] = fx;
    else {
        roditelj[fx] = fy;
        rang[fy]++;  } }

int main() {

return 0;    }
```

# 5 union-find, babe i dede

Umesto dva prolaza, može samo jedan...

Svaki čvor se usmerava na roditelja od roditelja (deda, baba). 

Sve putanje se smanje duplo.

```cpp
#include <bits/stdc++.h>
using namespace std;

int roditelj[1000];
int n;
int rang[1000];

void init() {
    for (int i = 0; i < n; i++) {
        roditelj[i] = i;
        rang[i] = 0;     } }

int nadji(int x) {
    while (x != roditelj[x]) {
        int tmp = roditelj[x];
        roditelj[x] = roditelj[roditelj[x]];
        x = tmp;     }
    return x; }

void spoji(int x, int y) {
    int fx = nadji(x), fy = nadji(y);
    if (rang[fx] < rang[fy])
        roditelj[fx] = fy;
    else if (rang[fy] < rang[fx])
        roditelj[fy] = fx;
    else {
        roditelj[fx] = fy;
        rang[fy]++;
    }
}

int main() {

return 0;    }
```

# 6 union-find druge babe i dede

Svaki drugi se usmeri na roditelja od roditelja.

Ovo rešenje se razlikuje od prvog sa roditeljima u samo jednom redu! 

Složenost je O(α(n)), α(n) je inverzna Akermanova f-ja, praktično O(1).

За било који број n који је мањи од броја атома у целом универзуму важи да је α(n)<5, тако да је време практично константно.

```cpp
#include <bits/stdc++.h>
using namespace std;

int roditelj[1000];
int n;
int rang[1000];

void init() {
    for (int i = 0; i < n; i++) {
        roditelj[i] = i;
        rang[i] = 0;    } }

int nadji(int x) {
    while (x != roditelj[x]) {
        roditelj[x] = roditelj[roditelj[x]]; // dodatak
        x = roditelj[x]; }
    return x; }

void spoji(int x, int y) {
    int fx = nadji(x), fy = nadji(y);
    if (rang[fx] < rang[fy])
        roditelj[fx] = fy;
    else if (rang[fy] < rang[fx])
        roditelj[fy] = fx;
    else {
        roditelj[fx] = fy;
        rang[fy]++;     } }

int main() {

    return 0;    }
```
