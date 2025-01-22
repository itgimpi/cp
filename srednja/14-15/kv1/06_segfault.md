---
hide:
  - toc
---

# 6 - Segfault

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 64MB |

Mali Perica i njegov kolega, haker mali Nikolaj, kao i svi hakeri, vole da u slobodno vreme igraju igricu «SIGSEGV», u kojoj se dva hakera takmiče za prevlast nad tuđom RAM memorijom. Da bi uspeli u svom cilju, treba da naprave programe koji zauzimaju što više polja te memorije za njih. 

Pravila igre su sledeća:

* RAM memorija je predstavljena kao matrica RAM[,]; svako polje te matrice može da bude ili **slobodno**, ili da **pripada nekom od hakera**, ili da **pripada korisniku mašine**.
* Programi koje Perica i Nikolaj pišu kreću iz nekog polja matrice, i smeju da izvrše samo **jednu vrstu komande**: ”pomeri se na polje direktno gore, dole, levo ili desno, i pokušaj da ga zauzmeš”. 
* Ukoliko program pokuša da zauzme polje koje ne pripada njegovom hakeru, a nije slobodno, dobija segfault (segmentation fault) i **prestaje sa radom**; međutim haker **zadržava za sebe svu memoriju koju je taj program zauzeo**.
* Hakeri mogu **paralelno da pokrenu više ovakvih programa**, ukoliko imaju pristup procesoru sa više jezgara. Programi se mogu pokretati **samo na početku igre**

Oba hakera su na različite načine stekli nepoštene prednosti u ovoj igri:

* Nikolaj je uspeo da učini zahteve zauzimanja brzim, tako da ukoliko i Perica i Nikolaj pokušaju da **u isto vreme** zauzmu neko slobodno polje, **Nikolajev program će ga zauzeti a Peričin program će prestati sa radom**.
* Nikolaj poseduje procesor sa $K$ jezgara, tako da **može da pokrene $K$ programa** na početku.
* Nikolaj je ubacio virus u Peričine programe, čiji efekat je da **svi Peričini programi moraju krenuti iz istog polja**.
* Perica je saznao **celokupno početno stanje memorije**, kao i sve Nikolajeve programe; pošto Nikolaj ne zna stanje memorije, **svi Nikolajevi programi se uvek kreću u jednom smeru**.
* Perica je takođe ubacio virus u Nikolajeve programe; efekat je da **Nikolajevi programi kreću sa radom tek nakon što Peričini zauzmu početno polje**.
* Perica poseduje najnoviji Pintel Core i∞ procesor koji ima beskonačno jezgara; tako da Perica na startu igre može pokrenuti **bilo koji broj programa**.

Pericu interesuje koliko najviše polja ove matrice može zauzeti ukoliko igra optimalno. Pomozite mu.

## Opis ulaza
U prvom redu standardnog ulaza nalaze se dva prirodna broja $N$ i $M$, odvojena razmakom, koji predstavljaju dimenzije RAM memorije. 

U narednih $N$ redova nalazi se po $M$ karaktera koji predstavljaju početno stanje memorije (RAM[i,j] je predstavljen $j$-tim karakterom u $i$-tom redu):

* karakter '.' predstavlja slobodno polje;
* karakter '#' predstavlja polje koje je zauzeo korisnik mašine;
* karakter 'S' predstavlja polje iz kojeg moraju poći svi Peričini programi.

U narednom redu nalazi se prirodan broj $K$, koji predstavlja broj jezgara koje ima Nikolajev procesor. U svakom od narednih $K$ redova nalazi se opis jednog od Nikolajevih programa u obliku $X$ $Y$ $DIR$ (parametri odvojeni razmakom), gde su $X$ i $Y$ prirodni brojevi koji predstavljaju početno polje tekućeg programa (koje nije zauzeto pre početka igre), a $DIR$ je karakter koji označava jedini smer u kome će tekući Nikolajev program da se kreće: 'U' - gore, 'D' - dole, 'L' - levo, 'R' - desno.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati broj polja memorije koje Perica može zauzeti ukoliko igra optimalno.

## Primer 1
### Ulaz
```
6 5
#.S.#
.....
..... 
...##
##...
...##
2
2 1 R
3 5 L
```

### Izlaz
```
18
```

## Objašnjenje primera
Ukoliko Perica pokrene program koji će da napravi prva dva koraka nadole, stanje table se menja na sledeći način (označimo sa 'P' polja koja poseduje Perica a 'N' polja koja poseduje Nikolaj):

```
#.P.#    #.P.#    #.P.#
.....    N.P..    NNP..
..... => ....N => ..PNN
...## => ...## => ...##
##...    ##...    ##...
...##    ...##    ...##
```

U narednom koraku, oba Nikolajeva programa će dobiti segfault, što ostavlja Pericu slobodnim da zauzme sva preostala slobodna polja (sveukupno će imati po tri u svakom redu matrice, tj. 18).

