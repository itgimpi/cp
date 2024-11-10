/*                        union-find

Elementi skupa se razbiju u podskupove sa po jednim elementom, disjunktne podskupove.
Treba da se obezbedi union (unija) i find (nađi koji je podskup) podskupova.

Svaki element se poveže sa skupom kome pripada i lako se dolazi do skupa.
Svaki element se pomoću niza od 0 do n-1 preslika u skup kome pripada.  
Ako elementi nisu brojevi, koristi se mapa. 

Find je trivijalna operacija, samo se pročita oznaka podskupa, O(1). 
Union je spora, jer se prolazi kroz ceo niz, O(n).

Sve su posebni skupovi:
0  1  2  3  4  5  6  7 <- id elemenata
0  1  2  3  4  5  6  7 <- elementi

unija 7 6

posebni: 0, 1, 2, 3, 4 i 5, plus skup {6, 7} u oznaci 6
0  1  2  3  4  5  6  6
0  1  2  3  4  5  6  7

unija 6 5

posebni: 0, 1, 2, 3 i 4, plus skup {5, 6, 7} u oznaci 5
0  1  2  3  4  5  5  5
0  1  2  3  4  5  6  7

nadji 5 -> 5

unija 5 4

posebni: 0, 1, 2 i 3, plus skup {4, 5, 6, 7} u oznaci 4
0  1  2  3  4  4  4  4
0  1  2  3  4  5  6  7

unija 4 3

posebni: 0, 1 i 2, plus skup {3, 4, 5, 6, 7} u oznaci 3
0  1  2  3  3  3  3  3
0  1  2  3  4  5  6  7

unija 3 2

posebni: 0 i 1, plus skup {2, 3, 4, 5, 6, 7} u oznaci 2
0  1  2  2  2  2  2  2
0  1  2  3  4  5  6  7

unija 2 1

posebni: 0, plus skup {1, 2, 3, 4, 5, 6, 7} u oznaci 1
0  1  1  1  1  1  1  1
0  1  2  3  4  5  6  7

unija 1 0

samo skup {0, 1, 2, 3, 4, 5, 6, 7} u oznaci 0
0  0  0  0  0  0  0  0
0  1  2  3  4  5  6  7

*/

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