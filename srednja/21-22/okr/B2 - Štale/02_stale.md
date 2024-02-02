---
hide:
  - toc
---

# B2 - Štale

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |



U ovom zadatku opustićemo se od užurbanog gradskog života i baviti se konjima i štalama. Trenutno obilazite farmu koju predstavlja dvodimenzionalna ravan sa štalama koje predstavljaju tačke u ovoj ravni. Vi ste na konju koji mnogo voli ceo broj $c$ i u jednom koraku može preći duž od tačke $(x,y)$ do $(x+ac,y+bc)$, gde $a,b \in \{-1,0,1\}$ (**dakle, može otići $c$ polja u levo, desno, gore ili dole, kao i "po dijagonali"**). Ukoliko se neka štala nađe na putu konja (na krajevima ove duži ili negde na njoj), smatramo da smo je **obišli**. Želimo da znamo koliko najviše štala možemo obići ako krećemo iz **proizvoljne štale od onih datih u ulazu** (nije važan broj koraka, niti iko brani konju da više puta bude u istoj tački).

## Opis ulaza
U prvom redu dati su razmakom razdvojeni brojevi $n$ i $c$ ($n$ je broj štala, a $c$ omiljeni broj konja). Zatim se unose $n$ redova, i u $i$-tom od njih dati su razmakom razdvojeni celi brojevi $x_i$ i $y_i$, koji predstavljaju $x$ i $y$ koordinatu $i$-te štale (nikoje dve štale se ne preklapaju).

## Opis izlaza
U jedinom redu izlaza potrebno je ispisati traženi rezultat.

## Primer 1

### Ulaz
```
4 3
0 0
0 5
6 4
2 1
```

### Izlaz
```
4
```

### Objašnjenje primera
Ako krenemo od štale $(0,5)$, u dva koraka stižemo do $(0,-1)$, krećući se duž $y$ ose, tako prolazeći kroz prvu štalu. Na dijagonali od $(0,-1)$ do $(3,2)$ nalazi se i štala $(2,1)$, te tako nju obiđemo. Sada smo u $(3,2)$ i idemo u jednom koraku do $(6,2)$ krećući se "na desno" dok onda odemo "na gore" i dođemo do $(6,5)$, prošavši kroz poslednju štalu, čime je naš obilazak svih 4 štala završen.

## Primer 2

### Ulaz

```
5 4
1 1
1 6
4 12
-1 0
-1 -2
```

### Izlaz

```
4
```


## Ograničenja:
- $n \leq 200.000$
- $1 < c < 100$
- $-10^9 < x_i,y_i < 10^9$

Primeri su podeljeni u 5 disjunktnih grupa: 

- U test primerima vrednim 15 poena: $n \leq 8$
- U test primerima vrednim 25 poena: $n \leq 18$
- U test primerima vrednim 10 poena: $c = 2$
- U test primerima vrednim 25 poena: $n \leq 2000$
- U test primerima vrednim 25 poena: nema dodatnih ograničenja

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Momčilo Tošić | Momčilo Tošić | Vladimir Milovanović | Andrej Ivašković |

Prema postavci zadatka, konj se, iz proizvoljne tačke, može kretati horizontalno, vertikalno, kao i (anti-)dijagonalno. Dodatno ograničenje je da se konj, polazeći iz neke tačke, isključivo kreće po dvodimenzionalnoj rešetki puteva, odnosno mreži tačaka koje su međusobno udaljene $s$ jedna od druge. Nije teško uvideti da iz određene tačke u kojoj se trenutno nalazi, konj može proći kroz bilo koju drugu tačku koja se nalazi na pomenutoj rešetki puteva.

## Kvadratno rešenje za 65 poena

Dovoljno je u dve ugnežđene petlje proći po svim štalama i ispitati da li je moguće doći od jedne do druge, računajući da se od $i$-te do $j$-te štale (naravno, samo za indekse $i \neq j$) može doći ako im se poklapaju horizontalne ($x$) ili vertikalne ($y$) koordinate ili se pak poklapa razlika ili zbir vertikalnih i horizonalnih koordinata (to jest nalaze se dijagonalno/antidijagonalno jedna od druge), pri čemu se 4 pomenutih jednakosti (jednake vrednosti $x$, $y$, $x-y$, $x+y$) računaju po modulu $c$ uz uslov da moduo bude pozitivan. Kako se u svakoj od dve petlje prolazi kroz sve štale i čuva maksimum, ovo rešenje ima kvadratnu vremensku složenost, odnosno $\mathcal{O}(n^2)$, gde $n$ predstavlja broj štala.

## Glavno rešenje u linearnoj složenosti

