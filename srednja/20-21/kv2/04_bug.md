---
hide:
  - toc
---

# 4 - BUG

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Posle velikog uspeha igre _JAG™_, kompanija "Najbolji ltd." je napravila još bolji nastavak, _BUG™_.

U ovoj učestvuje $10^9 + 7$ igrača i pobednik se odlučuje slučajnim izborom. Da bi izbor bio slučajan, kompanija je postavila stroga pravila za biranje tog igrača. Prvo numerišu igrače sa identifikacionim brojevima od $0$ do $10^9+6$. Zatim izaberu niz $A$ sa $N$ elemenata i broj $k$. Potom definišu pobednika kao igrača koji ima identifikacioni broj $f(A,k) \mod (10^9 + 7)$, gde je:

* $f(T,k) = \sum_{i=1}^{i \leq len(T)} T_i$, za $k=0$, gde je $len(T)$ dužina niza $T$.
* $f(T,k) = \sum_{i=1}^{i \leq len(T)} \sum_{j=i}^{j\leq len(T)} f(T[i...j],k-1)$ za $k>0$, gde je $len(T)$ dužina niza $T$ i $T[i...j]$ podniz niza $T$ sa elementima od $i$-te do $j$-te pozicije, tj. niz sa elementima $T_i, T_{i+1}, ..., T_{j-1}, T_{j}$.

Pomozite kompaniji "Najbolji ltd." i odredite pobednika igre.

## Opis ulaza
U prvom redu nalaze se brojevi $N$, dužina niza $A$ i $k$. U narednom redu nalazi se $N$ brojeva, elementi niza $A$. 

## Opis izlaza
U jedinom redu standardnog izlaza ispisati jednu vrednost, pobednika igre, tj. vrednost $f(A,k) \mod (10^9 + 7)$.


