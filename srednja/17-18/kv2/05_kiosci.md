---
hide:
  - toc
---

# 5 - Kiosci

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Poznati prodavac magle Džoni Fog je odlučio da svoj biznis proširi u jednom od najvećih gradova na svetu - Nišu, jer je čuo da se tamo od prodaje magle baš lepo živi. Poznato je da je Niš organizovan kao Njujork tj. sastoji se od $m$ paralelnih horizontalnih avenija i $m$ paralelnih vertikalnih bulevara u čijem se preseku nalazi  $m^2$ raskrsnica; označimo raskrsnicu u preseku $i$-te avenije i $j$-tog bulevara sa $(i,j)$. Kako su rastojanja između susednih avenija i susednih bulevara jednaka $1$ km, jasno je da je rastojanje između raskrsnica $(a,b)$ i $(c,d)$ jednako $|a-c| + |b-d|$ km. Džoni planira da otvori kioske magle na nekim raskrsnicama i da prodaje maglu na kilo.

Međutim, prodavcima magle nije lako - ukoliko se npr. pojave predstavnici zakona, Džoni mora da hvata maglu i prenosi je iz svih svojih kioska na neko sigurno mesto. Poznato je da je za prenos jednog kilograma magle na rastojanju od $1$ kilometar potreban $1$ minut. Pomozite Džoniju da isplanira svoje vreme tako što ćete simulirati $n$ upita nekog od sledeća dva tipa:

 - $1$ $x$ $y$ $v$ - Džoni otvara novi kiosk sa $v$ kilograma magle na raskrsnici $(x,y)$;
 - $2$ $x$ $y$ - Džonija zanima koliko bi mu minuta trebalo da prenese maglu iz svih trenutno otvorenih kioska na raskrsnicu $(x,y)$.

Ukoliko pomognete Džoniju, dobijate $5$kg magle!

## Opis ulaza

U prvom redu standardnog ulaza nalaze se dva prirodna broja $n$ i $m$, broj upita i broj avenija/bulevara, redom. U narednih $n$ redova nalaze se odgovarajući upiti: ili $4$ prirodna broja $1$ $x_i$ $y_i$ $v_i$ (ukoliko je u pitanju upit tipa $1$) ili $3$ prirodna broja $2$ $x_i$ $y_i$ (ukoliko je u pitanju upit tipa $2$) čije je značenje dato u opisu upita.

## Opis izlaza

Za svaki upit tipa $2$ ispisati, u posebnom redu i odgovarajućem redosledu, jedan prirodan broj - odgovor na taj upit.

## Primer 1
### Ulaz
```
5 20
1 3 7 10
1 2 2 8
2 5 3
1 10 10 3
2 1 1
```

### Izlaz
```
92
150
```

## Primer 2
### Ulaz
```
2 1000000000
1 1 1 10000
2 1000000000 1000000000
```

### Izlaz
```
19999999980000
```

## Objašnjenje primera

U prvom test primeru, prvo se otvori kiosk $10$kg magle na raskrsnici $(3, 7)$, zatim se otvara kiosk sa $8$kg magle na raskrsnici $(2, 2)$. Za sledeći upit, treba izračunati vreme prebacivanja magle iz ova dva kioska na raskrsnicu $(5, 3)$. Rastojanje između raskrsnica $(3, 7)$ i $(5, 3)$ je $|5-3| + |3-7| = 6$, rastojanje između raskrsnica $(2, 2)$ i $(5, 3)$ je $4$, pa je za ovaj poduhvat potrebno $10 \cdot 6 + 8 \cdot 4 = 92$ minuta. U sledećem upitu se otvara kiosk sa $3$kg magle na raskrsnici $(10, 10)$. U poslednjem upitu treba izračunati vreme prebacivanja magle iz otvorena $3$ kioska na raskrsnicu $(1,1)$ što je $80 + 16 + 54 = 150$ minuta.

## Ograničenja

