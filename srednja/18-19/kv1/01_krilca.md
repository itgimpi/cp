---
hide:
  - toc
---

# 1 - Pileća krilca

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Kineski restoran ima u ponudi samo pileća krilca. Prava vrednost jednog pilećeg krilca je $X$ Juana, ali da se gosti restorana ne bi opterećivali matematikom, vlasnici su napravili jelovnik u kome je za različite količine krilaca napisana njihova cena zaokružena na najbliži ceo broj. Preciznije, svaka stavka u jelovniku je oblika "$K$ krilaca košta $round(K\cdot X)$ Juana", gde je $K$ prirodan broj, a $round$ je funkcija koja dati realan broj zaokružuje na najbliži ceo broj. Vaš zadatak je da utvrdite kolika je najmanja moguća prava vrednost jednog pilećeg krilca, tj. minimalno $X$ za koje važe sve stavke u jelovniku.

## Opis ulaza

U prvoj liniji ulaza nalazi se broj $N$, ukupan broj stavki u jelovniku. U svakoj od narednih $N$ linija je navedena po jedna stavka iz jelovnika, predstavljena sa dva prirodna broja, $K$ i $C$, što znači da je za $K$ pilećih krilaca potrebno platiti $C$ Juana. Redosled navođenja stavki može biti proizvoljan.

## Opis izlaza

U jedinu liniju standardnog izlaza ispisati jedan realan broj, najmanju moguću pravu vrednost jednog pilećeg krilca.

## Primer 1

### Ulaz

~~~
1
5 5
~~~

### Izlaz

~~~
0.9
~~~

## Primer 2

### Ulaz

~~~
3
5 7
4 6
2 3 
~~~

### Izlaz

~~~
1.375
~~~

## Objašnjenje primera

Ako bi u prvom primeru jedno krilce vredelo tačno 0.9 Juana, pet krilaca bi vredela 4.5 Juana, što je kad se zaokruži na najbliži ceo broj jednako 5 Juana. Ako bi vrednost jednog krilca bila manja od 0.9 Juana, tada bi vrednost pet krilaca bila strogo manja od 4.5 Juana, a to zaokruženo na najbliži ceo broj ne može biti veće od 4. Zato je tražena minimalna vrednost jednaka 0.9.

## Ograničenja

* $1 \leq N \leq 100$
* $1 \leq K \leq 100$
* $0 \leq C \leq 10000$

U svim test primerima tačan rezultat će biti pozitivan broj. Garantuje se da će ulazni podaci biti takvi da rešenje postoji.

## Napomene

* Da bi se rezultat priznao kao tačan, apsolutna greška mora biti manja od $10^{-4}$.
* Brojevi jednako udaljeni od dva uzastopna cela broja se zaokružuju na prvi veći ceo broj (na primer, 3.5 se zaokružuje na 4, a 6.5 se zaokružuje na 7).

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Savić | Marko Savić | Marko Savić | Aleksa Milisavljević |

Sa $R$ označimo realnu cenu jednog krilca, koju želimo da izračunamo.

Ako u $i$-toj stavci menija piše da $K_i$ krilaca košta $C_i$ Juana, to znači da $K_i$ krilaca realno ne mogu koštati manje od $C_i-0.5$ Juana. Svaka manja realna cena za $K_i$ krilaca zaokružena na najbliži ceo broj ne bi dala $C_i$ kao rezultat zaokruživanja. Iz toga zaključujemo da je $K_i R \geq C_i-0.5$, odnosno $R \geq (C_i-0.5)/K_i$.

Sada je potrebno proći kroz sve stavke u meniju i za svaku naći ovo donje ograničenje za cenu. Jasno je da najmanja moguća realna cena za jedno krilce ne sme biti manja od svakog tako dobijenog donjeg ograničenja, što znači da ne sme biti manja od njihovog maksimuma. Pošto nam se u zadatku garantuje da su cene u meniju formirane ispravno, to znači da je najmanja moguća realna cena jednog krilca jednaka upravo tom maksimumu.

$$
R=\max_{i\in\{1,2,\ldots,n\}}(C_i-0.5/K_i)
$$

``` cpp title="01_krilca.cpp" linenums="1"
#include<bits/stdc++.h>
using namespace std;
//100p
int main()
{
	int n;
	scanf("%d",&n);
	double k,c;
	double m;
	for(int i=0;i<n;i++) {
		scanf("%lf %lf",&k,&c);
		if(i==0) m=(c-0.5)/k;
		else m=fmax(m,(c-0.5)/k);
	}
	printf("%.6lf",m);
	return 0;
}

```
