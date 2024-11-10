/* Структура података за представљање дисјунктних подскупова (union-find)

Elementi se ne preslikavaju u podskupove nego u roditelje. 
Formiraju se stabla, u kojima se koreni na početku preslikavaju sami u sebe. Npr roditelj od 5 je 5.

Podskup nekog elementa se određuje prolaskom kroz roditelje, do korena. Deca pokazuju na roditelje.

7   svi elementi ispod su u skupu koji je obeležen 7.
^
|
4   4 je roditelj od 2, 7 je roditelj od 4, 4 je oznaka skupa.
^
|
2   

Unija se dobija usmeravanjem korena jednog skupa prema drugom.

Први алгоритам одговара ситуацији у којој особа која промени адреду обавештава све друге особе о својој новој адреси. 

Други одговара ситуацији у којој само на старој адреси оставља информацију о својој новој адреси. 
Ово, наравно, мало успорава доставу поште, јер се мора прећи кроз низ преусмеравања, 
али ако тај низ није предугачак, може бити значајно ефикаснији од првог приступа.

Složenost zavisi od uravnoteženosti stabla. 
Najgori slučaj je O(n):

0  1  2  3  4  5  6  7 <- roditelj elementa
0  1  2  3  4  5  6  7 <- element

unija 7 6

0  1  2  3  4  5  6
                  7 (potomak od 6)

0  1  2  3  4  5  6  6 <- roditelj el. 7 je sada 6
0  1  2  3  4  5  6  7

unija 6 5

0  1  2  3  4  5 (predstavnik skupa {5,6,7})
               6 (potomak od 5)
               7

0  1  2  3  4  5  5  6 <- roditelj el. 6 je sada 5
0  1  2  3  4  5  6  7

unija 5 4

0  1  2  3  4
            5
            6
            7

0  1  2  3  4  4  5  6 <- roditelj el. 5 je sada 4
0  1  2  3  4  5  6  7

unija 4 3

0  1  2  3  3  4  5  6 <- roditelj el. 4 je sada 3
0  1  2  3  4  5  6  7

unija 3 2

0  1  2  2  3  4  5  6 <- roditelj el. 3 je sada 2
0  1  2  3  4  5  6  7

unija 2 1

0  1  1  2  3  4  5  6 <- roditelj el. 2 je sada 1
0  1  2  3  4  5  6  7

unija 1 0

0  0  1  2  3  4  5  6 <- roditelj el. 1 je sada 0
0  1  2  3  4  5  6  7

Kom skupu pripada element 7? Roditelj od 7 je 6, tako da on ukazuje na pripadnost.
Njegov roditelj je 5, onda 4, ... Tako do 0.
Za bilo koji el. da se proveri, dolazi se do 0.

Upit je u O(n).

Ovo je gore od 1. rešenja gde je find bio O(1).
Da je stablo uravnoteženo, bilo bi O(logn). 
Zadatak je efikasna struktura, koja omogućava uravnoteženo stablo.


*/

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