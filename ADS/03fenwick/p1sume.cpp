#include <bits/stdc++.h>
using namespace std;
//Суме сегмената променљивог низа
//https://petlja.org/sr-Latn-RS/biblioteka/r/Zbirka3/sume_segmenata_promenljivog_niza1

// na osnovu Fenvikovog stabla racuna zbir prefiksa [0, k) polaznog niza
int ps(const vector<int>& stablo, int k) { // prefiksna suma od 1. do k-tog elementa
    int zbir = 0;
    while (k > 0) {
        zbir += stablo[k];
        k -= k & -k;  }
    return zbir; }

// na osnovu Fenvikovog stabla racuna zbir segmenta [a, b] polaznog niza
int zbir(const vector<int>& stablo, int a, int b) {
    return ps(stablo, b+1) - ps(stablo, a); }

// element originalnog niza na poziciji i
int element(const vector<int>& stablo, int i) {
    return zbir(stablo, i, i); }

// azurira Fenvikovo stablo smesteno u niz stablo nakon sto se
// u originalnom nizu element na poziciji i uveca za x
void dodaj(vector<int>& stablo, int i, int x) {
    int k = i + 1; // nizovi pocinju od 0
    int n = stablo.size();
    while (k < n) {
        stablo[k] += x;
        k += k & -k;  } }

// azurira Fenvikovo stablo nakon sto se u originalnom nizu element na poziciji i promeni na x
void upis(vector<int>& stablo, int i, int x) {
    dodaj(stablo, i, x - element(stablo, i)); }

// na osnovu niza a u kom su elementi smesteni na pozicijama [0, n)
// pravi Fenvikovo stablo na pozicije iz segmenta [1, n]
vector<int> napravi(const vector<int>& a) {
    int n = a.size();
    vector<int> stablo(n + 1, 0); // i stablo od 0
    for (int k = 0; k < n; k++)
        dodaj(stablo, k, a[k]);
    return stablo; }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i]; // elementi niza od 0
    vector<int> stablo = napravi(a); // napravi fen. stablo

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        string upit; cin >> upit;
        if (upit == "p") { // na poz. i upisi vrednost v
            int i, v; cin >> i >> v >> ws;
            upis(stablo, i, v); } 
        else if (upit == "z") { // ispis zbira segmenta [a,b]
            int a, b; cin >> a >> b;
            cout << zbir(stablo, a, b) << '\n';  } }
    return 0; }