* $2 \leq n \leq 250.000$.
* $1 \leq m \leq 10^9$.
* $1 \leq x_i, y_i \leq m$.
* $1 \leq v_i \leq 10^4$.
* Moguće je da se više različitih prodavnica otvori na istoj raskrsnici.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima koji vrede $10$ poena važiće $n \leq 5.000$.
* U test primerima koji vrede $20$ poena važiće $n \leq 150.000$ i $m \leq 10^3$.
* U test primerima koji vrede $20$ poena svi upiti tipa $1$ biće pre svih upita tipa $2$.
* U test primerima koji vrede $25$ poena važiće $m \leq 300.000$.
* U test primerima koji vrede $25$ poena nema dodatnih ograničenja.






#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Ivan Stošić |

Označimo sa $(x_i, y_i)$ koordinate a sa $v_i$ količinu magle u $i$-tom po redu otvorenom kiosku. Jasno je da je za svaki upit tipa 2 sa parametrima $(x, y)$ potrebno izračunati sumu $\sum_{i=1}^k (|x - x_i| + |y - y_i|)\cdot v_i$, gde je $k$ trenutni broj izgrađenih kioska. Direktno računanje sume za svaki upit dovodi do rešenja složenosti $O(n^2)$ što je dovoljno samo za prvi podzadatak. Jedno korisno (i, kada se radi sa Menhetn rastojanjima, vrlo standardno) zapažanje je da se prethodna suma **može nezavisno posmatrati po $x$ i $y$ koordinatama**; dakle, dovoljno je rešiti problem računanja sume  $\sum_{i=1}^k |x - x_i|\cdot v_i$,  primeniti isti algoritam za $y$ koordinate i sabrati dve dobijene vrednosti na kraju.

Ukoliko je $m$ dovoljno mala vrednost, možemo koristiti pomoćne nizove $vx[]$ i $vy[]$ dužine $m$ gde je $vx[a] =$ suma vrednosti $v_i$ za sve izgrađene kioske čija je $x$-koordinata jednaka $a$ (analogno i za niz $vy[]$). Prilikom dodavanja novog kioska $(x_i, y_i, v_i)$, ažuriramo informacije sa $vx[x_i] \leftarrow vx[x_i] + v_i$ dok prilikom upita tipa 2 $(x, y)$, tražena suma se svodi na $\sum_{i=1}^m |x - i|\cdot vx[i]$. Ovim smo dobili algoritam složenosti $O(nm)$ koji koristi $O(m)$ memorije, što rešava drugi podzadatak. 

U trećem podzadatku, nakon učitavanja svih upita tipa 1, nema više promena; posmatrano po jednoj koordinati, zadatak postaje ekvivalentan "težinskoj" verziji zadatka Prodavnice sa prvog kruga kvalifikacija (videti odgovarajuće rešenje). Sortiranjem upita tipa 1 na početku i koristeći binarnu pretragu za upite tipa 2 dobiijamo rešenje složenosti $O(n \log n)$.

Motivisani rešenjem drugog podzadatka, neka je $A[i]$ suma vrednosti $v$ za sve kioske sa $x$-koordinatom $i$, a neka je $B[i] = i \cdot A[i]$ (na početku su oba niza popunjena nulama). Tražena suma (za upit $(x,y)$) se može transformisati kao

$$
\sum_{i=1}^k |x - x_i|\cdot v_i = \sum_{i=1}^m |x - i|\cdot A[i] = \sum_{1 \leq i \leq x} (x \cdot A[i] - B[i]) + \sum_{x < i \leq m} (B[i] - x \cdot A[i])
$$

$$
= 2x \cdot \sum_{1 \leq i \leq x} A[i] - 2 \cdot \sum_{1 \leq i \leq x} B[i] - (x \cdot totalA - totalB)
$$

gde su $totalA$ i $totalB$, redom, sume svih elemenata nizova $A$ i $B$. Zadatak se sada svodi na sledeće: prilikom upita tipa 1 $(x, y, v)$ treba ažurirati $A[x] \leftarrow A[x] + v$ i $B[x] \leftarrow B[x] + x \cdot v$ (kao i $totalA$ i $totalB$), dok prilikom upita tipa 2 $(x, y)$ treba izračunati sume $\sum_{1 \leq i \leq x} A[i]$ i $\sum_{1 \leq i \leq x} B[i]$ i ubaciti ih u gornju formulu.

