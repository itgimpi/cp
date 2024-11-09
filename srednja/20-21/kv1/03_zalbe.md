---
hide:
  - toc
---

# 3 - Žalbe

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Vračara Miljana poznata je po svojim predskazanjima o takmičenjima iz programiranja. Njena stručna oblast je pogađanje da li će Tajna Komisija prihvatiti neku takmičarsku žalbu.

Miljana ima svoju ludu teoriju: da postoji prirodan broj $X$ koji ne zna, takav da Komisija prihvata žalbe svakih $X$ godina, tj. ako je Komisija prihvatila žalbu u godini $A$ prva sledeća godina kada će prihvatiti žalbu je $A+X$, a takođe znači da je Komisija prihvatila žalbu u godini $A-X$.

Tačno $T$ takmičara je došlo da se posavetuje sa Miljanom. Ona je od svakog pojedinačno tražila da prikupi informacije o ranijim žalbama kako bi joj pomogli da nađe $X$. Svaki takmičar je izneo neke glasine koje je čuo na Algori. Za $N$ različitih godina $A_1, A_2, ..., A_N$ takmičar tvrdi da je Tajna Komisija prihvatala žalbe. Za $M$ različitih godina $B_1, B_2, ..., B_M$ tačmičar tvrdi da Tajna Komisija nije prihvatala žalbe.

Kako ne bi gubila vreme, Vračara Miljana je pitala vas, takmičara koji se neće žaliti, da za svakog od $T$ takmičara odredite da li postoji $X$ tako da su sve glasine koje je čuo tačne, odnosno da su žalbe prihvaćene u godinama $A_1, A_2, ..., A_N$, a nisu u godinama $B_1, B_2, ..., B_M$, prateći Miljaninu teoriju da se žalbe prihvataju svakih $X$ godina.

## Opis ulaza
U prvoj liniji ulaza nalazi se broj $T$ -- broj takmičara koji su se javili Vračari Miljani.

Za svakog takmičara unose se po još tri linije: u prvoj liniji se nalaze $N$ i $M$ -- broj glasina u kojima su žalbe prihvaćene i broj glasina u kojima su žalbe odbijene; u drugoj liniji nalazi se $N$ celih brojeva, niz $A_1, A_2, ..., A_N$ -- godine u kojima su, po glasinama, prihvaćene žalbe; u trećoj liniji nalazi se $M$ celih brojeva, niz $B_1, B_2, ..., B_M$ -- godine u kojima su, po glasinama, odbijene žalbe.

## Opis izlaza
Na standardni izlaz ispišite $T$ brojeva -- za svakog takmičara, u novom redu, ispisati $1$ ako postoji $X$ koje je u skladu sa njegovim glasinama, odnosno ispisati 0 u suprotnom.

## Ograničenja
- $1 \leq T \leq 5$

Za svakog od $T$ takmičara važi:

- $2 \leq N, M \leq 75000$
- $1 \leq A_i, B_i \leq 10^{18}$
- $A_i \neq A_j$, za $i \neq j$
- $B_i \neq B_j$, za $i \neq j$
- $A_i \neq B_j$, za svako $i, j$

Test primeri su podeljeni u 4 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $A_i, B_i, N, M \leq 3000$
-   U test primerima vrednim $10$ poena: $N = 2$
-   U test primerima vrednim $30$ poena: $A_i, B_i \leq 10^6$
-   U test primerima vrednim $50$ poena: Bez dodatnih ograničenja

## Primeri
### Primer 1
#### Ulaz
```
4
4 3
1 7 4 13
3 11 9
3 2
9 5 3
7 11
2 3
3 15
1 7 2
2 2
5643634654354 12346544323565
22341124534 7655867344
```

#### Izlaz
```
1
0
1
1
```

#### Objašnjenje
Za prvog takmičara moguće je uzeti $X = 3$ tako da zadovolji sve glasine.
Za drugog takmičara nemoguće je naći $X$.
Za trećeg takmičara moguće je uzeti $X = 12$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Mladen Puzić | Mladen Puzić | Mladen Puzić | Pavle Martinović |

Prvo sortiramo niz $A$ rastuće. Od sada sa $A_i$ označavamo $i$-ti najmanji element niza $A$. 

## Rešenje za $A_i, B_i, N, M \leq 3000$:
Dovoljno nam je da proverimo svako moguće $X$ (sve brojeve od $1$ do $3000$).  Neko $X$ je moguće samo ako deli $A_{i+1}-A_i$ za svako $1 \leq i \leq N-1$, a ne deli $|B_i-A_1|$ ni za jedno $1 \leq i \leq M$. Vremenska složenost je $O(T \cdot maxA \cdot (N+M))$.

## Rešenje za $N = 2$:
Znamo da $X$, ako postoji, mora da deli $A_2 - A_1$, ali pošto ta razlika može da bude velika, ne možemo da proverimo sve delioce. Možemo da primetimo da ako broj $p$ deli broj $q$, svaki delilac od $p$ takođe deli $q$. To nam govori da nam je dovoljno proveriti da li je $A_2 - A_1$ dobar kandidat za $X$, jer ako ne deli nijedno od $|B_i-A_1|$ onda je u redu, u suprotnom i svi njegovi delioci dele neki od $|B_i-A_1|$, pa rešenje ne postoji. Vremenska složenost je $O(T \cdot (N+M))$.

## Rešenje za $A_i \leq 10^6$:
Pošto $X$ mora da deli sve razlike $A_{i+1}-A_i$, jedini kandidati su delioci najmanjeg zajedničkog delioca tih razlika, odnosno, ako $X$ postoji, važi $X \mid NZD(A_2-A_1, A_3-A_2, ..., A_N-A_{N-1})$. NZD možemo nađi Euklidovim algoritmom, a pošto delioca ima $O(\sqrt{maxA})$, ukupna vremenska složenost je $O(T \cdot (NlogN + M\sqrt{maxA}))$. 

## Glavno rešenje:
Ako spojimo rešenja za prethodna dva podzadatka možemo videti da je dovoljno proveriti da li $X$ može biti $NZD(A_2-A_1, A_3-A_2, ..., A_N-A_{N-1})$. Ukoliko ne, ne može nijedan njegov delilac. Vremenska složenost je $O(T \cdot (NlogN + M))$.


``` cpp title="03_zalbe.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 100010
using namespace std;
#define lld long long
int N, M;
lld A[MAXN], B[MAXN];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--) {
        cin >> N >> M;
        for(int i = 1; i <= N; i++) cin >> A[i];
        for(int i = 1; i <= M; i++) cin >> B[i];
        sort(A+1, A+1+N);
        lld X = A[2]-A[1];
        int rez = 1;
        for(int i = 3; i <= N; i++) X = __gcd(X, A[i]-A[i-1]);
        for(int i = 1; i <= M; i++) {
            if(abs(B[i]-A[1])%X == 0) rez = 0;
        }
        cout << rez << endl;
    }
    return 0;
}

```
