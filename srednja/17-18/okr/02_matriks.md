---
hide:
  - toc
---

# B2 - Matriks

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Prošlo je vreme igre, uživanja i razonode. Prošlo je vreme malih matrica. Danas su računari neverovatno brzi i mogu izvršiti i do $10^{100}$ komandi u sekundi. Iz tog razloga komisija vam je spremila jednostavan zadatak sa jednom matricom i mnogo interesantnih upita. 

U ovom zadatku vam je data matrica $A$ dimenzije $n \times m$ - matrica ima tačno $n$ vrsta i tačno $m$ kolona. Vrste su numerisane brojevima od $1$ do $n$ odozgo nadole a kolone su numerisane brojevima od $1$ do $m$ sleva udesno. Za svako $i$ ($1 \leq i \leq n$) i $j$ ($1 \leq j \leq m$) vrednost na poziciji ($i,j$) u matrici $A$ (tj. na polju u preseku $i$-te vrste $j$-te kolone) je definisana na sledeći način :

$$A_{i,j} = i \ \text{xor} \ j$$

gde operacija $X \ \text{xor} \ Y$ predstavlja ekskluzivnu disjunkciju brojeva $X$ i $Y$.

Potrebno je odgovoriti na $q$ upita oblika: Naći vrednost $\text{xor}$-a svih brojeva u podmatrici matrice $A$ sa gornjim levim temenom $(x_l,y_l)$ i donjim desnim temenom $(x_r,y_r)$. Podmatrica matrice $A$ sa navedenim ograničenjima obuhvata sve elemente $A_{i,j}$ takve da važi  $x_l \leq i \leq x_r$ , $y_l \leq j \leq y_r$.

## Opis ulaza
U prvoj liniji standardnog ulaza nalaze se brojevi $n, m, q$, broj vrsta matrice $A$, broj kolona matrice $A$ i broj upita na koje je potrebno odgovoriti. Narednih $q$ linija sadrže po četiri broja, koji predstaljaju redom vrstu gornjeg levog temena podmatrice, kolonu gornjeg levog temena podmatrice, vrstu donjeg desnog temena podmatrice i kolonu donjeg desnog temena podmatrice.

## Opis izlaza
Na standardnom izlazu u $q$ redova odgovoriti na upite opisane u tekstu zadatka, tačnije u $i$-a liniji standardnog izlaza ispisati rešenje $i$-tog upita.

## Primer
### Ulaz
```
4 5 3
1 1 3 3
2 3 4 5
2 3 2 4
```

### Izlaz
```
0
7
7
```

## Objašnjenje primera
Matrica A je dimenzije $4 \cdot 5$ i ima oblik:
               
```
0 3 2 5 4
3 0 1 6 7
2 1 0 7 6
5 6 7 0 1
```

Prvi upit zadrži podmatricu sa gornjim levim temenom ($1,1$) i donjim desnim ($3,3$). Rešenje ovog upita je $\text{ xor }$ svih brojeva u podmatrici, odnosno : 

$$
0 \text{ xor } 3 \text{ xor } 2 \text{ xor } 3 \text{ xor } 0 \text{ xor } 1 \text{ xor } 2 \text{ xor } 1 \text{ xor } 0  = 0
$$

Treći upit sadrži samo dva broja $1$ i $6$, tako da je rešenja za ovaj primer $1 \text{ xor } 6 =7$ 

## Ograničenja

* $1 \leq n,m \leq 10^9$.
* $1 \leq q \leq 10^5$.

Test primeri su podeljeni u četiri disjunktne grupe.

* U primerima vrednim 20 poena važiće ograničenje $1\leq n,m,q \leq 100$.
* U primerima vrednim 20 poena važiće ograničenje $1\leq n,m \leq 1000$.
* U primerima vrednim 30 poena važiće ograničenje $1\leq n,m \leq 10^6$.
* U primerima vrednim 30 poena nema dodatnih ograničenja.

## Napomena
Operator ekskluzivne disjunkcije u Pascal-u je označen sa `xor`, dok u C++ ga zapisujemo pomoću simbola `^`. Ova operacija $x \ \text{xor} \ y$ se za nenegativne cele brojeve $x,y$ definiše na sledeći način: prvo se brojevi zapišu u binarnom zapisu. Ukoliko jedan broj ima manje cifara od drugog, dopisuju mu se vodeće nule sve dok ne budu imali isti broj binarnih cifara. Tako se dobijaju dva niza binarnih cifara, označimo ih sa $a_1, \ldots, a_k$ i $b_1, \ldots b_k$. Zatim se za svaku poziciju $i \in \{1, \ldots, k \}$ računa $c_i$ pomoću sledećih pravila:

* Za $a_i = 0, b_i = 0$ važi $c_i = 0$
* Za $a_i = 0, b_i = 1$ važi $c_i = 1$
* Za $a_i = 1, b_i = 0$ važi $c_i = 1$
* Za $a_i = 1, b_i = 1$ važi $c_i = 0$

Niz binarnih cifara $c_1, \ldots, c_k$ (koji možda ima vodeće nule) je binarni zapis rezultata, odnosno broja $x \ \text{xor} \ y$.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Nikola Jovanović | Ivan Stošić |

