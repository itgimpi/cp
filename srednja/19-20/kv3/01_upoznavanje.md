---
hide:
  - toc
---

# 1 - Upoznavanje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |


Miloš se nedavno preselio u jednodimenzionalni prostor. Njegova kuća se nalazi na $x$ metara od koordinatnog početka. On takođe zna da ima $n$ komšija i zna koordinate njihovih kuća.

Kao i svaki pristojan stanovnik jednodimenzionalnog prostora, Miloš bi želeo da se upozna sa svim svojim komšijama. On zna da mu je za pešačenje jednog metra potrebna jedna sekunda.

Pomozite Milošu i recite mu koliko mu je najmanje sekundi potrebno da obiđe sve svoje komšije.

## Opis ulaza

U prvom redu nalaze se dva cela broja $n$ i $x$, broj komšija i pozicija Miloševe kuće. Drugi red sadrži $n$ celih brojeva, $a_1, a_2, \dots, a_n$, gde je $a_i$ pozicija $i$-tog Miloševog komšije.

## Opis izlaza

Ispisati jedan ceo broj koji predstavlja minimalno vreme potrebno Milošu da obiđe sve svoje komšije.

## Primer 1

### Ulaz

```
2 1
4 7
```

### Izlaz

```
6
```

## Primer 2

### Ulaz

```
3 4
3 7 9
```

### Izlaz

```
7
```

## Objašnjenje primera

U prvom primeru, Miloš treba da se kreće na desno sve do kuće sa koordinatom $7$.

U drugom primeru, Miloš prvo obilazi levog komšiju na poziciji $3$, a nakon toga se kreće na desno do komšije sa koordinatom $9$.

## Ograničenja


- $1\le n \le 10^6$
- $-10^8 \le x \le 10^8$
- $-10^8 \le a_i \le 10^8$


Test primeri su podeljeni u 4 disjunktne grupe:

- U test primerima vrednim 30 poena: $n \le 10$.
- U test primerima vrednim 15 poena: sve komšije se nalaze desno od Miloša.
- U test primerima vrednim 15 poena: sve komšije se nalaze levo od Miloša.
- U test primerima vrednim 40 poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Pešić | Lazar Milenković | Dragan Urošević | Vladimir Milenković |


Reći ćemo da su komšije čija je pozicija manja od Miloševe pozicije komšije levo, a komšije čija je pozicija veća od Miloševe pozicije komšije desno. Ako su sve komšije levo od Miloša, onda će najbrže upoznati sve komšije tako što krene ulevo i upoznaje komšije u redosledu u kome stiže do svakog od njih. U tom slučaju će vreme upoznavanja biti razlika Miloševe pozicije i pozicije krajnje levog komšije. Slično, ako su sve komšije desno od Miloša, onda kreće udesno i upoznaje komšije u redosledu u kome stiže do svakog od njih. Tada će vreme upoznavanja biti razlika između pozicije krajnje desnog komšije i Miloševe pozicije. Ostaje da rešimo slučaj kada postoji bar jedan komšija levo i bar jedan komšija desno.

Pokažimo da Miloš u optimalnom postupku (redosledu) upoznavanja sa prijateljima ne može proći dva ili više puta "pored" svoje kuće. Neka su komšije sortirane prema svojoj poziciji, tj. tako da je
$$
a_1 \leqslant a_2 \leqslant a_3 \leqslant \dotsb \leqslant a_n.
$$

Neka je u optimalnom postupku upoznavanja, Miloš išao na desno do komšije ${r_1}$, zatim se "vratio" do komšije $l$, a potom od komšije ${l}$ ponovo krenuo udesno do komšije ${r_2}$ ($r_2 > r_1$). 
Tada je vreme upoznavanja tih komšija iznosilo
$$
(a_{r_1} – x) + (a_{r_1} – a_l) + (a_{r_2} – a_{l}).
$$
Međutim, ako bi Miloš išao prvo ulevo do komšije $l$, a nakon toga udesno do komšije ${r_2}$, upoznao bi isti skup komšija, ali bi vreme upoznavanja iznosilo
$$
(x – a_l) + (a_{r_2} – a_{l}).
$$
Lako se pokazuje da važi:
$$
(a_{r_1} – x) + (a_{r_1} – a_l) + (a_{r_2} – a_{l}) > 
(a_{r_1} – a_l) + (a_{r_2} – a_{r_1})  >
(x – a_l) + (a_{r_2} – a_{r_1}).
$$
Na sličan način bi se postupilo da je išao ulevo do komšije ${l_1}$, zatim udesno do $r$ i nakon toga ponovo ulevo do komšije ${l_2}$ ($l_2 < l_1$). Taj raspored bi se mogao zameniti rasporedom u kome bi išao udesno do komšije $r$, a zatim ulevo do komšije ${l_2}$ (a vreme upoznavanja za taj raspored je manje). 

Prema tome, ako postoji bar jedan komšija levo i bar jedan komšija desno, izdvajaju se dva redosleda za upoznavanje komšija:

- Miloš može ići ulevo do krajnje levog komšije, a zatim udesno do krajnje desnog komšije, ili
- Miloš može ići udesno do krajnje desnog komšije, a zatim ulevo do krajnje levog komšije.

Vreme upoznavanja u prvoj varijanti je
$$
x-a_1 + a_n – a_1,   
 $$
a u drugoj varijanti je
$$
a_n – x + a_n – a_1.
$$
Minimalno vreme upoznavanja je
$$
\min\{ x-a_1 + a_n – a_1, a_n-x + a_n – a_1,\} = a_n – a_1 + \min\{x-a_1, a_n – x\}.
$$
Za kraj primetimo da niz $a$ nije neophodno sortirati jer je su nam potrebne samo vrednosti prvog i poslednjeg elementa sortiranog niza, a to su zapravo najmanji i najveći element niza.
Vremenska složenost ovog rešenja je $O(n)$.



``` cpp title="01_upoznavanje.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
//    string path = argv[1];
//    freopen(path.c_str(), "r", stdin);
//    path = path.substr(0, path.length() - 2) + "out";
//    freopen(path.c_str(), "w", stdout);

    int n, x;
    cin >> n >> x;
    int mini = x, maxi = x;
    for (int i = 0; i < n; i++) {
        int y;
        cin >> y;
        mini = min(mini, y);
        maxi = max(maxi, y);
    }
    cout << min(x - mini, maxi - x) + maxi - mini;
    return 0;
}

```
