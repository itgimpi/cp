---
hide:
  - toc
---

# B3 - Zlatnici 2: Električni Bugalu

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 256MB |

Nastavak nikad nije dobar koliko i original. Stalno viđamo nastavke koji ne uspeju da razumeju zašto je original toliko voljen i ispadnu dosadni, standardni ili prosto loši. Naravno, mi nastojimo da promenimo to i zato vam predstavljamo silno isčekivani nastavak na kultni klasik prošlogodišnjeg ciklusa: "Zlatnici 2: Električni Bugalu"!

Kralj Mida pred sobom ima brojevnu pravu i na nekih $N$ različitih celobrojnih koordinata ima po jedan zlatnik. On igra igru gde u jednom potezu može da premesti jedan zlatnik na susednu poziciju na brojevnoj pravoj (sa $x$ ili na $x+1$ ili na $x-1$), ali ni u jednom trenutku dva zlatnika ne smeju da se nađu na istom mestu. Mida želi da postavi da se zlatnici nalaze jedan do drugog, ali ne zna još tačno gde. Zato će razmotriti $Q$ različitih scenarija za svoju igru. Svaki scenario će biti opisan jednim brojem $x$, i u tom scenariju će Midin cilj da bude da premesti zlatnike tako da se nalaze na različitim pozicijama iz skupa pozicija $\{x,x+1,\cdots,x+N-1\}$. Svi scenariji su nezavisni, to jest, zlatnici uvek kreću sa istih pozicija.

Kralj Mida je od vas zatražio pomoć da nađete najmanji broj poteza da bi završio igru u svakom scenariju, jer ako bi vam on već znao odgovor na to pitanje, to i ne bi bio nešto dobar zadatak.

## Opis ulaza
U prvom redu ulaza se nalazi prirodan broj $N$, broj zlatnika. U drugom redu se nalazi $N$ prirodnih brojeva $a_1<a_2<\cdots<a_N$ u rastućem poretku, koji predstavljaju početne pozicije zlatnika. U trećem redu se nalazi prirodan broj $Q$, broj scenarija. U narednih $Q$ linija se nalazi po jedan broj $x$ kojim su opisani scenariji.

## Opis izlaza
Na izlaz ispisati $Q$ brojeva, gde $i$-ti predstavlja najmanji broj poteza da Mida završi igru u $i$-tom scenariju.

## Ograničenja
-   $1 \leq N,Q \leq 200.000$
-   $0 < a_1<a_2<\cdots<a_N \le10^9$
-  $0<x\le10^9$ za svaki upit

Test primeri su podeljeni u 4 disjunktne grupe:

