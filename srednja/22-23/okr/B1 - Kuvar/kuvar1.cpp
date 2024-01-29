#include <bits/stdc++.h>
using namespace std;	
	
int main() {
    int n = 4;
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // test primer 1

    long long res = 0;
    for(int i = 0; i < n; i++)  // za svaku emisiju...
        for(int j = 0; j < n; j++)   // za svaki scenario...
            if (x[i] == y[z[j]-1])   // -1 zbog prebacivanja sa 1, 2, 3, ... na 0, 1, 2, ...
                res++; 
                
    cout << res;
    return 0; }