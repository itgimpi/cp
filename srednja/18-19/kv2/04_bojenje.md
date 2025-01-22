---
hide:
  - toc
---

# 4 - Bojenje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Tom je bio nevaljao, i za kaznu je dobio zaduženje da ofarba zid. Zid se može predstaviti kao matrica sa $N$ vrsta i $M$ kolona. Tom ima jako čudnu četku kojom može u $i$-toj vrsti da ofarba ili prvih $A_i$ kolona ili poslednjih $M-A_i$ kolona. Tomu je svaka kolona dosadna onoliko koliko iznosi proizvod broja ofarbanih i neofarbanih polja u toj koloni. Ukupna dosadnost zida je jednaka zbiru dosadnosti svih kolona. Pomozite Tomu i izračunajte najmanju moguću dosadnost zida nakon bojenja.

## Opis ulaza

U prvoj liniji standardnog ulaza se nalaze dva cela broja, $N$ i $M$, koja predstavljaju broj vrsta i broj kolona, U narednih $N$ linija se nalazi po jedan ceo broj, $A_i$, koji predstavlja granicu za farbanje $i$-te vrste ($0 \leq A_i \leq M$).

## Opis izlaza

U jedinoj liniji standardnog izlaza se nalazi jedan ceo broj koji predstavlja minimalnu dosadnost zida nakon farbanja.

## Primer 1

### Ulaz

~~~
2 3
1
2
~~~

### Izlaz

~~~
1
~~~

## Primer 2

### Ulaz

~~~
4 4
2 
1 
4 
1
~~~

### Izlaz

~~~
6
~~~

## Objašnjenje primera

U prvom primeru je najbolje ofarbati obe vrste sa desne strane i onda bi ukupna dosadnost bila $2 \cdot 0 + 1 \cdot 1 + 0 \cdot 2 = 1$.
~~~
.##
..#
~~~

U drugom primeru je najbolje prvu, drugu i četvrtu vrstu ofarbati sa leve strane, a treću sa desne (pošto je $A_3 = M$ ona će onda ostati neofarbana).
~~~
##..
#...
....
#...
~~~
Ukupna dosadnost je $1 \cdot 3 + 3 \cdot 1 + 4 \cdot 0 + 4 \cdot 0 = 6$.

## Ograničenja

* U test primerima vrednim 10 poena: $n \leq 15$ i $m \leq 15$.
* U test primerima vrednim 15 poena: $n \leq 100$ i $m \leq 100$.
* U test primerima vrednim 20 poena: $n \leq 600$ i $m \leq 600$.
* U test primerima vrednim 20 poena: $n \leq 10000$ i $m \leq 10000$.
* U test primerima vrednim 35 poena: $n \leq 100000$ i $m \leq 10000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dimitrije Erdeljan | Filip Ćosović | Dimitrije Erdeljan | Marko Savić |

## Analiza

Dokazaćemo da optimalno rešenje sigurno ima sledeći oblik: broj belih
polja u koloni opada do neke tačke, a zatim raste do kraja, ili raste
do neke tačke pa opada do kraja. Ovo znači da, ako sortiramo redove po
poziciji gde im se menja boja, prvih $K$ redova bojimo belo-crno, a
ostale crno-belo.

Da bi dokaz bio jednostavniji, umesto da biramo boje za redove,
biraćemo funkciju $f$, gde je $f(i)$ broj belih polja u koloni između
"promena" $i-1$ i $i$. Za validna bojenja zida važe sledeće osobine
$f$, i obrnuto, ako osobine važe možemo napraviti bojenje:

* $f(0) + f(n) = n$ (svi redovi promene boju)
* Za svako $i$, $|f(i) - f(i-1)| = 1$ (svaki put se menja tačno jedan
  red)

Dokaz ovoga ostavljamo čitaocu.

Prvo, sigurno postoji tačno jedan "trenutak" (deo zida između dve
promene) kada imamo po $\frac{N}{2}$ crnih i belih polja (za neparno
$N$, sličnim argumentom dokazujemo da se tačno jednom broj menja sa
"više belih" na "više crnih"), tj. postoji tačno jedno $x$ za koje
$f(x) = \frac{n}{2}$. Kada ovo ne bi bilo tačno, mogli bismo da
poboljšamo rešenje:

