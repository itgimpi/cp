---
hide:
  - toc
---

# 4 - Boje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |


Kao odmor od kvalifikacija, odlučili ste da uzmete tablu sa $N$ redova (numerisanih od 1 do $N$) i $M$ kolona (numerisanih od 1 do $M$) , i da je obojite u razne boje. Neka polja na tabli su već bila crna, pa ste odlučili da obojite ostala polja tako da važi sledeće:

- nijedno polje **ne obojite u crno**,
- **susedna polja obojite istom bojom** (polja su susedna ako dele ivicu, tako da jedno polje može imati najviše četiri suseda), i
- tabla sadrži **što više različitih boja**.

Vaš zadatak je da odredite koliko će vam različitih boja (ne računajući crnu) biti potrebno da obojite tablu.

## Opis ulaza

U prvoj liniji standardnog ulaza nalaze se tri broja $N$, $M$ i $K$, gde su $N$ i $M$ redom broj redova i kolona table, a $K$ je broj crnih polja.

U narednih $K$ redova nalaze se po dva broja $A_i$ i $B_i$, koji predstavljaju red i kolonu $i$-tog crnog polja.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati jedan broj: broj boja potrebnih da bi se tabla obojila u skladu sa datim uslovima.

## Primer 1

### Ulaz

```
4 4 5
1 1
2 2
3 3
4 4
1 3
```

### Izlaz

```
3
```

## Primer 2

### Ulaz

```
2 4 2
2 2
2 4
```

### Izlaz

```
1
```

# Objašnjenje primera

Jedan primer bojenja table date u prvom primeru se može videti na sledećoj slici.

