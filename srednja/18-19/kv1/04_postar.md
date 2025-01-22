---
hide:
  - toc
---

# 4 - Poštar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 128MB |

Kao i obično, ovaj zadatak se odnosi na jednu čudnu situaciju --
potrebno je isplanirati isporuke za svemirskog poštara
u 2318. godini. U pošti, koja se nalazi na planeti sa koordinatama
$(0,0)$, se nalazi $N$ paketa koje treba dostaviti na različite
planete, čije su koordinate date (svemir je dvodimenzionalan, koordinate
$i$-te planete su $(X_i,Y_i)$).

Svemirski poštar se mora pridržavati sledećih pravila:

* Paketi se raznose **dva po dva** - kada krene iz pošte, poštar mora
  da ode do jedne planete i isporuči paket, zatim od nje direktno do
  druge, i nakon toga da se vrati u poštu (gde će preuzeti naredna dva
  paketa, ako ih još ima).
* Između planeta (ukljjučujući i planetu na kojoj je pošta) se mora kretati **pravom linijom** (najkraćim putem).
* Putanja kojom se poštar kreće (izlomljena linija koja spaja planete)
  **ne sme seći samu sebe**.
  
Vaš zadatak je da pronađete put koji poštuje ova tri pravila, takav da
mu je ukupna dužina **minimalna**.

## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se jedan prirodan broj $N$ -
broj planeta na koje treba odneti pakete. U narednih $N$ linija se
nalaze po dva broja $X_i$ i $Y_i$ - koordinate $i$-te planete.

## Opis izlaza

U jedinoj liniji ispisati jedan realan broj - ukupnu dužinu najkraćeg
puta koji poštuje sva pravila. Rešenje će biti prihvaćeno ako se
razlikuje od tačnog za najviše $10^{-6}$ (kao relativna ili apsolutna
greška).

## Primer 1

### Ulaz

~~~
4
-1 1
-1 4
1 1
1 4
~~~

### Izlaz

~~~
17.07463838
~~~

## Objašnjenje primera

Najkraći put koji zadovoljava sva tri pravila je sledeći: $(0,0) \rightarrow
(-1,1) \rightarrow (-1,4) \rightarrow (0,0) \rightarrow (1, 4) \rightarrow (1, 1) \rightarrow (0,0)$. Kad ne bi
bilo trećeg pravila, poštar bi mogao da prvo dostavi pakete prvoj i
trećoj, a zatim drugoj i četvrtoj planeti, ali ta putanja nije
dozvoljena jer se putevi od pošte do druge planete i od prve do treće
seku.

## Ograničenja

* $N$ je parno.
* Za sve $i$, $-10^6 \leq X_i, Y_i \leq 10^6$.
* Nijedne dve planete (uključujući poštu) se ne nalaze na istoj poziciji.
* Nijedne tri planete (uključujući poštu) nisu kolinearne.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima vrednim 20 poena: $N \leq 8$ i za sve $i$ važi $Y_i > 0$.
* U test primerima vrednim 20 poena: $N \leq 100$ i za sve $i$ važi $Y_i > 0$.
* U test primerima vrednim 20 poena: $N \leq 500$ i za sve $i$ važi $Y_i > 0$.
* U test primerima vrednim 20 poena: $N \leq 100$.
* U test primerima vrednim 20 poena: $N \leq 500$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dimitrije Erdeljan | Dimitrije Erdeljan | Aleksa Milisavljević | Slobodan Mitrović |

## Analiza
Zadatak rešavamo dinamičkim programiranjem.

Rešimo prvo zadatak u slučaju da su sve koordinate $Y_i$ pozitivne. Prvo sortiramo tačke po uglu u odnosu na poziciju pošte. Neka je $dp[l][r]$ najmanja dužina puta, koju poštar mora da pređe, da bi obišao sve planere u intervalu $[l,r]$, ukoliko je to moguće i $inf$ u suprotnom.  Neka smo povezali $l$ sa nekom $m$ takvom da je $l<m<r$, to je  $dp[l][r] = min_{l<m<r}(dp[l][m]+dp[m+1][r])$. Druga opcija je da povežemo planetu $l$ sa $r$. Dovoljno je da proverimo da li duž koja ih spaja seče duž između pošte i neke druge planete. To možemo da uradimo u $O(N)$. Ukoliko ne seče, imamo još jednog kandidata za rešenje, pa je onda $dp[l][r]=min(dp[l][r],dist(l,r)+dp[l+1][r-1])$, gde je $dist(l,r)$ rastojanje između planete sa indeksom $l$ i planete sa indeksom $r$. Rezultat je u $dp[1][N]$, a vremenska složenost algoritma je $O(N^3)$.

Sada možemo rešenje da uopštimo na slučaj da koordinate $Y_i$ nisu pozitivne. Primetimo da kako god povezali planete, uvek možemo da nacrtamo jednu polupravu iz $(0,0)$, koja ne seče ni jednu putanju. Ovo važi zato što se putanje međusobno ne seku. "Luk" koji pravi jedan obilazak dve planete može da bude sadržan u nekom drugom i da sadrži neki drugi, ali ne mogu da se seku. Sada sortiramo tačke po uglu. Ako pretpostavimo da smo povukli tu polupravu negde između $i$ i $i+1$ planete, možemo da posmatramo niz koji je ciklično pomeren ulevo za $i$ mesta i da ponovimo dinamičko kao u prethodnom delu. Ovo rešenje radi u složenosti $O(N^4)$. 

