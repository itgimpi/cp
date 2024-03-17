#include <bits/stdc++.h>
using namespace std;
/* Subordinates, Time limit: 1.00 s Memory limit: 512 MB, https://cses.fi/problemset/task/1674
Given the structure of a company, your task is to calculate for each employee the number of their subordinates.
Input: The first input line has an integer n: the number of employees. 
The employees are numbered 1,2,\dots,n, and employee 1 is the general director of the company.
After this, there are n-1 integers: for each employee 2,3,\dots,n their direct boss in the company.
Output: Print n integers: for each employee 1,2,\dots,n the number of their subordinates.
Constraints: 1 \le n \le 2 \cdot 10^5
Example
Input:
5
1 1 2 3
Output:
4 1 1 0 0

element: 1, 2, 3, 4, 5
prev:    -, 1, 1, 2, 3

        1 ( sledbenik je 2, on ima jednog sledbenika 1+1, slicno i 3)
       / \
      /   \
     2     3 (2 i 3 po jednog sledbenika)
     |     |
     |     |
     4     5 (4 i 5 imaju 0 sledbenika)

nexts:
1->2, 3
2->4
3->5
4
5
*/
void dfs(int cvor, vector<vector<int>>&nexts, vector<int>&broj) {
    broj[cvor] = 1; // taj cvor

    for (int next : nexts[cvor]) { // za svakog sledeceg...
        dfs(next, nexts, broj);    // prvo svi obilasci...
        broj[cvor] += broj[next];  } } // onda dodavanja.

int main() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n; cin >> n; // ukupno
    vector<vector<int>>nexts(n+1); // za svakog se pamte sledbenici
    vector<int>broj(n+1, 0); // broj sledbenika
    for (int i = 2; i <= n; i++) { // za svaki i-ti od 2-og...
        int prev; cin >> prev; // unos preth.
        nexts[prev].push_back(i); } // sl. od preth. je i-ti, samo 1 smer

    dfs(1, nexts, broj); // od prvog...

    for (int i = 1; i <= n; i++) 
        cout << broj[i] - 1 << ' '; } // bez njega
