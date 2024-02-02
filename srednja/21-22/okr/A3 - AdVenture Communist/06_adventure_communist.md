# A3 - AdVenture Communist

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 512MB |

AdVenture Communist 2 je igrica u kojoj igrač kupuje fabrike sa ciljem da prikupi što više krompira za najkraće vreme. Ukupno postoji $N$ različitih tipova fabrika.



Broj krompira $a_0$ se svake sekunde poveća prvo $C$ puta, a zatim se doda broj krompira koji proizvede fabrika prvog tipa. Fabrika prvog tipa svake sekunde proizvodi $K_1$ krompira, dakle ukoliko u trenutku $t$ imate $a_0$ krompira i $a_1$ fabrika prvog tipa u trenutku $t+1$ ćete imati $C \cdot a_0 + K_1 \cdot a_1$ krompira. Broj fabrika tipa tipa $i$ se takođe svake sekunde prvo poveća $C$ puta, a zatim se doda broj fabrika tipa $i$ koje je proizvela fabrika tipa $i+1$. Fabrike tipa $i+1$ gde je $i>0$ svake sekunde proizvode $(i+1) \cdot K_{i+1}$ fabrika tipa $i$,  dakle ukoliko u trenutku $t$ imate $a_i$ fabrika tipa $i$ i  $a_{i+1}$ fabrika tipa $i+1$ u trenutku $t+1$ ćete imati $C \cdot a_i + (i+1) \cdot K_{i+1} \cdot a_{i+1}$ fabrika tipa $i$.



Zavisnost opisanog niza $a_0, a_1, ... , a_N$ od vremena se može formalno zapisati pomoću formule:



$$a_i(t+1) = C \cdot a_i(t) + (i+1) \cdot K_{i+1} \cdot a_{i+1}(t)$$



Vaš zadatak je da odredite ukupan broj krompira u trenutku $T$, to jest $a_0(T)$, po modulu $10^9+7$.

## Opis ulaza



Prva linija standardnog ulaza sadrži tri broja, broj elemenata niza $N$, trenutak $T$ i konstanta $C$. U drugom redu nalazi se $N$ celih brojeva koji predstavljaju vrednosti elemenata niza u trenutku $t=0$. U trećem redu nalazi se $N$ celih brojeva koji predstavljaju niz $K_0, K_1, ... , K_N$.



## Opis izlaza



Na standardni izlaz je postrebno ispisati jedan ceo broj $a_0(T)$ po modulu $10^9+7$.



## Primer



### Ulaz

```
3 3 2
1 1 1
1 1 1
```

### Izlaz

```
32
```



## Objašnjenja primera
Posle prve sekunde niz će izgledati ovako:
```
a = {3, 4, 2}
```
Posle druge sekunde niz će izgledati ovako:
```
a = {10, 12, 4}
```
Posle treće sekunde niz će izgledati ovako:
```
a = {32, 32, 8}
```
Kako tražimo vrednost u $a_0$ posle treće sekunde, odgovor je 32.



## Ograničenja
-   $1 \leq N\leq 200000$
-   $1\leq T\leq 10^9$
-   $1\leq C \leq 10^9$
-   $0\leq a_{i}\leq 10^9$
-   $0\leq K_{i}\leq 10^9$



Test primeri su podeljeni u 4 disjunktne grupe:

-   U test primerima vrednim $10$ poena: $N,T\leq2000$
-   U test primerima vrednim $20$ poena: $N\leq200$
-   U test primerima vrednim $20$ poena: $C=1$
-   U test primerima vrednim $20$ poena: $N\leq1000$
-   U test primerima vrednim $30$ poena: Nema dodatnih ograničenja

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Igor Pavlović | Igor Pavlović | Igor Pavlović | Tadija Šebez |

## Rešenje za $N, T \leq 2000$

Ovde je dovoljno simulirati dešavanja trenutak po trenutak u složenosti $O(NT)$.

## Rešenje za $N\leq 200$

U ovom slučaju je potrebno primetiti da je opisana rekurenta veza zapravo linearna transformacija koja se može predstaviti u matričnom obliku kao

$$
A(t+1)=K \cdot A(t)
$$ 

gde je

$$
A(t) = [a_0(t), a_1(t), ..., a_n(t)]^T
$$

$$
K_{i,i} = C \text{  ,  } K_{i,i+1} = (i+1) \cdot K_{i+1}
$$

$$
K_{ij}=0 \text{  za  } (j!=i) \wedge (j!=i+1)
$$

Odavde se dobija sledeća jednakost:

$$
A(t)=K^t \cdot A(0)
$$

iz koje možemo odrediti vrednost $a_0(T)$ u složenosti $O(N^3\log T)$ brzim stepenovanjem matrica.

## Rešenje za $C = 1$

Primetimo prvo da se doprinos svake pojedinače fabrike može posmatrati odvojeno od ostalih zato što je opisana transformacija linearna. Ukupan broj krompira u trenutku $T$ dobijamo kao zbir doprinosa svake fabrike.

