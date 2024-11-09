---
hide:
  - toc
---

# 4 - Filozof

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |

Mali Stojan od svih predmeta najviše voli filozofiju (zapravo, pre bi
se moglo reći da voli raspravljanje i filozofiranje). Nakon što je
izgubio pola časa na raspravu sa Stojanom, profesor filozofije mu je
postavio sledeći zadatak, u nadi da će ga to okupirati bar na neko
vreme:

Stari grčki filozof Mile iz Talesa je u svojoj bašti gajio
pravougaonike - svakog dana bi posadio jedan. Pravougaonici su
neobične biljke i traju samo $K$ dana, tako da bi Mile svakog dana
takođe uklonio pravougaonik koji je posadio pre $K$ dana. Pošto se
Mile pridržavao starogrčkih načela baštovanstva, sve pravougaonike je
sadio tako da su im stranice paralelne koordinatnim osama.

Da bi ih zaštitio od sunca, Mile je u bašti imao jedan pravougaoni
zaklon, koji je svakog dana pomerao tako da u potpunosti prekriva sve
pravougaonike. Zbog već pomenutih načela, ovaj zaklon je takođe uvek
morao biti paralelan osama i okrenut na istu stranu (nije se smeo
rotirati).

Iz Miletovih beležaka, poznate su pozicije i dimenzije svih
pravougaonika koje je posadio tokom $N$ dana, koliko se ukupno bavio
baštovanstvom. Na Stojanu je sada da pronađe dimenzije najmanjeg
zaklona koji bi uvek mogao da ih zaštiti od sunca. Pomozite mu da
odredi ovo, da bi se što pre vratio raspravljanju i filozofiranju.

## Opis ulaza
Pošto su test primeri potencijalno veoma veliki, da bi se izbeglo
učitavanje celih primera, vaš program treba da generiše primere na
sledeći način:

Na prvom i jedinom redu standardnog ulaza nalazi se šest brojeva:
$N$, $K$, $M$, $A$, $B$ i $S$. Nizovi $X$, $Y$, $XX$
i $YY$, gde $(X_i, Y_i)$ i $(XX_i, YY_i)$ predstavljaju
koordinate donjeg levog, odnosno gornjeg desnog pravougaonika koji je
Mile zasadio i-tog dana, se generišu na sledeći način (u pseudokodu
dole, nizovi su indeksirani od 1):

    for i from 1 to N:
        if i == 1
            X[i] = (A * S + B) mod M
        else
            X[i] = (A * YY[i-1] + B) mod M
        Y[i] = (A * X[i] + B) mod M
        XX[i] = (A * Y[i] + B) mod M
        YY[i] = (A * XX[i] + B) mod M

        if X[i] == XX[i]
            XX[i] = XX[i] + 1
        if X[i] > XX[i]:
            swap(X[i], XX[i])

        if Y[i] == YY[i]
            YY[i] = YY[i] + 1
        if Y[i] > YY[i]
            swap(Y[i], YY[i])

Na primer, za ulaz

    2 3 100000007 19997 31 73

generisane vrednosti su (svaki red odgovara vrednostima $X_i$,
$Y_i$, $XX_i$, $YY_i$ redom):

    1459812 29119072 95455781 91858558
    94042061 29119072 95455781 58962213

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati dva cela broja -
traženu minimalnu širinu i visinu zaklona.

## Primer 1
### Ulaz
```
4 2 13 2 5 2
```

### Izlaz
```
7 9
```

## Primer 2
### Ulaz
```
7 3 37 5 0 3
```

### Izlaz
```
30 32
```

## Objašnjenje primera
Prvi primer odgovara sledećim vrednostima koordinata pravougaonika
(redom $X_i$, $Y_i$, $XX_i$, $YY_i$):

    9 3 12 10
    11 1 12 3
    7 1 11 6
    4 0 5 2

Prvog dana, Mile može da zakloni prvi pravougaonik tako što postavi
zaklon tako da mu je donji levi ugao u $(9,3)$. Drugog dana ga
pomera na $(9,1)$. Trećeg dana, Mile uklanja prvi pravougaonik,
tako da zaklon tada može da stoji na primer u $(7,-2)$. Nakon što
ukloni drugi i doda četvrti pravougaonik, pomera zaklon u $(4,0)$.

