---
hide:
  - toc
---

# 5 - Nagrade

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Kao što se inače često dešava u takmičarskim zadacima, našli ste se u čudnoj situaciji: dato vam je $N$ gomila novčića ($i$-ta gomila sadrži $A_i$ novčića). Planirate da organizujete $N$ takmičenja, gde ćete za svako od njih iskoristiti jednu gomilu kao nagradni fond ($A_1$ za prvo, $A_2$ za drugo, i tako dalje). 

Za svako takmičenje treba da odaberete koliko će učesnika biti nagrađeno (obeležićemo broj nagrađenih na $i$-tom takmičenju sa $B_i$). Sve nagrade na jednom takmičenju su iste, tako da $A_i$ mora biti deljivo sa $B_i$. Dodatno, sve vrednosti $B_i$ moraju biti prosti brojevi (niste sigurni zašto, ali neko vam je rekao da je to dobra ideja).

Da bi ciklus takmičenja bio interesantniji, planirate da odaberete vrednosti $B_i$ tako da su nagrade na svim takmičenjima različite, tj. da za svaki par vrednosti $(i,j)$ važi $\frac{A_i}{B_i} \neq \frac{A_j}{B_j}$. Vaš zadatak je da napišete program koji će pronaći ovakvu podelu ili utvrditi da to nije moguće.

## Opis ulaza
U prvom redu standardnog ulaza nalazi se jedan ceo broj $N$ -- broj takmičenja koja organizujete. U drugom redu nalazi se $N$ brojeva $A_1, A_2, \ldots, A_N$, koji predstavljaju broj novčića u nagradnim fondovima pojedinačnih takmičenja.
 
## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati $N$ brojeva $B_1, B_2, \ldots, B_N$ -- broj nagrađenih takmičara na svakom takmičenju, tako da su uslovi iz teksta zadatka zadovoljeni. Ukoliko to nije moguće, ispisati $-1$.

Ukoliko postoji više rešenja, ispisati bilo koje.

## Primer 1
### Ulaz
```
4
10 8 15 7
```

### Izlaz
```
2 2 5 7
```

## Primer 2
### Ulaz
```
2
2 7
```

### Izlaz
```
-1
```

## Objašnjenje primera
U prvom primeru, jedno moguće rešenje je da se na prvom takmičenju dodele dve nagrade od po $5$ novčića, na drugom dve od po $4$, na trećem pet od po $3$ i na četvrtom sedam nagrada od po jednog novčića. Pošto su sve nagrade različite, i na svakom takmičenju je nagrađen prost broj takmičara, ova podela zadovoljava date uslove. Moguća su i druga rešenja, na primer da se na prvom takmičenju nagradi pet, a na trećem tri takmičara.

U drugom primeru, jedino rešenje gde je nagrađen prost broj takmičara je `2 7` (jer $1$ nije prost broj). Kako su na njemu nagrade na oba takmičenja iste (po jedan novčić), ono ne zadovoljava sve uslove, tako da ne postoji rešenje.

## Ograničenja

* $1 \leq N$.
* $1 \leq A_i$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede $20$ poena važi $N \leq 8, A_i \leq 1000$.
* U test primerima koji vrede $20$ poena važi $N \leq 1000, A_i \leq 3000$.
* U test primerima koji vrede $60$ poena važi $N \leq 1000, A_i \leq 200000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Boris Grubić | Dimitrije Erdeljan | Dimitrije Erdeljan | Ivan Stošić |

Prvo, za svaki broj sa ulaza nađimo sve različite proste brojeve koji ga dele. Ovo se može uraditi efikasno pomoću modifikacije Eratostenovog sita, kojom se svaki broj $x < M$ može faktorizovati u logaritamskoj složenosti, gde je $M$ gornja granica za Eratostenovo sito.

