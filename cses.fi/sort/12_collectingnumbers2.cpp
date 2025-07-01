#include <bits/stdc++.h>
using namespace std;

vector<int> collectingnumbersII(int n, int m, vector<int>& values,
                    vector<vector<int> >& swaps)
{
    values.insert(values.begin(), 0);
    vector<int> res;
    vector<int> position(n + 1);

    for (int i = 1; i <= n; i++)
        position[values[i]] = i;

    int count = 1;
    for (int i = 1; i < n; i++)
        count += (position[i] > position[i + 1]);

    set<pair<int, int> > updatedPairs;

    for (int i = 0; i < m; i++) {
        int l = swaps[i][0], r = swaps[i][1];

        if (values[l] + 1 <= n)
            updatedPairs.insert(
                { values[l], values[l] + 1 });
        if (values[l] - 1 >= 1)
            updatedPairs.insert(
                { values[l] - 1, values[l] });
        if (values[r] + 1 <= n)
            updatedPairs.insert(
                { values[r], values[r] + 1 });
        if (values[r] - 1 >= 1)
            updatedPairs.insert(
                { values[r] - 1, values[r] });

        for (auto swapped : updatedPairs)
            count -= position[swapped.first]
                     > position[swapped.second];

        swap(values[l], values[r]);

        position[values[l]] = l;
        position[values[r]] = r;

        for (auto swapped : updatedPairs)
            count += position[swapped.first]
                     > position[swapped.second];

        res.push_back(count);

        updatedPairs.clear();
    }
    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> swap(m, vector<int>(2, 0));
    for(int i = 0; i < m; i++) {
        cin >> swap[i][0] >> swap[i][1];
    }
    vector<int> res = collectingnumbersII(n, m, a, swap);

    for (auto i : res)
        cout << i << "\n";

    return 0;
}