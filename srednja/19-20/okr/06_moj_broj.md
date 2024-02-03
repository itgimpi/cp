---
hide:
  - toc
---

# A3 - Moj broj

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 300ms | 512MB |


Sanja iz Rzanja (pa normalno, odakle bi inače bio?) je veliki fan kviza Slagalica, posebno igre "Moj broj". Ovaj put je napisao niz $A$ od $n$ elemenata. On želi da pronađe niz $B$ pomoću kog će moći da predstavi sve brojeve iz niza $A$. Pravila predstaljanja su sledeća:

- niz $B$ se sastoji od $k$ (ne nužno različitih) prirodnih brojeva, koji nisu veći od $10^8$
- svaki član niza $A$ morate predstaviti kao kombinaciju elemenata niza $B$ (prilikom predstaljanja jednog člana niza $A$, svaki element niza $B$ smete koristi najviše onoliko puta koliko se javlja u nizu $B$)
- pored članova niza $B$, smete koristiti operacije sabiranja (`+`), oduzimanja (`-`) i množenja (`*`). **Deljenje nije dozvoljeno**
- dozvoljeno je koristiti otvorene i zatvorene zagrade (`(`, `)`)
- vaši bodovi zavise od broja $k$ (dužine niza $B$), pročitajte sekciju *Bodovanje* za više detalja

## Opis ulaza

Prva linija standardnog ulaza sadrži prirodan broj $n$, dužinu niza $A$.
Druga linija standardnog ulaza sadrži $n$ prirodnih brojeva, elemente niza $A$.

## Opis izlaza

U prvoj liniji standardnog izlaza ispisati broj $k$, dužinu niza $B$.
U drugoj liniji standardnog izlaza ispisati niz $B$.
U svakoj od narednih $n$ linija predstaviti po jedan broj iz niza $A$ korisiteći pretohdno napisana pravila. Konkretno u $i$-toj liniji predstaviti broj $A_i$, pomoću članova niza $B$, računskih operacija (sabiranje, oduzimanje, množenje) i zagrada. **Svaka linija ispisa ne sme biti duža od $1000$ karaktera.**

- Za sabiranje dve vrednosti koristite karakter `+` (vrednost u ascii tabeli $43$)
- Za oduzimanje dve vrednosti koristite karakter `-` (vrednost u ascii tabeli $45$)
- Za množenje dve vrednosti koristite karakter `*` (vrednost u ascii tabeli $42$)
- Za zagrade koristite karaktere `(` (vrednost u ascii tabeli $40$) i `)` (vrednost u ascii tabeli $41$)
- **Nije dozvoljeno koristiti znakove  `+` i `-` kao unarne operatore** (npr. izrazi $-3+5$ ili $5+(+9-3)$ nisu pravilni).
- Osim navedenih karaktera, dozvoljeno je ispisivati samo članove niza $B$ i razmake (ascii vrednost $32$) - nije obavezno ispisivati razmake između brojeva i operatora i formatirati izlaz.

## Primer 1

### Ulaz

```
6
30 13 15 5 3 21
```

### Izlaz

```
3
2 5 3
2*5*3
5*3- 2
5 *3
   (5)
5 -2
3* (5+2 )
```


## Objašnjenje primera

Dovoljno je $3$ broja da predstavimo sve brojeve iz ulaza ($B = [2, 5, 3]$):

- $2*5*3=30$
- $5*3-2=13$
- $5*3=15$
- $5=5$
- $5-2=3$
- $3*(5+2)=21$

## Ograničenja

- $1 \leq n \leq 124$
- $1 \leq A_i \leq 10^8$

- elementi niza $B$ su prirodni brojevi u opsegu $[1, 10^8]$.


## Bodovanje

Broj poena na svakom test primeru zavisi od $k$ (veličine niza $B$ koji koristite za predstaljanje brojeva), po sledećoj tabeli:

|         Veličina niza $B$ ($k$)          |  Broj poena u procenitima |
|:---------------------:|:-------------------------:|
|         $\leq 12$  |$100$|
|           $13$     |$90$|
|          $14-15$   |$80$|
|          $16-18$   |$70$|
|          $19-20$   |$60$|
|          $21-22$   |$50$|
|          $23-24$   |$40$|
|          $25-27$   |$30$|
|          $28-29$   |$20$|
|          $30-31$   |$10$|
|          $ > 31$   |$0$|

## Napomena

Janis Adetokumbo nije rođen u Rzanju.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksandar Zlateski | Aleksa Plavšić | Aleksa Milojević | Aleksandar Zlateski |


Ideja u ovom zadatku jeste distancirati se od konkretnih brojeva koji su dati u nizu $A$. Konstruisaćemo niz od $12$ brojeva $B$ takav da se svi brojevi od $1$ do $10^8$ mogu predstaviti kao kombinacija brojeva iz $B$ pomoću računskih operacija.

Jedan primer ovakvo skupa brojeva jesu svi stepeni dvojke $1, 2, 4, ..., 2^26$. Samo sabiranjem ovih brojeva mogu se predstaviti svi brojevi u intervalu $[1, 2^{27}-1]$, što je dovoljno jer je $2^27>10^8$. Konkretno predstavljanje svakog broja iѕ niza $A$ onda se može naći koristeći binarni zapis tog broja. Predviđeno je da ovo rešenje nosi $30$ bodova.

