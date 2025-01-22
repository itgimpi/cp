---
hide:
  - toc
---

# 3 - Karte 2

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2500ms | 256MB |

Koca se setio da, kao što je običaj, iza baštenskog rekvizita koji je dobio na poklon od drugara drži špil karata. Ovaj špil je pomalo neobičan, i sastoji se od $N$ karata obeleženih prirodnim brojevima
$A_1, A_2, \dots, A_N$.

Odlučio je da sa drugovima igra sledeću igru:

* Koca, kao prvi igrač, uzima koliko god želi karata sa vrha špila (a barem jednu). Za broj poena koji je osvojio, $P_1$, uzima se zbir brojeva na kartama koje je uzeo.
* Ukoliko je prebacio granicu $K$, odnosno $P_1 > K$, Koca gubi igru.
* U suprotnom, protivnik uzima koliko god želi karata sa vrha ostatka špila (može i nijednu), i dobija $P_2$ poena, koliko iznosi zbir karata koje je uzeo.
* Ukoliko je protivnik prebacio granicu, odnosno $P_2 > K$, Koca pobeđuje.
* U suprotnom, pobeđuje onaj igrač koji ima više poena. Ukoliko $P_1 = P_2$, pobeđuje Koca.

Koca ne planira da promeša špil, tako da će karte koje uzimaju on i protivnik biti izvučene redom: $A_1$, pa $A_2$, i tako dalje, do $A_N$. Zanima ga da li postoji broj karata koji treba da izvuče tako da sigurno pobeđuje, ma koliko karata njegov protivnik odluči da izvuče.

Koca je veoma radoznao, tako da u svakom primeru, umesto za jednu situaciju, treba dati odgovor za $T$ različitih situacija (svaka situacija je novi špil karata).

## Opis ulaza
U prvom redu ulaza nalazi se jedan ceo broj $T$: broj situacija za koje je potrebno odrediti da li Koca sigurno pobeđuje. U nastavku ulaza je dato $T$ opisa situacija, gde se svaka sastoji iz dva reda:

U prvom redu opisa nalaze se dva cela broja $N$ i $K$: broj karata u špilu i granica u poenima koju igrači ne smeju premašiti.

U drugom redu opisa nalazi se $N$ celih brojeva $A_1, A_2, \dots, A_N$: brojevi na kartama, redom od prve do poslednje u špilu.

## Opis izlaza
Za svaku od $T$ situacija (redom) ispisati po jedan red izlaza: `da` ako Koca može da odabere broj karata koje izvlači tako da sigurno pobedi, i `ne` u suprotnom.

## Ograničenja
* $1 \leq T \leq 20$
* $1 \leq N \leq 100000$
* $1 \leq K \leq 10^9$
* $1 \leq A_i \leq 10^9$

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim $?$ poena: $1 \leq N \leq 1000$.
* U test primerima vrednim $?$ poena: unutar svake situacije, sve karte su obeležene istim brojem.
* U test primerima vrednim $?$ poena nema dodatnih ograničenja.

## Primeri
### Primer 1
#### Ulaz
```
2
5 10
2 5 3 4 8
2 1000
100 200
```

#### Izlaz
```
da
da
```

#### Objašnjenje
U prvoj situaciji, Koca može da uzme prve dve karte i osvoji $7$ poena. To je manje od $10$, tako da je na potezu njegov protivnik, koji će ako izvuče manje od tri karte imati manje ili isto poena kao Koca, a
ako izvuče sve tri imati više od dozvoljenih $10$. Dakle, Koca sigurno pobeđuje.

U drugoj situaciji, Koca može da uzme sve karte i time sigurno ima više poena od protivnika.

### Primer 2
#### Ulaz
```
1
5 30
11 12 13 14 15
```

#### Izlaz
```
ne
```

#### Objašnjenje
Koca može da izvuče najviše dve karte bez premašivanja $30$ poena. Šta god da uradi, protivnik može da uzme naredne dve karte i pobedi.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Tadija Šebez | Dimitrije Erdeljan | Mladen Puzić | Aleksandar Zlateski |

## Rešenje za $1 \leq N \leq 1000$:
Pošto je $N$ malo, $O(N^2)$ rešenje je dovoljno brzo. Možemo fiksirati koliko prvih karata uzima Koca, osvojivši $P_1$ poena (naravno, tako da $P_1 \leq K$). Nakon toga idemo kroz preostale karte i gledamo da li je moguće izabrati nekoliko sledećih karata sa zbirom brojeva $P_2$ tako da $P_1 < P_2$ i $P_2 \leq K$. Ako je to nemoguće, onda Koca sigurno pobeđuje ako izvuče taj broj karata. 

## Rešenje kad su sve karte obeležene istim brojem:
Označimo taj broj sa $A$. Dakle, ako Koca uzme $k$ karata, onda će važiti $P_1 = k\cdot A$. Kako bi njegov protivnik osvojio više od $P_1$ poena, mora uzeti više od $k$ karata, odnosno makar $k+1$. Ako važi $(k+1)\cdot A > K$, onda ako uzme više od $k$ karata, prebaciće granicu. Samim tim nema pobednički potez, pa Koca uvek pobeđuje (ukoliko $k\cdot A \leq K$). Ako ipak važi $(k+1)\cdot A \leq K$ i njegov protivnik zaista može da uzme $k+1$ karata (ostalo je dovoljno karata u špilu), onda protivnik ima pobedničku strategiju i Koca ne sme da uzme $k$ karata ako želi da pobedi (a želi).

## Glavno rešenje:
Slično rešenju kad $1 \leq N \leq 1000$, fiksiramo koliko prvih karata uzima Koca, osvojivši $P_1$ poena. Sada treba da proverimo da li postoji prefiks preostalih karata tako da mu je zbir $P_2$ veći od $P_1$, a nije veći od $K$. Pošto se na kartama nalaze isključivo pozitivni brojevi, što više karata protivnik izvuče, to će zbir biti veći. Nađimo koristeći binarnu pretragu najmanji prefiks ostatka špila čiji je zbir veći od $P_1$ (zbir prefiksa možemo naći koristeći prefiksne sume). Nijedan manji prefiks ne može dovesti do pobede protivnika, jer ne zadovoljava uslov $P_1 < P_2$. Za taj prefiks proverimo da li je zbir veći od $K$. Ako jeste, svi veći prefiksi su takođe veći od $K$, pa samim tim ne postoji potez kojim protivnik pobeđuje, pa je odgovor da. Ako mu zbir nije veći od $K$, on zadovoljava oba uslova, pa je samim tim i pobednički potez za protivnika. Onda moramo probati sledeći moguć Kocin potez, dok ne proverimo sve moguće. Vremenska složenost: $O(NlogN)$, memorijska složenost: $O(N)$.

``` cpp title="03_karte2.cpp" linenums="1"
#include <cstdio>

const int N = 100005;
int a[N];

void single_test() {
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int j = 1, first = 0, second = 0;
    bool can_win = false;

    for(int i = 0; i < n; i++) {
        first += a[i];
        if(first > k) break;

        if(i > 0) second -= a[i];
        while(j < n && second <= first) {
            second += a[j++];
        }

        if(!(second > first && second <= k)) {
            can_win = true;
            break;
        }
    }

    printf("%s\n", can_win ? "da" : "ne");
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) single_test();
    return 0;
}

```
