#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 5;

struct MaxQueue {
    queue <pair <int, int>> q;
    deque <pair <int, int>> dq;

    void push(pair <int, int> element) {
        q.push(element);
        while (!dq.empty() && dq.back().first < element.first) 
            dq.pop_back();
        dq.push_back(element); }

    void pop() {
        if (q.front() == dq.front()) 
            dq.pop_front();
        q.pop(); }

  long long getMax() {
        return dq.front().first; } };

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;

    vector <vector <int>> wall(n, vector <int> (m, -INF));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) 
          cin >> wall[i][j];

    int r, s; cin >> r >> s;
    vector <vector <int>> phase1(n, vector <int> (m - s + 1, -INF));

    for (int i = 0; i < n; i++) {
        MaxQueue mq;
        for (int j = 0; j < s - 1; j++) 
            mq.push({wall[i][j], j});
        for (int j = s - 1; j < m; j++) {
            mq.push({wall[i][j], j});
            phase1[i][j - s + 1] = mq.getMax();
            mq.pop(); }    }

    vector <vector <int>> phase2(n - r + 1, vector <int> (m - s + 1));
    for (int j = 0; j < m - s + 1; j++) {
        MaxQueue mq;
        for (int i = 0; i < r - 1; i++) 
            mq.push({phase1[i][j], i});
        for (int i = r - 1; i < n; i++) {
            mq.push({phase1[i][j], i});
            phase2[i - r + 1][j] = mq.getMax();
            mq.pop();        }    }
    for (int i = 0; i < n - r + 1; i++) {
        for (int j = 0; j < m - s + 1; j++) 
            cout << phase2[i][j] << ' ';
        cout << '\n';     }

    return 0; }