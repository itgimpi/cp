---
hide:
  - toc
---

# 3 - Vodopad

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Mali Perica je rešio da obiđe Srbiju i posebno je zainteresovan za obilazak vodopada širom zemlje. Kada je bio na Gostiljskim vodopadima, pokušao je da proceni tok vode na dnu vodopada.



Kao što svi znamo, vodopad ima visinu $h$ metara i širinu $n$ metara. Vodopad je takođe sa leve i desne strane ograničen ivicama tako da voda nikada ne otiče levo i desno od njegovih granica. Još jedna zanimljiva stvar je što vodopad može imati stene koje će preusmeravati tok vode. Naime, ako vertikalni mlaz vode naiđe na stenu, sav njen tok se deli na dva dela tako da jedan deo otiče na desno a drugi na levo. Ukoliko se stena nalazi uz levu ili desnu granicu vodopada, tada se sav tok vode preusmerava na jednu stranu. Više stena se može nalaziti jedna pored druge i u tom slučaju se voda preusmerava samo na kraj i početak celog niza stena. Garantuje se da će u svakoj visini vodopada postojati bar jedno mesto koje nema stenu tako da je vodi garantovan prolaz na dole.



Formalno, vodopad možemo predstaviti binarnom matricom $h \times n$, u kojoj je svako polje ili prohodno ili se tu nalazi stena. Redovi se indeksiraju počevši od 1, tako da je prvi red na vrhu matrice, a $h$-ti red na dnu. Protok vode ima vrednost 1 na vrhu svake kolone. Voda se u svakoj koloni spušta niz matricu, sve dok ne naiđe na stenu. Ukoliko naiđe na stenu, sav protok se deli na dva celobrojna dela i polovina ide na levu stranu a druga polovina na desnu stranu. Ukoliko je protok neparan, tada preostala jedinica ide levo ili desno po sledećem pravilu:

* ukoliko je red neparan, jedinica viška ide levo

* ukoliko je red paran, jedinica viška ide desno



Ako se više uzastopnih nula nalazi u redu matrice (više uzastopnih stena), tada se ukupan protok iznad bloka uzastopnih nula deli na dva dela i jedna polovina preusmerava na prvo mesto levo od bloka a druga na desno. Pravilo za preostalu jedinicu protoka je isto kao i malopre - ako je red neparan višak ide levo od bloka, a ako je paran desno. Ako se stena ili blok stena nalazi uz levu ili desnu ivicu matrice, sav protok iznad stene ili bloka se usmerava na suprotnu stranu. Garantovano je da neće postojati red matrice koji sadrži samo nule.



Perica vam je dao matricu koja predstavljaja izgled jednog vodopada. Vaš zadatak je da odredite protok vode na svim mestima na njegovom dnu.


## Opis ulaza

U prvom redu standardnog ulaza nalaze se dva broja $h$ i $n$, koji predstavljaju visinu i širinu matrice, respektivno. U svakom od narednih $h$ redova nalazi se po $n$ brojeva iz skupa $\{0, 1\}$, pri čemu $0$ označava da se na odgovarajućem polju nalazi stena, dok $1$ predstavlja prohodno polje.

## Opis izlaza

U jedinom redu standardnog izlaza potrebno je ispisati $n$ brojeva - vrednost toka na dnu svake od kolona matrice.

## Primer 1

### Ulaz

```
3 3
1 1 0
1 0 1
0 1 1
```

### Izlaz

```
0 2 1
```

## Primer 2

### Ulaz

```
3 3
0 1 0
1 0 1
1 1 0
```

### Izlaz

```
1 2 0
```

## Primer 3

### Ulaz

```
4 5
1 0 1 0 1
1 1 0 0 1
0 1 1 1 0
1 0 1 0 1
```

### Izlaz

```
1 0 3 0 1
```


## Primer 4

### Ulaz

```
5 7
1 1 1 1 0 0 0
1 0 1 0 1 0 1
1 1 0 0 0 1 0
1 0 0 1 1 0 1
0 1 1 0 1 1 0
```

### Izlaz