Za transformaciju

$$
a_i(t+1)=a_i(t)+(i+1) \cdot K_{i+1} \cdot  a_{i+1}(t)
$$

se može indukcijom dokazati da je doprinos $i$-te fabrike ukupnom broju krompira nakon $t$ sekundi zapravo:

$$
d_i = \prod_{j=1}^{i} K_j \cdot (t-j+1)
$$

Sumiranjem svih doprinosa dobijamo:
$$
a_0(T) = a_0(0) + \sum_{i=1}^{N} a_i(0) \cdot d_i = a_0(0) + \sum_{i=1}^{N} a_i(0) \cdot \prod_{j=1}^{i} K_j \cdot (T-j+1)
$$

Na osnovu ovog izraza možemo odrediti $a_0(T)$ u složenosti $O(N)$.

## Glavno rešenje:

Primetimo da se zadata rekurentna veza može zapisati kao:

$$
a_i(t+1)=C \cdot a_i(t)+(i+1) \cdot K_{i+1} \cdot a_{i+1}(t)= C \cdot (a_i(t)+(i+1) \cdot \frac{K_{i+1}}{C} \cdot a_{i+1}(t))
$$

U matričnom obliku ova rekurentna veza može se zapisati kao kompozicija dve linearne transformacije na sledeći način:

$$
A(t+1)=C \cdot I \cdot K' \cdot A(t)
$$ 

gde je

$$
A(t) = [a_0(t), a_1(t), ..., a_n(t)]^T
$$

$$
K_{i,i} = 1 \text{  ,  } K_{i,i+1} = (i+1) \cdot \frac{K_{i+1}}{C}
$$

$$
K_{ij}=0 \text{  za  } (j!=i) \wedge (j!=i+1)
$$

i matrica $I$ je jedinična matrica.

Odavde se dobija sledeća jednakost:

$$
A(t)=C^t \cdot K'^{t} \cdot A(0)
$$

Pošto je matrica $K'$ ista kao u slučaju kada je $C=1$ možemo zaključiti da je doprinos $i$-te fabrike:

$$
d_i = C^t \prod_{j=1}^{i} \frac{K_j}{C} \cdot (t-j+1) = C^{t-i} \cdot \prod_{j=1}^{i} K_j \cdot (t-j+1)
$$

Sumiranjem svih doprinosa dobijamo:

$$
a_0(T) = a_0(0) + \sum_{i=1}^{N} a_i(0) \cdot d_i = a_0(0) + \sum_{i=1}^{N} a_i(0) \cdot C^{T-i} \cdot \prod_{j=1}^{i} K_j \cdot (T-j+1)
$$

Na osnovu ovog izraza možemo odrediti $a_0(T)$ u složenosti $O(N)$.

``` cpp title="06_adventure_communist.cpp" linenums="1"
#include <bits/stdc++.h>
 
using namespace std;
 
const int maxN = 1000005;
const int mod = 1000000007;
 
int n, t;
long long a[maxN], k[maxN], c, powC[maxN];
 
long long modPow(long long a, long long p) {
	if (p == 0) return 1;
 
	long long ans, tmp = modPow(a, p / 2);
	ans = tmp * tmp;
	ans %= mod;
 
	if (p % 2) {
		ans *= a;
		ans %= mod;
	}
 
	return ans%mod;
}
 
long long solve() {
	long long p = 1, ans = (a[0] * modPow(c,t))%mod;
 
	powC[0]=modPow(c,t-n+1);
 
	for(int i=1;i<n;i++){
		powC[i]=powC[i-1]*c;
		powC[i]%=mod;
	}
 
	ans = (a[0] * powC[n-1])%mod;
 
	for (int i = 1; i < n; i++) {
		p *= k[i];
		p %= mod;
		p *= (t - i + 1);
		p %= mod;
 
		long long tmp = a[i] * p;
		tmp %= mod;
 
		tmp *= powC[n-1-i];
		tmp %= mod;
 
		ans += tmp;
		ans %= mod;
	}
 
	if (ans < 0) ans += mod;
	return ans;
}
 
long long solveBrute() {
 
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < n - 1; j++) {
			long long tmp = a[j + 1] * k[j + 1];
			tmp %= mod;
			tmp *= (j + 1);
			tmp %= mod;
			tmp += c * a[j];
			tmp %= mod;
			a[j] = tmp;
		}
		a[n - 1] *= c;
		a[n - 1] %= mod;
	}
 
	if (a[0] < 0) a[0] += mod;
	return a[0];
}
 
int main()
{
    std::ios_base::sync_with_stdio(false);
    cin>>n>>t>>c;
 
    for(int i=0;i<n;i++) cin>>a[i];
 
    for(int i=0;i<n;i++) cin>>k[i];
 
    cout<<solve()<<endl;
    return 0;
}
```
