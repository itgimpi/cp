/* Структура података за представљање дисјунктних подскупова (union-find)

Iako složenost nije loša (za n unija је O(n logn)), može da se popravi.
Tehnika je kompresija putanje.

Kad se traže predstavnici, mogu svi čvorovi kroz koje se prolazi da se usmere prema korenu.
Prvim prolaskom se odredi koren, drugim se svi usmere prema korenu.

Svim čvorovima, kroz koje se prođe, je onda visina 1, što nagoveštava O(1).
Ali rangovi se ne menjaju... Doduše i ne moraju... Rangovi više nisu visine, već gornje granice visine, 
tj. koja bi bila visina da se ništa ne menja, i te vrednosti su korektne za uniju. 
 
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