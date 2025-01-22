---
hide:
  - toc
---

# 1 - Vorp spejs

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 400ms | 64MB |

Nakon što su ti prsti, masni od Smokija, skliznuli sa upravljača i nehotice pritisnuli dugme na kome je pisalo "vorp-spid", tvoj svemirski brod, Milenijumski Soko Štark, našao se izgubljen u vorp-spejsu. Ljuljanje broda uzrokovano jakim gravitacionim talasima ubrzo je učinilo da dobiješ morsku bolest. Ne želeći da polusvareni Smoki završi na komandama tvog broda, pritiskaš dugme sa natpisom "Tutanj!", koje te u najkraćem mogućem vremenu odvodi do izlaza iz vorp-spejsa, a to je vorm-hol čiji se drugi kraj nalazi u tvom wc-u na planeti Zemlji.


Par decenija ranije, u 2019. godini, evo tebe kako programiraš svoj budući svemirski brod. Poznavajući svoj slab stomak, predviđaš situaciju u kojoj ćeš hitno morati da napustiš vorp-spejs, te želiš da napišeš program koji će tvoj broj odvesti do izlaza u što kraćem vremenu.


Vorp-spejs ima oblik tabele dimenzija $D_x \times D_y$ ($D_x$ je broj kolona, a $D_y$ je broj vrsta). Na jednom od polja vorp-spejsa se nalazi tvoj brod, i na jednom od polja se nalazi izlaz (brod i izlaz mogu biti i na istom polju). U jednoj jedinici vremena tvoj brod može da pređe na neko od susedna četiri polja vorp-spejsa (gore, dole, levo ili desno). Međutim, vorp-spejs je uvrnut, pa **ako se nađeš na polju uz njegovu ivicu i pokušaš da se pomeriš u pravcu te ivice, osvanućeš na polju koje se nalazi na suprotnoj strani vorp-spejsa**. Preciznije, ako se nalaziš u prvoj vrsti i pokušaš da ideš gore, pojavićeš se u istoj koloni, ali u poslednjoj vrsti; i obrnuto, ako se nalaziš u poslednjoj vrsti i pokušaš da ideš dole, pojavićeš se u istoj koloni, ali u prvoj vrsti. Slično važi i za levo i desno - pomeranjem u levo u prvoj koloni, završićeš u poslednjoj koloni iste vrste; i obrnuto, pomeranjem u desno u poslednjoj koloni, završićeš u prvoj koloni iste vrste.


Veruješ da će tvoj stomak umiriti i prosto saznanje koliko je tvoj brod udaljen od izlaza iz vorp-spejsa, pa za prvu verziju programa želiš da izračunaš samo to - minimalno potrebno vreme da brod dođe do izlaza.



## Opis ulaza

U prvoj liniji nalaze se celi brojevi $D_x$ i $D_y$, koji predstavljaju broj kolona i broj vrsta vorp-spejsa. U drugoj liniji nalaze se celi brojevi $A_x$ i $A_y$, koji predstavljaju kolonu i vrstu u kojoj se nalazi tvoj brod. U trećoj liniji se nalaze celi brojevi $B_x$ i $B_y$, koji predstavljaju kolonu i vrstu u kojoj se nalazi izlaz. Brojevi vrsta i kolona počinju od $0$.

## Opis izlaza

U jedinoj liniji izlaza ispisati tačno jedan broj - minimalno potrebno vreme da tvoj brod dovedeš do izlaza.

## Primer 1

### Ulaz

~~~
6 6
0 3
2 2 
~~~

### Izlaz

~~~
3
~~~

### Objašnjenje

Do izlaza ćeš najbrže doći u tri jedinice vremena, na primer tako što ideš jednom na gore i dva puta na desno

## Primer 2

### Ulaz

~~~
9 7
6 1
1 5 
~~~

### Izlaz

~~~
7
~~~

### Objašnjenje

Jedno od mogućih najkraćih rešenja je prikazano na slici.

<img src="https://petljamediastorage.blob.core.windows.net/competitions/warpspace.svg" />

## Ograničenja

* $1 \leq D_x, D_y \leq 1000$
* $0 \leq A_x, B_x < D_x$
* $0 \leq A_y, B_y < D_y$

## Napomene

* Od Čoko-Smokija se manje maste prsti.
* Soko Štark nije sponzor ovog zadatka.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Savić | Marko Savić | Aleksa Milisavljević | Vladimir Milenković |

## Analiza

Primetimo da koordinate možemo da posmatramo nezavisno. Najlakši način da rešimo zadatak je analizom slučajeva. Za obe koordinate razmatramo dva slučaja, da li smo prešli preko ivice ili ne. Posmatrajmo $x$ koordinatu početnog i krajnjeg polja. Ukoliko nismo prešli ivicu od polja $A_{x}$ do polja $B_{x}$, rastojanje je $|A_{x}-B_{x}|$. Ukoliko jesmo i dužina vorp-spejsa je $D_{x}$, rastojanje je $D_{x}-|A_{x}-B_{x}|$.  Dakle, minimalan broj koraka da bi smo se našli na $x$ koordinati na kojoj je krajnje polje je $\min(|A_{x}-B_{x}|,D_{x}-|A_{x}-B_{x}|)$. Sličan rezultat dobijamo za $y$ koordinatu,   $\min(|A_{y}-B_{y}|,D_{y}-|A_{y}-B_{y}|)$. Ukupan broj koraka je $\min(|A_{x}-B_{x}|,D_{x}-|A_{x}-B_{x}|) + \min(|A_{y}-B_{y}|,D_{y}-|A_{y}-B_{y}|)$.

``` cpp title="01_vorpspejs.cpp" linenums="1"
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int m,n;
    int a,b;
    int c,d;
    scanf("%d %d",&m,&n);
    scanf("%d %d",&a,&b);
    scanf("%d %d",&c,&d);
    printf("%d",min(abs(c-a),m-abs(c-a))+min(abs(d-b),n-abs(d-b)));
    return 0;
}
```