Da bi se zadatak uradio na efikasan način, svrsishodno je makar prividno preslikati dvodimenzionalnu ravan $(x, y)$ na matricu dimenzija $c \times s$. Preslikavanje se vrši tako što se polje u $i$-toj vrsti i $j$-oj koloni pomenute matrice popunjava sa onoliko štala koliko ih se nalazi na koordinatama $x \mod c = i$ i $y \mod c = j$. Sve što je tada potrebno učiniti jeste pronaći polje u matrici sa najvećim zbirom ostalih elemenata koji se nalaze u istoj vrsti i koloni, kao i na istoj dijagonali i antidijagonali, tačnije sam zbir pomenutih elemenata sa trenutnim poljem koji zapravo predstavlja traženo rešenje zadatka. Prilikom prolaska kroz matricu treba biti pažljiv i obratiti pažnju da se samo polje kroz koje se prolazi ne uračuna više puta, kao i to da se, za parno $c$, polja na (produženoj) dijagonali i antidijagonali mogu poklapati, odnosno da se (produžene) dijagonale mogu seći. Kako je sama operacija preslikavanja ravni na matricu linearna po $n$, to jest $\mathcal{O}(n)$, a prolazak kroz matricu u opštem slučaju kvadratan po njenim dimenzijama, preciznije $\mathcal{O}(c^2)$, jasno je iz postavke zadatka u kojoj se kaže da je $n\leq200'000$, a $c\leq100$, pa je $n>c^2$, prvi član dominantan, te je i ukupna vremenska složenost rešenja, pod ovakvim pretpostavkama, linearna po broju štala.

## Alternativno rešenje

Kako je uslov da se iz tačke $(x_1,y_1)$ tačka $(x_2, y_2)$ može obići: $x_1 = x_2 \lor y_1 = y_2 \lor x_1-y_1 = x_2-y_2 \lor x_1+y_1 = x_2+y_2$, gde je jednakost po modulu $c$, to možemo za svaku tačku tražiti broj tačaka za koji važi ovaj uslov kao broj elemenata unije 4 skupa (skup svih sa određenom $x$ ili $y$ koordinatom, ili određenom razlikom/zbirom dveju koordinata). Ovo se može rešiti formulom uključenja-isključenja za 4 skupa, gde veličine preseka brojimo višedimenzionalnim matricama (ukupna memorijska složenost je $\mathcal{O}(c^4)$, što je u praksi i dosta manje od $512$ MB, dok je vremenska linearna jer svaku štalu ubacujemo u konstantan broj skupova koji služe za prebrojavanje).

``` cpp title="02_stale.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;
void fix(int &x, int c){
    if(x < 0){
        x += c;
    }
}//A - x
//B - y
//C - x+y
//D - x-y
int x[200100], y[200010];
int A[100],B[100],C[100],D[100],AB[100][100],AC[100][100],AD[100][100],BC[100][100],BD[100][100],CD[100][100],ABC[100][100][100],ABD[100][100][100],ACD[100][100][100],BCD[100][100][100],ABCD[100][100][100][100];

int main(){
        int n, c;
        cin >> n >> c;
        for(int j = 0; j < n; ++j){
            cin >> x[j] >> y[j];
            int xMod = x[j]%c, yMod = y[j]%c, xmyMod = (x[j]-y[j])%c, xpyMod = (x[j]+y[j])%c;
            fix(xMod,c);
            fix(yMod,c);
            fix(xmyMod,c);
            fix(xpyMod, c);
            A[xMod]++;
            B[yMod]++;
            C[xpyMod]++;
            D[xmyMod]++;
            AB[xMod][yMod]++;
            AC[xMod][xpyMod]++;
            AD[xMod][xmyMod]++;
            BC[yMod][xpyMod]++;
            BD[yMod][xmyMod]++;
            CD[xpyMod][xmyMod]++;
            ABC[xMod][yMod][xpyMod]++;
            ABD[xMod][yMod][xmyMod]++;
            ACD[xMod][xpyMod][xmyMod]++;
            BCD[yMod][xpyMod][xmyMod]++;
            ABCD[xMod][yMod][xpyMod][xmyMod]++;
        }
        int ans = 1;
        for(int j = 0; j < n; ++j){
            int xMod = x[j]%c, yMod = y[j]%c, xmyMod = (x[j]-y[j])%c,xpyMod = (x[j]+y[j])%c;
            fix(xMod,c);
            fix(yMod,c);
            fix(xmyMod,c);
            fix(xpyMod, c);
            ans = max(ans, A[xMod] + B[yMod]+ C[xpyMod] + D[xmyMod] -
                      AB[xMod][yMod] - AC[xMod][xpyMod] - AD[xMod][xmyMod] - BC[yMod][xpyMod] - BD[yMod][xmyMod] - CD[xpyMod][xmyMod] +
                      ABC[xMod][yMod][xpyMod] + ABD[xMod][yMod][xmyMod] + ACD[xMod][xpyMod][xmyMod] + BCD[yMod][xpyMod][xmyMod] -
                      ABCD[xMod][yMod][xpyMod][xmyMod] );
        }
        cout << ans << '\n';
        return 0;
    }

```