Pođimo od naivnog rešenja: ako za svaki upit računamo traženi $\text{xor}$ prolaskom kroz celu podmatricu ukupna vremenska složenost je $\mathcal{O}(qnm)$, što je dovoljno za **prvi podzadatak** u kom važi $1\leq n,m,q \leq 100$.

Označimo vrednost izraza koji treba izračunati za neku podmatricu sa $S$. U nastavku ćemo operaciju  $\text{xor}$ označavati simbolom $\oplus$. Važi $S = A_{x_ly_l} \oplus \ldots\oplus  A_{x_ry_r} = (x_l \oplus y_l) \oplus \ldots \oplus (x_r \oplus y_r)$. Označimo sada $S_x = x_l \oplus \ldots \oplus x_r$ i $S_y = y_l \oplus \ldots \oplus y_r$. Nezavisnim razmatranjem članova po $x$ i po $y$ u izrazu za $S$ dobijamo $S = (S_x \oplus \ldots \oplus S_x) \oplus (S_y \oplus \ldots \oplus S_y)$ pri čemu prva zagrada ima $\Delta y=y_r - y_l + 1$, a druga $\Delta x=x_r - x_l + 1$ članova (širina i visina podmatrice). Ovakva reprezentacija sledi iz komutativnosti operacije $\text{xor}$ i predstavlja osnovu za poboljšanje našeg rešenja.

Iskoristićemo poznato svojstvo operacije $\text{xor}$: za svako $a$ važi $a \oplus a = 0$. Iz ovoga sledi da je vrednost izraza $a \oplus \ldots \oplus a$ jednaka $a$ ako imamo neparan broj članova, a $0$ u suprotnom. Ako primenimo ovo na dobijenu reprezentaciju $S$ dobijamo da je vrednost prve zagrade jednaka $S_x$  kada je $\Delta y$ neparno, a $0$ kada je parno. Na isti način vrednost druge zagrade je $S_y$ kada je $\Delta x$ neparno, a $0$ kada je parno. Dakle, ako naivno izračunamo vrednosti $S_x$ i $S_y$ možemo u zavisnosti od parnosti dimenzija podmatrice naći $\text{xor}$ svih njenih vrednosti. Ovo nas dovodi do ukupne vremenske složenosti od $\mathcal{O}(q(n+m))$ što je dovoljno za **drugi podzadatak** u kom važi $1\leq n,m \leq 1000$.

Pokušajmo da ubrzamo računanje vrednosti $S_x$ i $S_y$. Ako označimo sa $P(a) = 1 \oplus \ldots \oplus a$ vidimo da je $S_x = P(x_r) \oplus P(x_l - 1)$ i $S_y = P(x_r) \oplus P(x_l - 1)$. Ovo sledi iz svojstva istaknutog u prethodnom pasusu. Ako unapred izračunamo sve potrebne vrednosti $P$ možemo pri svakom upitu računati $S_x$ i $S_y$ u konstantnom vremenu, tj. rešiti zadatak u ukupnoj vremenskoj složenosti od $\mathcal{O}(q)$. Za čuvanje vrednosti  $P$ nam je potreban niz odgovarajuće dužine, pa je ukupna memorijska složenost $\mathcal{O}(m+n)$, što je dovoljno za **treći podzadatak** u kom važi $1\leq n,m \leq 10^6$.

Da bismo došli do optimalnog rešenja smanjićemo memorijsku složenost bez pogoršavanja vremenske, tj. naći način da u konstantnom vremenu izračunavamo vrednosti $P(a)$. Za ovo treba primetiti još jedno, malo komplikovanije, svojstvo operacije $\text{xor}$: 

$$
P(a) =
\begin{cases}
a & \text{za} ~ a = 4k \\
1 & \text{za} ~ a = 4k+1 \\
a+1 & \text{za} ~ a = 4k+2 \\
0 & \text{za} ~ a = 4k+3
\end{cases}
$$

Do ovog svojstva je moguće doći posmatranjem naivno izračunatih vrednosti $P(a)$ ili direktno iz opservacije da svaka četvorka brojeva $(4k, 4k+1, 4k+2, 4k+3)$ u binarnom sistemu ima oblik $(\bar{L}00, \bar{L}01, \bar{L}10, \bar{L}11)$. 

Sada imamo **optimalno rešenje**: za svaki upit u konstantnom vremenu računamo vrednosti $P(a)$ potrebne da bi se dobili $S_x$ i $S_y$. Na osnovu njih, u zavisnosti od parnosti dimenzija podmatrice, računamo traženu vrednost $S$. 

``` cpp title="02_matriks.cpp" linenums="1"
#include<bits/stdc++.h>


using namespace std;

int n,m,q;

int calc(int x)
{
    if (x%4==0) return x;
    if (x%4==1) return 1;
    if (x%4==2) return x+1;
    return 0;
}

int main()
{

    cin>>n>>m>>q;

    while(q--)
    {
        int xl,yl,xr,yr;

        scanf("%d%d%d%d",&xl,&yl,&xr,&yr);

        int ans=0;

        if ((xr&1)==(xl&1))
            ans=calc(yr)^calc(yl-1);

        if ((yr&1)==(yl&1))
            ans^=calc(xr)^calc(xl-1);

        printf("%d\n",ans);
    }

  return 0;
}

```
