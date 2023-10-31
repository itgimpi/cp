#include <bits/stdc++.h>
using namespace std;

int main() { 
    int n; cin >> n;
    int bodovi = 0;
    for (int i = 0; i < n; i++) {
        string proba, resenje;
        cin >> proba >> resenje;
        if ( proba == resenje ) bodovi += 4;
        else if ( proba != "ooooo" ) bodovi -= 1;     }
    cout << bodovi << '\n' << 4 * n << '\n' << -n << '\n';

}

