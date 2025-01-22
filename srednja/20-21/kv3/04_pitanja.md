---
hide:
  - toc
---

# 4 - Pitanja

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 1024MB |

Poznato je da profesori programiranja ne vole da odgovaraju na pitanja studentima. Oni od svojih studenata očekuju da sami naprave razumnu pretpostavku o svemu što nije jasno definisano u zadatku koji su dobili, pa su zato odlučili da odgovore samo na ona pitanja studenata koja pristignu onim danima kada za to budu imali vremena.

Profesori su zbog toga odlučili da oslobode svoj raspored svakog $k$-tog dana počev od dana $x$ pa sve do dana $y$. Da bi izabrali ove brojeve potrebno je da za $Q$ upita oblika $x$, $y$ i $k$ odrede na koliko pitanja treba odgovoriti u tom slučaju. Pošto su zbog previše posla profesori zaboravili koliko dana ima u godini ovi brojevi mogu biti jako veliki.

Zbog toga su ovaj zadatak ostavili vama kako bi imali dovoljno vremena da odgovore na pitanja studenata.

## Opis ulaza
U prvoj liniji ulaza nalazi se broj $N$ - broj dana kada studenti mogu postavljati pitanja. U drugoj liniji nalazi se $N$ celih brojeva, niz $A_{1},A_{2},\ldots,A_{N}$ - očekivani broj pitanja svakog dana. U trećoj liniji nalazi se ceo broj $Q$ - broj upita na koje treba odgovoriti. U narednih $Q$ linija slede brojevi $x_{i}$, $y_{i}$ i $k_{i}$ - granice intervala i korak tog upita, (pri čemu $k_{i}$ uvek deli $y_{i}-x_{i}$).

## Opis izlaza
Na standardni izlaz ispisati $Q$ celih brojeva - za svaki upit, u novom
redu, ispisati ukupan broj pitnja na koje će biti odgovoreno.

## Ograničenja
-   $1 \leq N \leq 200000$
-   $1 \leq Q \leq 200000$
-   $1 \leq A_{i} \leq 5*10^{10}$
-   $1 \leq k_{i} \leq N$
-   $1 \leq x_{i} \leq y_{i} \leq N$
-   $k_{i}$ deli $y_{i}-x_{i}$

Test primeri su podeljeni u $4$ disjunktne grupe:

-   U test primerima vrednim $8$ poena: $A_{i}=i$
-   U test primerima vrednim $12$ poena: $A_{i}=i^2$
-   U test primerima vrednim $20$ poena: $N,Q \leq 10000$
-   U test primerima vrednim $60$ poena: Bez dodatnih ograničenja

## Primeri
### Primer 1
#### Ulaz
```
6
17 31 14 23 9 27
5
2 6 2
2 5 3
3 5 1
3 3 5
1 3 2
```

#### Izlaz
```
81
40
46
14
31
```

#### Objašnjenje
$A_2 + A_4 + A_6 = 81$
$A_2 + A_5 = 40$
$A_ 3 + A_4 + A_5 = 46$
$A_3 = 14$
$A_1 + A_3 = 31$

### Primer 2
#### Ulaz
```
10
1 2 3 4 5 6 7 8 9 10
5
2 8 3
4 9 1
1 9 2
5 10 5
1 9 8
```

#### Izlaz
```
15
39
25
15
10
```

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Igor Pavlović | Igor Pavlović | Aleksa Plavšić | Aleksandar Zlateski |

Definišimo sa $d_i = \frac{y_i - x_i}{k_i} + 1$. U $i$-tom upitu je potrebno izračunati sumu tačno $d_i$ brojeva.

## Prvi podzadatak
Kao pomoć potrebno je koristiti formulu za sumu prvih $n$ prirodnih brojeva $\sum_{i=1}^{n} i= \frac{n\cdot(n+1)}{2}$

Rešenje za $i$-ti upit možemo zapisati u oblikz $\sum_{j = 0}^{d_i -1} (x_i + j \cdot k_i) = \sum_{j = 0}^{d_i-1} x_i + k_i \cdot \sum_{j = 0}^{d_i-1} j = 
d_i \cdot x_i + k_i \cdot \frac{(d_i - 1)\cdot d_i}{2}$. Poslednje napisanu formulu možemo izračunati u vremenskoj i memorijskoj složenosti $O(1)$ po upitu.

## Drugi podzadatak
Pored formule iz prvog podzadatka potrebno je iskoristiti formulu za sumu prvih $n$ kvadrata prirodnih brojeva  $\sum_{i=1}^{n} i^2= \frac{n \cdot(n+1) \cdot(2n+1)}{6}$

