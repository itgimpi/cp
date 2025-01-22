---
hide:
  - toc
---

# 5 - Sportski centar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 200ms | 64MB |

Radi popularizacije sporta i rekreacije, škola planira izgradnju sportskog centra za svoje učenike. Za tu svrhu dobila je veliko parče zemljišta. Pre početka izgradnje, potrebno je najpre ograditi četvorougaoni deo zemlje. Komisija je odredila optimalnu površinu sportskog centra $P$. Međutim, to nije sve, ogradu nije moguće postaviti bilo gde na zemljištu, već je određen spisak dozvoljenih lokacija koje mogu biti temena četvorougla.

Vaš zadatak je da odraberete četiri dozvoljena temena, tako da površina ograđenog zemljišta **bude što bliža $P$**. 

## Opis ulaza
U prvom redu standardnog ulaza nalazi se broj $n$, koji predstavlja broj dozvoljenih lokacija. U drugoj liniji nalazi se prirodan broj $P$, optimalna površina zemljišta. Svaka od narednih $n$ linija sadrži po dva nenegativna cela broja $x$ i $y$, koordinate jedne dozvoljene lokacije.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan pozitivan realan broj - najbliža moguća površina koju je moguće dobiti. Broj ispisati sa tačno dve cifre iza decimalne tačke. Ukoliko su dve vrednosti podjednako udaljene od optimalne, **ispisati veću**.

## Primer 1
### Ulaz
```
5
30
0 0
10 0
0 10
10 10
7 3
```

### Izlaz
```
30.00
```

## Primer 2
### Ulaz
```
5
10
0 0
3 0
7 0
3 3
10 10
```

### Izlaz
```
10.50
```

## Objašnjenje primera
U prvom primeru možemo postići traženu površinu postavljanjem ograda od prve do druge lokacije, druge do četvrte, četvrte do pete i pete do prve. U drugom primeru nije moguće dobiti traženu vrednost, a najbližu možemo postići ako postavimo ograde od prve do druge lokacije, druge do treće, treće do četvrte i četvrte  do prve.

## Ograničenja
* $0 \leq P \leq 10^{18}$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima koji vrede $10$ poena važiće $n \leq 5$ i $0 \leq x, y \leq 10$.
* U test primerima koji vrede $30$ poena važiće $n \leq 100$ i $0 \leq x, y \leq 10^9$.
* U test primerima koji vrede $60$ poena važiće $n \leq 200$ i $0 \leq x, y \leq 10^9$.

## Napomena
Površina mora biti veća od nule, to jest nije dozvoljeno izabrati četiri kolinearne lokacije. Dozvoljeno je izabrati četiri tačke tako da tri od njih budu kolinearne, kao u drugom primeru. Četvorougao ne sme biti samopresecajući.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dušan Zdravković | Ivan Dejković | Dragan Urošević | Marko Savić |

##Glavno rešenje
Pravolinijsko rešenje se dobija tako što se obrađuje svaka četvorka tačaka i utvrđuje da li je površina četvorougla koji one određuju bliža zadatoj površini. Pri određivanju površine četvorougla koje određuju tačke $A, B, C$ i $D$ treba iskoristiti činjenicu da bar jedna od njegovih dijagonala pripada četvorouglu. Ta dijagonala deli četvorougao na dva trougla, a površina četvorougla će biti jednaka zbiru površina ta dva trougla. 

Kako odrediti tu dijagonalu? Pa ako npr. duž $AC$ predstavlja tu dijagonalu onda su tačke $B$ i $D$ sa različitih strana prave koju određuju tačke $A$ i $C$. Proveru možemo izvesti tako što ćemo kroz tačke $A$ i $C$ postaviti pravu. Ako su $x_A$ i $y_A$ koordinata tačke $A$,  a $x_C$ i $y_C$ koordinate tačke $C$, onda je jednačina prave

$$
\frac{x-x_A}{x_C-x_A} = \frac{y-y_A}{y_C-y_A}
$$

ili 

$$
(x-x_A)(y_C-y_A) – (y-y_A)(x_C-x_A) = 0
$$

Ako neka treća tačka ne pripada pravoj postavljenoj kroz tačke $A$ i $C$, onda izraz koji dobijamo kada u levoj strani gornjeg izraza zamenimo $x$ i $y$ sa koordinatama te tačke ima vrednost različitu od nule. Ako su vrednosti koje se dobiju kada se $x$ i $y$ zamene koordinatama tačke $B$, odnosno koordinatama tačke $D$ različitog znaka, onda su tačke $B$ i $D$ sa različitih strana prave $AC$.

Kako odrediti površinu trougla čija su temena tačke $A(x_A,y_A)$, $B(x_B,y_B)$ i $C(x_C,y_C)$? Možemo formirati vektore $\vec{AB}=(x_B-x_A,y_B-y_A)$ i $\vec{AC}=(x_C-x_A,y_C-y_A)$. Onda vektorski proizvod ova dva vektora predstavlja vektor čija je dužina jednaka površine paralelograma razapetog nad tim vektroima. Aritmetički, izraz

$$
(x_B-x_A)(y_C-y_A) – (x_C-x_A)(y_B-y_A)
$$

može biti i pozitivan i negativan (ali isto tako i nula, ako su tačke $A, B$ i $C$ kolinearne), a njegova apsolutna vrednost je jednaka baš površini paralelograma razapetog nad vektorima  $\vec{AB}$ i $\vec{AC}$, odnosno dvostrukoj površini trougla $ABC$. Napomenimo da ako si izrazi 