![](https://petljamediastorage.blob.core.windows.net/root/Media/Default/Takmicenja/Kvalifikacije/boje.png)



U drugom primeru, jedini način da se zadovolje svi uslovi je da se sva polja koja nisu crna oboje istom bojom.

## Ograničenja

- $1 \leq A_i \leq N$ i $1 \leq B_i \leq M$.
- $0 \leq K \leq 100000$.
- Postoji barem jedno belo polje.

Test primeri su podeljeni u 4 disjunktne grupe:

- U test primerima vrednim 20 poena, $N, M \leq 10$.
- U test primerima vrednim 20 poena, $N, M \leq 1000$.
- U test primerima vrednim 20 poena, $N, M \leq 10^9$ i $K \leq 3000$.
- U test primerima vrednim 40 poena, $N, M \leq 10^9$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Dimitrije Erdeljan | Vladimir Milenković | Slobodan Mitrović |


## Analiza
Lako je videti da se ovaj zadatak može svesti na traženje broja povezanih komponenti među poljima koja nisu obojena. Svaku takvu komponentu možemo obojiti novom obojom. U ostatku rešenja ćemo opisati kako se broj povezanih komponenti može efikasno naći pod ograničenjima datim u ovom zadatku.


## Rešenje u $O(N \cdot M)$
Da bismo pronašli broj komponenti, jednostavno možemo da primenimo Depth First Search (DFS) algoritam od svakog neobojenog polja koje nismo do sada ovim algoritmom posetili. Pošto broj čvorova i grana u grafu koji predstavljaju neobojena polja ima složenost $O(N \cdot M)$, ovaj pristup bi bio vrlo spor za najveće test primere.

Posmatrajmo primer gde je $N = M = 10^9$ i $K = 10^5$. U tom primeru postoje "veliki" delovi table koji su neobojeni a povezani. Intuitivno, umesto da svako polje tih "velikih" delova posmatramo kao čvor, bilo bi zgodno ako bismo ceo "veliki" deo posmatrali kao jedan čvor. U tom slučaju bi gore opisani DFS-pristup imao daleko manju složenost. Naravno, glavno pitanje ovde je kako izabrati velike delove tako da je zgodno sa njima raditi, a usput svesti broj čvorova koje posmatramo na mali broj. U ostatku rešenja ćemo se fokusirati na ovo pitanje.


## "Veliki" delovi table i rešenje u $O(K \cdot \log{K})$
Sada ćemo objasniti kako da od ulaza napravimo graf koji ima $O(K)$ čvorova i $O(K)$ grana.

### Čvorovi
Najpre, uzastopne kolone koji nemaju ijedno crno polje ćemo posmatrati kao jedan čvor. Pošto je, sem prvog i poslednjeg, svaki takav čvor ograničen kolonama koje imaju bar jedno crno polje, broj takvih čvorova je najviše $K + 1$.


Posmatrajmo sada kolonu koja ima bar jedno crno polje. Ako kolona ima $t$ crnih polja tada se ona može izdeliti u $t + 1$ ili manje nizova uzasotpnih neobojenih polja. Svaki od tih nizova ćemo posmatrati kao poseban čvor. Takvih čvorova ima najviše $2 K$.

### Grane
Da bismo izlistali grane, posmatraćemo po dve susedne kolone i čvorove koje one definišu, pod uslovom da bar jedna od kolona ima bar jedno crno polje. (Dve susedne kolone koje nemaju crna polja su deo istog čvora.) Neka je $C_1$ lista čvorova prve, a neka je $C_2$ lista čvorova druge kolone. Svaki čvor $v$ je predstavljen kao par $(a, b)$, što znači da je $v$ podniz uzastopnih neobojenih polja koji se u odgovarajućoj koloni pružaju između redova $a$ i $b$. Pretpostavimo da su čvorovi u $C_1$ i $C_2$ sortirani u rastućem poretku po prvoj koordinati. Tada, se sledeći algoritam može primeniti da se nađu sve grane između čvorova u $C_1$ i $C_2$.

Neka je $v_1 = (a_1, b_1) \in C_1$ trenutni čvor koji obrađujemo u $C_1$, a $v_2 = (a_2, b_2) \in C_2$ trenutni čvor koji obrađujemo u $C_2$. Na početku, $v_1$ je prvi čvor iz $C_1$, a $v_2$ je prvi čvor iz $C_2$. Primenjujemo sledeće sve dok nismo prošli sve čvorove iz bar $C_1$ ili $C_2$:
- Ako $b_1 < a_2$, postavimo $v_1$ da bude sledeći čvor u $C_1$.
- Ako $b_2 < a_1$, postavimo $v_2$ da bude sledeći čvor u $C_2$.
- Inače, dodamo granu između $v_1$ i $v_2$. Ako je $b_1 < b_2$, onda postavimo $v_1$ da bude sledeći čvor u $C_1$, a inače postavimo $v_2$ da bude sledeći čvor u $C_2$.

Nije teško proveriti da se na ovaj način zaista definišu sve grane između čvorova u $C_1$ i $C_2$. Pored toga, svaki put kad se doda grana čvor $v_1$ ili čvor $v_2$ se pomere za jedan mesto. To znači da se u ovom procesu doda najviše $|C_1| + |C_2|$ grana. Pošto je svaka kolona susedna sa najviše dve druge kolone i pošto smo rekli da je ukupan broj čvorova $K + 1 + 2 K$, ovim procesom se doda najviše $2 (3K + 1)$ grana.


Da bismo pronašli broj povezanih komponenti nad ovakvim grafom možemo da primenimo DFS; alternativno, umesto DFS-a možemo iskoristiti union-find strukturu. Cortiranje čvorova u koloni $C$ se može uraditi u vremenu $O(|C| \log{|C|})$, tako da je ukupna složenost celog algoritma $O(K \log{K})$.

## Alternativno rešenje
Ovaj zadatak sa takođe može rešiti primenom Ojlerove formule za planarne grafove. Naime, ako nam je dat planaran graf $G$ na $n$ čvorova, sa $m$ grana, $f$ povezanih oblasti i $c$ komponenti, tada važi $n - m + f = 1 + c$. Ovu formulu možemo iskoristiti da rešimo zadatak na sledeći način.

Za četiri polja koja imaju koordinate $(x, y)$, $(x, y + 1)$, $(x + 1, y)$, $(x + 1, y + 1)$ kažemo da čine 2x2 kvadrat.

Zamislićemo da je tabla oivičena trakom crne boje. Celu tu traku ćemo posmatrati kao jedan čvor. Potom, u centar svakog crnog polja ćemo staviti čvor. Povezaćemo dva čvora granom ako odgovarajuća crna polja dele makar jedno teme, i pored toga izbacićemo grane koje spajaju naspramna polja u 2x2 crnom kvadratu (granu koja spaja polja $(x, y)$ i $(x + 1, y + 1)$, i granu koja spaja polja $(x + 1, y)$, $(x, y + 1)$). Ove grane izbacujemo da bismo očuvali planarnost. Primetimo da je ova definicija susednih crnih polja drugačija nego ona u postavci zadatka. Takođe ćemo povezati traku koja oivičava tablu sa svakim čvorom koji dodiruje ivicu table, tj., sa svakim čvorom koji se nalazi u prvom ili u poslednjem redu ili u prvoj ili u poslednjoj koloni. Ovaj graf je planaran. Pored toga, graf ima $O(K)$ grana, tako da vrednost $c$ možemo lako naći, na primer, DFS algoritmom.

Koristeći navedenu formulu možemo da izračunamo $f$. Ali šta predstavlja $f$? Najpre, svaka četiri čvora koja čine 2x2 kvadrat će u ovoj definiciji planarnog grafa formirati jednu povezanu oblast. Takođe će i svaka tri čvora u "G obliku" (tj. imaju koordinate $(x, y)$, $(x, y + 1)$, $(x + 1, y)$) i rotacijama ove konfiguracije činiti povezane oblasti. Pored ovih oblasti, $f$ broji povezane oblasti koje odgovaraju neobojenim poljima, što je upravo broj onih oblasti koje su rešenje ovog problema. Dakle, da bismo rešili ovaj problem, potrebno je da od $f$ oduzmemo 2x2 crne kvadrate.

Za implementiranje DFS-a možemo smestiti sva crna polja u hash mapu, ili na primer u strukturu map u C++. Pristupom ovoj mapi je onda lako naći koje susede ima dati čvor.

Da rezimiramo, da bismo rešili problem, potrebno je da: (1) napravimo graf kao što je to opisano; (2) izračunamo $c$; (3) prebrojimo 2x2 crne kvadrate, i prebrojimo crne kvadrate koji čine "G oblik" i njegove rotacije; i (4) koristeći navedenu formulu izračunamo rešenje ovog problema.

``` cpp title="04_boje.cpp" linenums="1"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

const int N = 500005;
int set[N], rank[N], n_dsu;

int n, m, n_pts;

int push() { set[n_dsu] = n_dsu; rank[n_dsu] = 0; return n_dsu++; }
int find(int x) { return set[x] == x ? x : find(set[x]); }
void join(int x, int y)
{
    x = find(x); y = find(y);
    if(x == y) return;
    if(rank[x] < rank[y])
        set[x] = y;
    else
    {
        set[y] = x;
        rank[x] += rank[x] == rank[y];
    }
}

struct block { int start, end, colour; } ;

void join_all(std::vector<block> &a)
{
    for(int i = 0; i < a.size() - 1; i++)
    {
        join(a[i].colour, a[i + 1].colour);
    }
}

void join_all(std::vector<block> &a, std::vector<block> &b)
{
    for(int i = 0; i < a.size() - 1; i++)
        join(a[i].colour, a[i + 1].colour);
    for(int i = 0; i < b.size() - 1; i++)
        join(b[i].colour, b[i + 1].colour);
    if(a.size() && b.size())
        join(a[0].colour, b[0].colour);
}


void join_pairs(std::vector<block> &a, std::vector<block> &b)
{
    int j = 0;
    for(int i = 0; i < b.size(); i++)
    {
        while(j < a.size() && a[j].end < b[i].start) j++;
        while(j < a.size() && a[j].start <= b[i].end)
        {
            join(a[j].colour, b[i].colour);
            j++;
        }
        if(j) j--;
    }
}

void try_add_empty(std::map<int, std::vector<block>> &blocks, int x, std::vector<int> &existing_rows)
{
    if(x < 0 || x >= n) return;
    if(blocks.find(x) == blocks.end())
    {
        blocks[x].push_back({0, m - 1, push()});
        existing_rows.push_back(x);
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &n_pts);

    std::map<int, std::vector<int>> points;
    for(int i = 0; i < n_pts; i++)
    {
        int ii, jj;
        scanf("%d %d", &ii, &jj);
        ii--; jj--;
        points[ii].push_back(jj);
    }

    std::map<int, std::vector<block>> blocks;
    std::vector<int> existing_rows;
    for(auto &row : points)
    {
        row.second.push_back(m);
        sort(row.second.begin(), row.second.end());

        int prev_j = -1;
        for(int point : row.second)
        {
            block curr = {prev_j + 1, point - 1, -1};
            if(curr.start <= curr.end)
            {
                curr.colour = push();
                blocks[row.first].push_back(curr);
            }
            prev_j = point;
        }

        if(blocks.find(row.first) != blocks.end())
            existing_rows.push_back(row.first);
    }

    // ugly hack
    for(auto &row : points)
    {
        try_add_empty(blocks, row.first - 1, existing_rows);
        try_add_empty(blocks, row.first + 1, existing_rows);
    }
    std::sort(existing_rows.begin(), existing_rows.end());

    for(int i = 0; i < existing_rows.size(); i++)
    {
        int prev = i ? existing_rows[i - 1] : -1;
        int curr = existing_rows[i];
        int next = i < existing_rows.size() - 1 ? existing_rows[i + 1] : n;

        // prev or next row empty
        if(prev != curr - 1 || next != curr + 1)
            join_all(blocks[curr]);

        // adjacent rows
        if(i && prev == curr - 1)
            join_pairs(blocks[prev], blocks[curr]);

        // empty between
        if(i && prev != curr - 1)
            join_all(blocks[prev], blocks[curr]);
    }
    
    std::set<int> colours;
    for(int i = 0; i < n_dsu; i++)
        colours.insert(find(set[i]));

    printf("%d\n", colours.size());
    
    return 0;
}


```
