---
hide:
  - toc
---

# A1 - Sličice

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |



Jakov skuplja sličice za album. U ovoj ekskluzivnoj kolekciji postoji $N$ različitih vrsta sličica koje je moguće skupiti i na njima su naslikani različiti prirodni brojevi od $1$ do $N$. Svaka od tih $N$ vrsta sličica je odštampana u više primeraka. Jakov je do sada već skupio $N$ sličica, a na svakoj od njih je napisan broj $2$ (tj. Jakov je skupio $N$ primeraka vrste sličice sa brojem $2$).

Srećom po Jakova on može da razmenjuje svoje sličice sa društvom. Međutim, pravila razmene su stroga. Dva druga mogu da razmene sličice samo ukoliko je najveći zajednički delilac brojeva nacrtanim na njima strogo veći od $1$. Kada se razmeni sa nekim, Jakov više nema sličicu koju je dao, ali može da koristi sličicu koju je upravo dobio za druge trampe. Jakov se pita koliko najviše različitih vrsta sličica može skupiti nakon svih razmena?

Jakov se takođe pita i koliko bi sličica uspeo da skupi za neke druge vrednosti broja $N$. Potrebno je odgovoriti na $Q$ ovakvih pitanja. Upiti su nezavisni, tj. na svaki se posebno odgovara i za svaki od upita, Jakov na početku ima $N$ sličica sa vrednošću $2$.
## Opis ulaza
Prva linija standardnog ulaza sadrži ceo pozitivan broj $Q$ - broj upita na koje je potrebno dati odgovor. U narednih $Q$ linija dat je po jedan ceo pozitivan broj $N$ - broj različitih sličica u kolekciji.
## Opis izlaza
Na standardni izlaz je postrebno ispisati $Q$ linija - u $i$-toj od njih odgovor na $i$-ti upit.
## Primer

### Ulaz

```
2
5
7
```

### Izlaz

```
2
4
```
## Objašnjenja primera
U prvom upitu, postoji $5$ različitih vrsta sličica u kolekciji, a Jakov je do sada skupio $5$ sličica sa brojem $2$. Od tih $5$ sličica na kojima je napisan broj $2$, može jednu da razmeni za sličicu sa brojem $4$. Na kraju, Jakov će imati $2$ različite vrste sličica i to sa brojevima $2$ i $4$. Primetite da on ima ukupno $2$ različite vrste, iako ima $4$ primerka sličice na kojoj je napisan broj $2$.

U drugom upitu, postoji $7$ različitih vrsta sličica u kolekciji, a Jakov je do sada skupio  $7$ sličica sa brojem $2$. Potom razmeni jednu od njih za sličicu sa brojem $4$, a dve za dve sličice sa brojem $6$. Konačno, on može da razmeni jednu sličicu sa brojem $6$ za sličicu sa brojem $3$. Na kraju, Jakov će imati $4$ vrste sličica i to sa brojevima $2$, $3$, $4$ i $6$.

## Ograničenja
-   $4 \leq N \leq 10.000.000$
-   $1 \leq Q \leq 200.000$

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $N \leq 10$
-   U test primerima vrednim $10$ poena: $N, Q \leq 200$
-   U test primerima vrednim $20$ poena: $N, Q \leq 2.000$
-   U test primerima vrednim $20$ poena: $N \leq 100.000$
-   U test primerima vrednim $40$ poena: Bez dodatnih ograničenja

Za početak odredimo koje karte Jakov može skupiti, a koje ne može.

Jakov može skupiti kartu sa bilo kojim parnim brojem, jer je najveći zajednički delilac za $2$ (Jakov ima na raspolaganju proizvoljno mnogo karti sa brojem $2$) i tog parnog broja jednak $2$ što je veće od $1$.

Jakov može skupiti i karte sa neparnim brojevima $p$ ne većim od $\lfloor\frac{n}{2}\rfloor$ (naravno, većim od $1$), jer prvo može kartu sa brojem $2$ razmeniti za kartu sa brojem $2p$, a nakon toga kartu sa brojem $2p$ za kartu sa brojem $p$.