## Ograničenja
* $1 \leq N, K$
* $1 \leq M \lt 10^9$
* $0 \leq A, B, S \leq 10^9$

Ograničenja za $M$, $A$, $B$ i $S$ garantuju da će se sve koordinate
nalaziti u intervalu $[0, 10^9]$. Međurezultati pri generisanju ulaza
mogu biti izvan ovog intervala, tako da se preporučuje korišćenje
64-bitnih tipova za njih (long long u C/C++, int64 u Paskalu).

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede 20 poena važi $N, K \leq 1000$
* U test primerima koji vrede 50 poena važi $N, K \leq 10^5$
* U test primerima koji vrede 30 poena važi $N, K \leq 2 * 10^6$

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Slobodan Mitrović | Dimitrije Erdeljan | Dragan Urošević | Slobodan Mitrović |

## Glavno rešenje
Ako sa $x_i$  $y_i$ označimo koordinate donjeg levog temena pravougaonika sa rednim brojem $i$, a sa $xx_i$ i $yy_i$ koordinate gornjeg desnog temena pravougaonika sa rednim brojem $i$, onda će kordinate donjg levog temena obuhvatajućeg pravougaonika nakon dodavanja pravougaonika broj biti $j$ 

$$
xo_j=\min\{x_{j-k+1}, x_{j-k+2},...x_j\}, \quad yo_j=\min\{y_{j-k+1}, y_{j-k+2},...y_j\}.
$$ 

Jasno, koordinate gornjeg desnog temena će biti:

$$
xxo_j=\max\{xx_{j-k+1}, xx_{j-k+2},...xx_j\}, \quad yyo_j=\max\{yy_{j-k+1}, yy_{j-k+2},...yy_j\}.
$$

Ako je $j<k$, onda se formule neznatno menjaju te će koordinate donjeg levog temena biti

$$
xo_j=\min\{x_{1}, x_{2},...x_j\}, \quad yo_j=\min\{y_{1}, y_{2},...y_j\}.
$$

Analogno bi se određivale koordinate gornjeg desnog temena obuhvatajućeg pravougaonika.
Jasno, stranice minimalnog obuhvatajućeg pravougaonika, nakon -tog dana imaju dužine

$$
dx_j = xxo_j - xo_j,\quad dy_j=yyo_j-yo_j,
$$

a dužine stranica minimalnog obuhvatajućeg pravougaonika za kompletan period od dana će biti jednake maksimumima odgovarajućih nizova sa dužinama.

Prema tome, potrebno je samo određivati minimume (ili maksimume) za svakih $k$ uzastopnih elemenata nekog niza (niza sastavljenog od $x$ ili $y$ koordinata temena pravougaonika). Opisaćemo kako određujemo minimume od svakih $k$ uzastopnih elemenata, a slično se određuju maskimumi. 

Svakako se na prvi pogled nameće pravolinijsko rešenje u kome se za svaki podniz od $k$ uzastopnih ponovo  izračunava minimum i to rešenje ima složenost $\Theta(nk)$.

Malo profinjenje ovog pravolinijskog rešenja dobijamo tako što pokušamo da iskoristimo prethodno izračunati minimum. Naime, pretpostavimo da smo završili obradu elementa $x_i$ i već izračunali minimum $xo_i$ podniza od $k$ uzastopnih kome je poslednji element $x_i$. Kada se pomerimo na sledeći element, treba da izračunamo $xo_{i+1}$. Ako je $x_{i+1} \leq xo_{i}$, onda će $xo_{i+1}$ biti jednako baš $x_{i+1}$ ($xo_{i+1}=x_{i+1}$). Ako je pak $x_{i+1} >  xo_{i}$, onda $x_{i+1}$ ne mora biti minimum od $k$ poslednjih uzastopnih. Međutim, ako je $xo_{i}=x_{i-k+1}$, onda je prethodni minimum bio baš jednak elementu koji "ispada" ia bloka uzastopnih i zbog toga treba ponovo izračunati minimum poslednjih $k$.  Složenost ovakvog rešenja zavisi od izgleda ulaznih podataka (tj. od toga koliko često se dešava drugi slučaj), a u najnepovoljnijem slučaju može biti $\Theta(nk)$.