## Ograničenja
* $1 \leq N, M \leq 1000$
* RAM[i,j] pripada skupu {‘.’,‘#’,‘S’}.
* Tačno jedno polje u matrici 𝑅𝐴𝑀[,] će biti ‘𝑆’.
* $1\leq K \leq 5\cdot 10^5$
* $1\leq X\leq N$
* $1\leq Y \leq M$
* RAM[X, Y] $\neq$ '#'
* DIR pripada skupu {‘U’,‘D’,‘L’,‘R’}

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim 50 poena važi $N,M,K\leq 600$.
* U test primerima vrednim 20 poena važi $K\leq 1000$.
* U test primerima vrednim 30 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Petar Veličković | Nemanja Majski | Aleksandar Ivanović |

## Rešenje za $N,M,K \le 600$
Kako Perica može da pusti beskonačno mnogo programa, a programa dužine $N\cdot M$ ima konačno mnogo, možemo da pretpostavimo da će Perica da pusti sve njih. To znači da ako je Percija zauzeo neko polje, on će u sledećem potezu zauzeti sva njegova susedna polja, osim ako ih Nikolaj ili korisnik mašine nije već zauzeo. 

Za ovaj podzadatak je dosta da se radi simulacija Pericinog zauzimanja, što može da se uradi preko BFS-a. Samo treba za svako polje koje Perica zauzme da se proveri da li ga je Nikolaj zauzeo pre njega, što možemo da uradimo preko for petlje.

Vremenska složenost je $O(N\cdot M\cdot K)$.

## Rešenje za $K \le 1000$
Ovde je neophodno odratiti prekalkulaciju. Za svako polje, treba da odredimo trenutak kada će neki od Nikolajevih programa da zauzme to polje pod pretpostavkom da ih pre toga ne zauzme Perica. Ta prekalkulacija može da se uradi dvostrukom petljom u složenosti $O(K \cdot max(N,M))$. 

Nakon toga ćemo pustiti BFS kao u prošlom podzadatku. Ali, umesto da proveravamo petljama da li je Nikolaj već zauzeo to polje, možemo da pogledamo da li je prekalkulisano vreme zauzimanja manje ili jednako od vremena kada Pericin program stigne na to polje.

Ukupna vremenska složenost je $O(K \cdot max(N,M) + N\cdot M)$.

## Glavno rešenje
Glavna ideja je da ako program koji ide na neku stranu dođe na polje gde je bio neki drugi program koji ide na istu tu stranu, originalni program može da prestane sa radom pošto će drugi program doći na svako sledeće polje pre njega. Sa ovom modifikacijom, složenost prekalkulacije je amortizovano $O(N \cdot M + K)$, a ukupna složenost $O(N\cdot M + K)$.

``` cpp title="06_segfault.cpp" linenums="1"
/*
 Author: Petar 'PetarV' Velickovic
 Task: Segfault
*/

#include <stdio.h>
#include <queue>

#define MAX_N 1001
#define INF 987654321

using namespace std;

int n, m, l;

char line[MAX_N];
bool blok[MAX_N][MAX_N];
bool mark[MAX_N][MAX_N];

int sx, sy;
int lx, ly;
char ldir[5];

queue<int> lqX, lqY, lqI, lqT, pqX, pqY, pqT;
bool lmark[MAX_N][MAX_N][4];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

inline int BFS()
{
    int ret = 0;
    int curr_t = 0;
    
    while (!pqX.empty() || !lqX.empty())
    {
        while (!lqX.empty() && lqT.front() == curr_t)
        {
            int xt = lqX.front(); lqX.pop();
            int yt = lqY.front(); lqY.pop();
            int it = lqI.front(); lqI.pop();
            int tt = lqT.front(); lqT.pop();
            
            if (lmark[xt][yt][it]) continue;
            if (blok[xt][yt]) continue;
            if (mark[xt][yt]) continue;
            
            lmark[xt][yt][it] = true;
            
            int xt1 = xt + dx[it];
            int yt1 = yt + dy[it];
            
            if (xt1 < 0 || xt1 > n - 1 || yt1 < 0 || yt1 > m - 1) continue;
            if (blok[xt1][yt1]) continue;
            if (lmark[xt1][yt1][it]) continue;
            if (mark[xt1][yt1]) continue;
            
            lqX.push(xt + dx[it]);
            lqY.push(yt + dy[it]);
            lqI.push(it);
            lqT.push(tt + 1);
        }
        
        while (!pqX.empty() && pqT.front() == curr_t)
        {
            int xt = pqX.front(); pqX.pop();
            int yt = pqY.front(); pqY.pop();
            int tt = pqT.front(); pqT.pop();
        
            if (lmark[xt][yt][0] || lmark[xt][yt][1] || lmark[xt][yt][2] || lmark[xt][yt][3]) continue;
            if (blok[xt][yt]) continue;
            if (mark[xt][yt]) continue;
            
            mark[xt][yt] = true;
            ret++;
        
            for (int i=0;i<4;i++)
            {
                int xt1 = xt + dx[i];
                int yt1 = yt + dy[i];
                int tt1 = tt + 1;
            
                if (xt1 < 0 || xt1 > n - 1 || yt1 < 0 || yt1 > m - 1) continue;
                if (lmark[xt1][yt1][0] || lmark[xt1][yt1][1] || lmark[xt1][yt1][2] || lmark[xt1][yt1][3]) continue;
                if (blok[xt1][yt1]) continue;
                if (mark[xt1][yt1]) continue;
            
                pqX.push(xt1);
                pqY.push(yt1);
                pqT.push(tt1);
            }
        }
        
        curr_t++;
    }
    
    return ret;
}

int main()
{
    scanf("%d%d", &n, &m);
    
    for (int i=0;i<n;i++)
    {
        scanf("%s", line);
        for (int j=0;j<m;j++)
        {
            if (line[j] == 'S') sx = i, sy = j;
            else if (line[j] == '#') blok[i][j] = true;
        }
    }
    
    scanf("%d", &l);
    
    while (l--)
    {
        scanf("%d%d%s", &lx, &ly, ldir);
        lx--; ly--;
        
        int idd;
        if (ldir[0] == 'U') idd = 0;
        else if (ldir[0] == 'R') idd = 1;
        else if (ldir[0] == 'D') idd = 2;
        else if (ldir[0] == 'L') idd = 3;
        
        lqX.push(lx);
        lqY.push(ly);
        lqI.push(idd);
        lqT.push(1);
    }
    
    pqX.push(sx);
    pqY.push(sy);
    pqT.push(0);
    
    printf("%d\n", BFS());
    
    return 0;
}
```
