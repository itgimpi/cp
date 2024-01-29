#include <bits/stdc++.h>
using namespace std;    

int main() {
    int n = 4;
    int x[] = {1, 1, 4, 3}, y[] = {3, 1, 3, 4}, z[] = {1, 3, 2, 2}; // nizovi
    int *px, *py, *pz;
	
    int res = 0;
    for (int i = 0; i < n; i++) {  
        px = x + i;
        for (int j = 0; j < n; j++) {
            //if (x[i] == y[z[j]-1])    res++; 
            pz = z + j;
            py = y + *pz - 1;
            if ( *px == *py ) res++;    } }
                
    cout << res;
    return 0; }