Ovih različitih prostih brojeva ima ne više od $6$, jer je proizvod najmanjih $7$ prostih brojeva veći od $2 \times 10^5$. Sada, za svaki broj nađimo količnik njega i svakog različitog prostog broja koji ga deli. Neka je za $i$-ti broj $P_i$ lista njegovih različitih prostih delilaca a $C_i$ lista  koja se dobija kada se $A_i$ podeli sa svakim elementom liste $P_i$. Cilj zadatka je da nađemo niz različitih brojeva $B$ tako da je za svako $i$, $B_i = A_i / P_{i, j} = C_{i, j}$ za neko $j$. Ovaj problem je poznat i pod nazivom sistem različitih predstavnika familije skupova $C$. Ovo se može rešiti u polinomijalnom vremenu tako što se predstavi kao bipartitni graf, gde su čvorovi sa leve strane indeksi iz originalnog niza, a sa desne strane količnici. Za svako $i$ dodajemo granu od čvora $i$ sa leve strane do čvorova $C_{i, j}$ sa desne, za svako $j$. Svaki sistem različitih predstavnika sada odgovara jednom perfektnom sparivanju (mečingu) u ovom grafu, odnosno mečingu gde je svaki čvor sa leve strane sparen. Dakle želimo da ispitamo da li ovako dobijen graf ima mečing sa $N$ grana i koji je to mečing.

Najjednostavniji i najpoznatiji algoritam jeste Ford-Fulkersonov algoritam koji radi u složenosti $O(VE)$, gde je $V$ broj čvorova, a $E$ broj grana u grafu, što u našem slučaju, zbog gore pomenutog ograničenja na broj grana iznosi $O(N^2)$. Primetimo da ne moramo da dodajemo sve čvorove sa desne strane već samo one koji se bar jednom pojavljuju kao količnici.

``` cpp title="05_nagrade.cpp" linenums="1"
#include <iostream>
#include <map>
#include <vector>

const int P = 2000005;
bool is_prime[P];
std::vector<int> primes;

void gen_primes()
{
    for(int i = 0; i < P; i++)
	is_prime[i] = true;

    for(int i = 2; i < P; i++)
	if(is_prime[i])
	{
	    primes.push_back(i);
	    for(int j = 2 * i; j < P; j += i)
		is_prime[j] = false;
	}
}

const int N = 10000;
struct node
{
    int v;
    node *next;
    bool valid;
    node(int vv, node *n, bool x) { v = vv; next = n; valid = x; } 
} *graph[N];

std::map<int, int> factors;
std::vector<int> vals;

int register_factor(int x)
{
    if(factors.find(x) != factors.end())
	return factors[x];
    factors[x] = vals.size();
    vals.push_back(x);

    return vals.size() - 1;
}

void add_edge(int i, int j)
{
    graph[i] = new node(j, graph[i], true);
    graph[j] = new node(i, graph[j], false);
}

bool mark[N];
int prev[N];

bool dfs(int curr, int sink)
{
    if(curr == sink) return true;

    for(node *i = graph[curr]; i; i = i->next)
	if(i->valid && !mark[i->v])
	{
	    mark[i->v] = true;
	    if(dfs(i->v, sink))
	    {
		i->valid = false;
		for(node *j = graph[i->v]; j; j = j->next)
		    if(j->v == curr)
			j->valid = true;
		return true;
	    }
	}

    return false;
}

int matching(int left)
{
    int n = vals.size() + 2;
    int source = n - 2, sink = n - 1;

    for(int i = 0; i < left; i++)
	add_edge(source, i);
    for(int i = left; i < source; i++)
	add_edge(i, sink);

    int res = 0;
    while(true)
    {
	for(int i = 0; i < n; i++)
	    mark[i] = false;
	
	if(!dfs(source, sink)) break;
	res++;
    }

    return res;
}

int main()
{
    gen_primes();

    int n;
    std::cin >> n;
    vals.resize(n);

    for(int i = 0; i < n; i++)
    {
	std::cin >> vals[i];

	int n_f = 0;
	int last = 0;

	int curr = vals[i];
	for(int p : primes)
	{
	    if(p * p > curr) break;
	    if(curr % p == 0)
	    {
		n_f++;
		last = p;
		add_edge(i, register_factor(vals[i] / p));

		curr /= p;
	    }
	}

	if(n_f && curr != 1)
	    add_edge(i, register_factor(vals[i] / curr));
	if(n_f == 0 && vals[i] > 1)
	    add_edge(i, register_factor(1));
    }

    int res = matching(n);
    if(res != n)
	std::cout << -1 << std::endl;
    else
    {
	for(int i = 0; i < n; i++)
	    for(node *j = graph[i]; j; j = j->next)
		if(!j->valid)
		    std::cout << vals[i] / vals[j->v] << " ";
	std::cout << std::endl;
    }

    return 0;
}

```
