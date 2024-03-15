---
hide:
  - toc
---

# A3 - NZD permutacije

=== "Zadatak"

 | Vremensko ograničenje | Memorijsko ograničenje |
 |:-:|:-:|
 | 2000ms | 256MB |

 Dat je niz $A$ od $N$ prirodnih brojeva. Izračunati ostatak koji pri deljenju sa $10^9 + 7$ daje zbir najvećih zajedničkih delilaca susednih članova svih $N!$ permutacija niza $A$.

 Drugim rečima, ako je $S_N$ skup svih permutacija dužine $N$, izračunati $\sum_{P \in S_N} \sum_{i=1}^{N-1} NZD(A_{P_i}, A_{P_{i+1}})$ po modulu $10^9+7$.

## Opis ulaza

 U prvom redu standardnog ulaza nalazi se broj $N$. U narednom redu nalazi se $N$ prirodnih brojeva, niz $A$.

## Opis izlaza

 Ispisati rešenje na standardni izlaz.

## Ograničenja

- $1 \leq N \leq 10^5$
- $1 \leq A_i \leq 10^6$

## Podzadaci

 1. (11 poena) $N \leq 9$.
 2. (17 poena) $N \leq 1000$.
 3. (21 poena) $A_i \leq 1000$.
 4. (6 poena) U nizu $A$ ima najviše dve različite vrednosti.
 5. (45 poena) Nema dodatnih ograničenja.

## Primeri

### Primer 1

#### Ulaz

 ```
 3
 12 15 15
 ```

#### Izlaz

 ```
 84
 ```

#### Objašnjenje

 Tražimo zbir za $6$ permutacija:

- $[12, 15, 15]$, $3 + 15 = 18$
- $[12, 15, 15]$, $3 + 15 = 18$
- $[15, 12, 15]$, $3 + 3 = 6$
- $[15, 15, 12]$, $15 + 3 = 18$
- $[15, 12, 15]$, $3 + 3 = 6$
- $[15, 15, 12]$, $15 + 3 = 18$

 Rešenje je $18 + 18 + 6 + 18 + 6 + 18 = 84$.

### Primer 2

#### Ulaz

 ```
 7
 20 25 9 10 21 29 12
 ```

#### Izlaz

 ```
 69120
 ```

=== "Rešenje"

 | Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
 |:-:|:-:|:-:|:-:|
 | Tadija Šebez | Tadija Šebez | Tadija Šebez | Aleksa Plavšić |

## Rešenje za $N \leq 9$

 Možemo da izgenerišemo sve permutacije i nađemo traženi zbir.

## Rešenje za ostale podzadatke

 Primetimo da se svaka dva broja iz niza $A$ pojavljuju kao susedni u tačno $2 (N-1)!$ permutacija, pa je rešenje zbir najvećih zajedničkih delilaca svih parova puta $2 (N-1)!$. Kada je $N \leq 1000$ možemo da prođemo kroz sve parove, dok je kod ostala dva podzadatka potrebno prvo prebrojati koliko se puta koja vrednost pojavljuje u nizu.

## Rešenje za 100 poena

 Neka je $cnt_i$ broj pojavljivanja broja $i$ u nizu, a $d_i$ broj članova niza koji su deljivi sa $i$. Niz $d_i$ se može naći po formuli $d_i = \sum_{j=1}^{i*j \leq M} cnt_{i*j}$ u $O(M log M)$ gde je $M$ najveći broj u nizu. Neka je $dp_i$ broj parova čiji je NZD jednak $i$. Primetimo da je $\binom{d_i}{2}$ broj parova čiji je NZD deljiv sa $i$, pa kada od toga oduzmemo broj parova čiji je NZD jednak $2i$, $3i$, ... dobijamo broj parova čiji je NZD jednak $i$. Sada možemo izračunati niz $dp$ od $dp_n$ do $dp_1$ po formuli $dp_i = \binom{d_i}{2} - \sum_{j=2}^{i*j \leq M} dp_{i*j}$. Vremenska složenost rešenja je $O(M log M)$, a memorijska $O(M)$.

 Napomena: Računanje nizova $d_i$ i $dp_i$ je složenosti $O(M log M)$ jer se za njihovo izračunavanje prolazi kroz ceo niz, pa kroz svaki drugi član, zatim kroz svaki treći, ... U zbiru to je $\sum_{i=1}^{M} \lfloor \frac{M}{i} \rfloor$ što je približno jednako $M$ puta $H_M = \sum_{i=1}^{M} \frac{1}{i}$. $H_n$ su harmonijski brojevi i oni se ponašaju kao prirodni logaritam.

 ``` cpp title="06_nzd_permutacije.cpp" linenums="1"
 #include <bits/stdc++.h>
 using namespace std;
 #define ll long long
 const int mod=1e9+7;
 int add(int x,int y){x+=y;return x>=mod?x-mod:x;}
 int sub(int x,int y){x-=y;return x<0?x+mod:x;}
 int mul(int x,int y){return (ll)x*y%mod;}
 
 const int N=1000050;
 ll dp[N];
 int cnt[N],dv[N],a[N];
 int main(){
  int n;
  scanf("%i",&n);
  for(int i=1;i<=n;i++){
   scanf("%i",&a[i]);
   cnt[a[i]]++;
  }
  for(int i=1;i<N;i++){
   for(int j=i;j<N;j+=i){
    dv[i]+=cnt[j];
   }
  }
  int ans=0;
  for(int i=N-1;i>=1;i--){
   dp[i]=(ll)dv[i]*(dv[i]-1)/2;
   for(int j=i*2;j<N;j+=i){
    dp[i]-=dp[j];
   }
   ans=add(ans,mul(dp[i]%mod,i));
  }
  ans=mul(ans,2);
  for(int i=1;i<=n-1;i++)ans=mul(ans,i);
  printf("%i\n",ans);
  return 0;
 }

 ```
