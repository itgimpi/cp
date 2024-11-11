#include <bits/stdc++.h>
using namespace std;

// К-ти парни број
//https://petlja.org/sr-Latn-RS/biblioteka/r/Zbirka3/kti_parni

/* К-ти парни број
vreme	memorija	ulaz	izlaz	test primeri
1,35 s	64 Mb	standardni izlaz	standardni ulaz	
Написати програм који омогућава да се у низу природних бројева који је на почетку испуњен нулама, 
али чији се елементи често мењају током извршавања програма ефикасно проналази позиција k-тог парног броја по реду.

Улаз
Са стандардног улаза се учитава дужина низа n (1≤n≤50000), а затим и број упита m (1≤m≤50000). 
Извршавањем упита облика u p x се у низ на позицију 1≤p≤n уписује број x, 
док се упитом c k на стандардни излаз исписује позиција k-тог парног броја у текућем садржају низа (позиције се броје од 1).

Излаз
На стандардном излазу приказати резултате извршавања упита c. Ако у неком случају у низу има мање парних бројева од вредности k, 
тада уместо позиције исписати -.

Пример
Улаз
5
8
u 3 1
c 4
u 1 7
u 2 5
c 1
u 1 2
c 2
c 4
Излаз
5
4
4
- 
На основу низа може да се направи низ нула и јединица, тако да се јединице налазе на месту парних елемената. 
Тада је позиција k-тог парног броја најмања позиција таква да је збир свих јединица закључно са том позицијом једнак k. 
Ако низ нула и јединица одржавамо у Фенвиковом стаблу, врло ефикасно можемо да израчунавамо збирове сваког фиксираног префикса. 
Збирови префикса су монотоно неопадајући (када се префикси продужавају), позиција може ефикасно да се одреди бинарном претрагом. 
Ако има m1 операција ажурирања и m2 операција претраге укупна сложеност ће бити O(m1 log(n)+m2 logn^2), тј. O(m logn^2).
*/

void dodaj(vector<int>& stablo, int k, int v) {
    while (k < (int)stablo.size()) {
        stablo[k] += v;
        k += k & -k;     } }

int zbirPrefiksa(const vector<int>& stablo, int k) {
    int zbir = 0;
    while (k > 0) {
        zbir += stablo[k];
        k -= k & -k;     }
    return zbir; }

// vraca prvu poziciju p tako da je zbir niza na pozicijama [1, p] veci ili jednak k
int prefiksK(const vector<int>& stablo, int k) {
    // poziciju pronalazimo binarnom pretragom po vrednosti zbira prefiksa
    int l = 1, d = stablo.size() - 1;
    while (l <= d) {
        int s = l + (d - l) / 2;
        if (zbirPrefiksa(stablo, s) < k)
            l = s + 1;
        else
            d = s - 1;     }
    return l; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    // Fenvikovo stablo sa jedinicama
    vector<int> stablo(n + 1, 0);
    for (int k = 1; k <= n; k++)
        dodaj(stablo, k, 1);
    // elementi niza
    vector<int> niz(n + 1, 0);

    // broj upita
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        if (c == 'u') { // upis elementa u niz
            int p, x; cin >> p >> x;
            if (x % 2 == 0 && niz[p] % 2 != 0) // novi paran element na poziciju p
                dodaj(stablo, p, 1);
            else if (x % 2 != 0 && niz[p] % 2 == 0) // novi neparan element na poziciju p
                dodaj(stablo, p, -1);
            niz[p] = x; } 
        else if (c == 'c') { // upit odredjivanja k-tog parnog elementa
            int k; cin >> k;
            // najkraci prefiks ciji je zbir jednak k
            int p = prefiksK(stablo, k);
            // da li takav prefiks zaista postoji
            if (p <= n)
                cout << p << "\n";
            else
                cout << "-" << "\n";  } }
    return 0; }