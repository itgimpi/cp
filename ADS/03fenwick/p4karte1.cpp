#include <bits/stdc++.h>
using namespace std;

// Трик са картама  
//https://petlja.org/sr-Latn-RS/biblioteka/r/Zbirka3/trik_sa_kartama

/* Трик са картама
vreme	memorija	ulaz	izlaz	test primeri
0,1 s	64 Mb	standardni izlaz	standardni ulaz	
Мали мађионичар хоће да сложи карте тако да са њима изведе следећи трик. 
У првом кораку једну карту са врха шпила пребацује на дно шпила, 
узима следећу карту са врха шпила и испоставља се да је на њој број 1. 
У другом кораку пребацује два пута карту са врха шпила на дно шпила, 
узима следећу карту са врха шпила испоставља се да је на њој број два. 
Наставља да ради по истом приниципу, пребацујући у сваком кораку по једну карту више са врха на дно шпила, 
да би се након тога са врха шпила скинула управо карта са наредним редним бројем.

Улаз
Са стандардног улаза се учитава број карата у шпилу n (1≤n≤50000).

Излаз
На стандардни излаз исписати редослед карата у шпилу, од врха ка дну (након сваке карте исписати један размак).

Пример
Улаз
12
Излаз
7 1 4 9 2 11 10 8 3 6 5 12

Ако кренемо од празног низа (можемо га иницијално попунити нулама), 
карте можемо попунити тако што кренемо од почетка, 
затим прескочимо једно празно место и упишемо јединицу, 
затим прескочимо два празна места и упишемо двојку, 
затим прескочимо три празна места и упишемо тројку и тако даље. 
Можемо приметити да када се број повећа и број празних места смањи, 
прескакање празних места и по неколико пута обилази низ. 
Ако прескочимо сва празна места у низу (којих у k-том кораку има n−k+1) долазимо на исто место са ког смо пошли, 
па се убрзање може постићи тако што пре прескакања k празних места пронађемо остатак тог броја при дељењу са n−k+1.

*/

void dodaj(vector<int>& drvo, int k, int v) {
    while (k < drvo.size()) {
        drvo[k] += v;
        k += k & -k;     } }

int zbirPrefiksa(const vector<int>& drvo, int k) {
    int zbir = 0;
    while (k > 0) {
        zbir += drvo[k];
        k -= k & -k;     } 
    return zbir; }

// vraca prvu poziciju p tako da je zbir niza na pozicijama [1, p]
// veci ili jednak k
int prefiksK(const vector<int>& drvo, int k) {
    // poziciju pronalazimo binarnom pretragom po vrednosti zbira prefiksa
    int l = 1, d = drvo.size() - 1;
    while (l <= d) {
        int s = l + (d - l) / 2;
        if (zbirPrefiksa(drvo, s) < k)
            l = s + 1;
        else
            d = s - 1;
    }
    return l;
}


int main() {
    // broj i niz karata
    int n;    cin >> n;
    vector<int> karta(n, 0);

    // Fenvikovo drvo nad nizom koji cuva 1 na praznim i 0 na zauzetim pozicijama (brojanje krece od 1)
    vector<int> drvo(n + 1, 0);
    for (int k = 1; k <= n; k++)
        dodaj(drvo, k, 1);
    
    // trenutna slobodna pozicija
    int p = 0;
    for (int k = 1; k <= n; k++) {
        // treba da se pomerimo za k praznih pozicija

        // posto je preostalo n-k+1 praznih, one se ciklicno ponavljaju,
        // pa je dovoljno preskociti k % (n-k+1) praznih pozicija

        // odredjujemo najmanju poziciju takvu da se zakljucno sa njom
        // nalazi za k slobodnih pozicija vise nego sto se nalazi
        // zakljucno sa trenutnom slobodnom pozicijom (sve po modulu n-k+1)
        p = prefiksK(drvo, (zbirPrefiksa(drvo, p) + k) % (n-k+1) + 1);

        // upisujemo kartu, poziciju oznacavamo punom i azuriramo drvo drvo 
        karta[p-1] = k;
        dodaj(drvo, p, -1);    }
    
    // ispisujemo konacan raspored karata
    for (int k : karta)
        cout << k << " ";
    cout << endl;
    return 0; }