* Nađemo $x$ takvo da je $f(x) = \frac{n}{2}$ i $f(x-1) = f(x+1) =
  \frac{n}{2} + 1$ (ili slično za $-1$) -- ako ne postoji, možemo
  odabrati neki interval između dve tačke gde $f(i) = \frac{n}{2}$ i
  "obrnuti" ih (postaviti $f(i) = n - f(i)$) tako da se ne promeni
  vrednost rešenja.
* Postavimo $f(x) = \frac{n}{2} - 2$.

Bez gubitka opštosti pretpostavićemo da $f(0) < \frac{n}{2}$ (počinjemo
sa manje belih nego crnih polja). Na sličan način možemo dokazati da na
intervalu od $0$ to tačke gde imamo isti broj crnih i belih polja
funkcija $f$ opada do neke tačke pa raste, a od te tačke raste pa
opada.

Dakle, optimalno $f$ mora imati oblik "opada, pa raste, pa
opada". Sada ćemo dokazati da ne možemo imati oba opadajuća dela: ako
postoje, možemo smanjiti $f(0)$ za $2$ i povećati $f(n)$ za $2$ i
dobiti bolje rešenje.

Sada smo dokazali da je optimalno rešenje ili da broj belih polja raste
do neke tačke pa opada do kraja, ili obrnuto. Kako za svaki izbor
broja belih polja na početku postoji tačno jedna tačka gde možemo preći
sa rastućeg na opadajuće, ili sa opadajućeg na rastuće (kada su sva
polja iste boje), imamo $\mathcal{O}(n)$ opcija koje treba proveriti.

Sada još ostaje da nađemo način da izračunamo koliko bojenje vredi, ako
je dat broj belih polja $K$ na početku, i znamo da taj broj opada prvih
$x$ kolona a zatim raste do $N-K$.

## Smernice za algoritam

Izračunaćemo samo vrednost bojenja od početka do kolone $x$. Od te
kolone do kraja metod je identičan.

Vrednost koju treba izračunati je:

$$
\sum_{i = 0}^{x} (A_i - A_{i-1}) \cdot (K - i) = K \sum_{i=0}^x(A_i - A_{i-1}) - \sum_{i=0}^x i \cdot (A_i - A_{i-1})
$$

Da bismo ovo računali u konstantnom vremenu, na početku programa je
dovoljno da izračunamo nizove prefiksnih suma koje nam daju ove dve
"male" sume za svako $x$.

``` cpp title="04_bojenje.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

const int MAXN=int(2e5+50);

long long n,m,a[MAXN],s[MAXN],s2[MAXN],ps[MAXN],ps2[MAXN],pm[MAXN],p[MAXN],qs[MAXN],qs2[MAXN],qm[MAXN],q[MAXN];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

    cin >> n >> m;

    for (int i=0; i<n; i++)
        cin >> a[i];

    sort(a,a+n);

    a[n]=m;
    s[0]=a[0];
    ps[0]=s[0];
    ps2[0]=0LL;
    pm[0]=0LL;
    p[0]=0LL;
    for (int i=1; i<=n; i++)
    {
        s[i]=a[i]-a[i-1];
        ps[i]=ps[i-1]+s[i];
        ps2[i]=ps2[i-1]+ps[i-1];
        pm[i]=pm[i-1]+2*ps2[i-1]+ps[i-1];
        p[i]=n*ps2[i]-pm[i];
    }

    s2[0]=s[n];
    qs[0]=s2[0];
    qs2[0]=0LL;
    qm[0]=0LL;
    q[0]=0LL;
    for (int i=1; i<=n; i++)
    {
        s2[i]=s[n-i];
        qs[i]=qs[i-1]+s2[i];
        qs2[i]=qs2[i-1]+qs[i-1];
        qm[i]=qm[i-1]+2*qs2[i-1]+qs[i-1];
        q[i]=n*qs2[i]-qm[i];
    }


    long long rez=-1;
    for (int i=0; i<=n; i++)
        if (p[i]+q[n-i]<rez || rez==-1)
            rez=p[i]+q[n-i];

    printf("%lld\n",rez);

    return 0;
}

```
