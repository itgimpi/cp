#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, res = 1, b_max; // resenje pocinje od 1, zato sto krecemo od druge duzi
    cin >> n;
    vector<pair<int, int>> duzi(n);
    for(int i = 0; i < n; i++) {
        cin >> duzi[i].first;
    }
    for(int i = 0; i < n; i++) {
        cin >> duzi[i].second;
    }
    sort(duzi.begin(), duzi.end());
    b_max = duzi[0].second;
    for(int i = 1; i < n; i++) {
        if(duzi[i].second <= b_max || duzi[i].first == duzi[i - 1].first) { // provera da li se seku
            continue;
        }
        else { // u suprotnom, duz i je pocetak novog ostrva
            res++;
            b_max = duzi[i].second;
        }
    }
    cout << res << endl;
    return 0;
}