-   U test primerima vrednim $10$ poena: $N = 1$.
-   U test primerima vrednim $10$ poena: $N,Q\leq 1000$,  $a_i\le 100.000$ i $x\le 100.000$ za svaki scenario.
-   U test primerima vrednim $30$ poena: $a_i=p+i\cdot d$, to jest početne pozicije zlatnika formiraju aritmetičku progresiju.
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
2
2 4
2
5
2
```

#### Izlaz
```
5
1
```

#### Objašnjenje
U prvom scenariju, drugi zlatnik možemo da premestimo $2$ mesta udesno (sa $4$ na $6$), a prvi zlatnik $3$ mesta udesno (sa $2$ na $5$) i time smo završili igru. U drugom scenariju, dovolljno je premestiti drugi zlatnik jedno mesto ulevo.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Mladen Puzić | Aleksa Plavšić |

## Rešenje za $N = 1$:
Imamo samo jedan zlatnik koji je u svakom scenariju potrebno dovesti na odgovarajuću poziciju. Da bismo sa pozicije $a_1$ došli do pozicije $x$ potrebno je $|a_1 - x|$ poteza. Vremenska složenost je $O(N+Q)$.

## Rešenje za $N, Q \leq 1000$ i $a_i, x \leq 10^5$:
Pošto nije dozvoljeno da se dva zlatnika nalaze na istoj poziciji, takođe nije moguće da se dva zlatnika mimoiđu. Samim tim, zlatnik sa pozicije $a_1$ će završiti na poziciji $x$, zlatnik sa pozicije $a_2$ na $x+1$, ..., zlatnik sa pozicije $a_N$ na $x+N-1$.  Pošto će u svakom trenutku postojati zlatnik koji može da se približi svojoj krajnjoj poziciji, rešenje je $|a_1-x|+|a_2-x-1|+...+|a_N-x-N+1|$, odnosno $\sum_{i=0}^{N-1} |a_{i+1}-x-i|$. Pošto su $N$ i $Q$ mali, možemo ručno izračunati ovu sumu za svaki scenario. Vremenska složenost je $O(N\cdot Q)$.

## Rešenje za $a_i = p + i\cdot d$:
Primetimo da važi $|a_{i+1}-i-x| = x-(a_{i+1}-i)$ ako $a_{i+1}-i\leq x$, a $|a_{i+1}-i-x| = a_{i+1}-i-x$ u suprotnom. Pošto je niz $a_i$ rastući, za prvih nekoliko (potencijalno nula) žetona važiće prvi slučaj, dok 
će za ostale važiti drugi slučaj. Označimo sa $k$ indeks poslednjeg žetona za koji važi $a_{i+1}-i\leq x$ (ako ne postoji takav žeton onda $k = 0$, inače $k = i+1$). Primetimo da onda važi $\sum_{i=0}^{N-1} |a_{i+1}-x-i| = \sum_{i=0}^{k-1} (x-(a_{i+1}-i)) + \sum_{i=k}^{N-1} ((a_{i+1}-i)-x)$. Odnosno rešenje je $k\cdot x - \sum_{i=0}^{k-1} (a_{i+1}-i) + \sum_{i=k}^{N-1} (a_{i+1}-i) - (N-k)\cdot x$. Kada znamo $k$, sume iz formule možemo naći prefiksnim sumama. Sve ovo u stvari znači da ćemo nekoliko prvih novčića pomerati udesno, dok ćemo ostale pomerati ulevo. 

Ostalo nam je samo da nađemo $k$. Ako $a_i = p + i\cdot d$,  možemo uzeti $p = a_1$ i $d = a_2-a_1$ (ako $N \geq 2$). Tražimo najveće $k = i+1$ tako da važi  $a_{i+1}-i\leq x$, tj. $p + (i+1)\cdot d - i \leq x$. Važi $i+1 \leq \frac{x+i-p}{d}$. Samim tim važi $k = \lfloor\frac{x+i-p}{d}\rfloor$, gde je $\lfloor x \rfloor$ ceo deo od $x$. Vremenska složenost je $O(N+Q)$.

## Glavno rešenje:
Jedina razlika ovog rešenja i rešenja za prethodnu grupu test primera je nalaženje $k$. Za $100$ poena potrebno je da koristimo binarnu pretragu nad nizom $a_{i+1}-i$ (tražimo prvo $i$ za koje je to veće od $x$). Vremenska složenost je $O(N+QlogN)$.

``` cpp title="03_zlatnici2.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 200007
using namespace std;
long long a[MAXN],pr[MAXN],su[MAXN];
long long formula(long long x,long long k)
{
	return x*k+(k*(k-1))/2;
}
int binarna(int l,int r,long long x)
{
	if(l==r) return l;
	int s=(l+r+1)/2;
	if(a[s]-s<x) return binarna(s,r,x);
	return binarna(l,s-1,x);
}
int main()
{	int n,q;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%lld",&a[i]);
	pr[0]=a[0];
	for(int i=1;i<n;i++) pr[i]=pr[i-1]+a[i];
	su[n]=0;
	for(int i=n-1;i>=0;i--) su[i]=su[i+1]+a[i];
	scanf("%d",&q);
	while(q--)
	{
		long long x;
		scanf("%lld",&x);
		if(a[0]>=x) {printf("%lld\n", pr[n-1]-formula(x,n)); continue;}
		int t=binarna(0,n-1,x);
		printf("%lld\n",(formula(x,t+1)-pr[t])+(su[t+1]-formula(x+t+1,n-t-1)));
	}
}

```