Očigledno je da prethodna ideja nije optimalna jer ne koristi znakove $-$ i $*$. Da bismo mogli pravilno da iskoristimo znak $-$, napravićemo malu promenu u prethodnoj ideji: umesto stepena dvojke, koristićemo stepene trojke. Za to imamo pomoćno matematičko tvrđenje:

Lema: Svaki broj od $1$ do $3^n$ može se predstaviti u obliku $e_03^0+e_13^1+...+e_n3^n$, gde su $e_i\in \{-1, 0, 1\}$.
Dokaz: Ovakvo predstavljanje brojeva jako je slično sa ternarnim zapisom, ali umesto cifre $2$, koristimo cifru $-1$. Do ovakvog zapisa dolazimo tako što prvo napišemo broj u ternarnom zapisu, a zatim počevši od cifre najmanje vrednosti proveravamo da li je ta cifra $2$. Ako jeste, menjamo je u $-1$, a sledećoj cifri najmanje vrednosti dodajemo $1$ (u suštini, $2*3^k$ menjamo sa $3^{k+1}-3^k$).

Koristeći predstavljanje opisano gore, moguće je naći izraz oblika koji koristi znakove $+$ i $-$ i predstavlja svaki broj od $1$ do $3^{17}$ koristeći brojeve $1, 3, ..., 3^{17}$. Ovo rešenje nosi $70$ bodova. Ovde je dobro prokomentarisati i složenost ovog rešenja. Naime, opisani algoritam za svaki broj nalazi predstavljanje u $O($dužina ternarnog zapisa$)$, što je $O(log A[i])$. Ovo znači da je složenost ukupnog rešenja $O(n*log 10^8)$.

Pomoću ideja opisanih gore, lako je generalizovati postupak na baze veće o tri. Na primer, ako uzmemo brojeve $1, 7^1, 7^2, ..., 7^9$, moguće je pokazati, istim algoritmom kao u dokazu leme, da se svaki broj od $1$ do $10^8$ može predstaviti kao $e_07^0+e_17^1+...+e_97^9$, gde su $e_i$ cifre $-3, -2, -1, 0, 1, 2, 3$. Zato ćemo u naš niz $B$ dodati i brojeve $2, 3$, što daje niz $B$ od ukupno $12$ brojeva. Zatim ćemo grupisati sve stepene sedmice uz koje stoji +2 ili -2 u jednu zagradu i nju pomnožiti sa $2$ (analogno za $3$). To znači da bismo mogli dobiti izraz oblika npr. $2*(7^7-7^3)+3*(7^6+7^1)-7^5=1982561$. Ovaj algoritam i dalje radi u gore navedenoj složenosti $O(n*log 10^8) $. U opisanoj implementaciji samo treba biti pažljiv da svaka zagrada počinje sa pozitivnim sabirkom (ako neka zagrada sadrži samo negativne sabirke, treba izvući minus ispred zagrade).


``` cpp title="06_moj_broj.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

#define pb push_back

const int maxN = 125;
const int maxE = 1e8;

int n;
int a[maxN];
int b[maxN];
string expr[maxN];
vector<int> base, mult;

void ispis()
{
    cout<<12<<endl;

    for (int i=0; i<12; i++)
        cout<<b[i]<<" ";

    cout<<endl;

    for (int i=1; i<=n; i++)
        cout<<expr[i]<<endl;

    fclose(stdout);
}

void mult_add(int idx)
{
    for (auto i = 0 ; i< mult.size(); i++)
    {
        if (mult[i]>0 && i)
            expr[idx]+='+';
        expr[idx] = expr[idx] + to_string(mult[i]);
    }
}

void solve(int x, int idx)
{
    int curId = 0;

    for (int i = 0 ; i < 10; i++)
        base[i] = 0;

    while(x>0)
    {
        if (x%7>3)
        {
            base[curId] = x%7 - 7;
            x+=7;
        }
        else
            base[curId] = x%7;
        x/=7;
        curId++;
    }

    int nasao = 0;
    expr[idx] = "";

    for (int i = 9 ; i>=0; i--)
        if (base[i])
        {
            mult.clear();

            for (int j = i ; j>=0; j--)
                if (abs(base[i]) == abs(base[j]))
                {
                    if (base[i]*base[j] < 0)
                        mult.pb(-(b[j]));
                    else
                        mult.pb(b[j]);
                    if (i>j)
                        base[j] = 0;
                }

            if (base[i]<0 && nasao)
                expr[idx]+='-';
            if (base[i]>0 && nasao)
                expr[idx]+='+';

            if (abs(base[i])>1)
            {
                expr[idx] = expr[idx] + to_string(abs(base[i]));
                expr[idx]+='*';
            }

            expr[idx]+='(';
            mult_add(idx);
            expr[idx]+=')';
            nasao = 1;
        }
}
void prepare_base()
{
    b[0] = 1;

    for(int i = 1; i<=9; i++)
        b[i] = b[i-1]*7;

    b[10] = 2;
    b[11] = 3;

    base.resize(10);
}
int main()
{
    cin>>n;

    assert(n>0 && n<maxN);

    for (int i = 1; i<=n; i++)
    {
        cin>>a[i];
        assert(a[i]>0 && a[i]<=maxE);
    }

    prepare_base();

    for (int i = 1; i<=n; i++)
        solve(a[i], i);

    ispis();
}

```
