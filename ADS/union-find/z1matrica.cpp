/*                                         Први пут кроз матрицу
vreme	memorija	ulaz	izlaz	test primeri
0,1 s	64 Mb	standardni izlaz	standardni ulaz	

Логичка матрица димензије n×n у почетку садржи све нуле. Након тога се насумично додаје једна по једна јединица. 
Кретање по матрици је могуће само по јединицама и то само на доле, на горе, на десно и на лево. 
Написати програм који учитава димензију матрице, а затим позицију једне по једне јединице и одређује након колико њих је 
први пут могуће сићи од врха до дна матрице (са произвољног поља прве врсте до произвољног поља последње врсте матрице).

Улаз
Са стандардног улаза се учитава димензија матрице 1≤n≤200, затим број поља m (1≤m≤n^2) у које се уписује јединица, 
а затим у наредних m редова координате тих поља (број врсте и број колоне од 0 до n−1, раздвојени размаком).

Излаз

Пример
Улаз
4 // 4x4
9 // jedinice
0 0
1000
0000
0000
0000

0 1
1100
0000
0000
0000

1 1
1100
0100
0000
0000

3 3
1100
0100
0000
0001

1 3
1100
0101
0000
0001

2 0
1100
0101
1000
0001

3 0
1100
0101
1000
1001

2 1
1100      1
0101      1
1100     11
1001     1

2 2

Излаз
8
Објашњење
После 8 учитаних поља, матрица постаје

1100
0101
1100
1001
и врх и дно постају спојени.

Основна идеја је да се формирају сви подскупови елемената између којих постоји пут (они формирају тзв. компоненте повезаности). 
Сваки пут када се успостави веза између нека два елемента таква два подскупа, подскупови се спајају. 
Провера да ли постоји пут између два елемента своди се онда на проверу да ли они припадају истом подскупу.

Путања од врха до дна постоји ако постоји путања од било ког елемента у првој врсти матрице до било ког елемента у дну матрице. 
То би довело до тога да у сваком кораку морамо да проверавамо све парове елемената из горње и доње врсте. 

Међутим, може боље. 
Додаћемо вештачки почетни чвор и спојићемо га са свим чворовима у првој врсти матрице 
и завршни чвор и спојићемо га са свим чворовима у последњој врсти матрице. 
Тада се у сваком кораку само може проверити да ли су извор и ушће спојени тј. да ли припадају истом подскупу.

Подскупове можемо чувати помоћу структуре података за представљање дисјунктних подскупова (енгл. union-find).

*/

#include <bits/stdc++.h>
using namespace std;

vector<int> roditelj;
vector<int> rang;

void init(int n) {
    roditelj.resize(n);
    rang.resize(n);
    for (int i = 0; i < n; i++) {
        roditelj[i] = i;
        rang[i] = 0; }  }

int nadji(int x) {
    while (x != roditelj[x]) {
        roditelj[x] = roditelj[roditelj[x]];
        x = roditelj[x];    }
    return x; }

void spoji(int x, int y) {
    int fx = nadji(x), fy = nadji(y);
    if (rang[fx] < rang[fy])
        roditelj[fx] = fy;
    else if (rang[fy] < rang[fx])
        roditelj[fy] = fx;
    else {
        roditelj[fx] = fy;
        rang[fy]++;   }  }

int rb(int x, int y, int n) { // redni broj elementa (x, y) u matrici
    return x * n + y; }

int main() {
   
    int n; cin >> n;  // dimenzija matrice
    
    vector<vector<bool>> a(n); // alocira matricu n*n
    for (int i = 0; i < n; i++)
        a[i].resize(n, false);

    // dva dodatna veštačka čvora, već su zauzeti od 0 do n*n-1...
    const int pocetak = n * n;
    const int kraj = n * n+1;

    // inicijalizujemo union-find strukturu za sve elemente matrice (njih n*n), pocetak i kraj
    init(n * n + 2);

    // spaja pocetak sa svim elementima u prvoj vrsti matrice
    for (int i = 0; i < n; i++)
        spoji(pocetak, rb(0, i, n));

    // spajamo sve elemente u poslednjoj vrsti matrice sa krajem
    for (int i = 0; i < n; i++)
        spoji(rb(n-1, i, n), kraj);

    // broj jedinica
    int m; cin >> m;

    // korak u kom se spajaju pocetak i kraj
    int res = -1; // nema rešenja...

    // ucitavamo i obrađujemo jednu po jednu jedinicu
    for (int i = 1; i <= m; i++) {
        int r, k; cin >> r >> k; // red i kolona
        
        if (a[r][k]) continue; // ako je u matrici već jedinica, nema šta da se radi
        
        a[r][k] = true; // upisujemo jedinicu u matricu
        
         // spajaju se podskupovi u sva četiri smera
        if (r > 0 && a[r-1][k]) // nije prvi red i gore je moguć spoj?
            spoji(rb(r, k, n), rb(r-1, k, n));
        if (r + 1 < n && a[r+1][k]) // nije zadnji red i dole je moguć spoj?
            spoji(rb(r, k, n), rb(r+1, k, n));
        if (k > 0 && a[r][k-1]) // nije prva kolona i levo je moguć spoj?
            spoji(rb(r, k, n), rb(r, k-1, n));
        if (k + 1 < n && a[r][k+1]) // nije zadnja kolona i desno je moguć spoj?
            spoji(rb(r, k, n), rb(r, k+1, n));
        
        if (nadji(pocetak) == nadji(kraj)) { // proveravamo da li su pocetak i ušće spojeni
            res = i; // rešenje!
            break; } } // i kraj!

    cout << res;

    return 0; }