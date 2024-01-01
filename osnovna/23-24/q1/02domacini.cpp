#include <bits/stdc++.h>
using namespace std;



int main() {

    int res = 0;
    int d, g;

    d = g = 0;

    int cd, cg;

    cin >> cd >> cg;

    res = max(res, cd - g);

    d+=cd;
    g+=cg;


    cin >> cd >> cg;

    res = max(res, cd - g);

    d+=cd;
    g+=cg;

    //...


    return 0;
}