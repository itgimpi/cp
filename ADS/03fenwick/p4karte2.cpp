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

Празна места (тј. њихове позиције) можемо чувати у листи, 
јер нам она даје могућност да веома ефикасно избацимо елемент из средине. 
Приликом кретања по листи морамо водити рачуна о томе да када стигнемо до краја, обилазак кренемо из почетка.

*/

int main() {
    // broj i niz karata
    int n; cin >> n;
    vector<int> karte(n);

    // lista trenutno slobodnih pozicija
    list<int> pozicije;
    for (int i = 0; i < n; i++)
        pozicije.push_back(i);

    // pokazivac na trenutno slobodnu poziciju
    list<int>::iterator p = begin(pozicije);
    for (int k = 1; k <= n; k++) {
        // treba da se pomerimo za k praznih pozicija
        // posto je preostalo n-k+1 praznih, one se ciklicno ponavljaju,
        // pa je dovoljno preskociti k % (n-k+1) praznih pozicija
        for (int i = 0; i < (k % (n - k + 1)); i++) {
        // prelazimo na sledecu poziciju u listi, krecuci se ciklicno
        p = next(p);
        if (p == end(pozicije))
            p = begin(pozicije);
        }
        // upisujemo element na tu slobodnu poziciju
        karte[*p] = k;
        // brisemo poziciju iz liste slobodnih i odredjujemo
        // narednu slobodnu poziciju
        p = pozicije.erase(p);
        if (p == end(pozicije))
        p = begin(pozicije);
    }

    // ispisujemo konacan raspored karata
    for (int k : karte)
        cout << k << " ";
    cout << endl;

    return 0;
}