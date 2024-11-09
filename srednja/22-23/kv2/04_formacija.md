---
hide:
  - toc
---

# 4 - Formacija

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

FIFA je uvela neočekivano pravilo pred finale svetskog prvenstva u fudbalu. Umesto $11$ igrača na terenu, sada svaki tim ima $N$ igrača i igrači su numerisani brojevima od $1$ do $N$ (brojevi im se, naravno, nalaze na dresu).

Finale je u toku i Mesi ima ozbiljnu šansu za gol. Ukoliko teren posmatramo kao koordinatni sistem, Mesijeva trenutna koordinata je $(0, 0)$, a koordinata francuskog fudbalera sa dresom broj $k$ je $(x_k, y_k)$ (za svako $1 \leq k \leq N)$.

Mesi je veoma inteligentan igrač i malo je poznato da je zapravo i sjajan takmičarski programer. Zato, uzeo je da posmatra svoje protivnike kako bi našao slabost.

On posmatra svih $2^N - 1$ nepraznih podskupova francuskih igrača. Da bi odredio kvalitet svoje šanse, potrebno mu je da sazna koliko podskupova postoji, takvih da konveksni omotač tačaka fudbalera tog podskupa - sadrži tačku $(0,0)$. Pošto ovaj broj može biti veoma velik, potrebno je ispisati njegov ostatak pri deljenju brojem $10^9+7$.

Ovo mu ne bi pravilo problem da je kod kuće za računarom i radi srpske kvalifikacije za okružno takmičenje, ali pošto je u finalu Svetskog prvenstva, potrebna mu je vaša pomoć.

**Napomena:** Konveksni omotač skupa tačaka $S$ definišemo na sledeći način:

- ukoliko se u $S$ nalazi samo jedna tačka, konveksni omotač je samo ta tačka;
- ukoliko se u $S$ nalazi skup kolinearnih tačaka (sve tačke na istoj pravoj), konveksni omotač je najkraća duž koja sadrži sve tačke;
- u suprotnom, konveksni omotač je konveksni mnogougao najmanje površine koji sadrži sve tačke skupa $S$.

Računamo da konveksni omotač sadrži tačku i u slučaju da se tačka nalazi na nekoj od ivica konveksnog omotača.

## Opis ulaza
Prva linija standardnog ulaza sadrži jedan ceo broj $N$ - broj igrača u timu po novim pravilima.
U $k$-toj od narednih $N$ linija nalazi se po dva cela broja $x_k$, $y_k$ - koordinate protivničkog igrača sa brojem dresa $k$.

## Opis izlaza
U jedinoj liniji standardnog izlaza, ispisati ostatak broja nepraznih podskupova francuskih igrača u čijem konveksnom omotaču se nalazi Mesi, nakon što ga podelimo brojem $10^9+7$.

## Primer 1
### Ulaz
```
5
3 -1
8 -1
-9 1
7 -1
-4 1
```

### Izlaz
```
9
```

## Primer 2
### Ulaz
```
18
25 32
36 40
-13 7
-26 -49
3 27
-33 -39
-19 -9
36 6
-16 -31
-17 -48
-29 34
-49 36
-28 -25
7 37
2 45
-18 15
-23 -26
41 42
```

### Izlaz
```
239247
```

## Objašnjenje primera
U prvom primeru odgovarajući neprazni podskupovi igrača su: 

- $\{1, 2, 3, 4, 5\}$
- $\{1, 2, 3, 5\}$
- $\{1, 2, 4, 5\}$
- $\{1, 2, 5\}$
- $\{1, 3, 4, 5\}$
- $\{1, 4, 5\}$
- $\{2, 3, 4, 5\}$
- $\{2, 3, 5\}$
- $\{3, 4, 5\}$

## Ograničenja

- $1 \leq N \leq 10^5$.
- $-10^9 \leq x_k, y_k \leq 10^9$, za $1 \leq k \leq N$.
- $(x_k, y_k) \neq (x_j, y_j)$, za $1 \leq k < j \leq N$.
- $(x_k, y_k) \neq (0, 0)$, za $1 \leq k \leq N$.

Test primeri su podeljeni u pet disjunktnih grupa:

