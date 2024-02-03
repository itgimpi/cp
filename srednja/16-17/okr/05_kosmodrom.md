---
hide:
  - toc
---

# A2 - Kosmodrom

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 256MB |

Nakon uspešne ekspedicije, na Marsu je izgrađen ,,Bibop'', prvi veliki
kosmodrom u Sunčevom sistemu. Sa njega svakog dana poleće $N$ raketa, i
za svaku raketu se zna njeno planirano vreme poletanja $T_i$ (mereno u
marsovskim sekundama proteklim od ponoći).

Kada raketa treba da poleti, u nju se utovaruje teret koji treba da
ponese. Pošto radnici na kosmodromu drže sve kutije sa teretom
naslagane jednu na drugu, mogu da utovare samo teret iz kutije koja je
na vrhu gomile. Srećom, veoma su brzi -- proces utovarivanja ne zahteva
nimalo vremena. Ako se desi da kutija koju traže nije na vrhu,
lansiranje rakete mora da sačeka dok se ne utovare sve kutije koje su
iznad tražene.

Da bi olakšali ovaj proces lansiranja, na kosmodromu postoji uređaj
koji može da uzme proizvoljan broj kutija sa vrha gomile i prevrne ih
(tako da budu poređane suprotnim redosledom). Pošto je ovaj proces
spor i može oštetiti teret, uređaj se može iskoristiti *samo jednom* i
to *na početku dana* (pre prvog poletanja).

Radnici ,,Bibopa'' su greškom poređali kutije sa teretom po rednim
brojevima raketa umesto po redu letenja (tako da je na vrhu kutija
namenjena za raketu $1$, ispod nje za raketu $2$, i tako dalje). Pomozite
im da odaberu broj kutija koje će okrenuti ovim uređajem, tako da
najduže vreme koje neka od raketa provede čekajući na teret bude što
manje.

## Opis ulaza
U prvom redu standardnog ulaza nalazi se jedan prirodan broj $N$ --
broj raketa koje poleću tokom dana. U drugom redu standardnog ulaza
nalazi se $N$ prirodnih brojeva, $T_1, T_2, \dots, T_N$, gde je
$i$-ti broj vreme poletanja rakete sa rednim brojem $i$.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan prirodan
broj, koji predstavlja minimalno "najduže vreme čekanja", koje se
dostiže za optimalan izbor prevrnutih kutija.

## Primer 1
### Ulaz
```
5
6 3 8 2 5
```

### Izlaz
```
5
```

## Primer 2
### Ulaz
```
3
2 2 1
```

### Izlaz
```
0
```

## Objašnjenje primera
U prvom primeru, prva raketa koja treba da poleti je raketa $4$, dve
sekunde posle ponoći, ali ne može odmah da poleti jer njen teret nije
na vrhu gomile. Sledeća po redu je raketa $2$ (tri sekunde posle
ponoći), koja takođe mora da čeka, a zatim raketa $5$, koja isto čeka.

Nakon što poleti raketa $1$ (šest sekundi posle ponoći), koja ne mora da
čeka na svoju kutiju, raketa $2$ odmah može da poleti, jer je njen teret
sada na vrhu. Ona je, dakle, čekala $6-3=3$ sekunde. Dve sekunde kasnije
(osam sekundi posle ponoći) raketa $3$ poleće bez čekanja, a odmah zatim
i rakete $4$ i $5$, sa čekanjima od $6$ i $3$ sekunde redom.

Ako radnici okrenu gornje četiri kutije, tako da je redosled vremena
poletanja raketa (od vrha gomile do dna) $2,8,3,6,5$, raketa koja
poleće tri sekunde posle ponoći će čekati najduže -- pet
sekundi. Nijedan izbor ne daje čekanja koja su sva kraća od pet
sekundi, tako da je ovo optimalno rešenje.

U drugom primeru, ako se cela gomila prevrne, nijedna raketa ne mora
da čeka -- pošto utovarivanje tereta ne oduzima vreme, nijedna raketa
koja poleće dve sekunde posle ponoći ne mora da čeka.