Međutim, ovo je poznati problem koji se najefikasnije rešava pomoću **Kumulativne tabele** ili **Segmentnog stabla** nad nizovima $A$ i $B$ (i, naravno, odgovarajućim nizovima za $y$-koordinate). Koristeći ove strukture, dobijamo složenost $O(\log n)$ po upitu, tj. ukupno $O(n \log n)$. Kako ove strukture zahtevaju $O(m)$ memorije, pravolinijska implementacija je dovoljna za prva 4 podzadatka. Da bismo očuvali ovu složenost, finalni pozadatak je potrebno raditi '*offline*' uz par trikova: učitati sve koordinate i kompresovati ih na segment $[1,n]$ (npr. sortiranjem) uz odgovarajuće mapiranje - time se memorijska složenost svodi na $O(n)$. Memorijsko ograničenje je dozvoljavalo i da se zadatak radi '*online*' koristeći **Implicitno segmentno stablo** - u tom slučaju je vremenska i memorijska složenost algoritma $O(n \log m)$.

``` cpp title="05_kiosci.cpp" linenums="1"
/* online solution with implicit segment tree */

#include <cstdlib>
#include <cstdio>

const int MAX_N = 250000;
const int MAX_LOG_M = 31;

struct SegmentTree
{
	struct node
	{
		int left, right;
		long long sumVal;
		long long sumProd;
		node()
		{
			left = 0; right = 0;
			sumVal = 0LL; sumProd = 0LL;
		}
	};

	node nodes[MAX_N * MAX_LOG_M];
	int currNode;
	int M;

	void init(int m)
	{
		M = m;
		currNode = 1;
	}

	void update(int nodeNum, int curr_l, int curr_r, int ind, int val)
	{
		if (ind < curr_l || ind > curr_r)
			return;
		nodes[nodeNum].sumVal += val;
		nodes[nodeNum].sumProd += (long long)ind * val;

		if (curr_l != curr_r)
		{
			int mid = (curr_l + curr_r) / 2;

			if (nodes[nodeNum].left == 0)
				nodes[nodeNum].left = ++currNode;
			update(nodes[nodeNum].left, curr_l, mid, ind, val);
			if (nodes[nodeNum].right == 0)
				nodes[nodeNum].right = ++currNode;
			update(nodes[nodeNum].right, mid + 1, curr_r, ind, val);
		}
	}

	long long query(int nodeNum, int curr_l, int curr_r, int l, int r, int ind)
	{
		if (nodeNum == 0 || r < curr_l || l > curr_r)
			return 0LL;
		if (l <= curr_l && curr_r <= r)
		{
			return (nodes[nodeNum].sumVal * ind - nodes[nodeNum].sumProd);
		}

		int mid = (curr_l + curr_r) / 2;
		return query(nodes[nodeNum].left, curr_l, mid, l, r, ind) + query(nodes[nodeNum].right, mid + 1, curr_r, l, r, ind);
	}

	void bulidKiosk(int ind, int val)
	{
		update(1, 1, M, ind, val);
	}

	long long getTotalTime(int ind)
	{
		long long sol = query(1, 1, M, 1, ind, ind);
		sol = sol * 2 - nodes[1].sumVal * ind + nodes[1].sumProd;
		return sol;
	}
};

SegmentTree treex, treey;

int n, m;

int main()
{
	scanf("%d%d", &n, &m);
	treex.init(m);
	treey.init(m);

	for (int i = 1; i <= n; i++)
	{
		int type, x, y, v;
		scanf("%d", &type);
		if (type == 1)
		{
			scanf("%d%d%d", &x, &y, &v);
			treex.bulidKiosk(x, v);
			treey.bulidKiosk(y, v);
		}
		else
		{
			scanf("%d%d", &x, &y);
			long long sol = treex.getTotalTime(x) + treey.getTotalTime(y);
			printf("%lld\n", sol);
		}

	}
	return 0;
}
```