Sledeća varijanta rešenja se dobija tako što se "aktuelni elementi" (tj. poslednjih $k$ obrađenih) čuvaju u min-hip-u. To obezbeđuje da u konstantnom vremenu određujemo minimum od $k$ uzastopnih. Međutim, treba imati u vidu da pri obradi narednog elementa niza, taj element treba dodati u hip i istovremeno element koji ispada iz bloka aktuelnih izbaciti iz hip-a. Složenost ovih operacija je $\Theta(\log_2 k)$ (pošto se u hipu nalazi $k$ elemenata) pa je tako složenost kompletnog rešenja $\Theta(n\log_2 k)$.

Za najefkasnije rešenje zamislimo da smo ceo niz podelili na disjunktne blokove sastavljene od po $k$ uzastopnih: prvi blok čine elementi od prvog do $k$-og, drugi od $k+1$-og do $2k$-og, treći od $2k+1$-og do $3k$-og, itd.  Tada će svaki blok od tačno $k$ uѕastopnih biti sastavljen od delova iz ne više od dva uzastopna bloka: desni kraj jednog bloka (neka je to blok $B_1$) i levi kraj narednog bloka (neka je to blok $B_2$). Minimum tog bloka se može lako izračunati ako su prethodno izračunati minimumi za odgovarajuće delove iz blokova $B_1$ i $B_2$ (kao manji od ta dva minimuma). Minimumi svih ovih delova se mogu jednostavno izračunati sa dva prolaza kroz niz: jedan prolaz za računanje minimuma levih krajeva i jedan prolaz za računanje minimuma desnih krajeva.

Prikažimo još jedan postupak za određivanje minimuma za svakih $k$ uzastopnih. Element $x_i$  je kandidat za najmanji element podnizova (od $k$ uzastopnih) koji se završavaju na pozicijama $i, i+1, ..., i+k-1$. Međutim, ako za $x_j$ ($i<j$) važi da je $x_j<x_i$, onda $x_i$ prestaje biti kandidat za minimum podnizova koji se završavaju na pozicijama $j, j+1, ..., i+k-1$ (znači može se eliminisati iz razmatranja).  Možemo posmatrati i obratno: nakon uključivanja elementa $x_j$, svi elementi ubačeni pre $x_j$ koji imaju osobinu da su veći (ili jednaki) od $x_j$ ne mogu biti više kandidati za minimum od $k$ uzastopnih (bez obzira što se nalaze u bloku od $k$ poslednjih uzastopnih).  Zbog toga se mogu izbaciti iz razmatranja svi elemente niza $x$ koji imaju osobinu da su veći (ili jednaki) od $x_j$. Primetimo da se taj element ($x_j$) dodaje na kraj liste kandidata (kao poslednji kandidat), zato što je on poslednji dodati i u jednom trenutku svi pre njega dodati će biti izbačeni te on ima šanse da bude najmanji u podnizu od poslednjih $k$ nakon izbacivanja tih prethodnih. Element koji se nalazi na početku liste kandidata jeste baš najmanji za naredni blok uzastopnih. Ali kada u jednom trenutku on bude na rastojanju bar $k$ od elementa koji se trenutno obrađuje, on prestaje da bude kandidat i zato se briše iz te liste kandidata. Prema tome, lista kandidata ima osobinu da se sa jedne strane (početka) elementi izbacuju kada prestanu da budu aktuelni, dok se sa druge strane i dodaju, ali isto tako i izbacuju kada se pojavi neki manji.

**Algoritamske smernice**

Radi ilustracije moguće implementacije, prilažemo telo funkcije koja kao argumente dobija: dužinu nizova koji sadrže $x$ koordinate levih krajeva pravougaonika i $x$ koordinate desnih krajeva tih pravougaonika (broj $n$), broj $k$, kao i nizove sa $x$ koordinatama levih krajeva i $x$ koordinatama desnih krajeva, a koja vraća širinu minimalnog obuhvatajićeg pravougaonika. Indeksiranje elemenata nizova kreće od nula (0).

Jedna moguća implementacija ѕasnovana na podeli niza uz blokove dužine $k$ može imati sledeći izgled:

