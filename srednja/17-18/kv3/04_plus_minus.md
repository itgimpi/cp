---
hide:
  - toc
---

# 4 - Plus-minus

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Mikica ja na papiru zapisao jedan niz celih brojeva, koji je za njega bio vrlo bitan. U toku jednog pospremanja svoje sobe, izgubio je papir na kome je bio zapisan taj niz i sada ne može nikako da ga nađe. Ali ostao je papir na kome su zabeležene neke informacije o tom nizu. Te informacije su oblika: zbir elemenata niza od elementa sa indeksom  $p$ (odnosno od elementa na poziciji $p$) do elementa sa indeksom  $k$ (odnosno elementa na poziciji $k$) je pozitivan  (ili negativan). Pomozite Mikici da na osnovu tih činjenica odredi jedan niz koji zadovoljava te činjenice. Ako takav niz ne postoji (može se desiti da je Mikica pogrešio negde tokom računanja), ispisati odgovarajuću poruku.

## Opis ulaza
U prvom redu standardnog ulaza se nalazi ceo broj $T$ i on predstavlja broj nizova koje je zamislio Mikica. U narednim redovima se nalazi $T$ blokova u kojima su opisani nizovi koje je zamislio Mikica. U prvom redu opisa se nalaze dva cela broja $n$ i $m$. Broj $n$ predstavlja broj elemenata u nizu, a broj $m$ je broj informacija o nizu koje je Mikica zapisao. Svaki od narednih $m$ redova u bloku sadrži tri cela broja: $p$, $k$ i $z$ ($1\leq p\leq k\leq n$, $z\in\{-1,1\}$). Ta tri broja označavaju da je zbir elemenata niza od elementa na poziciji $p$ do elementa na poziciji $k$ pozitivan (ako je $z=1$), odnosno negativan (ako je $z=-1$).

## Opis izlaza
Za svaki od $T$ nizova iz ulaza treba ispisati odgovor (onim redom u kome se nalaze u ulazu). Ako za neki opis niza ne postoji niz koji odgovara opisu, onda u jednom redu ispisati broj $-1$. Ako za neki opis niza postoji takav niz onda u jednom redu izlaza ispisati broj $1$, a u narednom redu ispisati elemente niza razdvojene razmacima (elementi niza treba da budu celi brojevi čija apsolutna vrednost nije veća od $10^9$).

## Primer 1
### Ulaz
```
1
3 2
1 2 1
2 3 -1
```

### Izlaz
```
1
-1 2 -3
```

## Primer 2
### Ulaz
```
2
6 4
1 3 1
1 5 -1
6 6 -1
4 6 1
2 1
1 2 1
```

### Izlaz
```
-1
1
-1 2
```

## Objašnjenje primera
U prvom primeru, sabiranjem odgovarajućih elemenata se lako proverava da su oba uslova koje je Mikica zapisao ispunjena.

## Ograničenja i podzadaci

* $1\leq T \leq 4$.
* $1\leq n \leq 10000$.
* $1\leq m \leq 200000$.
* Elementi niza koji je Mikica zapisao su celi brojevi između $-10^9$ i $10^9$.

Test primeri su podeljeni u dve disjunktne grupe:

* U 30% test primera važi $1\leq n \leq 15$.
* U ostalim test primerima nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dragan Urošević | Dragan Urošević | Dragan Urošević | Nikola Jovanović |

Označimo sa $s_k$ zbir prvih $k$ elemenata niza, tj. $s_k = \sum_{i=1}^k x_k$ za $1 \leq k\leq n$. Zvaćemo ove zbirove parcijalne sume. Lako se zaključuje da je zbir elemenata ed elementa na poziciji $i$ do elementa na poziciji $j$ jednak

$$
x_i + x_{i+1} + ... +x_{j-1} + x_j = s_j - s_{i-1}.
$$

Ako je zbir elemanata od elementa na poziciji $i$ do elementa na poziciji $j$ pozitivan, onda je $s_j-s_{i-1} > 0$, odnosno $s_{i-1} < s_j$.  Ako je zbir elemanata od elementa na poziciji $i$ do elementa na poziciji $j$ negativan, onda je $s_j-s_{i-1} < 0$, odnosno $s_{j} < s_{i-1}$. 
 
Formiraćemo orijentisan graf $G=(V,E)$ u kome čvorovi odgovaraju parcijalnim sumama (možemo čvorove numerisati i brojevima između $0$ i $n$). Za svaku nejednakost oblika $s_a < s_b$ uvodimo ivicu od čvora koji odgovara parcijalnoj sumi $s_a$ do čvora koji odgovara parcijalnoj sumi $s_b$. Ako u tom grafu postoji petlja, onda ne postoji niz koji zadovoljava zadate uslove. Naime, petlja je niz čvorova u kome se prvi i poslednji čvor poklapaju takav da između svaka dva uzastopna postoji ivica. Neka taj niz čine čvorovi

$$
s_{k_1}, s_{k_2}, s_{k_3}, ..., s_{k_c}, s_{k_1}.
$$

