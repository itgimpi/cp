---
hide:
  - toc
---

# 4 - Gušter

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 128MB |


GUŠTER, novi strani investitor, došao je u Srbiju i njegova prva biznis avantura je otvaranje herpetološke radnje u centru Beograda.
Plan poslovanja je napravljen, ali je došlo do problema pri izboru naziva radnje.

![Primer logotipa](https://petljamediastorage.blob.core.windows.net/competitionimages/hastalavista%20(1).png)

Menadžeri i PR stručnjaci GUŠTER-a su ustanovili da je važno da logotip iznad ulaznih vrata sadrži izabrano ime i bude u obliku zmije: najpre se prvi red logotipa čita sleva na desno, pa se drugi red čita zdesna na levo, pri čemu je početak drugog reda na istoj poziciji kao i kraj prvog reda; treći red se čita sleva na desno, a početak trećeg reda je na istoj poziciji kao i kraj drugog reda itd.
**Logotip može da bude napisan u bilo kom broju redova (čak i jednom), dokle god svaki red sadrži bar dva slova.**
Na primer, reč “`hastalavista`” može da se napiše u obliku zmije na sledeći način:
```
hast
 ala
 vista
```
Nisu svi oblici zmije podjednako dobri.
Stručnjaci su ustanovili da je najpogodniji logotip za datu reč onaj koji ima najveći **zmija-skor**.
Zmija-skor se definiše kao broj (neuređenih) parova slova, jedno *tik iznad* drugog, koja se *poklapaju*.
Na primer, navedena zmija ima zmija-skor 1: prvo i treće slovo “`a`” su jedno iznad drugog. Međutim, moguće je postići zmija-skor 2 sledećom zmijom:
```
   has
ivalat
sta
```
Ljudi iz GUŠTER-a imaju predlog za ime radnje, ali ne znaju kako treba da izgleda optimalan logotip.
Odlučili da se obrate vama, mladim programerima, ne bi li rešili problem i privukli što je moguće više mušterija.
Pomozite GUŠTER-u da zaradi što je moguće više.

## Opis ulaza
U prvom i jedinom redu standardnog ulaza nalazi se niska koja predstavlja predlog imena herpetološke radnje.
Znaci u ovoj niski su mala slova engleske abecede.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan nenegativan ceo broj: najveći zmija-skor koji može da se ostvari nekim zmijolikim rasporedom predloženog imena.

## Primer 1
### Ulaz
```
hastalavista
```

### Izlaz
```
2
```

### Objašnjenje
Primer iz teksta zadatka.

## Primer 2
### Ulaz
```
anavolimilovana
```

### Izlaz
```
0
```

### Objašnjenje
Nije moguće postaviti bilo koji par istih slova jedno tik iznad drugog.

## Primer 3
### Ulaz
```
abccbbcaac
```

### Izlaz
```
6
```

### Objašnjenje
Optimalan raspored je:
```
abc
 bc
 bca
  ca
```
Dva puta se slovo `b` nalazi iznad slova `b`, tri puta se slovo `c` nalazi iznad slova `c`, a samo jednom se `a` nalazi iznad slova `a`, što daje ukupan zmija-skor 6.

## Ograničenja

- Znaci niske su mala slova engleske abecede.
- Niska sadrži ne više od $3000$ znakova i ne manje od dva znaka.

Test primeri su podeljeni u tri disjunktne grupe:

- U test primerima vrednim $30$ poena: Niska nema više od $100$ znakova.
- U test primerima vrednim $20$ poena: Niska ima više od $100$, a ne više od $500$ znakova.
- U test primerima vrednim $50$ poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Lazar Milenković | Aleksa Milisavljević |

Ovaj zadatak se rešava **dinamičkim programiranjem**, što se vidi po tome što je reč o *optimizaciji* i po tome što *naći optimalno rešenje za dati ulaz zavisi od optimalnih rešenja za podniske tog ulaza*.

Osnova rešenja za tri podzadatka je ista: dobiti $50$ ili $100$ poena na ovom zadatku zahteva da se primete moguće optimizacije.
Neka je $n$ dužina date niske $s$ (indeksirane od nule).

## Rešenje za $n \leq 100$

Definišimo dvodimenzioni niz $\mathit{dp}$ formata $(n+1)\times(n+1)$:

* $\mathit{dp}[i][j]$ za $i,j>0$: optimalan zmija-skor koji sufiks niske $s$ dužine $i$ može da ostvari, ukoliko se u prvog redu logotipa nalazi $j$ znakova; ako ne postoji nijedan takav dozvoljen logotip, $-\infty$;
* $\mathit{dp}[i][0]$ i $\mathit{dp}[0][j]$ mogu da se ignorišu i nemaju nikakvo posebno značenje.

Ukoliko znamo sve vrednosti $\mathit{dp}[i][j]$, tada je rešenje jednako $\max_{2 \leq j \leq n} \{\mathit{dp}[n][j]\}$: optimalno rešenje sadrži bilo koji (dozvoljen) broj simbola u prvom redu.

Najpre primetimo neke osnovne činjenice o $\mathit{dp}[i][j]$ koje služe kao temelj određivanja konačnog rešenja:

* $\mathit{dp}[i][i] = 0$, reč je o rešenju u kom ceo logotip za sufiks dužine $i$ staje u jedan red;
* $\mathit{dp}[i][j] = -\infty$ za $i<j$;
* $\mathit{dp}[i][1] = -\infty$ (nije moguće da u bilo kom redu bude samo jedan znak).

Za dalje računanje se oslanjamo na naredno zapažanje:

Ako sufiks niske $s$ dužine $i$ sadrži $j$ znakova ($1<j<i$), optimalan zmija-skor koji može da se ostvari je najveći od svih zbirova $\mathit{dp}[i-j][k]$ i broja poklapanja znakova ukoliko se u prvom redu nalazi $j$, a u drugom $i$ znakova.

Broj poklapanja može da se izračuna proverom da li se poklapaju znaci $s$ na pozicijama $n-i+j+p-1$ i $n-i+j-p$, pri čemu se $p$ menja. Ako definišemo $P(t,p)$ kao indikator da li se ovi znaci na pozicijama $n-t+p-1$ i $n-t-p$ poklapaju (dakle $0$ ili $1$; $0$ je odgovor i u slučaju da je jedan od ovih znakova van opsega niske), prethodna činjenica može da se zapiše u vidu naredne rekurentne veze:

$$
\mathit{dp}[i][j] = \max_{2<k\leq i-j} \{\mathit{dp}[i-j][k] + \sum_{p=1}^{\min(j,k)} P(i-j,p)\}
$$

Sve vrednosti $\mathit{dp}[i][j]$ mogu da se odrede prateći ovu formulu.
U pseudokodu, ovako izgleda glavni deo algoritma:
```
for i in 1 .. n:
    for j in 2 .. i:
        dp[i][j] = -∞
        for k in 2 .. j:
            broj_poklapanja = 0
            for p in 1 .. min(j, k):
                broj_poklapanja += P(i - j, p)
            dp[i][j] = max(dp[i][j], dp[i - j][k] + broj_poklapanja)
```

Konačna vremenska složenost je $O(n^4)$, a memorijska $O(n^2)$.

## Rešenje za $n \leq 500$

U ovom slučaju potrebno je primetiti da pri određivanju $\mathit{dp}[i][j]$ i $\mathit{dp}[i][j+1]$ treba da vodimo računa o naredne dve sume:
* $\sum_{p=1}^{\min(j,k)} P(i-j,p)$;
* $\sum_{p=1}^{\min(j,k+1)} P(i-j,p)$
a njihova razlika je ili $0$ ili poslednji sabirak u zbiru: $P(i-j,k+1)$.

Prethodno rešenje stoga može da se uprosti time što se promenljiva `broj_poklapanja` ažurira svaki put kada se ažurira $k$. Implementacija se menja na sledeći način:
```
for i in 1 .. n:
    for j in 2 .. i:
        dp[i][j] = -∞
        broj_poklapanja = P(i - j, 1)
        for k in 2 .. j:
            if k <= j:
                broj_poklapanja += P(i - j, k)
            dp[i][j] = max(dp[i][j], dp[i - j][k] + broj_poklapanja)
```

Rezultujuća složenost je $O(n^3)$, a memorijska $O(n^2)$.

## Glavno rešenje

Rešenje za svih $100$ poena radi u vremenskoj složenosti $O(n^2)$ i zasniva se na **izbegavanju ponavljanja nepotrebnog rada**.

Primetimo da u rešenju prethodnog podzadatka imamo iteracije po $j$ i po $k$, koje određuju dužine dva uzastopna reda.
Kako se ažurira $j$, menja se poslednji znak u prvom redu i prvi znak u drugom redu, kao i podaci o svim poklapanjima.
Stoga u optimizovanom rešenju želimo da iskoristimo iste podatke o poklapanjima što je moguće duže tako što će spoljna iteracija biti po položaju poslednjeg znaka prvog reda.
Sufiksu dužine $z+d$, u kom prvi red ima dužinu $d$, prvi red se završava znakom sa indeksom $n-z-1$ i drugi red počinje znakom sa indeksom $n-z$ – spoljna iteracija je po $z$, unutrašnja po $d$.

Za dobijanje konačnog rešenja neophodno je posmatrati šta se dešava u slučaju dva susedna reda u logotipu ukoliko drugi red počinje znakom sa indeksom $n-z$. Pretpostavimo da prvi red ima dužinu $d$.

* Ako je prvi red kraći od drugog, broj znakova koji se poklapaju je jednak $\sum_{p=1}^{d} P(i-j,p)$.
Dakle, jedino je pitanje odrediti neko $k \geq d$ tako da je $\mathit{dp}[z][k]$ maksimizovano.
* Ako je prvi red duži od ili jednake dužine kao i drugi, tada nas među svim $\mathit{dp}[z][k]+\sum_{p=1}^{k} P(i-j,p)$ za koje je $k\leq d$ zanima ono najveće.

U prvom slučaju je dovoljno uvesti matricu $m$ definisanu na sledeći način:

* $m[i][j] = \max_{j\leq k\leq i}\{\mathit{dp}[i][k]\}$ za $j \leq i$

koja može da se izračuna pomoću rekurentne veze:

* $m[i][i] = \mathit{dp}[i][i] = 0$;
* $m[i][j] = \max\{\mathit{dp}[i][j],m[i][j+1]\}$, za $0\leq j<i$.

U drugom slučaju radimo sličnu stvar kao u drugom podzadatku: pratimo aktuelno najveće $\mathit{dp}[z][k] + \sum_{p=1}^{k} P(i-j,p)$ za sve $k\leq d$.
To vodi narednom pseudokodu (izuzev inicijalizacije):
```
for d in 2 .. n:
    broj_poklapanja[1] = P(i - j, 1)
    sufiks_max[d][d] = dp[d][d]
    poklapanje_plus_ostatak[0] = 0;
    for k in 1 .. d:
        sufiks_max[d][d - k] = max(sufiks_max[d][d - k + 1], dp[d][d - k]);
        poklapanje_plus_ostatak[k] = 0;
    for t in 2 .. min(d, n - d):
        broj_poklapanja[t] = broj_poklapanja[t - 1] + P(d, t);
        poklapanje_plus_ostatak[t] = broj_poklapanja[t] + dp[d][t];
        dp[d + t][t] = max(dp[d + t][t], sufiks_max[d][t] + broj_poklapanja[t]);
    max_zbir = 0;
    for j in 2 .. (n - d):
        if j <= d:
            max_do_sad = max(max_do_sad, poklapanje_plus_ostatak[j]);
        dp[d + j][j] = max(dp[d + j][j], max_do_sad);
```

Za kraj, pomenimo da je moguće dobiti sve poene čak i kada se implementira rešenje složenosti $O(n^2 \log n)$, pod uslovom da je konstanta sakrivena $O$-notacijom dovoljno mala.
Jedno ovakvo rešenje se zasniva na idejama iz prva dva podzadatka, pri čemu se računanje traženog minimuma vrši korišćenjem *segmentnog stabla*.
Međutim, rešenje vremenske složenosti $O(n^2)$ je kraće i brže.

``` cpp title="04_guster.cpp" linenums="1"
#include <iostream>
#include <string>

#define MAXN 3000

int poklapanje(std::string& s, int n, int p, int j) {
  if (p - j < 0 || p + j - 1 >= n) {
    return 0;
  }
  return s[p - j] == s[p + j - 1];
}

int min(int x, int y) {
  return x < y? x : y;
}

int max(int x, int y) {
  return x > y? x : y;
}

std::string s;
int n;
int dp[MAXN + 1][MAXN + 1];
int sufiks_max[MAXN + 1][MAXN + 1];
int broj_poklapanja[MAXN + 1];
int poklapanje_plus_ostatak[MAXN + 1];
int resenje;

int main() {
  // efikasnost standardnog ulaza i izlaza
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // ulaz
  std::cin >> s;
  n = s.length();

  // inicijalizacija DP
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = (i == j) - 1;
      sufiks_max[i][j] = 0;
    }
    broj_poklapanja[i] = 0;
    poklapanje_plus_ostatak[i] = 0;
  }

  // DP rekurentna veza
  for (int d = 2; d <= n; d++) {
    broj_poklapanja[1] = poklapanje(s, n, n - d, 1);
    // racunanje sufiksnih maksimuma za dp[d]
    sufiks_max[d][d] = dp[d][d];
    poklapanje_plus_ostatak[0] = 0;
    for (int k = 1; k <= d; k++) {
      sufiks_max[d][d - k] = max(sufiks_max[d][d - k + 1], dp[d][d - k]);
      poklapanje_plus_ostatak[k] = 0;
    }
    // t: razlicite duzine sledeceg reda
    for (int t = 2; t <= min(d, n - d); t++) {
      broj_poklapanja[t] = broj_poklapanja[t - 1] + poklapanje(s, n, n - d, t);
      poklapanje_plus_ostatak[t] = broj_poklapanja[t] + dp[d][t];
      dp[d + t][t] = max(dp[d + t][t], sufiks_max[d][t] + broj_poklapanja[t]);
    }
    // slucaj kada je trenutni red duzi od sledeceg
    int max_do_sad = 0;
    for (int j = 2; j <= n - d; j++) {
      if (j <= d) {
        max_do_sad = max(max_do_sad, poklapanje_plus_ostatak[j]);
      }
      dp[d + j][j] = max(dp[d + j][j], max_do_sad);
    }
  }
  
  // resenje: sve dozvoljene duzine prvog reda
  resenje = dp[n][0];
  for (int i = 1; i <= n; i++) {
    resenje = max(resenje, dp[n][i]);
  }

  // izlaz
  std::cout << resenje << std::endl;
  return 0;
}

```
