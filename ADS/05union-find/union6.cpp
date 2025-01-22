/* Структура података за представљање дисјунктних подскупова (union-find)

2. način: Svaki drugi se usmeri na roditelja od roditelja.
Ovo rešenje se razlikuje od prvog sa roditeljima u samo jednom redu! 

Složenost je O(α(n)), α(n) je inverzna Akermanova f-ja, praktično O(1).

За били који број n који је мањи од броја атома у целом универзуму важи да је α(n)<5, тако да је време практично константно.

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