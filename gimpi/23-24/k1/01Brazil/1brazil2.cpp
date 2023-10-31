#include <bits/stdc++.h>

using namespace std;

int main()
{
    int p, d;
    cin >> p >> d;
    int c = p - d;
    if((c > 5) || (c < -5)){
        cout << "DA";
    }
    else {
        cout << "NE";
    }

    return 0;
}