## Ograničenja
* $1 \leq N \leq 2 \cdot 10^{5}$.
* $0 \leq k \leq 2 \cdot 10^{5}$.
* $0 \leq A_i \leq 10^9$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 10 poena: $N \leq 10^3$, $k=1$.
* U test primerima vrednim 15 poena: $N \leq 5$, $k \leq 5$.
* U test primerima vrednim 25 poena: $N \leq 300$, $k \leq 300$.
* U test primerima vrednim 40 poena: $N \leq 2000$, $k \leq 2000$.
* U test primerima vrednim 10 poena: Nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
5 0
1 6 3 4 7
```

#### Izlaz
```
21
```

#### Objašnjenje
$f(A,k) = f([1,6,3,4,7],0) = 1 + 6 + 3 + 4 + 7 = 21$, pa je $f(A,k) \mod (10^9 + 7) = 21$

### Primer 2
#### Ulaz
```
5 1
1 6 3 4 7
```

#### Izlaz
```
147
```

#### Objašnjenje
$$
f(A,k) = f([1,6,3,4,7],1) = f([1],0) + f([1,6],0) + f([1,6,3],0) + f([1,6,3,4],0) + f([1,6,3,4,7],0) + f([6],0) + f([6,3],0) + f([6,3,4],0) + f([6,3,4,7],0) + f([3],0) + f([3,4],0) + f([3,4,7],0) + f([4],0) + f([4,7],0) + f([7],0) = 1 + 1 + 6 + 1 + 6 + 3 + 1 + 6 + 3 + 4 + 1 + 6 + 3 + 4 + 7 + 6 + 6 + 3 + 6 + 3 + 4 + 6 + 3 + 4 + 7 + 3 + 3 + 4 + 3 + 4 + 7 + 4 + 4 + 7 + 7 = 147,
$$

pa je 

$$
f(A,k) \mod (10^9 + 7) =147
$$

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Aleksa Milisavljević | Vladimir Milenković | Vladimir Milenković |

## Prvi potproblem
Ovaj potproblem nas pita da nađemo zbir zbirova svakog podniza niza $A$, što možemo uraditi iteriranjem po svakom podnizu, računajući zbir koristeći niz prefiksnih suma. Složenost ovog algoritma je $\mathcal{O}(N^2)$, što je dovoljno dobro.

## Drugi potproblem
Čistom simulacijom izračunavanja funkcije $f$, na način opisan u tekstu zadatka, možemo u eksponencijalnom vremenu uraditi ovaj potproblem.

## Ostali potproblemi
Možemo lako uočiti da će vrednost funkcije $f(A, k)$ biti jednako izrazu $\sum_{i=1}^{n} c_i \cdot A_i$ za neki niz koeficijenata $c$ -- hajde da vidimo koliki su ti koeficijenti. Koeficijent uz $A_i$ će biti jednak broju finalnih podnizova u kojima se pojavljuje taj element. 

Skup svih podniza čiji će se zbirovi sabirati u fazama kada je $k = 0$ u kojima se sadrži element $A_i$ je u bijekciji sa skupom parova nizova $l$ i $r$ od $k$ elemenata, za koje važi $1 \leq l_1 \leq l_2 \leq \dots \leq l_k \leq i \leq r_k \leq r_{k-1} \leq \dots \leq r_1 \leq n$. Ovo lako možemo proveriti tako što posmatramo da je taj podniz u prvoj fazi bio podniz niza $A[1..n] = A$, u drugoj podniz niza $A[l_1 .. r_1]$, itd. Takođe, primetimo da su nizovi $l$ i $r$ na neki način nezavisni, broj ovakvih parova nizova $(l, r)$ je jednak proizvodu broja adekvatnih $l$ i $r$ nizova.

Treba da izračunamo koliko ovakvih podnizova postoji (simetrično računamo za $l$ i $r$ nizove). Računajući za $l$ nizove prvo, uvođenjem $d_i = l_i - l_{i-1}$ (uz $l_0 = 1$), možemo videti da nizova $l$ ima koliko i rešenja jednačine $d_1 + d_2 + \cdots + d_k = i - 1$ (gde $d_i \geq 0$), čiji je broj rešenja ${k + i - 1 \choose k}$. 

Koristeći sličnu analizu za broj nizova $r$, dobijamo da je $c_i = {k + i - 1 \choose k} \cdot {k + n - i \choose k}$. Sve što nam ostaje je da izračunamo ove binomne koeficijente.

## Podzadaci 3 i 4
Sve binomne koeficijente možemo izračunati koristeći Paskalov trougao, i ukupna vremenska složenost je $O(N^2)$.

## Podzadatak 5
Ovde moramo koristiti brži način izračunavanja binomnih koeficijenata, koristeći segmentno stablo nad prostim činiocima. Alternativno, možemo prekalkulisati faktorijele i računati binomne koeficijente deljenjem, koristeći modularni inverz.

``` cpp title="04_bug.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 500000
using namespace std;
long long mod=1000000007;
inline long long step(long long a,long long b) {
    if(b==0ll) return 1ll;
    if(b&1ll) return (a*step(a,b-1ll))%mod;
    else return step((a*a)%mod,b>>1ll);
}
int lp[maxn];
long long seg[4*maxn];
inline void set_seg(int id,int l,int r) {
    seg[id]=1;
    if(l==r) return;
    int m=(l+r)/2;
    set_seg(id*2+1,l,m);
    set_seg(id*2+2,m+1,r);
}
int pos[maxn];
inline void update_seg(int id,int l,int r,int p) {
    if(l==r) {
        seg[id]=step(p,pos[p]);
        return;
    }
    int m=(l+r)/2;
    if(p<=m) update_seg(id*2+1,l,m,p);
    else update_seg(id*2+2,m+1,r,p);
    seg[id]=(1ll*seg[id*2+1]*seg[id*2+2]);
    if(seg[id]>=mod) seg[id]%=mod;
}
long long a[maxn];
long long val[maxn];
int n,k;
int main() {
    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++) scanf("%lld",&a[i]);
    set_seg(0,0,maxn-1);
    for(int i=2;i<maxn;i++) {
        if(!lp[i]) {
            lp[i]=i;
            for(long long j=1ll*i*i;j<maxn;j+=i) {
                if(!lp[j] || lp[j]>i) lp[j]=i;
            }
        }
    }
    int nf=0;
    val[0]=1;
    for(int i=1;i<n;i++) {
        int x=k+i;
        int y=i;
        while(x>1) {
            int p=lp[x];
            int c=0;
            while(lp[x]==p) {
                c++;
                x=x/lp[x];
            }
            pos[p]+=c;
            update_seg(0,0,maxn-1,p);
        }
        while(y>1) {
            int p=lp[y];
            int c=0;
            while(lp[y]==p) {
                c++;
                y=y/lp[y];
            }
            pos[p]-=c;
            update_seg(0,0,maxn-1,p);
        }
        val[i]=seg[0];
    }
    long long ans=0;
    for(int i=0;i<n;i++) {
        ans=(ans+((((a[i]*val[i])%mod)*val[n-1-i])%mod))%mod;
    }
    printf("%lld",ans);
    return 0;
}

```
