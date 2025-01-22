/* Днк префикси, 1,1 s	64 Mb	стандардни излаз	стандардни улаз	
Напиши програм који омогућава унос генетских секвенци (ниски које се састоје само од карактера a, c, t и g) 
и који за сваку унету секвенцу исписује колико има секвенци којима је секвенца која се уноси префикс.

Улаз
Свака линија стандардног улаза садржи ниску која садржи највише 10000 карактера a, c, t или g.

Излаз
За сваку унету ниску исписати колико има раније унетих ниски којима је она префикс.

Пример
Улаз
tacg
tac
ta
ca
cat

Излаз
0
1
2
0
0
Задатак можемо решити коришћењем префиксног дрвета 
тако што ћемо у сваком чвору дрвета чувати број ниски којима је ниска представљена тим чвором префикс. 
Током убацивања ниске увећаваћемо бројач свих чворова кроз које се пролази током убацивања (то су сви њени префикси).
*/

#include <iostream>

using namespace std;


int kod(char c) { // karaktere iz azbuke kodiramo brojevima
    switch(c) {
    case 'c': return 0;
    case 't': return 1;
    case 'g': return 2;
    case 'a': return 3;     }
    return -1; }

// cvor prefiksnog drveta
struct Cvor {
    Cvor* grane[4];
    int brojPrefiksa; };

// kreira se novi, prazan cvor
Cvor* noviCvor() {
    Cvor* novi = new Cvor();
    fill(novi->grane, novi->grane+4, nullptr);
    novi->brojPrefiksa = 0;
    return novi; }

// ubacivanje reci str u prefiksno drvo sa korenom koren
// funkcija vraca novi koren drveta
void ubaci(Cvor* koren, const string& str) {
    Cvor* cvor = koren;
    for (char c : str) {
        if (cvor->grane[kod(c)] == nullptr)
            cvor->grane[kod(c)] = noviCvor();
        cvor = cvor->grane[kod(c)];
        cvor->brojPrefiksa++;
    }
}

// ocitavanje broja reci u drvetu sa korenom koren koje za prefiks
// imaju rec str
int brojPrefiksa(Cvor* koren, const string& str) {
    Cvor* cvor = koren;
    for (char c : str) {
        if (cvor->grane[kod(c)] == nullptr)
            return 0;
        cvor = cvor->grane[kod(c)];
    }
    if (cvor == nullptr)
        return 0;
    return cvor->brojPrefiksa;
}

// brise drvo sa korenom koren
void obrisi(Cvor* koren) {
    if (koren != nullptr) {
        for (Cvor* c : koren->grane)
        obrisi(c);
        delete koren;
    }
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    // prefiksno drvo u kome se cuvaju ucitane niske i broje prefiksi
    Cvor* drvo = noviCvor();
    // ucitavamo jednu po jednu nisku do kraja ulaza
    string niska;
    while (cin >> niska) {
        // ispisujemo broj niski u drvetu kojima je tekuca niska prefiks
        cout << brojPrefiksa(drvo, niska) << '\n';
        // ubacujemo novu nisku u drvo
        ubaci(drvo, niska);
    }
    // brisemo prefiksno drvo
    obrisi(drvo);
    return 0;
}