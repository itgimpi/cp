/* Днк секвенце
време	меморија	улаз	излаз	тест примери
2,05 s	64 Mb	стандардни излаз	стандардни улаз	

ДНК секвенце се представљају нискама које се састоје од карактера c, t, a и g. 
У програму се одржава скуп подсеквенци једне дате генетске секвенце. 
Програм подржава три операције: убацивање подсеквенце у скуп (ако је подсеквенца већ у скупу, ова операција нема ефекта), 
избацивање подсеквенце из скупа (ако се подсеквенца не налази у скупу, ова операција нема ефекта) и 
испистивање да ли се подсеквенца налази у скупу.

Улаз
Са стандардног улаза се уноси број упита n (1≤n≤50000), а затим у наредних n редова по један упит. 
Упит може бити облика ubaci niz, izbaci niz или trazi niz, 
при чему се свака ниска састоји само од карактера c, t, a и g и дугачка је између једног и 5000 карактера.

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

U svakom čvoru prefiksnog stabla je mapa, koja preslikava slova u nove čvorove. 
Функције можемо имплементирати рекурзивно.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct cvor { // struktura čvora prefiksnog stabla
    unordered_map<char, cvor*> grane; // niz grana obeleženih slovima ka potomcima
    bool kraj = false; }; //  da li je u tom čvoru kraj neke reči

// ubacuje deo niza, od pozicije poz, u stablo, na čiji koren ukazuje pokazivač
void ubaci(cvor* stablo, const string& niz, size_t poz) {
    if (poz == niz.size()) {   // kraj reči
        stablo->kraj = true;
        return;     }
    auto it = stablo->grane.find(niz[poz]);  // traži granu na kojoj je niz[i]
    if (it == stablo->grane.end())   // ako grana ne postoji, dodaje se novi čvor
        stablo->grane[niz[poz]] = new cvor();
    // grana sa w[i] postoji i preko nje se dodaje deo niza, koji počinje na i+1
    ubaci(stablo->grane[niz[poz]], niz, poz+1);     }

cvor* ubaci(cvor *stablo, string& niz) { // umeće niz u stablo, na čiji koren ukazuje pokazivač stablo
    if (stablo == nullptr) // ako je stablo prazno...
        stablo = new cvor(); // napravi novi čvor...
    ubaci(stablo, niz, 0); // ubaci čvor u stablo...
    return stablo; } // vrati pokazivač na koren

// izbacuje iz stabla, na čiji koren ukazuje pokazivač, deo niza od pozicije poz
// funkcija vraca T/F, da li je posle brisanja prazno stablo
bool izbaci(cvor* stablo, const string& niz, size_t poz) {
    if (stablo == nullptr)     // ako je stablo prazno, ništa se ne izbacuje
        return true;  // stablo je bilo i ostalo prazno
    if (poz == niz.length())   // kraj reči?
        stablo->kraj = false;  // u tom čvoru nije više kraj neke reči
    else { // stablo nije prazno i nije kraj reči...
        auto it = stablo->grane.find(niz[poz]); 
        if (it != stablo->grane.end() && izbaci(it->second, niz, poz+1)) // ako se dobije prazno stablo i granu
            stablo->grane.erase(it);     } // briše sufiks,
    if (!stablo->kraj && stablo->grane.size() == 0) { // ako je u stablu ostao jedan potpuno prazan čvor
        delete stablo;  // brišemo ga
        return true;  }  // nakon brisanja je prazno stablo
    else
        return false;  // stablo nakon brisanja nije prazno
    }

// iz stabla na koji ukazuje pokazivač se briše niz 
cvor* izbaci(cvor* stablo, const string& w) {
    if (izbaci(stablo, w, 0)) // stablo je ostalo prazno?
        return nullptr; // pok. na null
    else
        return stablo; } // pok. na koren

// traži sufiks reči w koji počinje od pozicije i u drvetu na čiji koren ukazuje pokazivač stablo
bool sadrzi(cvor *stablo, const string& w, size_t i) {
    if (stablo == nullptr)   // ako je stablo prazno, ono ne sadrži traženu reč
        return false;
    // ako je sufiks prazan, on je u korenu akko je u korenu obeleženo da je tu kraj reči
    if (i == w.size())
        return stablo->kraj;

    auto it = stablo->grane.find(w[i]);     // tražimo granu na kojoj piše w[i]
    if(it != stablo->grane.end())     // ako je nađemo, rekurzivno tražimo ostatak sufiksa od pozicije i+1
        return sadrzi(it->second, w, i+1);
 
    return false;   // nismo našli granu sa w[i], pa reč ne postoji
}

// traži reč w u stablu na čiji koren ukazuje pokazivač stablo
bool sadrzi(cvor* stablo, const string& w) {
    return sadrzi(stablo, w, 0); }


void obrisi(cvor* koren) {  // brise prefiksno stablo sa korenom koren
    if (koren != nullptr) {
        for (auto it : koren->grane)
            obrisi(it.second);
        delete koren;     } }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cvor * koren = nullptr;

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        string upit, niz; cin >> upit >> niz >> ws;

        if (upit == "ubaci")
            koren = ubaci(koren, niz);

        else if (upit == "izbaci")
            koren = izbaci(koren, niz);

        else if (upit == "trazi") {
            if (sadrzi(koren, niz, 0))
                cout << "da" << "\n";
            else
                cout << "ne" << "\n"; }  }
    obrisi(koren); // oslobodi memoriju
    return 0; }