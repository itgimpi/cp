---
hide:
  - toc
---

# A2 - Škrinja

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Perice su drugari iz klupa. Oni jednostavno ne prepisuju. Sređujući školski tavan pronašli su škrinju, a u njoj drevni .*pdf* pun algoritama. .*pdf* je pisao stari učitelj Huang-Cu, i posuo blagim mirisom trešnje. Skinuli su prašinu sa njega i pogledali o čemu se tu zapravo radi.

.*pdf* se sastoji od poglavlja sastavljenih od određenog broja strana. Svako poglavlje detaljno opisuje jednu drevnu tehniku algoritama. Pošto su tehnike stvarno komplikovane, i pošto se algoritmi najbolje uče tako što neko objasni, odlučili su da podele posao. **Svaka tehnika biće dodeljena jednom i samo jednom Perici** da je nauči i prezentuje ostalima. Kao dobri drugari tehnike će podeliti **tako da je razlika između broja strana Perice koji ima najviše strana da nauči i Perice koji ima najmanje strana da nauči najmanja moguća**. Pošto Perice još uvek nisu naučile drevne veštine Huang-Cua, ne znaju sami da izvrše tu podelu. Ti ćeš im pomoći.

## Ulaz
U prvom redu standardnog ulaza nalaze se dva prirodna broja $N$ i $K$, broj poglavlja u knjizi i broj Perica, redom. U drugom redu nalazi se $N$ prirodnih brojeva $A_i$ – broj strana $i$-tog poglavlja.

## Izlaz
U prvom redu standardnog izlaza ispisati najmanju moguću razliku između broja strana Perice koji ima najviše strana da nauči i Perice koji ima najmanje strana da nauči. 

U drugom redu ispisati $N$ brojeva gde $i$-ti broj predstavlja Pericu koji treba da nauči $i$-to poglavlje. Ukoliko postiji više rešenja sa najmanjom razlikom, štampati bilo koje.

## Ograničenja:
- $1 \leq N \leq 13$
- $1 \leq K \leq 13$
- $1 \leq A_i \leq 10^8$

Test primeri su podeljeni u četiri disjunktne grupe:

- U test primerima vrednim 10 poena važi $N\leq 3$.
- U test primerima vrednim 30 poena važi $N\leq 8$.
- U test primerima vrednim 30 poena važi $N\leq 11$.
- U test primerima vrednim 30 poena nema dodatnih ograničenja.


## Primer:
### Ulaz
```
5 3
1 3 2 5 3
```

### Izlaz
```
1
1 2 2 3 1
```

### Objašnjenje primera
Imamo $5$ poglavlja knjige i $3$ Perice. Prvi Perica će učiti tehnike $1$ (jedna strana) i $5$ (tri strane), drugi tehnike $2$ (tri strane) i $3$ (dve strane) dok će treći samo tehniku $4$ (pet strana). U ovakvoj podeli Perice imaju redom $4$, $4$ i $5$ strana da nauče što znači da je razlika između Perice koji ima najviše da nauči i Perice koji ima najmanje da nauči jednaka $1$. Za dati primer nije moguće napraviti podelu tako da svi dobiju jednako da nauče, pa je razlika $1$ optimalna.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Dimitrije Dimić | Bogdan Petrović | Nikola Milosavljević |


``` cpp title="05_skrinja.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

const int MAX_N = 20;
const int MAX_SUM = 2000000001;

int n, k, sol;
long long counter = 0LL, counter2 = 0LL;
int a[MAX_N], b[MAX_N], sum[MAX_N], part[MAX_N];

void check()
{
	for (int i = 0; i < k; i++) sum[i] = 0;
	int minSum = MAX_SUM, maxSum = 0;

	for (int i = 0; i < n; i++)
	{
		sum[ b[i] ] = sum[ b[i] ] + a[i];
	}

	for (int i = 0; i < k; i++)
	{
		minSum = (sum[i] < minSum ? sum[i] : minSum);
		maxSum = (sum[i] > maxSum ? sum[i] : maxSum);
	}

	if (maxSum - minSum < sol)
	{
		sol = maxSum - minSum;
		for (int i = 0; i < n; i++)
		{
			part[i] = b[i];
		}
	}
}

void F(int currSet, int currNum, int currMinIndex)
{
	if (currNum >= n)
	{
		return;
	}
	if (currSet == k)
	{
		check();
		//counter++;
		return;
	}

	b[currMinIndex] = currSet;
	for (int mask = 0; mask < (1 << (n - currNum - 1)); mask++)
	{
		counter2++;

		int ind = -1;
		int newMinInd = -1;
		int numOfElems = 1;
		for (int i = currMinIndex + 1; i < n; i++)
		{
			if (b[i] == 0)
			{
				ind++;
				if ((mask & (1 << ind)) != 0) 
				{
					b[i] = currSet;
					numOfElems++;
				}
				else if (newMinInd == -1) newMinInd = i;
			}
		}
		F(currSet + 1, currNum + numOfElems, newMinInd);
		for (int i = currMinIndex + 1; i < n; i++)
		{
			if (b[i] == currSet) b[i] = 0;
		}
	}
	b[currMinIndex] = 0;
}

int main() 
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);

	sol = MAX_SUM;
	for (int i = 0; i <= n; i++)
		b[i] = 0;

	F(1, 0, 0);
	printf("%d\n", sol);

	for (int i = 0; i < n; i++)
		printf("%d ", part[i] + 1);
	printf("\n");

	/*counter = 0LL;
	counter2 = 0LL;
	F(1, 0, 0);
	printf("%lld\n", counter);
	printf("%lld\n", counter2);*/
	return 0;
}
```
