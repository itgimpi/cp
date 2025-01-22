---
hide:
  - toc
---

# 5 - Vrednost dodele

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1600ms | 1024MB |

Maca Jaca ima za vas sledeći zadatak: Daće vam brojeve $N, M$ a zatim niz $B = [B_1, B_2, \ldots, B_M]$, za svaki element važi $1 \leq B_i \leq M$ (vrednosti brojeva mogu da se ponavljaju). Vaš zadatak je da formirate niz $A = [1, 2, \ldots, N]$ (niz se indeksira od $1$), a da zatim, za svako $i$ iz niza $[0, 1, \ldots, N-M]$ (u rastućem redosledu) uradite sledeću operaciju:
```
for (int j=1; j<=M; j++)
  A[i + B[j]] = A[i + j]
```
Drugim rečima, da za svako $j$ počev od $1$ do $M$ (u rastućem redosledu), vrednost u $A_{i+j}$ upišete u element $A_{i + B_j}$. Za kraj, Jaca će vam dati ceo broj $C$. Vaš zadatak je da izračunate vrednost $X = \sum_{i=1}^{N}(C^i \times A_i)$ po modulu $998244353$ nakon svih operacija.

## Opis ulaza

U prvoj liniji standardnog ulaza nalaze se dva prirodna broja $N$ i $M$. U narednom redu se nalaze brojevi $B_1, B_2, \ldots, B_M$, odvojeni razmakom. U naredom redu nalazi se jedan ceo broj $C$.

## Opis izlaza

U jedinu liniju standardnog izlaza ispišite traženi broj $X$ ($0 \leq X < 998244353$).

## Primer 1

### Ulaz

~~~
14 6
6 4 3 3 2 1
-1
~~~

### Izlaz

~~~
16
~~~

### Objašnjenje primera

Niz $A$ će nakon svih operacija izgledati ovako:
~~~
1 5 1 5 1 5 1 5 1 5 2 2 5 1
~~~

### Ograničenja

U svim test primerima važi: $M \leq N, -10^9 \leq C \leq 10^9$

* U test primerima vrednim 10 poena: $N, M \leq 10000$.
* U test primerima vrednim 60 poena: $N \leq 500.000, M \leq 100.000$.
* U test primerima vrednim 30 poena: $N \leq 20.000.000, M \leq 100.000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Nikola Spasić | Nikola Spasić | Aleksa Milisavljević |


Označimo skup $\{1, 2, \ldots, N\}$ sa $[[N]]$.
Posmatrajmo dodele vrednosti za $i = 0$ i definišimo dve funkcije 

* $f : [[N]] \rightarrow [[N]]$, takva da je $a'_j = f(a_j)$, gde je $a'_j$ vrednost na poziciji $j$ u nizu $A$ nakon izvršavanja dodela vrednosti za $i = 0$ a $a_j$ je ta vrednost pre izvršavanja dodela.
* $g : [[N]] \rightarrow [[N]], g(N) := 1; g(x) := x + 1, x \neq N$ ciklično pomeranje za jedno mesto ulevo.

Sada ćemo operaciju koju treba izvršiti na nizu $A$ (za svako $i \in \{0, 1, \ldots, N-M \}$ i za svako $j \in \{0, 1, \ldots, M-1\}$) označiti sa $z$, gde je $z : [[N]] \rightarrow [[N]]$. Označimo sa $z_i : [[N]] \rightarrow [[N]]$ operaciju na nizu $A$ koja odgovara izvršavanju unutrašnje for-petlje (po $j$) za dato fiksno $i$. Jasno je da važi: $z = z_{N-M} \circ z_{N-M-1} \circ \ldots \circ z_0$. Ključna ideja je to što $z_i$ možemo zapisati u obliku $z_i = g^{-i} \circ f \circ g^i$. Ovo važi zato što preslikavanjem $g^i$ "rotiramo" niz u takvu poziciju da element koji je bio na poziciji $i$ je sada na poziciji $0$. Nakon toga primenjujemo dodelu vrednosti sa $f$ i ponovo rotiramo niz u kontra smeru za $i$ mesta.

Ako zatim proširimo izraz za $z$ i skratimo susedne parove $\ldots g^{i} \circ g^{-(i-1)} \ldots$ ostaje nam $z = g^{-(N-M)} \circ (f \circ g)^{N-M} \circ f$, odnosno, kraće $z = g^{-k} \circ (g \circ f)^k$, gde smo uveli oznaku $k := N-M+1$. Kako se $g^{-k}$ lako računa kao desna rotacija za $k$ mesta, ako uvedemo oznaku $h := g \circ f$ ostaje nam da izračunamo $k$-ti  stepen ove funkcije.