Na sličan način možemo rešiti i drugi podzadatak, uz malo veću manipulaciju sa matematičkim formulama. Tako da rešenje možemo predstaviti u obliku $\sum_{j = 0}^{d_i -1} (x_i + j\cdot k_i)^2 = \sum_{j = 0}^{d_i -1} (x_i^2 + 2\cdot x_i \cdot k_i \cdot j + (j\cdot k_i)^2) = \sum_{j = 0}^{d_i -1} x_i^2 + 2\cdot x_i \cdot k_i \cdot \sum_{j = 0}^{d_i -1} j + k_i^2 \cdot \sum_{j = 0}^{d_i -1} j^2 = d_i \cdot x_i^2 + 2 \cdot x_i \cdot k_i \cdot \frac{d_i\cdot (d_i - 1)}{2} + k_i^2 \cdot \frac{(d_i -1)\cdot d_i \cdot (2 \cdot d_i - 1)}{6}$. Slično kao i u prvom podzadatku, navedeni izraz možemo izračunati u vremenskoj i memorijskoj složenosti $O(1)$ po upitu.

## Treći podzadatak:
U $i$-tom upitu možemo proći kroz svih $d_i$ brojeva i izračunati njihovu sumu. U najgorem slučaju za naš program potrebno je $N$ iteracija po upitu (na primer $x_i=1, y_i=N, k_i=1$). Vremenska složenost opisanog algoritma je $O(NQ)$.

## Četvrti podzadatak:
Algoritam opisan u trećem podzadatku je efiksan za upite čija je vrednost $d_i$ relativno mala. Postavićemo granicu $B$, i svaki upit za koji važi $d_i \leq B$ obradićemo kao i u trećem podzadatku. U slučaju $d_i > B$, vrednost broja $k$ ne može biti veća od $\frac{N}{B}$. Napravićemo matricu $D$ dimenzije $\frac{N}{B} \times N$, gde vrednost $D[i][j]$ predstavlja $\sum A_x$ tako da važi $x \mod i = j \mod i$ i $x\leq j$. Opisanu matricu možemo izračunati u vremenskoj složenosti $O(\frac{N^2}{B})$, slično postupku preračunavanja prefiksnih suma. Kada izračunamo matricu $D$ odgovor na upit $(x_i, y_i, k_i)$, za koji važi $d_i > B$ možemo dobiti kao $D[k_i][y_i] - D[k_i][x_i] + A_{x_i}$ y vremenskoj složenosti $O(1)$. Konačan algoritam koji kombinuje prethodna dva u zavisnosti od vrednosti $d_i$ ima vremensku složenost $O(\frac{N^2}{B} + Q \cdot B)$ i memorijsku $O(\frac{N^2}{B})$. Ako konstantu $B$ postavimo na vrednost $B$~$\sqrt N$ dobili smo algoritam vremenske složenosti $O(N \sqrt N + Q \sqrt N)$ i memorijske $O(N\sqrt N)$.

Primetiti da memorijsku složenost algoritma možemo poboljšati ako upite za koje važi $d_i > B$ obrađujemo u grupama po istoj vrednosti $k_i$ (npr. prvo obradimo sve upite za koje važi $k_i = 1$, zatim $k_i = 2$ itd). U ovom slučaju je dovoljno pamtiti samo jedan niz $D$ koji bi se nakon svake grupe jednakih resetovao na $0$. Postoje i mnogi drugi načini optimizacije memorije na linearnu, međutim to se ne zahteva za maksimalan broj bodova u zadatku.


``` cpp title="04_pitanja.cpp" linenums="1"
#include <bits/stdc++.h>
#define maxN 200005
#define maxQ 200005

using namespace std;

struct upit{
long long x,y,k,id;
};

upit u[maxQ],tmp;
long long n,q,i,a[maxN],x,y,k,s[maxN],ans[maxQ];
vector<int> v;

bool poredi(upit a,upit b){
return a.k<b.k;
}

void resetuj(){
for(int i=0;i<v.size();i++) s[v[i]]=-1;
v.clear();
}

long long resi(int x,int k){
if(s[x]!=-1) return s[x];
v.push_back(x);
if(x<k) s[x]=a[x];
else s[x]=a[x]+resi(x-k,k);
return s[x];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    //ifstream fin("27.in.txt");
    //ofstream fout("27.out.txt");
    cin>>n;
    for(i=0;i<n;i++) cin>>a[i];
    cin>>q;
    for(i=0;i<q;i++){
        cin>>x>>y>>k;
        tmp.x=x-1;
        tmp.y=y-1;
        tmp.k=k;
        tmp.id=i;
        u[i]=tmp;
    }
    for(i=0;i<n;i++) s[i]=-1;
    sort(u,u+q,poredi);
    for(i=0;i<q;i++){
        if(i!=0 && u[i].k!=u[i-1].k) resetuj();
        ans[u[i].id]=resi(u[i].y,u[i].k)-resi(u[i].x,u[i].k)+a[u[i].x];
    }
    for(i=0;i<q-1;i++) cout<<ans[i]<<"\n";
    cout<<ans[q-1];
    return 0;
}

```
