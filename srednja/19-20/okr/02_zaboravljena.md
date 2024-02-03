---
hide:
  - toc
---

# B2 - Zaboravljena partija

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |


Pera i Mika vole da igraju uopšteni iks-oks, igru sa dva igrača sa
sledećim pravilima:

* igra se na tabli sa **$N$ redova i $N$ kolona**,
* igrači igraju naizmenično,
* u svakom potezu, trenutni igrač **obeležava jedno slobodno polje
  svojim simbolom**: X za prvog igrača, odnosno O za drugog, i
* pobednik je onaj koji **prvi napravi niz koji čini $K$ uzastopnih
  simbola** tog igrača (horizontalno, vertikalno ili dijagonalno).
  Ukoliko se tabla popuni, a ovaj uslov ne ispuni, rezultat partije je
  nerešen.

Pera i Mika se sećaju da su juče igrali odličnu partiju uopštenog
iks-oksa, ali se ne sećaju kako je ta partija išla, osim da je jedan
od njih dvojice pobedio i da je trajala tačno $T$ poteza. Zanima ih
kako bi ta partija mogla da izgleda, tako da od vas traže da im date
jedan mogući primer, ili da im kažete da su nešto pogrešno upamtili i
da takva partija ne može da postoji.

## Opis ulaza

U prvom i jedinom redu standardnog ulaza nalaze se tri broja: $N$, $K$
i $T$, koji redom predstavljaju dimenziju table na kojoj se igra
uopšteni iks-oks, broj uzastopnih simbola potreban za pobedu, i
broj poteza koji su Pera i Mika odigrali.

## Opis izlaza

Ukoliko ne postoji partija koja se uklapa u podatke date na ulazu, u
jedinoj liniji izlaza ispisati `nemoguce`. 

U suprotnom, u prvih $N$ redova ispisati po $N$ karaktera, koji
predstavljaju stanje table nakon završetka partije, gde su `X` i `O`
(**velika slova**) simboli prvog i drugog igrača, a `.` prazno polje.
Između polja **ne treba** ispisati razmake.

U naredni red ispisati dva broja $i$ i $j$: red i kolonu polja na kojem
je odigran poslednji potez (gde gornjem levom polju odgovaraju koordinate
$(1, 1)$, tj. kolone se broje sa leva na desno, a redovi od gore na
dole).

Ukoliko postoji više partija koje se uklapaju u date podatke,
**ispisati bilo koju**.

## Primer 1

### Ulaz

```
4 3 5
```

### Izlaz

```
XXX.
....
..O.
...O
1 3
```

## Primer 2

### Ulaz

```
2 2 4
```

### Izlaz

```
nemoguce
```

## Objašnjenje primera

Jedan mogući redosled polja na koja su Pera i Mika upisivali svoje
simbole u prvoj partiji je $(1,1), (4,4), (1,3), (3,3), (1,2)$.

U drugom primeru, kako god da su Pera i Mika igrali, nakon trećeg
poteza bi postojala dva susedna polja sa simbolom `X`, tako da bi prvi
igrač tada pobedio. Dakle, partija koja bi trajala četiri poteza ne
postoji.

## Ograničenja

- $2 \leq N \leq 100$
- $2 \leq K \leq N$
- $1 \leq T \leq N^2$

Test primeri su podeljeni u 4 disjunktne grupe:

- U test primerima vrednim 20 poena: $N = K = 3$.
- U test primerima vrednim 25 poena: $K = 2$.
- U test primerima vrednim 25 poena: $T \leq \frac{N^2}{4}$.
- U test primerima vrednim 30 poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dimitrije Erdeljan | Dimitrije Erdeljan | Dimitrije Erdeljan | Aleksandar Zlateski |

Za početak, treba odrediti da li je uopšte moguće generisati tablu
kakva se traži u zadatku. Ukoliko $T < 2K-1$, očigledno nije, jer ni
jedan igrač neće stići da postavi $K$ simbola neophodnih za pobedu. U
suprotnom, rešenje uvek postoji (što će biti jasno iz algoritma koji ga
generiše), osim ukoliko je $K = 2$ i $T > N \cdot \lceil \frac{N}{2}
\rceil + 1$. Da bi dokazali da u ovom slučaju nema rešenja, možemo
podeliti tablu na $2 \times 2$ kvadrate i primetiti da pre poslednjeg
poteza u svakom od njih može biti najviše jedan `X` i jedan `O`.

Rešenje za proizvoljno $T$ možemo napraviti od rešenja gde $T = N^2$ (`X`
pobeđuje u poslednjem potezu), odnosno $T = N \cdot \lceil \frac{N}{2}
\rceil + 1$ ako $K = 2$, na sledeći način:

* ukoliko je $T$ parno (`O` treba da pobedi), zamenimo sve `X` sa `O`
  i obrnuto,
* izračunamo koliko će `X` i `O` biti na tabli posle $T$ poteza, i
* brišemo simbole dok ne ostane očekivan broj, vodeći računa da ne
  obrišemo nijedan iz niza od $K$ uzastopnih zbog kog je jedan od
  igrača pobedio.
  
Ostaje samo da konstruišemo takvo rešenje. Ovo ćemo uraditi odvojeno za
tri slučaja: $K = 2$, $K = 3$ i $K > 3$

## $K = 2$