```
int solve(int n, int k, int left[], int right[])
{
    int pref_min[MAXN], pref_max[MAXN];
    int suff_min[MAXN], suff_max[MAXN];
    for(int i = 0; i < n; i++)
pref_min[i] = (i % k == 0) ? left[i] : min(pref_min[i - 1], left[i]);
    for(int i = n - 1; i >= 0; i--)
suff_min[i] = (i % k == k - 1) ? left[i] : min(suff_min[i + 1], left[i]);    
    for(int i = 0; i < n; i++)
pref_max[i] = (i % k == 0) ? right[i] : max(pref_max[i - 1], right[i]);
    for(int i = n - 1; i >= 0; i--)
suff_max[i] = (i % k == k - 1) ? right[i] : max(suff_max[i + 1], right[i]);
    int res = 0;
    for(int i = 0; i < n; i++)
    {
int low = min(pref_min[i], suff_min[max(i - k + 1, 0)]);
int high = max(pref_max[i], suff_max[max(i - k + 1, 0)]);
res = max(res, high - low);
    }
    return res;
}

```
Implementacija zasnovana na formiranju liste (reda) kandidata za minimum (maksimum) od svakih $k$ uzastopnih može imati sledeći izgled:

```
int solve(int n, int k, int x1[], int x2[]) {
  int dxm, dxt;
  int qx1[MAXN], qx2[MAXN];
  int qx1s, qx1e, qx2s, qx2e;
  qx1s = qx2s = 0;
  qx1e = qx2e = 1;
  qx1[0] = qx2[0] = 0;
  dxm = x2[0] - x1[0];
  for (int i = 1; i < n; i++) {
      if (i - qx1[qx1s] >= k) qx1s++;
      if (i - qx2[qx2s] >= k) qx2s++;
      while ((qx1e > qx1s) && (x1[qx1[qx1e-1]] >= x1[i])) qx1e--;
      qx1[qx1e++] = i;
      while ((qx2e > qx2s) && (x2[qx2[qx2e-1]] <= x2[i])) qx2e--;
      qx2[qx2e++] = i;
      dxt = x2[qx2[qx2s]]-x1[qx1[qx1s]];
      if (dxt > dxm) dxm = dxt;
  }  
  return dxm;
}
```

``` cpp title="04_filozof.cpp" linenums="1"
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 2000005;

// (x,y) -- donji levi, (xx, yy) -- gornji desni
int x[N], y[N], xx[N], yy[N];
int pref_min[N], suff_min[N], pref_max[N], suff_max[N];
int n, k;

int solve(int left[], int right[])
{
    for(int i = 0; i < n; i++)
	pref_min[i] = (i % k == 0) ? left[i] : min(pref_min[i - 1], left[i]);
    for(int i = n - 1; i >= 0; i--)
	suff_min[i] = (i % k == k - 1) ? left[i] : min(suff_min[i + 1], left[i]);
    
    for(int i = 0; i < n; i++)
	pref_max[i] = (i % k == 0) ? right[i] : max(pref_max[i - 1], right[i]);
    for(int i = n - 1; i >= 0; i--)
	suff_max[i] = (i % k == k - 1) ? right[i] : max(suff_max[i + 1], right[i]);

    int res = 0;
    for(int i = 0; i < n; i++)
    {
	int low = min(pref_min[i], suff_min[max(i - k + 1, 0)]);
	int high = max(pref_max[i], suff_max[max(i - k + 1, 0)]);

	res = max(res, high - low);
    }

    return res;
}

long long m, a, b, s;
int rand(long long s) { return s = (a * s + b) % m; }

int main()
{

    cin >> n >> k >> m >> a >> b >> s;
    for(int i = 0; i < n; i++)
    {
	x[i] = rand(i ? yy[i - 1] : s);
	y[i] = rand(x[i]);
	xx[i] = rand(y[i]);
	yy[i] = rand(xx[i]);

	if(x[i] == xx[i]) xx[i]++;
	if(x[i] > xx[i]) swap(x[i], xx[i]);

	if(y[i] == yy[i]) yy[i]++;
	if(y[i] > yy[i]) swap(y[i], yy[i]);

	// cout << x[i] << " " << y[i] << " " << xx[i] << " " << yy[i] << endl;
    }
    
    printf("%d ", solve(x, xx));
    printf("%d\n", solve(y, yy));
    
    return 0;
}

```
