#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << ", " <<

int bodovi[50000][4];
vector< vector<int> > signature[1 << 4];

int main() {
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    REP(i, n) {
        REP(j, k)
            cin >> bodovi[i][j];
        FOR(mask, 1, 1 << k) {
            vector<int> t;
            REP(j, k)
                if ((mask >> j) & 1)
                    t.push_back(bodovi[i][j]);
            signature[mask].push_back(t);
        }
    }

    long long sol = (long long)n * (n - 1) / 2;
    FOR(mask, 1, 1 << k) {
        sort(signature[mask].begin(), signature[mask].end());
        long long parova = 0;
        long long istih = 0;
        vector<int> prev;
        for (auto &t : signature[mask]) {
            if (t == prev)
                ++istih;
            else {
                parova += istih * (istih - 1) / 2;
                istih = 1;
                prev = t;
            }
        }
        parova += istih * (istih - 1) / 2;
        if (__builtin_popcount(mask) & 1)
            sol -= parova;
        else
            sol += parova;
    }
    cout << sol << endl;
    return 0;
}