Na kraju može skupiti i karte sa bilo kojim složenim neparnim brojem $m$ iz intervala $\left[\lceil\frac{n}{2}\rceil,n\right]$. Svaki takav neparan složen broj ima bar jedan prost faktor $p\leq \sqrt{m} \leq \sqrt{n} \leq \lfloor\frac{n}{2}\rfloor$. Zbog toga kartu sa brojem $2$ može razmeniti za kartu sa brojem $2p\leq n$, zatim kartu sa brojem $2p$ za kartu sa brojem $p$ i na kraju kartu sa brojem $p$ za kartu sa brojem $m$.

Jakov ne može skupiti karte sa neparnim prostim brojem $p$ većim od $\lfloor\frac{n}{2}\rfloor$. Da bi skupio tu kartu morao bi da ima kartu sa brojem deljivim sa brojem $p$. Ali najmanji broj (različit od $p$) koji je deljiv brojem $p$ je $2p$ koji je veći od $n$.

Zbog toga je broj karti koje Jakov može skupiti jednak razlici brojeva $n-1$ (broj brojeva većih od $1$, ali manjih od ili jednakih $n$) i broja prostih brojeva većih od $\lfloor\frac{n}{2}\rfloor$ i manjih od ili jednakih $n$.

  
## Rešenje kad je $N \leq 10$
Sve karte koje može skupiti Jakov se mogu odrediti varijacijom pretrage u širinu.

## Rešenje kad je $N, Q \leq 200$, $N, Q \leq 2000$

Za svaki upit se određuje broj prostih brojeva u intervalu $\left[\lfloor\frac{n}{2}\rfloor+1,n\right]$.

## Rešenje kad je $N \leq 100.000$
Neposredno nakon učitavanja vrednosti broja $N$ za sve upite, određuje se najveća vrednost za $N$ (neka je to $N_{\max}$), a nakon toga za svaku vrednost $N \leq N_{\max}$ broj prostih brojeva koji nisu veći od $N$ (označimo taj broj sa $p(N)$).  Vrednost $p(N)$ se određuje na osnovu vrednosti $p(N-1)$. Naime, vrednost $p(N)$ je jednaka $p(N-1)+1$, ako je $N$ prost broj, odnosno $p(N-1)$, ako je $N$ složen broj. Provera da li je broj $N$ prost se može izvesti u složenosti $O(\sqrt{N})$, pa je složenost određivanje svih vrednosti $p(N)$ jednaka $O(N_{\max}\sqrt{N_{\max}})$.
 Nakon toga se broj prostih brojeva u intervalu  $\left[\lfloor\frac{n}{2}\rfloor+1,n\right]$ određuje po formuli $p(N)-p\left(\frac{N}{2}\right)$, tj. u složenosti $O(1)$. Složenost kompletnog algoritma je $O(N_{\max}\sqrt{N_{\max}}+Q)$.


## Glavno rešenje


Neposredno nakon učitavanja vrednosti broja $N$ za sve upite, određuje se najveća vrednost za $N$ (neka je to $N_{\max}$), a nakon toga za svaku vrednost $N \leq N_{\max}$ broj prostih brojeva koji nisu veći od $N$ (označimo taj broj sa $p(N)$).  Za razliku od prethodnog podzadatka, provera da li su prirodni brojevi prosti se izvodi primenom Eratostenovog sita. Zahvaljujući tome, složenost izračunavanja svih vrednosti $p(N)$ je $O(N_{\max}\log N_{\max})$, a složenost kompletnog rešenja je $O(N_{\max}\log N_{\max} + Q)$.


``` cpp title="04_slicice.cpp" linenums="1"
#include<bits/stdc++.h>
#define maxn 10000000
using namespace std;
bool nopr[maxn+5];
int cnt[maxn+5];
int main() {
for(long long i=2;i<=maxn;i++) {
	cnt[i]=cnt[i-1];
	if(!nopr[i]) {
		cnt[i]+=1;
		for(long long j=i*i;j<=maxn;j+=i) {
			nopr[j]=true;
		}
	}
}
int q;
scanf("%d",&q);
for(int i=1;i<=q;i++) {
	int n;
	scanf("%d",&n);
	printf("%d\n",n-1-cnt[n]+cnt[n/2]);
}
return 0;
}
```