- U testovima vrednim 10 poena: $N = 3$.
- U testovima vrednim 10 poena: $y_1 = 1$ i $y_k = -1$, za $1 < k \leq N$.
- U testovima vrednim 25 poena: $y_k \in \{-1, 1\}$, za $1 \leq k \leq N$.
- U testovima vrednim 15 poena: $N \leq 18$.
- U testovima vrednim 40 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Mladen Puzić | Pavle Martinović |

Za tri tačke $A, B$ i $C$ kažemo da trojka $(A, B, C)$ ima levi zaokret ukoliko ako se krećemo od $A$ do $C$ preko tačke $B$ moramo skrenuti u levo. Slično definišemo desni zaokret. Tačke $A, B$ i $C$ su kolinearne ukoliko postoji prava koja sadrži sve tri. Sve ovo možemo proveriti koristeći vektorski proizvod vektora $\overrightarrow{AB}$ i $\overrightarrow{BC}$.

## Rešenje kada $N = 3$
Za svaki podskup potrebno je proveriti posebno. Imamo tri podskupa sa dva igrača, gde je potrebno proveriti da li se Mesi nalazi na duži između ta dva igrača. To možemo tako što proverimo da li je kolinearan sa ta dva igrača, kao i da su mu $x$ i $y$ koordinate između njihovih.

Takođe je potrebno proveriti za podskup od sva tri fudbalera. Ako je Mesi u tački $M$, a tri date tačke $A, B$ i $C$, onda je potrebno da trojke $(A, B, M)$, $(B, C, M)$ i $(C, A, M)$ imaju isti zaokret, kako bi se $M$ nalazio u konveksnom omotaču tačaka $A, B$ i $C$.

Vremenska i memorijska složenost je $O(1)$.

## Rešenje kada $y_1 = 1$ i $y_k = -1$, za $1 < k \leq N$
Jasno je da ćemo igrača sa dresom broj $1$ morati da uključimo u podskup kako bi konveksni omotač sadržao tačku $(0, 0)$. 

Posmatrajmo tačku $(-x_1, -1)$. Postoji dva slučaja:

- Ukoliko postoji igrač koji se nalazi u toj tački, tada, ako ga uključimo u podskup, možemo uzeti bilo koji podskup ostalih igrača, kojih ima $2^{N-2}$. Sem toga, moramo dodati broj podskupova u kojima se ne nalazi taj igrač;
- Ukoliko ne postoji igrač u toj tački, nećemo dodati $2^{N-2}$ na rešenje.

Recimo da posmatramo broj podskupova koji ne sadrže igrača u tački $(-x_1, -1)$ (ako takav uopšte postoji). Jasno je da onda moramo uzeti makar jednog igrača levo (odnosno sa manjom $x$ koordinatom) od te tačke i makar jednog igrača desno (odnosno sa većom $x$ koordinatom). Ako sa $L$ označimo broj igrača levo, a sa $R$ broj igrača desno, onda je rešenje $(2^L-1)\cdot (2^R - 1)$ (na šta dodajemo $2^{N-2}$ ukoliko postoji igrač u tački $(-x_1, -1)$).

Vremenska složenost je $O(NlogN)$, a memorijska $O(N)$.

## Rešenje kada $y_k \in \{-1, 1\}$, za $1 \leq k \leq N$
Slično prethodnom rešenju, moramo da imamo makar po jednog igrača sa obe $y$ koordinate. Ako fiksiramo najlevlju i najdešnju tačku sa prave $y = 1$ iz podskupa koji biramo, onda ponovo nalazimo $L$ i $R$ i primenjujemo sličnu formulu kao u prethodnom rešenju. 

Ovo je presporo pa je potrebno da primetimo da $L$ zavisi samo od najlevlje odabrane tačke, a $R$ samo od najdešnje odabrane tačke. Ovo koristimo uz tehniku prefiksnih suma, da nađemo zbir svih podskupova za fiksiranu najlevlju tačku (a kroz sve moguće najdešnje). 

Vremenska složenost je $O(NlogN)$, a memorijska $O(N)$.


## Rešenje kada $N \leq 18$
Za svaki podskup tačaka, nađimo konveksni omotač nekim poznatim algoritmom (npr. monotoni lanac) i onda proverimo da li se tačka $(0, 0)$ nalazi u njemu. To možemo uraditi tako što idemo u krug kroz ivice omotača i proveravamo da li sve ivice imaju isti zaokret sa tačkom $(0, 0)$.

