#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

const int MAX = 1 << 18;

int N;
int cnt[MAX];
vector <pii> adj[MAX];

void load() {
  scanf("%d", &N);
  while (N--) {
    int mask = 0;
    for (int i = 0; i < 6; i++) {
      int x;
      scanf("%d", &x);
      mask = 8 * mask + x;
    }
    cnt[mask]++;
  }
}

inline ll choose2(int n) {
  return (ll)n * (n - 1);
}

int get_sevens(int x) {
  int res = 0;
  for (int i = 5; i >= 0; i--) {
    if (x % 8 == 7)
      res |= 1 << i;
    x /= 8;
  }
  return res;
}

ll solve() {
  vector <int> trans;
  for (int i = 0; i < 1 << 6; i++) {
    int tmp = 0;
    for (int j = 0; j < 6; j++)
      tmp = 8 * tmp + (i >> j & 1);
    trans.push_back(tmp);
  }
  for (int i = 0; i < MAX; i++) {
    int mask = get_sevens(i);
    for (int j = 1; j < 1 << 6; j++)
      if (!(mask & j))
        adj[i].push_back({i + trans[j], __builtin_popcount(j) % 2 ? -1 : 1});
  }
  ll sol = 0;
  for (int i = MAX - 1; i >= 0; i--) {
    int tmp = cnt[i];
    for (auto it : adj[i])
      cnt[i] -= it.second * cnt[it.first];
    ll pairs = choose2(cnt[i] - 1);
    for (auto it : adj[i])
      pairs += it.second * choose2(cnt[it.first]);
    sol += tmp * pairs;
  }
  return sol;
}

int main() {
  load();
  printf("%lld\n", solve());
  return 0;
}