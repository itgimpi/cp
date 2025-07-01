#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> a;
bool comp(int i, int j) {
    return a[i] < a[j];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> aI;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a.emplace_back(x, y);
        aI.push_back(i);
    }
    sort(aI.begin(), aI.end(), comp);
    set<pair<int, int>> rooms;
    vector<int> s(n);
    int roomsCount = 0;
    for(int i = 0; i < n; i++) {
        auto it = rooms.lower_bound(make_pair(a[aI[i]].first, 0));
        int room;
        if(it == rooms.begin()) {
            room = roomsCount + 1;
            roomsCount++;
        }
        else {
            it--;
            room = it->second;
            rooms.erase(it);
        }
        rooms.emplace(a[aI[i]].second, room);
        s[aI[i]] = room;
    }
    cout << roomsCount << '\n';
    for(int i = 0; i < n; i++) {
        cout << s[i] << ' ';
    }
    return 0;
}