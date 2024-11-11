#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
int n, broj;
int xmz[30];
string pogodi[maxn];
string boje[maxn];

inline bool proveri(int g, string& res) {
    memset(xmz, 0, sizeof xmz);
    for (int i = 0; i < 5; i++) {
        xmz[res[i] - 'a']++;
        if (pogodi[g][i] == res[i])
            xmz[pogodi[g][i] - 'a']--; } 
    bool ret = 1;
    for (int i = 0; i < 5; i++) {
        int l = pogodi[g][i] - 'a';
        char boja;
        if (pogodi[g][i] == res[i])
            boja = 'G';
        else
            if (xmz[l] > 0) {
                boja = 'R';
                xmz[l]--; }
        else
            boja = 'B';
        if (boja != boje[g][i])  
            return 0; }
    return 1; }

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> pogodi[i] >> boje[i];
    for (char l1 = 'a'; l1 <= 'z'; l1++)
        for (int l2 = 'a'; l2 <= 'z'; l2++)
            for (int l3 = 'a'; l3 <= 'z'; l3++)
                for (int l4 = 'a'; l4 <= 'z'; l4++)
                    for (int l5 = 'a'; l5 <= 'z'; l5++) {
                        string res = ""; 
                        res += l1; res += l2; res += l3; res += l4; res += l5;
                        bool ok = 1;
                        for (int i = 0; i < n; i++) 
                            if (!proveri(i, res)) {
                                ok = 0;
                                break; }    
                        broj += ok; } 
    cout << broj << endl;
    return 0; }