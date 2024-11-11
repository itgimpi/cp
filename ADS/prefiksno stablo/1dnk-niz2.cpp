/* Днк секвенце
време	меморија	улаз	излаз	тест примери
2,05 s	64 Mb	стандардни излаз	стандардни улаз	
ДНК секвенце се представљају нискама које се састоје од карактера c, t, a и g. 
У програму се одржава скуп подсеквенци једне дате генетске секвенце. 
Програм подржава три операције: убацивање подсеквенце у скуп (ако је подсеквенца већ у скупу, ова операција нема ефекта), 
избацивање подсеквенце из скупа (ако се подсеквенца не налази у скупу, ова операција нема ефекта) 
и испистивање да ли се подсеквенца налази у скупу.

Улаз
Са стандардног улаза се уноси број упита q (1 ≤ q ≤ 50000), а затим у наредних q редова по један упит. 
Упит може бити облика ubaci niz, izbaci niz или trazi niz, 
pri čemu se svaki niz sastoji od slova: c, t, a и g, maksimalne dužine 5000 slova.

Излаз
За сваки упит trazi исписати da ако се тражена ниска тренутно налази у скупу или ne ако се не налази.

Пример
Улаз
14
ubaci cta 
ubaci ct
ubaci ctg
trazi cta
trazi ct
trazi ctg
trazi ctc
izbaci ct
trazi ct
trazi ctg
izbaci ctg
trazi ctg
ubaci ctg
trazi ctg

Излаз
da cta
da
da
ne
ne
da
ne
da

У случају када је азбука мала (што је случај у овом задатку), пресликавање карактера у наредне чворове дрвета можемо чувати у низу (на местима карактера који немају наследнике чуваћемо null показиваче). Пошто је за брисање битно да знамо колико наследника има неки чвор, у чвору ћемо чувати и ту информацију. Функције за убацивање и претрагу дрвета једноставно можемо имплементирати и итеративно. Са друге стране, избацивање није једноставно имплементирати итеративно (јер је након брисања речи потребно вратити се уз дрво и обрисати све празне чворове, а немамо показиваче ка родитељским чворовима којима бисмо се једноставно могли враћати унатраг).
*/

#include <iostream>
using namespace std;

int kod(char c) { // 4 slova se kodiraju brojevima od 0 do 3
    switch(c) {
        case 'c': return 0;
        case 't': return 1;
        case 'g': return 2;
        case 'a': return 3; }
    return -1; } // nije ctga

struct Cvor { // cvor prefiksnog stabla...
    Cvor* grane[4]; // potencijalne 4 grane za 4 moguća slova na toj poziciji
    int broj; // br. različitih slova na toj poziciji
    bool kraj; }; // da li je slovo kraj nekog niza?

Cvor* noviCvor() { // kreira se novi, prazan cvor
    Cvor* novi = new Cvor(); // alokacija
    fill(novi->grane, novi->grane+4, nullptr); // od grane0 do grane3 postavi null
    novi->broj = 0; // još nema slova
    novi->kraj = false; // nije kraj
    return novi; } // vrati adresu novog elementa

Cvor* ubaci(Cvor* koren, const string& niz) { // ubacivanje niza u prefiksno drvo sa korenom koren
    if (koren == nullptr)  // prazno stablo?
        koren = noviCvor();
    Cvor* cvor = koren;
    for (char c : niz) { // za svako slovo c iz niza...
        if (cvor->grane[kod(c)] == nullptr) { // ako to slovo ne postoji na tom mestu...
            cvor->grane[kod(c)] = noviCvor(); // dodaj ga...
            cvor->broj++; } // i ažuriraj br. razl. slova
        cvor = cvor->grane[kod(c)]; }
    cvor->kraj = true;
    return koren; } // funkcija vraca novi koren drveta

Cvor* izbaci(Cvor* koren, const string& niz, size_t i) {// izbacuje niz od pozicije i iz drveta sa korenom koren
    if (koren == nullptr)  // ako je drvo vec prazno, nema sta da se izbacuje
        return koren;

    if (i == niz.length())  // ako smo dosli do kraja reci
        koren->kraj = false;  // rec brisemo tako sto oznacavamo da u tom cvoru vise nije kraj neke reci
    else {
        if (koren->grane[kod(niz[i])] != nullptr) {  // ako postoji grana sa sa tekucim slovom reci
            Cvor* c = izbaci(koren->grane[kod(niz[i])], niz, i+1);  // brisemo ostatak te reci iz drveta
            if (c == nullptr)  // ako se tim brisanjem potpuno uklonio deo drveta ispod te grane
                koren->broj--;  // onda uklanjamo i tu granu
            koren->grane[kod(niz[i])] = c;         }     }

    if (!koren->kraj && koren->broj == 0) {  // ako je nakon brisanja koren potpuno prazan
        delete koren;  // brisemo ga i vracamo null kao oznaku praznog stabla
        return nullptr;    } 
    else 
        return koren;  // vraca tekuci koren
}

bool sadrzi(Cvor* koren, const string& str) { // da li prefiksno drvo sa korenom koren sadrzi rec str
    if (koren == nullptr)
        return false;
    Cvor* cvor = koren;
    for (char c : str) {
        if (cvor->grane[kod(c)] == nullptr)
            return false;
        cvor = cvor->grane[kod(c)];     }
    return cvor != nullptr && cvor->kraj; }

void obrisi(Cvor* koren) { // funkcija brise prefiksno drvo sa korenom koren
    if (koren != nullptr) {
        for (Cvor* c : koren->grane)
            obrisi(c);
        delete koren;   } }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    
    Cvor* koren = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string naredba, niska; cin >> naredba >> niska >> ws;
        if (naredba == "ubaci")
            koren = ubaci(koren, niska);
        else if (naredba == "izbaci")
            koren = izbaci(koren, niska, 0);
        else if (naredba == "trazi") {
            if (sadrzi(koren, niska))
                cout << "da" << "\n";
            else
                cout << "ne" << "\n";         }     }
    obrisi(koren);
    return 0; }