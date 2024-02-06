#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, logar;
    string a;
    int boje[6] = {0, 0, 0, 0, 0, 0}; // boje, redom
    // crvena, plava, zuta, narandzasta, zelena, crvena
    cin >> n; // unos
    for(int i = 0; i < n; i++) {
        cin >> a;
        for(int j = 0; j <= a.size(); j++) {
            switch(a[j]) {
                case '1':
                    boje[0]++;
                    break;
                case '2':
                    boje[1]++;
                    break;
                case '3':
                    boje[2]++;
                    break;
                case '4':
                    boje[3]++;
                    break;
                case '5':
                    boje[4]++;
                    break;
                case '6':
                    boje[5]++;
                    break;
            }
        }
    }
    cout << boje[0] * 2 + boje[3] + boje[5] << ' '; // mg crvene
    cout << boje[1] * 2 + boje[4] + boje[5] << ' '; // mg plave
    cout << boje[2] * 2 + boje[3] + boje[4] << ' '; // mg zute
    return 0;
}