Međutim možemo da primetimo da veliki deo tog dinamičkog mi izračunavamo više puta. Možemo da dupliramo sortirani niz, tj. ciklično ga ponovimo drugi put i ponovo izračunamo $dp[l][r]$. Primetimo da je sada u $dp[i][i+N]$ upravo rešenje koje se dobija kada bi poluprava bila između planeta $i-1$ i $i$. Pa je krajnji rezultat $min_{1 \leq i \leq N}(dp[i][i+N])$. Vremenska složenost $O(N^3)$, memorijska složenost $O(N^2)$.

``` cpp title="04_postar.cpp" linenums="1"
#include <algorithm>
#include <cmath>
#include <cstdio>

struct point
{
    long long x, y;
} ;
point operator-(point a, point b) { return {a.x - b.x, a.y - b.y}; }
// (z-component of) cross product
long long operator*(point a, point b) { return a.x*b.y - a.y*b.x; }
const point ORIGIN = {0, 0};

// we need sorting by polar angle
bool operator<(point a, point b)
{
    // int s_a = (a.y > 0) || (a.y == 0 && a.x < 0);
    // int s_b = (b.y > 0) || (b.y == 0 && b.x < 0);
    // if(s_a == s_b)
    //     return a * b > 0;
    // else return s_a;
    return std::atan2(a.y, a.x) < std::atan2(b.y, b.x);
}

const int N = 1000;
point pts[2 * N];
bool ok[N][N];
double dp[2 * N][2 * N];
int n;

long long sgn(long long x) { return x < 0 ? -1 : 1; }

bool diff_side(point a, point b, point x, point y)
{
//    printf("%lld %lld\n", (b-a)*(x-a), (b-a)*(y-a));
    return sgn((b-a) * (x-a)) != sgn((b-a) * (y-a));
}

bool intersect(point a, point b, point x, point y)
{
//    printf("%d%d\n", diff_side(a, b, x, y), diff_side(x, y, a, b));
    return diff_side(a, b, x, y) && diff_side(x, y, a, b);
}

bool check_ok(int i, int j)
{
    if((j - i) % 2 == 0)
        return false;

    for(int k = 0; k < n; k++)
        if(k != i && k != j)
        {
//            printf("%d %d %d -> %d\n", i, j, k, intersect(pts[i], pts[j], pts[k], ORIGIN));
            if(intersect(pts[i], pts[j], pts[k], ORIGIN))
                return false;
        }
    
    return true;
}

bool is_ok(int i, int j)
{
    if(j - i >= n) return false; // angle more than full circle
    if((pts[j] - pts[i]) * (ORIGIN - pts[i]) < 0)
        return false; // angle more than half-circle
    return ok[i % n][j % n];
}

long long sqr(long long x) { return x * x; }
double dist(int i, int j)
{
    return std::sqrt(sqr(pts[i].x - pts[j].x) + sqr(pts[i].y - pts[j].y));
}

int main()
{
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%lld %lld", &pts[i].x, &pts[i].y);

    std::sort(pts, pts + n);
//    for(int i = 0; i < n; i++) fprintf(stderr, "(%lld, %lld)\n", pts[i].x, pts[i].y);
    for(int i = 0; i < n; i++)
        pts[i + n] = pts[i];

    // simple O(N^3) precomputation (complexity is dominated by the DP
    // anyway, no need for a quadratic algorithm here)
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++)
            ok[i][j] = ok[j][i] = check_ok(i, j);

    for(int delta = 0; delta < 2 * n; delta++)
        for(int i = 0; i < 2 * n; i++)
        {
            int j = i + delta;
            if(j >= 2 * n) continue;
            
            dp[i][j] = INFINITY;

            if(is_ok(i, j))
                dp[i][j] = dp[i + 1][j - 1] + dist(i, j);
            for(int k = i + 1; k < j; k++)
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j]);

            // if(is_ok(i,j) && dp[i][j] == dp[i+1][j-1] + dist(i,j))
            //     printf("%d %d -> outer\n", i, j);
            // else for(int k = i + 1; k < j; k++)
            //          if(dp[i][j] == dp[i][k] + dp[k+1][j])
            //          {printf("%d %d -> %d\n", i, j, k); break;}
        }

    double res = INFINITY;
    for(int i = 0; i < n; i++)
        res = std::min(res, dp[i][i + n - 1]);

    // for(int i = 0; i < 2 * n; i++)
    //     for(int j = 0; j < 2 * n; j++)
    //         printf("%10.2lf%c", dp[i][j], j == 2*n-1 ? '\n' : ' ');
    // for(int i = 0; i < n; i++) printf("%10.2lf\n", dp[i][i+n-1]);

    for(int i = 0; i < n; i++)
        res += std::sqrt(sqr(pts[i].x) + sqr(pts[i].y));

    // for(int i = 0; i < n; i++)
    //     for(int j = 0; j <= n; j++)
    //         printf("%c", j == n ? '\n' : ok[i][j] ? '+' : '.');

    // double ss = 0;
    // for(int i = 0; i < n; i++)
    //     ss += std::sqrt(sqr(pts[i].x) + sqr(pts[i].y));
    // for(int i = 1; i <= 3; i++)
    //     printf("%d -> %.8lf\n", i, ss+dist(0, i) + dist(i == 1 ? 2 : 1, i == 3 ? 2 : 3));
    
    printf("%.8lf\n", res);
    return 0;
}

```
