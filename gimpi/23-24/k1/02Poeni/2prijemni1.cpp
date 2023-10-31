#include <bits/stdc++.h>
using namespace std;

int main() { 
    int n; cin >> n;
    int bodovi = 0;
    for (int i = 0; i < n; i++) {
        string proba, resenje;
        cin >> proba >> resenje;

        int poz1 = -1, poz2 = -1;

        for (int j = 0; j < 5; j++)
            if ( proba[j] == 'x' ) poz1 = j;

        for (int j = 0; j < resenje.size(); j++)
            if ( resenje[j] == 'x' ) poz2 = j;
        
        if ( poz1 == poz2 ) bodovi += 4;
        else if ( (poz1 != -1) && (poz1 != poz2) ) bodovi -= 1; 
        }
    cout << bodovi << '\n' << 4 * n << '\n' << -n << '\n';

}

