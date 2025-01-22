/* union-find

Kod unije bi bilo dobro da se visina stabla (od korena do najdaljeg lista) što manje povećava.

Koren manjeg stabla treba da pokazuje na veće. Onda se visina ne povećava:

1 + 2 -> 1, 1 + 3 -> 1,  1 + 4 -> 1,   1 + 3 -> 1,   1 + 4 -> 1
         2  2       2 3 2 3     2 3 4  2   4   2 3  2 3  5  2 3 4
                                                 4              5

Samo ako su visine iste, visina unije se poveća za 1.
 
Visine stabala (disj. skupova) su u nizu rang:

0  0  0  0  0  0  0  0, rang je 0, tj. h = 0
1  2  3  4  5  6  7  8, elementi

spoji 1 2

1  0  0  0  0  0  0, rang
1  3  4  5  6  7  8, samo {1, 2} ima rang 1 (h=1)
2

spoji 6 7

1  0  0  0  1  0, rang
1  3  4  5  6  8, {1, 2} i {6, 7} imaju rang 1
2           7

spoji 4 7

1  0  0    1    0, rang
1  3  5    6    8, {1, 2} i {6, 7, 4} imaju rang 1
2        4   7

spoji 5 8

1  0    1     1, rang
1  3    6     8, {1, 2}, {6, 7, 4} i {8, 5} imaju rang 1
2     4   7   5

spoji 1 3

  1       1     1, rang
  1       6     8, {1, 2, 3}, {6, 7, 4} i {8, 5} imaju rang 1
2   3   4   7   5

spoji 5 4

  1        2, rang
  1        6   , {1, 2, 3} ima rang 1, {6, 4, 7, 8, 5} ima rang 2
2   3   4  7  8
              5
              
spoji 3 7

       2, rang
       6    , {1, 2, 3, 4, 5, 6, 7, 8} ima rang rang 2
  1  4  7  8
2   3      5

Find je složenosti O(logn), unija (koristi find) takođe.

Ово важи зато што и овај начин прављења уније гарантује да не можемо имати високо дрво са малим бројем чворова. 
Да би се добило дрво висине 1, потребна су најмање два чвора; 
да би се добило дрво висине 2 најмање четири чвора (јер се спајају два дрвета висине 1 која имају бар по два чвора). 
Да би се добило дрво висине h потребно је најмање 2^h чворова. 
Одавде следи да ће висине свих дрвета у овој структури бити висине O(logn).

*/

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