```
0 2 1 0 2 2 0
```

## Primer 5

### Ulaz

```
1 3
1 0 1
```

### Izlaz

```
2 0 1
```


## Objašnjenje primera
U prvom primeru, posle prvog reda, protoci imaju vrednosti $[1, 2, 0]$, jer se voda iz treće kolone preusmerava na levo zbog toga što je tu stena uz desnu ivicu. Nakon drugog reda, protoci su $[2, 0, 1]$, jer se dve jedinice protoka iz srednje kolone dele na dva dela. Konačno, protok na kraju trećeg reda je $[0, 2, 1]$, jer se tok uz ivicu preusmerava na suprotnu stranu.

![](https://petljamediastorage.blob.core.windows.net/root/Media/Default/Takmicenja/Kvalifikacije/draw01.svg)


U drugom primeru, protoci na kraju redova su:

```
0 3 0
1 0 2
1 2 0
```

![](https://petljamediastorage.blob.core.windows.net/root/Media/Default/Takmicenja/Kvalifikacije/draw02.svg)


U trećem primeru protoci na kraju redova su:

```
2 0 2 0 1
2 1 0 0 2
0 3 0 2 0
1 0 3 0 1
```

![](https://petljamediastorage.blob.core.windows.net/root/Media/Default/Takmicenja/Kvalifikacije/draw03.svg)


U četvrtom primeru, protoci na kraju redova su:

```
1 1 1 4 0 0 0
1 0 4 0 2 0 0
1 3 0 0 0 3 0
2 0 0 2 1 0 2
0 2 1 0 2 2 0
```

![](https://petljamediastorage.blob.core.windows.net/root/Media/Default/Takmicenja/Kvalifikacije/draw04.svg)


U petom primeru postoji samo jedan red, na čijoj se sredini nalazi stena. Pošto je u pitanju neparan red, tok iz sredine se preusmerava na levo.

![](https://petljamediastorage.blob.core.windows.net/root/Media/Default/Takmicenja/Kvalifikacije/draw00.svg)


## Ograničenja

- $1 \leq n,h$
- $n \cdot h \le 10^6$

Test primeri su podeljeni u 5 disjunktnih grupa:

- U test primerima vrednim $20$ poena: $n \le  10$, $h \le 10$.
- U test primerima vrednim $20$ poena: $h \le 10$.
- U test primerima vrednim $20$ poena: $n \le 100$.
- U test primerima vrednim $20$ poena: ni u jednoj vrsti nema uzastopnih nula.
- U test primerima vrednim $20$ poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Vladimir Milovanović | Lazar Milenković | Slobodan Mitrović | Aleksandar Zlateski |


## Analiza
Najpre ćemo objasniti rešenje koje radi u složenosti $O(n^2 \cdot h)$, što je dovoljno da se osvoji 70 poena, a zatim ćemo pokazati kako se to rešenje može jednostavno izmeniti tako da radi u složenosti $O(n \cdot h)$ i donese 100 poena.

## Rešenje u $O(n^2 \cdot h)$
Ovo rešenje dobijamo jednostavnim simuliranjem protokoa. Naime, za svako $i = 1 \ldots n$ "pustimo" jedinični protok sa vrha vodopada $i$-te kolone i simuliramo ponašanje tog jediničnog protoka. Kad protok udari u stenu, tada ga preusmeravamo levo ili desno prateći pravila opisana u postavci zadatka. Kada protok završi na dnu vodopada u koloni $j$ tada uvećamo za $1$ ispis za kolonu $j$.

Da bismo protok koji udari u stenu pravilno podelili levo i desno, primetimo prvo da postavku problema možemo preformulisati na sledeći način. Posmatrajmo blok stena $B$.
- Ako je $B$ u neparnom redu, tada se neparni po redu protok koji udari u $B$ preusmerava levo, dok se parni po redu protok koji udari u $B$ preusmerava desno.
- Ako je $B$ u parnom redu, tada se neparni po redu protok koji udari u $B$ preusmerava desno, dok se parni po redu protok koji udari u $B$ preusmerava levo.

Dakle, za simulaciju je dovoljno da za svaki blok stena pamtimo gde smo \emph{poslednji} put preusmerili protok sa tog bloka.

U ovom rešenju imamo $n$ jediničnih protoka koje simuliramo "polje po polje". Pošto blok stena može imati dužinu $n - 1$, dati protok može obići $O(n \cdot h)$ polja pre nego što dođe do dna. Odatle sledi gore naznačeno vreme izvršavanja.

## Rešenje u $O(n \cdot h)$
Da bismo ubrzali opisano rešenje iznad, dovoljno je da za svaki blok stena zapamtimo gde su kraj i početak bloka. Tada kada protok udari bilo gde u blok možemo ga odmah simulirati sa jednog od krajeva bloka, bez potrebe da protok polje po polje prelazi preko celog bloka stena. To znači da se svaki red može simulirati u $O(1)$ vremenu, što daje ukupnu složenost od $O(n \cdot h)$.

## Smernice za algoritam
Za algoritam je potrebno da označimo kom bloku svaka stena pripada, kao i da za svaki blok odredimo njegov početak i kraj. Da bismo to uradili, najpre ćemo svakom bloku uzastopnih stena dodeliti jedinstven broj, na primer, redom brojeve počevši od $1$. To možemo uraditi na sledeći način. Čuvaćemo promenljivu $blockNumber$, koja će označavati redni broj trenutnog bloka, i obilaziti polja redom po redovima. Kada naiđemo na stenu, ona je početak novog bloka ako i samo ako je ta stena prva u tom redu, ili ako je prethodno polje bilo $1$. Kada detektujemo početak bloka, tada uvećamo $blockNumber$ za $1$. Steni, bila prva u bloku ili ne, dodelimo $blockNumber$.

Posle ovih koraka svakoj steni je dodeljen broj koji označava kom bloku ona pripada. Stena bloka sa najmanjom kolonom označava početak odgovarajućeg bloka, a stena bloka sa najvećom kolonom označava kraj odgovarajućeg bloka.

## Bonus zadatak
Simulacija koja donosi 100 poena ključno zavisi od činjenice da postoji $n$ jediničnih protoka. Kako bi se mogao ovaj zadatak rešiti u $O(n \cdot h)$ vremenu ako se sa vrha vodopada iz $i$-te kolone pušta između $0$ i $10^9$ zapremine vode?

``` cpp title="03_vodopad.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int h, n;
vector<int> tok, novitok;
vector<vector<int>> mat;

void rasporedi(vector<int> &a, bool oddrow, int l, int r, ll curr) {
    if (l == -1) {
        // sve ide desno - garantovano je da desno postoji
        a[r] += curr;
    } else if (r == n) {
        // sve ide levo - garantovano je da levo postoji
        a[l] += curr;
    } else {
        // podjednako se raspodeli
        a[l] += curr / 2;
        a[r] += curr / 2;
        if (oddrow) {
            // u neparnim redovima višak ide levo
            a[l] += (curr & 1);
        } else {
            // u parnim redovima višak ide desno
            a[r] += (curr & 1);
        }
    }
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin >> h >> n;
    tok.resize(n);
    novitok.resize(n);
    mat.resize(h);
    for (int i = 0; i < h; i++) {
        mat[i].resize(n);
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mat[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        tok[i] = 1;
    }
    for (int i = 0; i < h; i++) {
        int last = -1;
        int curr = 0;
        for (int j = 0; j < n; j++) {
            novitok[j] = 0;
            if (mat[i][j] == 0) {
                if (last == -1) {
                    last = j;
                }
                curr += tok[j];
            } else {
                novitok[j] += tok[j];
                if (last != -1) {
                    rasporedi(novitok, (i + 1) & 1, last - 1, j, curr);
                    last = -1;
                    curr = 0;
                }
            }
        }
        if (last != -1) {
            rasporedi(novitok, (i + 1) & 1, last - 1, n, curr);
        }
        tok = novitok;
    }
    for (int i = 0; i < n; i++) {
        cout << tok[i] << " ";
    }
    cout << endl;
    return 0;
}

```
