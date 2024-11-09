---
hide:
  - toc
---

# 5 - Min max plus

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 3000ms | 256MB |


Dat je niz od $N$ funkcija $F_1(x), F_2(x), \dots, F_N(x)$. Ove funkcije su opisane pomoću dva niza $T_1, T_2, \dots, T_N$ i $K_1, K_2, \dots, K_N$ od po $N$ celih brojeva.

- $F_i(x) = \left\{\begin{array}{lr}min(x, K_i) , & T_i = 1\\ max(x, K_i), & T_i = 2\\ x + K_i, & T_i = 3 \end{array}\right\}$

Potrebno je odgovoriti na $Q$ upita, gde je $i$-ti upit opisan sa brojevima $L_i$, $R_i$ i $X0_i$. Odgovor na upit je: 

- $F_{L_i}(X0_i) + F_{L_i + 1}(F_{L_i}(X0_i)) + \dots + F_{R_i}(F_{R_i - 1}(\dots F_{L_i + 1}(F_{L_i}(X0_i)) \dots))$


## Opis ulaza

U prvom redu standardnog ulaza nalazi se broj $N$.
U drugom redu standardnog ulaza nalazi se $N$ celih brojeva, $i$-ti od njih je $T_i$.
U trećem redu standardnog ulaza nalazi se $N$ celih brojeva, $i$-ti od njih je $K_i$.
U četvrtom redu standardnog ulaza nalazi se broj $Q$.
U narednih $Q$ redova nalazi se po 3 cela broja, u $i$-tom brojevi $L_i$, $R_i$ i $X0_i$.

## Opis izlaza

Na standardni izlaz ispisati odgovore na upite, u zasebnim redovima.

## Primer 1
### Ulaz
```
5
3 3 2 1 3
3 8 -7 -6 -6
2
1 1 4
1 4 -5
```

### Izlaz
```
7
4
```

### Objašnjenje

- $F_1(x) = x + 3$
- $F_2(x) = x + 8$
- $F_3(x) = max(x, -7)$
- $F_4(x) = min(x, -6)$
- $F_5(x) = x - 6$
- Za prvi upit: $F_1(4) = 7$
- Za drugi upit: 
- $F_1(-5) + F_2(F_1(-5)) + F_3(F_2(F_1(-5))) + F_4(F_3(F_2(F_1(-5)))) =$ 
- $-2 + F_2(-2) + F_3(F_2(-2)) + F_4(F_3(F_2(-2))) =$ 
- $-2 + 6 + F_3(6) + F_4(F_3(6)) =$ 
- $-2 + 6 + 6 + F_4(6) = -2 + 6 + 6 -6 = 4$

## Primer 2
### Ulaz
```
10
1 1 2 2 1 2 3 2 1 3
0 10 -7 -15 -13 -7 -4 4 12 -15
6
9 9 11
1 9 -7
7 7 -20
1 8 6
9 10 -2
9 10 -13
```

### Izlaz
```
11
-51
-24
-27
-19
-41
```

## Ograničenja

- $1 \leq N, Q \leq 2 \times 10^{5}$
- $0 \leq |K_i| \leq 10^{9}$ za $T_i \in \{ 1, 2 \}$
- $0 \leq |K_i| \leq 10^{6}$ za $T_i = 3$
- $1 \leq L_i \leq R_i \leq N$
- $0 \leq |X0_i| \leq 10^{9}$

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 8 poena: $N, Q \leq 10^{3}$.
- U testovima vrednim 20 poena: $T_i = 3$ za sve $1 \leq i \leq N$.
- U testovima vrednim 20 poena: $T_i = 1$ za sve $1 \leq i \leq N$.
- U testovima vrednim 24 poena: $N, Q \leq 4 \times 10^{4}$.
- U testovima vrednim 28 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Tadija Šebez | - | Tadija Šebez |



