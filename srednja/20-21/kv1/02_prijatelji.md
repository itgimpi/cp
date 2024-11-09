---
hide:
  - toc
---

# 2 - Prijatelji

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |

Mika je uspešno sakupio 256 poena na kvalifikacijama i tako se kvalifikovao za Okružno takmičenje. Kao i svakom drugom programeru, Miki je ovo jedna od retkih prilika da stekne nove prijatelje. Zato je odlučio da svrati do vračare Miljane koja će ga uputiti u to kako se stvaraju prijateljstva na Okružnom takmičenju. 

Na Okružno takmičenje je pozvano $N$ učenika, numerisanih brojevima $1, 2, …, N$. Kako nisu svi učenici podjednako druželjubivi, za svakog učenika moguće je definisati koliko voli druženje. Tako ćemo pretpostaviti da učenik $i$ ima određenu druželjubivost $A_i$. Među takmičarima postoji $M$ parova poznanika, pri čemu svaka dva učenika koja se poznaju mogu biti **prijatelji ili neprijatelji**. Sreću takmičara $i$ možemo definisati kao proizvod njegove druželjubivosti i razlike broja njegovih prijatelja i neprijatelja. Na primer, ako takmičar ima druželjubivost $2$, ima tri prijatelja i jednog neprijatelja, njegova sreća iznosi $2*(3-1)=4$. Pri tome, neki **takmičari mogu imati negativnu druželjubivost**, u kom slučaju su srećniji kada imaju više neprijatelja, a manje prijatelja. Ukupnu sreću celog takmičenja definišemo kao **zbir sreća svih takmičara**. 

Vračara je Malom Miki otkrila koji su parovi učesnika poznanici, ali mu nije rekla da li su ti parovi prijatelji ili neprijatelji. Sada Miku interesuje koja je najveća moguća ukupna sreća celog takmičenja? Kako je Mika veoma zauzet pripremama za Okružno takmičenje, zamolio vas je da mu pomognete.

## Opis ulaza
U prvoj liniji ulaza nalaze se brojevi $N$ i $M$. Zatim sledi $N$ linija, tako da se u $(i+1)$-oj liniji nalazi druželjubivost $i$-tog takmičara, $A_i$. Zatim sledi još $M$ linija koje opisuju poznanstva među takmičarima, tako da se u $(N+1+i)$-om redu nalazi par poznanika $X_i, Y_i$. 

## Opis izlaza
U prvu i jedinu liniju izlaza treba ispisati najveću moguću sreću čitavog takmičenja.

## Ograničenja
-   $1 \leq N \leq 100\ 000$
-   $1 \leq M \leq 100\ 000$
-   $A_i\in [-10^9, 10^9]$
-   $1\leq X_i, Y_i\leq N$
-   $X_i\neq Y_i$, za $i\in [1, M]$
-   $\{X_i, Y_i\}\neq \{X_j, Y_j\}$, za $i, j\in [1, M], i\neq j$

Test primeri su podeljeni u 3 disjunktne grupe:

-   U test primerima vrednim $20$ poena važi $N, M \leq 10$.
-   U test primerima vrednim $20$ poena važi $A_i=1$ za sve $i\in [1, N]$.
-   U test primerima vrednim $60$ poena nema dodatnih organičenja.

## Primeri
### Primer 1
#### Ulaz
```
3 2
1
1
1
1 2
2 3
```

#### Izlaz
```
4
```

#### Objašnjenje
Svi takmičari su podjednako druželjubivi, pa se maksimalna sreća postiže kada su svi takmičari prijatelji. Tada je sreća takmičara $1$ jednaka $1$, sreća takmičara $2$ je $2$ i sreća takmičara $3$ je $1$. Dakle, najveća moguća ukupna sreća takmičenja je $4$.

### Primer 2
#### Ulaz
```
3 2
2
-5
5
1 2
2 3
```

#### Izlaz
```
3
```

#### Objašnjenje
Maksimalna sreća postiže se kada su svi poznanici neprijatelji. Tada sreća iznosi $2\cdot(0-1)+(-5)\cdot(0-2)+5\cdot(0-1) = 3$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Aleksa Milojević | Mladen Puzić | Mladen Puzić |

## Rešenje za $N, M \leq 10$:
Za svako poznanstvo pomoću rekurzije ili bitmaski fiksiramo da li je **prijateljstvo** ili **neprijateljstvo**. Probamo sve mogućnosti za sva poznanstva i uzmemo najbolju kombinaciju. Vremenska složenost je $O(2^M\cdot(N+M))$

## Rešenje za $A_i = 1$:
Pošto su druželjubivosti svih ljudi pozitivne, nikada nam se neće isplatiti da imamo **neprijateljstva**, tj. sva poznanstva će biti **prijateljstva**. Dakle, ako sa $P_i$ označimo broj poznanika (odnosno i prijatelja) osobe $i$, naše rešenje će biti $\sum^{N}_{1} A_i\cdot P_i$. Pošto važi $A_i = 1$ za svako $i$, ta suma je ekvivalentna $\sum^{N}_{1} P_i$. Detaljnijom analizom ove sume možemo zaključiti da ona iznosi $2\cdot M$, jer svako poznanstvo povećava našu sumu za 2. Vremenska složenost je $O(N+M)$ ili $O(1)$ u zavisnosti od implementacije.

## Glavno rešenje:
Označimo ponovo broj prijatelja osobe $i$ sa $P_i$, a broj neprijatelja sa $Q_i$. Onda je naš krajnji rezultat $\sum^{N}_{1} A_i \cdot (P_i - Q_i)$, po tekstu zadatka. Možemo uočiti da je ovo ekvivalentno tome da za svako prijateljstvo između osoba $x$ i $y$ doprinosi rezultatu $A_x + A_y$, dok svako neprijateljstvo doprinosi rezultatu $-(A_x + A_y)$. Pošto želimo da maksimiziramo naš rezultat, svako poznanstvo za koje važi $A_x + A_y \geq 0$ ćemo postaviti kao prijateljstvo, a svako poznanstvo za koje važi $A_x + A_y < 0$ ćemo postaviti kao neprijateljstvo. Može se primetiti da je u tom slučaju naše rešenje $\sum^{M}_{1} |A_{X_i} + A_{Y_i}|$. Vremenska složenost je $O(N+M)$.


``` cpp title="02_prijatelji.cpp" linenums="1"
//Prijatelji 100
#include <bits/stdc++.h>
#define MAX_N 100005
#define MAX_M 100005

using namespace std;

int N, M;
long long A[MAX_N];
int X[MAX_M], Y[MAX_M];


int main(){
	ios::sync_with_stdio(false);
	cin>>N>>M;
	for(int i=1; i<=N; i++){
		cin>> A[i];
	}
	for(int i=1; i<=M; i++){
		cin>>X[i]>>Y[i];
	}
	long long max_sreca=0;
	for(int i=1; i<=M; i++){
		max_sreca+=abs(A[X[i]]+A[Y[i]]);
	}
	cout<<max_sreca;
	return 0;
}

```