Da bismo za svako $i$ pronašli vrednost $h^k(i)$ konstruišemo graf sa čvorovima $\{1 \ldots N\}$ i usmerenim granama $\{x \rightarrow h(x), x \in [[N]]\}$. Kako je usmeren, konačan i iz svakog čvora izlazi tačno jedna grana, komponente povezanosti (posmatrajući graf kao neusmeren) izgledaju kao ciklusi sa stablima čiji je tačno jedan čvor deo ciklusa (primetiti da kako je moguće da $h(i) = i$ postoji mogućnost da ciklus sadrži samo jedan čvor). Usmerenje grana u ciklusu mora biti takvo da je ciklus i u usmerenom grafu, dok usmerenje grana u stablima mora biti takvo da je ulazni čvor bliži ciklusu od izlaznog.

Obilazeći svaku komponentu povezanosti (posmatrajući graf kao neusmeren) u njoj pronalazimo ciklus za čiji svaki čvor nalazimo $h^k(i)$ kao $c((id(i) + k) \mod d)$ gde je $d$ dužina ciklusa koji sadrži čvor $i$, $idx(x)$ daje redni broj čvora $x$ u ciklusu dok $c(x)$ označava $x$-ti čvor na tom ciklusu. Za "početak" ciklusa možemo izabrati proizvoljan čvor. Zatim _dfs_ obilaskom, kroz stabla povezana sa tim ciklusom, unazad (suprotno usmerenju grana) za svaki čvor $i$ čiji je otac u stablu obilaska $o_i$ računamo $h^k(i)$ ili kao prethodnika čvora $h^k(o_i)$ u ciklusu ukoliko je $i$ na rastojanju od ciklusa manjem od $k$ ili kao sina čvora $h^k(o(i))$ u stablu obilaska u čijem podstablu se nalazi čvor $i$. Ovog sina možemo naći tako što održavamo niz koji odgovara steku čvorova tokom _dfs_-a i uzimanjem $k$-tog prethodnika trenutnog čvora.

Na kraju potrebno je samo izračunati traženu vrednost, znajući vrednosti niza $A$ nakon svih dodela vrednosti.

* Vremenska složenost algoritma $O(n)$
* Prostorna složenost algoritma $O(n)$

``` cpp title="05_vrednost_dodele.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define ldb long double
#define mt make_tuple
const int N=100050;
const int L=25;
const int mod=998244353;
const int inf=1e9+7;
int n,m,b[N],c,sol,bsol;
void input()
{
	scanf("%i %i",&n,&m);
	for(int i=1;i<=m;i++) scanf("%i",&b[i]);
	scanf("%i",&c);
	c%=mod;
	if(c<0) c+=mod;
}
void output()
{
	printf("%i\n",sol);
}
int par[N][L],a[N],mx[N];
void Solve()
{
	for(int i=1;i<=m;i++) a[i]=i;
	for(int j=1;j<=m;j++)
		a[b[j]]=a[j];
	for(int i=1;i<=m;i++) par[i-1][0]=a[i];
	par[m][0]=-1;
	for(int j=1;j<L;j++) for(int i=0;i<=m;i++)
	{
		if(par[i][j-1]==-1) par[i][j]=-1;
		else par[i][j]=par[par[i][j-1]][j-1];
	}
	for(int i=0;i<=m;i++)
	{
		if(par[i][L-1]!=-1) mx[i]=inf;
		else
		{
			mx[i]=0;
			int u=i;
			for(int j=L-1;~j;j--) if(par[u][j]!=-1) u=par[u][j],mx[i]+=1<<j;
			mx[i]++;
		}
	}
	sol=0;
	int mul=c;
	int zero=0;
	for(int i=1;i<=n;i++)
	{
		int pos;
		if(zero!=-1) zero=par[zero][0];
		if(i+m>n)
		{
			int po=n-m+1;
			pos=i-(n-m+1);
			if(mx[pos]>po)
			{
				for(int k=0;k<L;k++) if((po>>k)&1) pos=par[pos][k];
			}
			else
			{
				pos=po-mx[pos]+m+1;
			}
		}
		else
		{
			int po=i;
			pos=0;
			if(mx[pos]>po)
			{
				pos=zero;
				//for(int k=0;k<L;k++) if((po>>k)&1) pos=par[pos][k];
			}
			else
			{
				pos=po-mx[pos]+m+1;
			}
		}
		sol+=(ll)mul*pos%mod;
		if(sol>=mod) sol-=mod;
		mul=(ll)mul*c%mod;
		//printf("%i ",pos);
	}
	//printf("\n");
}
void Run()
{
	input();
	Solve();
	output();
}

int main()
{
	Run();
	return 0;
}
```