``` cpp title="05_min_max_plus.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long
const ll inf=2e18;
const int N=200050;
const int M=2*N;
int root,tsz,ls[M],rs[M],x[N],tme;
ll mn[M],smn[M],mx[M],smx[M],lzy_bot[M],lzy_top[M],lzy_add[M];
ll lzy_D_bot[M],lzy_D_top[M],lzy_D_add[M];
void pull(int c){
	if(mn[ls[c]]<mn[rs[c]]){
		mn[c]=mn[ls[c]];
		smn[c]=min(smn[ls[c]],mn[rs[c]]);
	}else if(mn[ls[c]]>mn[rs[c]]){
		mn[c]=mn[rs[c]];
		smn[c]=min(mn[ls[c]],smn[rs[c]]);
	}else{
		mn[c]=mn[ls[c]];
		smn[c]=min(smn[ls[c]],smn[rs[c]]);
	}
	if(mx[ls[c]]>mx[rs[c]]){
		mx[c]=mx[ls[c]];
		smx[c]=max(smx[ls[c]],mx[rs[c]]);
	}else if(mx[ls[c]]<mx[rs[c]]){
		mx[c]=mx[rs[c]];
		smx[c]=max(mx[ls[c]],smx[rs[c]]);
	}else{
		mx[c]=mx[ls[c]];
		smx[c]=max(smx[ls[c]],smx[rs[c]]);
	}
}
void Build(int&c,int ss,int se){
	c=++tsz;
	lzy_bot[c]=-inf;
	lzy_top[c]=inf;
	if(ss==se){
		mn[c]=mx[c]=x[ss];
		smn[c]=inf;
		smx[c]=-inf;
		return;
	}
	int mid=ss+se>>1;
	Build(ls[c],ss,mid);
	Build(rs[c],mid+1,se);
	pull(c);
}
void upd(int c,ll bot,ll top,ll add,ll D_bot,ll D_top,ll D_add){
	mn[c]+=add;
	smn[c]+=add;
	mx[c]+=add;
	smx[c]+=add;
	lzy_bot[c]+=add;
	lzy_top[c]+=add;
	lzy_add[c]+=add;
	lzy_D_add[c]+=D_add;
	if(mn[c]==mx[c]){
		if(mn[c]<bot){
			lzy_add[c]+=bot-mn[c];
			lzy_D_add[c]+=D_bot;
			mn[c]=mx[c]=bot;
		}
		if(mx[c]>top){
			lzy_add[c]+=top-mx[c];
			lzy_D_add[c]+=D_top;
			mn[c]=mx[c]=top;
		}
	}else{
		if(mn[c]<bot){
			if(mx[c]==smn[c]){
				smx[c]=bot;
			}
			mn[c]=bot;
			lzy_bot[c]=bot;
			lzy_D_bot[c]+=D_bot;
		}
		if(mx[c]>top){
			if(mx[c]==smn[c]){
				smn[c]=top;
			}
			mx[c]=top;
			lzy_top[c]=top;
			lzy_D_top[c]+=D_top;
		}
	}
}
void push(int c){
	if(lzy_bot[c]!=-inf||lzy_top[c]!=inf||lzy_add[c]!=0||lzy_D_add[c]!=0){
		upd(ls[c],lzy_bot[c],lzy_top[c],lzy_add[c],lzy_D_bot[c],lzy_D_top[c],lzy_D_add[c]);
		upd(rs[c],lzy_bot[c],lzy_top[c],lzy_add[c],lzy_D_bot[c],lzy_D_top[c],lzy_D_add[c]);
		lzy_bot[c]=-inf;
		lzy_top[c]=inf;
		lzy_add[c]=0;
		lzy_D_bot[c]=0;
		lzy_D_top[c]=0;
		lzy_D_add[c]=0;
	}
}
void Min(int c,int ss,int se,int qs,int qe,int k){
	if(qs>qe||qs>se||ss>qe||k>=mx[c])return;
	if(qs<=ss&&qe>=se&&k>smx[c]){
		upd(c,-inf,k,0,0,(ll)(mx[c]-k)*(tme-1),0);
		return;
	}
	int mid=ss+se>>1;
	push(c);
	Min(ls[c],ss,mid,qs,qe,k);
	Min(rs[c],mid+1,se,qs,qe,k);
	pull(c);
}
void Max(int c,int ss,int se,int qs,int qe,int k){
	if(qs>qe||qs>se||ss>qe||mn[c]>=k)return;
	if(qs<=ss&&qe>=se&&smn[c]>k){
		upd(c,k,inf,0,(ll)(mn[c]-k)*(tme-1),0,0);
		return;
	}
	int mid=ss+se>>1;
	push(c);
	Max(ls[c],ss,mid,qs,qe,k);
	Max(rs[c],mid+1,se,qs,qe,k);
	pull(c);
}
void Add(int c,int ss,int se,int qs,int qe,int k){
	if(qs>qe||qs>se||ss>qe)return;
	if(qs<=ss&&qe>=se){
		upd(c,-inf,inf,k,0,0,(ll)-k*(tme-1));
		return;
	}
	int mid=ss+se>>1;
	push(c);
	Add(ls[c],ss,mid,qs,qe,k);
	Add(rs[c],mid+1,se,qs,qe,k);
	pull(c);
}
pair<ll,ll> Get(int c,int ss,int se,int qi){
	if(ss==se)return {mx[c],lzy_D_add[c]+lzy_D_bot[c]+lzy_D_top[c]};
	int mid=ss+se>>1;
	push(c);
	if(qi<=mid)return Get(ls[c],ss,mid,qi);
	else return Get(rs[c],mid+1,se,qi);
}
int qrd[N],iqrd[N],l[N],r[N],x0[N],t[N],k[N];
vector<int> Qs[N];
ll ans[N];
int main(){
	int n;
	scanf("%i",&n);
	for(int i=1;i<=n;i++)scanf("%i",&t[i]);
	for(int i=1;i<=n;i++)scanf("%i",&k[i]);
	int q;
	scanf("%i",&q);
	for(int i=1;i<=q;i++){
		scanf("%i %i %i",&l[i],&r[i],&x0[i]);
		qrd[i]=i;
		Qs[r[i]].pb(i);
	}
	sort(qrd+1,qrd+1+q,[&](int i,int j){return l[i]<l[j];});
	for(int i=1;i<=q;i++)x[i]=x0[qrd[i]],iqrd[qrd[i]]=i;
	Build(root,1,q);
	int ptr=0;
	for(int i=1;i<=n;i++){
		while(ptr<q&&l[qrd[ptr+1]]<=i)ptr++;
		tme++;
		if(t[i]==1)Min(root,1,q,1,ptr,k[i]);
		else if(t[i]==2)Max(root,1,q,1,ptr,k[i]);
		else Add(root,1,q,1,ptr,k[i]);
		for(int qi:Qs[i]){
			ll val,D;
			tie(val,D)=Get(root,1,q,iqrd[qi]);
			ans[qi]=D+tme*val-(ll)(l[qi]-1)*x0[qi];
		}
	}
	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
	return 0;
}

```
