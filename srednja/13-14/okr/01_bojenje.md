---
hide:
  - toc
---

# B1 - Bojenje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 64MB |

Marica, studentkinja prirodno-matematičkog fakulteta, redovno pohađa vežbe iz predmeta “Teorija aproksimacija i kvadraturne formule”. Vežbe su vrlo jednostavne: asistentkinja na tabli napiše $N$ prirodnih brojeva i od studenata traži da ih aproksimiraju a zatim i kvadriraju. Međutim, Marica ne poznaje dovoljno ovu teoriju pa se koncentriše na svoju omiljenu razonodu – bojenje datih brojeva vodenim bojicama.

Marica cifre svakog broja **boji na specifičan način**: cifru $1$ boji crvenom, cifru $2$ plavom, cifru $3$ žutom, cifru $4$ narandžastom, cifru $5$ zelenom i cifru $6$ ljubičastom bojom. Ostale cifre joj nisu zanimljive i njih ne boji. Naravno, ona koristi samo **osnovne boje – crvenu, plavu i žutu**. Za bojenje jedne cifre osnovnom bojom potrebno joj je **$2$ miligrama (mg) odgovarajuće boje** dok joj je za bojenje ostalim bojama potrebno **po $1$ miligram odgovarajućih osnovnih boja**: za narandžastu $1mg$ crvene i $1mg$ žute, za zelenu $1mg$ žute i $1mg$ plave, za ljubičastu $1mg$ plave i $1mg$ crvene boje.

Za datih $N$ prirodnih brojeva, pomozite Marici da izračuna koliko će joj biti potrebno miligrama svake od osnovnih boja da bi ih sve obojila.

## Ulaz
U prvom redu standardnog ulaza nalazi se prirodan broj $N$ – broj brojeva koje Marica planira da oboji. U narednih $N$ redova nalazi se po jedan prirodan broj $A_i$ – brojevi koje treba obojiti.

## Izlaz
U prvom i jedinom redu standardnog izlaza ispisati $3$ cela broja odvojena po jednim razmakom – broj miligrama crvene, plave i žute boje, **u tom redosledu**, neophodan Marici za traženo bojenje.

## Primer 1
### Ulaz
```
2
123
34086
```

### Izlaz
```
4 3 5
```

## Objašnjenje primera
Potrebno je obojiti dva broja. Za bojenje prvog broja ($123$) potrebno je po $2mg$ svake od osnovnih boja. Za bojenje drugog broja: za cifru $3$ je potrebno $2mg$ žute, za cifru $4$ po $1mg$ crvene i žute, cifre $0$ i $8$ se ne boje, za cifru $6$ po $1mg$ plave i crvene. Ukupno je potrebno $4mg$ crvene, $3mg$ plave i $5mg$ žute boje.

## Ograničenja

* $1 \leq N \leq 10^5$.
* $1 \leq A_i \leq 10^9$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim $30$ poena važi $1\leq A_i\leq 9$, tj. svi brojevi su jednocifreni.
* U test primerima vrednim $30$ poena važi $N=1$.
* U test primerima vrednim $40$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Milica Mićić | Dimitrije Dimić |

## Rešenje za $1 \leq A_i \leq 9$, odnosno kad su svi brojevi jednocifreni
Sve cifre su već odvojene i njihov broj je poznat pošto je svaki broj jednocifren. Za svaku od cifara je potrebno proći kroz slučajeve kako bi se utvrdilo koja je i u skladu sa brojem treba dodati po $1$ mg određene dve boje (za brojeve $4$, $5$ ili $6$) ili $2$ mg određene boje (za brojeve $1$, $2$ ili $3$) ili ništa (za sve ostale brojeve). Vremenska složenost: $O(N)$, memorijska složenost: $O(1)$.

## Rešenje za $N=1$
Dat je samo jedan broj koji može imati bilo koliko cifara. Tom broju skidamo poslednju cifru i za nju kao u prethodnoj grupi primera proveravamo koje boje je potrebno iskoristiti za farbanje i u kojoj količini. Proces se ponavlja dok se celobrojnim deljenjem broja sa $10$ ne dobije nula. Vremenska složenost: $O(logN)$, memorijska složenost: $O(1)$.

## Glavno rešenje
Ideja za rešavanje prethodnog primera se sad koristi na svakom od $N$ brojeva pojedinačno, dok se količina crvene, plave i žute farbe potrebnih sabira za sve brojeve. Vremenska složenost: $O(NlogN)$, memorijska složenost: $O(1)$.

``` cpp title="01_bojenje.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

int red, blue, yellow;
int n, num;

int main()
{
	red = 0; blue = 0; yellow = 0;
	scanf("%d", &n);
	
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &num);
		while (num > 0)
		{
			switch (num % 10)
			{
			case 1: red += 2; break;
			case 2: blue += 2; break;
			case 3: yellow += 2; break;
			case 4: red++; yellow++; break;
			case 5: yellow++; blue++; break;
			case 6: blue++; red++; break;
			}
			num /= 10;
		}
	}

	printf("%d %d %d\n", red, blue, yellow);
	return 0;
}
```
