#include <bits/stdc++.h>
using namespace std;

// Увећања сегмената и читање елемената
//https://petlja.org/sr-Latn-RS/biblioteka/r/Zbirka3/uvecanja_segmenata_citanje_elemenata

// azurira Fenvikovo stablo nakon sto se u originalnom nizu element na poziciji k uveca za x
void dodaj(vector<int>& stablo, int k, int x) {
    k++;
    int n = stablo.size();
    while (k < n) {
        stablo[k] += x;
        k += k & -k;  }}

// na osnovu Fenvikovog stabla izracunava zbir prefiksa [0, k) originalnog niza
int zbirPrefiksa(const vector<int>& stablo, int k) {
    int zbir = 0;
    while (k > 0) {
        zbir += stablo[k];
        k -= k & -k;     }
    return zbir; }

void uvecajSegment(vector<int>& stablo, int a, int b, int v) {
    dodaj(stablo, b+1, -v);
    dodaj(stablo, a, v); }

int element(const vector<int>& stablo, int a) {
    return zbirPrefiksa(stablo, a+1); }

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> stablo(n+1);
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        string upit; cin >> upit;
        if (upit == "u") {
            int a, b, v; cin >> a >> b >> v;
            uvecajSegment(stablo, a, b, v); } 
        else if (upit == "e") {
            int a; cin >> a;
            cout << element(stablo, a) << '\n';   } }
    return 0; }