#include <bits/stdc++.h>
using namespace std;
// za brzo odredjivanje nedijane se koriste 2 hipa
// 2 za x i 2 za y koordinate
priority_queue<pair<int,int>> hipx1; priority_queue<pair<int,int>> hipy1;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> hipx2;
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> hipy2;

void uhipx(int vrednost, int i) { // u hip idu 
    pair<int, int> nova = {vrednost, i};
    if (i == 1) // prva tacka ide u prvi hip1, njegov max je medijana
        {hipx1.push(nova); return;} // i to je to
    if (i & 1) {  // tacke sa neparnim indeksima, hipovi su pre dodavanja iste dimenzije
        if(nova < hipx2.top()) // nije veca od najmanjeg iz hipa2, 
            hipx1.push(nova); // ide u hip1, hip1 je za 1 veci od hipa 2
        else { // ipak je veca od najmanjeg iz hipa2, onda je za hip2, ali...
            // treba da se odrzava balansiranost hipova!
            pair<int,int> tmp = hipx2.top(); // zapamti najmanji iz hipa2
            hipx2.pop(); // izbaci najmanji iz hipa2
            hipx2.push(nova); // dodaj novi u hip2
            hipx1.push(tmp); } // dodaj prethodno najmanji iz hipa2 u hip1
            //  opet je hip1 za 1 veci od hipa 2
        return; } // i to je to
    // tacke sa parnim indeksima, hip1 je pre dodavanja veci za 1
    if (nova > hipx1.top()) // ako je nova tacka za hip2
        hipx2.push(nova); // ide u hip2
    else { // ipak je za hip1
        pair<int,int> tmp = hipx1.top(); // zapamti najveci iz hipa1
        hipx1.pop(); // izbaci ga iz hipa1
        hipx1.push(nova); // dodaj novu u hip1
        hipx2.push(tmp); } } // zapamcenu u hip2

void uhipy(int vrednost, int i) {
    pair<int,int> nova = {vrednost, i};
    if(i == 1) 
        {hipy1.push(nova); return;}
    if(i & 1) { 
        if(nova < hipy2.top()) hipy1.push(nova);
        else {
            pair<int,int> r=hipy2.top();
            hipy2.pop(); hipy2.push(nova);
            hipy1.push(r); }
        return; }
    if(nova>hipy1.top()) hipy2.push(nova);
    else { 
        pair<int,int> r=hipy1.top();
        hipy1.pop(); hipy1.push(nova);
        hipy2.push(r); } }

int medijanax() {
    if(hipx1.size()!=hipx2.size()) // ako su dimenzije hipova razlicite
        return hipx1.top().second; // vrati indeks najvece iz prvog hipa
    return -1; }

int medijanay() {
    if(hipy1.size()!=hipy2.size()) 
        return hipy1.top().second;
    return -1; }

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); // zbog IO preplitanja 
    int n; cin >> n;
    for(int i = 1; i <= n; i++) { // tacke od 1 do n...
        int x, y; cin >> x >> y;
        uhipx(x, i); // na hip idu koordinata i redni broj / indeks tacke
        uhipy(y, i);
        int mx = medijanax(); // odredi medijanu po x
        int my = medijanay(); // i po y
        if (mx == my) cout << mx << '\n'; // ako je to isti indeks, medijana postoji
        else cout << -1 << '\n'; } } // inace ne