$$
(x_B-x_A)(y_C-y_A) – (x_C-x_A)(y_B-y_A)\quad  i \quad
(x_B-x_A)(y_D-y_A) – (x_D-x_A)(y_B-y_A)
$$

( su koordinate tačke ), različitog znaka, onda su tačke $C$ i $D$ sa različitih strana prave $AB$.

Napredniji algoritam dobijamo tako što analiziramo sve moguće parove tačaka kao kandidate za dijagonalu četvorougla i to onu dijagonalu koja pripada unutrašnjosti četvorougla. Ako su $A$ i $B$ kandidati za krajeve dijagonale, onda ostale tačke delimo u dve grupe, zavisno od toga sa koje strane prave $AB$ se nalaze. Neka su $P’_1, P’_2, …, P’_{n’}$ površine trouglova koji se nalaze sa jedne strane prave, a $P’’_1, P’’_2, …, P’’_{n’’}$ površine trouglova koji se nalaze sa druge strane prave $AB$. Ta dva niza sortiramo (npr. u neopadajućem poretku). Nakon toga se simultano krećemo kroz nizove pokušavajući da sumu površina trouglova iz ta dva niza maksimalno približimo traženoj vrednosti. Zbog toga po jednom od nizova krećemo od početka (tj. od najmanje površine), a po drugom od kraja (tj. od najveće površine). Ako je trenutni zbir manji od ciljane vrednosti, pomeramo se po nizu po kome idemo od početka (i na taj način povećavamo zbir). Ako je površina veća od ciljane vrednosti, pomeramo se po nizu po kome se krećemo od kraja. Naravno, prekidamo u trenutku kada potrošimo jedan od nizova. Složenost dela koji se odnosi na obradu jednog para tačaka (kao kandidata za krajeve dijagonale) je $\Theta(n\log n)$ (sortiranje nizova sa površinama). Kako je broj parova tačaka, to je složenost kompletnog postupka $\Theta(n^3\log n)$.

**Algoritamske smernice**

Prilažemo samo blok programa u kome se obrađuje svaki par tačaka kao krajevi dijagonale. Prepuštamo čitaocu da dopuni sa blokom za učitavanje i ispis rezultata. Napominjemo da funkcija `area(i,j,k)` izračunava površinu trougla čija su temena tačke sa indeksima `i`, `j` i `k`,. 

```    
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            // za svaki par tačaka se analiziraju sve preostale tačke i dele
            // u dve grupe, zavisno od toga sa koje strane 
            // dve fiksirane tačke se nalaze
            left_cnt = 0;
            right_cnt = 0;
            // obrada ostalih tačaka
            for (int k=0; k<n; k++) {
                if (k == i || k == j) continue;
                Triangle t;
                t.index = k;
                t.area = area(i, j, k);
                if (t.area > 0)
                    tleft[left_cnt++] = t;
                else if (t.area < 0) {
                    t.area = -t.area;
                    tright[right_cnt++] = t;
                }
            }
            if (left_cnt == 0 || right_cnt == 0) continue;
            // Sortiramo trouglove sa jedne strane fiksiranog para tačaka
            sort(tleft, tleft + left_cnt);
            // Sortiramo trouglove sa druge strane fiksiranog para tačaka
            sort(tright, tright + right_cnt);
            // Krećemo sa različitih krajeva sortiranih nizova
            // i tražimo par trouglova za koji je zbir površina
            // najbliži traženom
            pos_left = 0;
            pos_right = right_cnt-1;
            while (pos_left < left_cnt && pos_right >= 0) {
                sum = tleft[pos_left].area + tright[pos_right].area;
                difference = abs_val(sum - 2 * target_area);
                if (difference < min_difference || 
                   (difference == min_difference && sum > sol)) {
                    min_difference = difference;
                    sol = sum;
                }
                if (sum > 2 * target_area)
                    pos_right--;
                else
                    pos_left++;
            }
        }
```

``` cpp title="05_sportski_centar.cpp" linenums="1"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;


struct Vector2D {
    int x, y;

    Vector2D(int _x, int _y) : x(_x), y(_y) {
    }

    Vector2D(istream& is) {
        int _x, _y;
        is >> x >> y;
        Vector2D(x, y);
    }

    Vector2D operator -(const Vector2D& o) const {
        return {x - o.x, y - o.y};
    }

    long long operator ^(const Vector2D& o) const {
        return 1ll*x*o.y - 1ll*y*o.x;
    }
};


long long areaTarget, areaBest;
vector<Vector2D> points;


void solve() {
    long long diffBest = LLONG_MAX;

    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            long long t[points.size() - 2];
            int nt = 0;
            for (int k = 0; k < points.size(); k++) {
                if (k != i && k != j) {
                    t[nt++] = (points[j] - points[i]) ^ (points[k] - points[i]);
                }
            }
            sort(t, t + nt);

            int k = 0;
            int l = 0;

            while (l < nt) {
                long long area = t[l] - t[k];
                long long diff = llabs(area - areaTarget);

                if (t[k] < 0 && t[l] > 0) {
                    if ((diff < diffBest) || ((diff == diffBest) && (area > areaBest))) {
                        areaBest = area;
                        diffBest = diff;
                    }
                }

                if (area < areaTarget) {
                    l++;
                } else {
                    k++;
                }
            }
        }
    }
}


int main() {
    int n;
    cin >> n >> areaTarget;
    areaTarget *= 2;

    for (int i = 0; i < n; i++) {
        points.push_back(Vector2D(cin));
    }

	solve();

    cout << areaBest / 2 << ((areaBest % 2 == 0) ? ".00\n" : ".50\n");

    return 0;
}

```