Tablu možemo popuniti na sledeći način (naizmenični `X` i `O`) u
svakom drugom redu (primer za $N = 7$):

~~~
XOXOXOX
*......
OXOXOXO
.......
XOXOXOX
.......
OXOXOXO
~~~

Igrač koji igra poslednji potez igra na polje obeleženo sa `*`.

## $K = 3$

Počećemo od table na kojoj ni jedan igrač ne pobeđuje:

~~~
xOXOXOX
XoXOXOX
OXOXOXO
OXOXOXO
XOXOXOX
XOXOXOX
OXOXOXO
~~~

Primetimo da, ukoliko zamenimo polja $(1,1)$ i $(2,2)$ (obeležena malim
slovima), dobijamo tablu na kojoj `X` pobeđuje u poslednjem potezu ako
"za kraj" ostavi $(2, 2)$.

## $K > 3$

Slično kao za $K = 3$, počećemo od table u kojoj niko ne pobeđuje,
koju konstruišemo na sledeći način:

* U prvom redu imamo $K-1$ simbola `X`, zatim jedan `O`, pa opet $K-1$
  `X`, i tako dalje.
* Drugi red je isti, sa zamenjenim `X` i `O`.
* Dalje redove pravimo naizmeničnim ponavljanjem ova dva.
* Ukoliko je $N$ neparno, da bi imali očekivani broj `X` i `O`,
  poslednji red čine naizmenični `X` i `O`.
  
Na primer, za $N = 7, K = 4$:

~~~
XXXXoxX
OOOOXOO
XXXXOXX
OOOOXOO
XXXXOXX
OOOOXOO
XOXOXOX
~~~

Slično kao u prošlom slučaju, možemo zameniti prvi `O` sa `X` koji se
nalazi posle njega i dobiti poziciju u kojoj `X` "čuva" potez $(1, K)$
za kraj i pobeđuje u poslednjem potezu.

Ukoliko $N = K$, ne možemo zameniti ova dva simbola (jer nema ničeg
desno od tog `O`). U ovom slučaju, nije teško videti da umesto toga
možemo zameniti prvi `O` sa poljem $(3, 1)$.

``` cpp title="02_zaboravljena.cpp" linenums="1"
#include <cstdio>
#include <algorithm>

#define IMPOSSIBLE "nemoguce\n"

const int N = 105;
char board[N][N];
int n, k, t;

char other_player(char p) { return p == 'X' ? 'O' : 'X'; }

void replace(char a, char b)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(board[i][j] == a)
                board[i][j] = b;
}

void swap_xo()
{
    replace('X', '?');
    replace('O', 'X');
    replace('?', 'O');
}

void delete_until(char c, int cnt)
{
    int total = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(board[i][j] == c)
                total++;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(board[i][j] == c && total > cnt)
            {
                board[i][j] = '.';
                total--;
            }
}

int main()
{
    scanf("%d %d %d", &n, &k, &t);

    if(t < 2*k - 1)
    {
        printf(IMPOSSIBLE);
        return 0;
    }
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            board[i][j] = '.';
    int last_i, last_j;
    
    if(k == 2)
    {
        int max_draw = n * ((n+1)/2);
        if(t > max_draw + 1)
        {
            printf(IMPOSSIBLE);
            return 0;
        }

        char last = (t % 2) ? 'X' : 'O';  // we'll modify t, save this now
        
        char curr = 'X';
        for(int i = 0; i < n; i += 2)
            for(int j = 0; j < n; j++)
                if(t > 1)
                {
                    board[i][j] = curr;
                    t--;
                    curr = other_player(curr);
                }

        board[1][0] = last;
        last_i = 1; last_j = 0;
    }
    else if(k == 3)
    {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                board[i][j] = (i/2 + j) % 2 ? 'O' : 'X';
        std::swap(board[0][0], board[1][1]);
        for(int i = 0; i < 3; i++)
            board[1][i] = '*';
        last_i = last_j = 1;
    }
    else
    {
        for(int i = 0; i < n - n%2; i++)
        {
            char curr = i % 2 ? 'O' : 'X';
            for(int j = 0; j < n; j++)
                board[i][j] = (j % k != k - 1) ? curr : other_player(curr);
        }
        if(n % 2)
            for(int j = 0; j < n; j++)
                board[n - 1][j] = j % 2 ? 'O' : 'X';

        if(n == k)
        {
            std::swap(board[0][n - 1], board[2][0]);
            last_i = 0; last_j = n - 1;
            for(int i = 0; i < n; i++)
                board[0][i] = '*';
        }
        else
        {
            std::swap(board[0][k - 1], board[0][k]);
            last_i = 0; last_j = k - 1;
            for(int i = 0; i < k; i++)
                board[0][i] = '*';
        }
    }

    if(k > 2)
    {
        if(t % 2 == 0) swap_xo();
        int want_x = (t + 1) / 2;
        int want_o = t - want_x;

        // '*' that get replaced
        if(t % 2 == 0) want_o -= k;
        else want_x -= k;
        
        delete_until('X', want_x);
        delete_until('O', want_o);
        replace('*', t % 2 == 0 ? 'O' : 'X');
    }
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n+1; j++)
            printf("%c", j == n ? '\n' : board[i][j]);
    printf("%d %d\n", last_i + 1, last_j + 1);
    return 0;
}

```