## Ograničenja
* $1 \leq T_i \leq 10^9$

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede 20 poena važi $1 \leq N \leq 100$.
* U test primerima koji vrede 30 poena važi $1 \leq N \leq 2000$.
* U test primerima koji vrede 50 poena važi $1 \leq N \leq 200000$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dimitrije Erdeljan | Dimitrije Erdeljan | Nepoznato | Slobodan Mitrović |

##Glavno rešenje
Da bismo odredili pronašli optimalno rešenje, isprobaćemo svih $N + 1$
mogućih izbora za broj prevrnutih kutija $K$ (gde $0 \leq K \leq
N$). Neophodno je da za svako $K$ odredimo najveće čekanje, i onda je
ukupno rešenje minimum tih vrednosti.

Najveće čekanje ćemo odrediti tako što za svaku raketu izračunamo
koliko će čekati i uzmemo maksimum tih vrednosti. Ovo možemo da
uradimo u $O(N^3)$ -- nakon što "okrenemo" prvih $K$ elemenata niza
$T$, za svaku kutiju znamo da će se "osloboditi" kada sve kutije iznad
nje budu odnesene, tj. da će $i$-ta kutija biti na vrhu gomile u
trenutku $max(T_j : j < i)$ i samim tim čekati $min(0, T_i - max(T_j :
j < i))$ (na kutiju ne može da se čeka negativno dugo). Računanje ovih
maksimuma u linearnom vremenu (prolaženjem kroz $T$) daje ukupno
kvadratnu složenost za određivanje čekanja svih raketa (za fiksno $K$).

Ako za računanje gore opisanih maksimuma iskoristimo već izračunatu
vrednost za prethodni element niza (posmatramo maksimum prethodne
vrednosti i trenutnog elementa $T_{i-1}$), možemo odrediti sva čekanja
u jednom prolazu kroz niz, tako da je ukupna složenost $O(N^2)$
($O(N)$ za svako $K$).

Za fiksno $K$, kutije možemo podeliti u dve grupe -- one koje su u
prevrnutom delu gomile i kutije ispod prevrnutog dela. Označimo
maksimalna čekanja u ove dve grupe sa $U_K$ i $D_K$ redom.

Za fiksno $K$, najveće čekanje u okrenutom delu gomile je uzrokovano
ili jednom od kutija iz prvih $K-1$ (u originalnom nizu) koja čeka na
$K$-tu (sada gornju), ili čekanjem jedne od prvih $K-1$ na drugu iz
istog skupa. Prva vredmost se može odrediti kao $min(0, T_K - max(T_i
: i < K))$, a druga je jednaka $U_{K-1}$, tako da se ceo niz $U$ može
izračunati u $O(N)$ (opet, neophodno je da pamtimo maksimume svih
prefiksa i računamo ih kao u prethodnom delu).

Pošto na kutije koje nisu okrenute ne utiče raspored kutija iznad njih,
za vremena čekanja koja utiču na $D_K$ možemo uzeti vremena za $K=0$
(koja računamo u $O(N)$ na ranije opisan način), gde je $D_K$ maksimum
sufiksa ovog niza. Kao i za čekanja, ovo možemo odrediti u jednom
prolazu (unazad), na osnovu već izračunatog $D_{K+1}$.

Nakon što u linearnom vremenu izračunamo nizove $U$ i $D$, konačno
rešenje je najmanja vrednost $max(U_i, D_i)$, tako da je ukupna
složenost algoritma $O(N)$.

``` cpp title="05_kosmodrom.cpp" linenums="1"
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 200005;
int a[N], orig_wait[N];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
	scanf("%d", &a[i]);

    int orig_max = 0;
    for(int i = 0; i < n; i++)
    {
	orig_max = max(a[i], orig_max);
	orig_wait[i] = orig_max - a[i];
    }

    for(int i = n - 1; i >= 0; i--)
	orig_wait[i] = max(orig_wait[i], orig_wait[i + 1]);
    
    int top_min = 1 << 30, top_wait = 0;
    int res = orig_wait[0];
    for(int i = 0; i < n; i++)
    {
	top_min = min(a[i], top_min);
	top_wait = max(a[i] - top_min, top_wait);

	res = min(res, max(top_wait, orig_wait[i + 1]));
    }

    printf("%d\n", res);
    
    return 0;
}

```