Tada za parcijalne sume važi

$$
s_{k_1} < s_{k_2} < s_{k_3} < ..., <s_{k_c} < s_{k_1} 
$$

i zbog tranzitivnosti je $s_{k_1} < s_{k_1}$, što je kontradikcija.

Ako u grafu $G$ ne postoji ciklus, čvorovi grafa se mogu poređati u niz tako da ako postoji ivica od čvora $s_a$ do čvora $s_b$ onda je čvor $s_a$ stoji u nizu pre čvora $s_b$. Svako takvo ređanje u niz se naziva topološko sortiranje i može se obaviti varijacijom na obilazak grafa u dubinu. Na osnovu tog nabrajanja čvorova, parcijalnim sumama (čvorovima grafa) možemo dodeliti cele brojeve, tako da se čvoru $s_0$ dodeli vrednost 0, čvorovima koji se nalaze posle njega u tom nabrajanju redom brojevi $1, 2, 3, \ldots$ (u skladu sa poretkom u nabrajanju), a čvorovima koji se nalaze pre njega redom brojevi $-1, -2, -3, \ldots$ (ovaj put sdesna ulevo, u skladu sa nabrajanjem). Lako se uveravamo da će za svaka dva čvora $s_a$ i $s_b$ važiti da ako je $s_a$ pre (levo) od $s_b$ u nabrajanju, onda je $s_a < s_b$. Drugim rečima, parcijalnim sumama smo dodelili različite cele brojeve i oni zadovoljavaju sve nejednakosti koje su zadate u ulaznim podacima.

Na osnovu parcijalnih suma se mogu odrediti elementi niza $x_i = s_i - s_{i-1}$ za $1\leq i \leq n$.

## Smernice za algoritam
Dajemo samo pseudokod za topoško sortiranje (nabrajanje). Pretpostavljamo da je graf reprezentovan pomoću vektora/listi suseda svojih čvorova. Rezultat koji vraća funkcija je $0$, ako graf jeste acikličan (pored toga je u nizu `tops` njegovo topološko sortiranje), a $1$, ako je graf ima bar jednu petlju i samim tim ne postoji topološko sortiranje. 

```
topsort() {
p = n;
for (i = 0; i <= n; i++)
mark[i] = BEO
for (i = 0; i <= n; i++) 
if (mark[i] == BEO)
if (topsortr(i) != 0) return 1;
return 0;
}
topsortr(i) {
mark[i] = SIV;
for (k = 0; k < susedi[i].size(); k++) {
  j = susedi[i][k];
  if (mark[j] == SIV) return 1;
  if (mark[j] == BEO)
  if (topsortr(j) != 0) return 1;
}
tops[p] = i;
p = p - 1;
mark[i] = CRN;
return 0;
}
```



``` cpp title="04_plus_minus.cpp" linenums="1"
# include <stdio.h>
# include <vector>
# include <algorithm>

using namespace std;

# define MAXN 30030

# define BEO 0
# define SIV 1
# define CRN 2

int n, m, no;

vector<int> susedi[MAXN];

int mark[MAXN];
int tord[MAXN];
int s[MAXN], x[MAXN];

citaj() {
  int i, j, k, zn;
  scanf("%d%d", &n, &m);
  for (k = 0; k <= n; k++)
  	susedi[k].clear();
  for (k = 1; k <= m; k++) {
  	scanf("%d%d%d", &i, &j, &zn);
  	if (zn > 0)
  	  susedi[i-1].push_back(j);
  	else
  	  susedi[j].push_back(i-1);
  }
}

int topordr(int c1) {
  int k, c2;
  mark[c1] = SIV;
  for (k = 0; k < susedi[c1].size(); k++) {
  	c2 = susedi[c1][k];
  	if (mark[c2] == CRN) continue;
  	if (mark[c2] == SIV) return 1;
  	if (topordr(c2) != 0) return 1;
  }
  tord[no--] = c1;
  mark[c1] = CRN;
  return 0;
}

int topord() {
  int k;
  for (k = 0; k <= n; k++) mark[k] = BEO;
  no = n;
  for (k = 0; k <= n; k++) 
    if (mark[k] == BEO)
      if (topordr(k)) return 1;
  return 0;
}

resi() {
  int i, j, k;
  k = 0; 
  while (tord[k] != 0) k++;
  s[0] = 0;
  for (i = k-1, j = -1; i >= 0; i--, j--) 
    s[tord[i]] = j;	
  for (i = k+1, j = 1; i <= n; i++, j++) 
    s[tord[i]] = j;	
  for (k = 1; k <= n; k++) 
    x[k] = s[k] - s[k-1];
}

main() {
  int s, t;
  scanf("%d", &t);
  for (s = 1; s <= t; s++) {
  	citaj();
  	if (topord() != 0)  
    	printf("-1\n");
  	else {
  		resi();
    	printf("1\n");
  		for (int k = 1; k < n; k++)
  	  		printf("%d ", x[k]);
  	  	printf("%d\n", x[n]);
    }    
  }
  return 0;
}

```
