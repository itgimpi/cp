/* union-find

Umesto dva prolaza, može samo jedan...

1. način: Svaki čvor se usmerava na roditelja od roditelja (deda, baba). 

Sve putanje se smanje duplo.

*/

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