Vremenska složenost je $O(2^N \cdot N)$, a memorijska $O(N)$.

## Glavno rešenje
Umesto da računamo broj podskupova u čijem konveksnom omotaču se Mesi nalazi, od $2^N - 1$ oduzmimo broj podskupova u čijem konveksnom omotače se **ne nalazi** Mesi. To radimo zato što je lakše proveriti ovaj uslov - dovoljno je da postoji prava kroz $(0, 0)$, tako da su sve tačke podskupa sa iste strane ove prave.

Pretpostavićemo da nema kolinearnih tačaka (čak ni kad računamo Mesijevu poziciju). Rešanje kolinearnih tačaka svede se detalje implementacije. Krenuvši od pozitivne $x$ ose, sortirajmo tačke po polarnom uglu oko tačke $(0, 0)$, rastuće. Označimo sa $M$ tačku $(0, 0)$. 

Fiksirajmo svaku tačku $p_i$ i sa $cnt$ označimo broj drugih tačaka koje imaju levi zaokret sa vektorom od $p_i$ do $M$. Onda je broj podskupova u kojima je $p_i$ *najlevlja* tačka (tačka takva da nije zaokret $(M, x, p_i)$ nije nadesno, za svako $x$ u podskupu),  a da konveksni omotač ne sadrži tačku $M$ - $2^{cnt}$. Kada od $2^N - 1$ oduzmemo ovaj rezultat za svaku tačku $p_i$, dobijemo konačno rešenje. Broj $cnt$ možemo održavati tehnikom dva pokazivača.

Vremenska složenost je $O(NlogN)$, a memorijska $O(N)$.






``` cpp title="04_formacija.cpp" linenums="1"
#include <iostream>
#include <algorithm>
#define MAXN 100010
#define MOD 1000000007
#define x first
#define y second
#define Point pair<int, int>
using namespace std;
Point p[2*MAXN], o;
int st2[MAXN];

long long crossProduct(Point a, Point b, Point c) {
  return (long long)(b.x-a.x)*(c.y-b.y) - (long long)(b.y-a.y)*(c.x-b.x);
}

bool collinear(Point a, Point b, Point c) {
  return crossProduct(a, b, c) == 0;
}
bool leftTurn(Point a, Point b, Point c) {
  return crossProduct(a, b, c) > 0;
}
bool rightTurn(Point a, Point b, Point c) {
  return crossProduct(a, b, c) < 0;
}

int quadrant(Point a) {
  if(a.x > 0) {
    if(a.y >= 0) return 0;
    if(a.y <  0) return 3;
  } else if(a.x < 0) {
    if(a.y >  0) return 1;
    if(a.y <= 0) return 2;
  } else {
    if(a.y >  0) return 1;
    if(a.y <  0) return 3;
  }
}

bool cmp(Point a, Point b) {
  int kA = quadrant(a), kB = quadrant(b);
  if(kA != kB) return kA < kB;
  if(!collinear(o, a, b)) return leftTurn(o, a, b);
  return abs(a.x) <= abs(b.x) && abs(a.y) <= abs(b.y);
}

bool shouldPop(Point A, Point B) {
  if(rightTurn(A, o, B)) return true;
  if(collinear(A, o, B) && quadrant(A) != quadrant(B)) return true;
  if(collinear(A, o, B) && (abs(B.x) > abs(A.x) || abs(B.y) > abs(A.y))) return true;
  return false;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int N; cin >> N;
  st2[0] = 1;
  for(int i = 1; i <= N; i++) {
    st2[i] = st2[i-1]*2;
    if(st2[i] >= MOD) st2[i] %= MOD;
  }
  o = {0, 0};
  for(int i = 1; i <= N; i++) {
    cin >> p[i].x >> p[i].y;
  }
  sort(p+1, p+1+N, cmp);
  int idx = 2, sol = 0;
  for(int i = N+1; i <= 2*N; i++) {
    p[i] = p[i-N];
    while(idx < i && (shouldPop(p[i], p[idx]) || idx+N == i)) idx++;
    sol += st2[i-idx];
    if(sol >= MOD) sol %= MOD;
  }
  cout << (st2[N]-1-sol+MOD)%MOD;
  return 0;
}

```
