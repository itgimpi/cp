---
hide:
  - toc
---

# 3 - Deljenje niza

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 498ms | 64MB |

Perica ima niz od $N$ pozitivnih brojeva i pokušao je da ga u potpunosti podeli na dva niza uzastopnih brojeva, tako da ta dva niza imaju istu sumu brojeva.

Kako to nije uspeo da uradi, malo se iznervirao i odlučio da uništi jedan deo niza (neki **uzastopni podniz** unutar niza). **Nakon uništavanja podniza, niz se ponovo spaja.** Takođe, **Perica ne sme da uništi ceo niz.** Da li možete da mu pomognete da nakon uništenja nekog podniza ostvari svoju prvobitnu zamisao, tako što ćete da ispišete indekse početka i kraja tog podniza ili **-1 ako nema rešenja** za Pericu.


## Opis ulaza

U prvoj liniji standardnog ulaza nalazi se broj $N$, dužina niza.
U drugoj liniji nalazi se $N$ pozitivnih brojeva, koji predstavljaju elemente niza. Garantuje se da dati niz nije moguće podeliti na dva niza uzastopnih brojeva koji imaju istu sumu.

## Opis izlaza

U jedinoj liniji ispisati dva broja - indeks početka i kraja podniza koji uništavamo. Indeksi počinju od 1.
Ukoliko takav podniz ne postoji, ispisati -1.
Ukoliko postoji više takvih podnizova, ispisati bilo koji.

## Primer 1

### Ulaz

~~~
7
7 5 9 1 3 9 6
~~~

### Izlaz

~~~
3 4
~~~

## Primer 2

### Ulaz

~~~
3
1 10 100
~~~

### Izlaz

~~~
-1
~~~

## Objašnjenje primera

Ako u prvom primeru uništimo podniz od 3. do 4. elementa,
ostaje nam 7 5 3 9 6, što možemo podeliti na
[7,5,3] i [9,6]. Koji god podniz da uništimo u drugom primeru, nije moguće podeliti niz na dva dela sa istom sumom.

## Ograničenja

- $1 \leq A_i \leq 10^9$  
- $1 \leq N \leq 8000$  

Test primeri su podeljeni u 4 disjunktne grupe:  

- U test primerima vrednim 15 poena: $N \leq 80$  
- U test primerima vrednim 25 poena: $N \leq 400$  
- U  test primerima vrednim 25 poena: $N \leq 2000$  
- U test primerima vrednim 35 poena: $N \leq 8000$

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Aleksa Milisavljević | Vladimir Milovanović | Marko Savić |

## Analiza

Jedna od ključnih stavki u zadatku jeste garancija da bez izbacivanja, odnosno uništenja nekog uzastopnog podniza nije moguće podeliti zadati niz tako da su mu podzbirovi nekog prefiksa i ostatka niza jednaki. Takođe, postavka zadatka uslovljava da su svi članovi ulaznog niza strogo pozitivni, što uz pažljivo rešavanje pojednostavljuje kompleksnost korišćenog algoritma pretrage.

Najpre, neka je zbir svih članova zadatog niza $z$, a zbir članova nekog njegovog prefiksa (odnosno sufiksa) $p$. Neophodno je odrediti neki neprazan podniz ulaznog niza koji ne obuhvata prefiks (odnosno sufiks), takav da ako zbir njegovih članova označimo sa $s$, mora biti zadovoljen uslov $z = p + s + p = 2p + s$. Drugim rečima, zbir članova podniza koji se uništava $0<s<z$, mora biti jednak ukupnoj sumi svih članova izvornog niza umanjenoj za dvostruku vrednost prefiksa, $s=z-2p$.

Sada je potrebno izvršiti pretragu po svim prefiksima (odnosno sufiksima) i svim uzastopnim podnizovima ulaznog niza i proveriti da li je moguće zadovoljiti malopređašnju jednakost. Ukoliko bi ta pretraga naivno bila izvršena kroz tri nezavisne petlje (prva po prefiksima niza, a druga i treća po levoj i desnoj granici podniza za uništenje), dobila bi se kubna vremenska složenost $\mathcal{O}(N^3)$ po dužini niza. Međutim, uz nešto veštiju pretragu po levoj i desnoj granici uzastopnog podniza tu složenost moguće je i umanjiti.

## Smernice za algoritam

Naime, na početku iteracije po prefiksima (odnosno sufiksima) inicijalizovati levu i desnu granicu na prvi susedni član prefiksa (odnosno sufiksa). U svakoj iteraciji neophodno je ispitati da li je vrednost izraza $z - 2p - s$ veća, manja ili jednaka nuli, te ako je veća, pomerati desnu granicu, a ukoliko je manja, pomerati levu. Pretraga se završava ili kada izraz poprimi vrednost nula nakon čega sledi ispis utvrđenih granica podniza, ili kada leva i desna granica dođu do kraja izvornog niza, kada se prelazi na sledeći prefiks (odnosno sufiks). Pošto prilikom napredovanja granica mora biti zadovoljen i uslov da indeks leve granice nije viši od indeksa desne, to je ukupna složenost ove unutrašnje petlje linearna $\mathcal{O}(N)$ po dužini niza. Kako je neophodno pretragu uraditi za sve prefikse i sufikse izvornog niza (zbog asimetrije pretrage), to je ukupna složenost ovog algoritma kvadratna $\mathcal{O}(N^2)$, što se i zahtevalo za maksimalan broj poena u ovom zadatku.

``` cpp title="03_deljenje_niza.cpp" linenums="1"
#include<bits/stdc++.h>
#define MAXN 8005
using namespace std;
//100p
int n;
int a[MAXN];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	long long total_sum=0,s=0;
	for(int i=0;i<n;i++) total_sum+=a[i];
	for(int i=0;i<n;i++) {
		s+=a[i];
		long long cs=0;
		int l=i+1,r=i+1;
		cs=a[i+1];
		while(l<n && r<n) {
			while(r<n && (r<l || total_sum-cs-s>s)) {
				r++;
				cs+=a[r];
			}
			if(total_sum-cs-s==s) {
				printf("%d %d",l+1,r+1);
				return 0;
			}
			cs-=a[l];
			l++;
		}
	}
	s=0;
	reverse(a,a+n);
	for(int i=0;i<n;i++) {
		s+=a[i];
		long long cs=0;
		int l=i+1,r=i+1;
		cs=a[i+1];
		while(l<n && r<n) {
			while(r<n && (r<l || total_sum-cs-s>s)) {
				r++;
				cs+=a[r];
			}
			if(total_sum-cs-s==s) {
				printf("%d %d",n-r,n-l);
				return 0;
			}
			cs-=a[l];
			l++;
		}
	}
	printf("-1");
	return 0;
}

```
