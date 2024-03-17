#include <bits/stdc++.h>
using namespace std;

/*You are given a tree consisting of n nodes.
A matching is a set of edges where each node is an endpoint of at most one edge. 
What is the maximum number of edges in a matching?
Input
The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Output
Print one integer: the maximum number of pairs.
Constraints

1 \le n \le 2 \cdot 10^5
1 \le a,b \le n

Example
Input:
5
1 2
1 3
3 4
3 5

        1 ( )
       / \
      /   \
     2     3 ()
          / \  
         /   \  
        4     5    ()

Output:
2

Neka je odabran cvor 1. Ako se odabere i 2 (12), onda ne moze da se odabere i 3 (1 je 2x kraj).
Neka je odabran cvor 1. Ako se odabere i 3 (13), onda ne moze da se odabere ni 4 ni 5 (3 je 2x kraj).

                      Cvor c moze da se odabere ili ne...

                      Ako cvor c nije odabran, moze da se odabere bilo koji od sledbenika...
        c             resenje je zbir najboljih vrednosti sledbenika od s1 do sn (odabrani ili ne) 
       / \                     n
      /   \           dp0[c] = ∑ max ( dp0[si], dp1[si] ) 
     /     \                  i=1
    /       \ 
   __         __ 
  |s1|  ...  |sn|
  | .|       | .|
  | .|       | .|
  | .|       | .|
   
                      Ako cvor c jeste odabran, sj moze da bude odabran ili ne
        c         grana od c do sj, odabrani svi s1,..., sn, osim sj 
       /|\                        |<-                       sj nije odabran                        ->|    
      / | \           dp1[c]= 1 + ∑ max ( dp0[si], dp1[si] ) - max(dp0[sj], dp1[sj])         + dp0[sj]
     /  |  \                 csj  |<-      dp0[c]        ->|    
    /   |   \         
   __         __ 
  |s1|..sj.. |sn|
  |  | / \   |  |                
      /   \           dp1[c] = max(dp1[c], // neki od preth. daju bolje resenje
     /     \                       dp0[c] - max(dp0[sj], dp1[sj]) + dp0[sj] + 1)       
    /       \ 
   /         \
 ___         ___
|ss1|  ...  |ssn|<-dp0[sj], ako sj nije, njegovi sledbenici ssi modu
| . |       | . |



*/

void dfs(int c, int preth, vector<vector<int>>&veze, vector<int>&dp0, vector<int>&dp1) {
    for (int s : veze[c]) 
        if (s != preth) {
            dfs(s, c, veze, dp0, dp1);
            dp0[c] += max(dp0[s], dp1[s]); }  

    for (int s : veze[c]) 
        if (s != preth) 
            dp1[c] = max(dp1[c], dp0[s] + 1 + dp0[c] - max(dp0[s], dp1[s])); }

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<vector<int>> veze(n+1);
    vector<int>dp0(n+1, 0); // i-ti cvor nije odabran 
    vector<int>dp1(n+1,0);  // i-ti cvor je odabran 
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        veze[u].push_back(v);
        veze[v].push_back(u);  }
    dfs(1, 0, veze, dp0, dp1);

    cout << max(dp0[1], dp1[1]) << endl; }