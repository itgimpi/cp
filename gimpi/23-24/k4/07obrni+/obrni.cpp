#include <bits/stdc++.h>
using namespace std;
int cnt[30];

int main(void) {
    ios::sync_with_stdio(false);
    int q, slovo = 25, smer = 1;
    cin >> q;
    int zadnje = 0;
    for (int i = 0; i < q; ++i) {
        string type;
        int n;
        cin >> type >> n;
        
        int nn = n - zadnje;
        for (int i = 0; i < 26; ++i) 
            cnt[i] += nn / 26;
        nn %= 26;
        for (int i = 0; i < nn; ++i) {
            slovo = (slovo + smer + 26) % 26;
            ++cnt[slovo];     }
        zadnje = n; 
        
        if (type[0] == 'O')  // OBRNI
            smer *= -1; 
        else {
            string s;
            cin >> s;
            cout << cnt[s[0] - 'a'] << '\n'; } }

    return 0;

}
