---
hide:
  - toc
---

# 2 - Mlađioničar

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |


Mladen je pre nekoliko dana gledao mađioničarsku predstavu, u kojoj je
mađioničar odlučio da izvede jedan neobičan trik. 

Prvo je ubacio $N$ kuglica u džak, koristeći samo crvene, zelene i
plave kuglice. Zatim je izvlačio kuglice jednu po jednu, dok nije
izvukao crvenu. Posle toga ih je sve vratio u džak, pa je izvlačio
kuglice dok nije pronašao zelenu. Na kraju, opet ih je vratio i
izvlačio dok nije pronašao plavu kuglicu.

Ideja trika je bila da pokaže da su kuglice magično menjale boju dok su
bile sakrivene, i da su događaji kakvi su se desili nemogući ako je u
džaku stvarno bilo $N$ kuglica sa početka. Mladen, ipak, nije siguran
da je ovo tačno, i misli da je sve što je video moguće bez trikova.

Mladen se ne seća svega što je video, ali se seća koliko je kuglica
izvučeno u svakom od tri dela trika, i koliko je kuglica ubačeno u džak
na početku. Interesuje ga da li postoji neki broj crvenih, zelenih i
plavih kuglica u džaku takav da je ovaj ishod moguć, i ako jeste, da mu
date jedan takav primer.

## Opis ulaza

U prvom redu standardnog ulaza nalaze se četiri cela broja $N, A, B,
C$: broj kuglica u džaku i redom brojevi kuglica izvučeni u prvoj (do
prve crvene kuglice), drugoj (do prve zelene) i trećoj (do prve plave)
fazi trika.

Broj izvučenih kuglica **uključuje i poslednju**. Na primer, ako su u
prvoj fazi izvučene dve zelene, plava, i na kraju jedna crvena
kuglica, $A$ je $4$.

## Opis izlaza

Ukoliko postoje brojevi $R, G, B$ takvi da su događaji opisani u
zadatku mogući ukoliko je u džaku na početku bilo $R$ crvenih, $G$
zelenih i $B$ plavih kuglica, u prvoj liniji standardnog izlaza
ispisati `moguce`, i u drugoj liniji ispisati brojeve $R$, $G$ i $B$.

U suprotnom, u jedinoj liniji standardnog izlaza ispisati `nemoguce`.

## Primer 1
### Ulaz
```
10 3 4 2
```

### Izlaz
```
moguce
5 3 2
```

### Objašnjenje
Ako je u džaku bilo pet crvenih, tri zelene i dve plave kuglice, jedna
mogućnost je da se trik odvijao na sledeći način: prvo su izvučene dve
plave pa crvena kuglica, u drugoj fazi crvena, plava, crvena pa
zelena, i u trećoj zelena pa plava kuglica.

## Primer 2
### Ulaz
```
5 5 5 5
```

### Izlaz
```
nemoguce
```

### Objašnjenje
Ako su u prvoj fazi izvučene sve kuglice, možemo zaključiti da džak
sadrži tačno jednu (poslednju) crvene boje. Slično možemo zaključiti da
postoji tačno jedna plava i jedna zelena kuglica. Kako postoji pet
kuglica, ovakav niz događaja nije moguć.


## Ograničenja

- $1 \leq N \leq 10^9$
- $1 \leq A, B, C \leq N$

Test primeri su podeljeni u tri disjunktne grupe:

- U testovima vrednim 30 poena važi $N \leq 200$.
- U testovima vrednim 30 poena važi $N \leq 2000$.
- U testovima vrednim 40 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Andrej Ivašković | Dimitrije Erdeljan | Dragan Urošević | Andrej Ivašković |

Označimo sa $r$, $g$ i $b$, redom broj crvenih, zelenih i plavih kuglica. Tada će u najnepovoljnijem slučaju crvenu kuglici izvući nakon što izvuče sve zelene i plave. Slično će zelenu kuglicu izvući najkasnije nakon izvlačenja svih crvenih i plavih, a plavu nakon što izvuče sve crvene i zelene. Prema tome, važiće sledeće nejednakosti
$$
A \leq g+b+1,\quad B \leq r+b+1, \quad C \leq r+g+1.
$$
Pored toga je ukupan broj kuglica jednak $N$, pa važi:
$$
r+g+b = N.
$$

## Rešenje kad je $N \leq 200$

U ovom slučaju, možemo za sve moguće vrednosti brojeva $r$, $g$ i $b$ (a to su prirodni brojevi između $1$ i $N$), proveriti da li zadovoljavaju tri nejednakosti i poslednju jednakost i prekinuti proveravanje onog trenutka kada su zadovoljene. Ako pomenute nejednakosti i jednakost nisu zadovoljeni ni za jednu kombinaciju vrednosti $r$, $g$ i $b$, ne postoji raspored kuglica koji odgovara vrednostima $A$, $B$ i $C$. Očigledno je složenost ovog rešenja $O(N^3)$. 

## Rešenje kad je $N \leq 2000$

Primetimo da za fiksirane vrednosti broja crvenih ($r$) i zelenih ($g$) kuglica možemo odrediti broj plavih kuglica po formuli $b=N-r-g$. Zbog toga je dovoljno za sve kombinacije vrednosti brojeva $r$ i $g$ (a to su brojevi između $1$ i $N$), odrediti vrednost broja $b$, a nakon toga proveriti da li su zadovoljene tri nejednakosti. 
Složenost ovog rešenja $O(N^2)$.

## Glavno rešenje

Kako u vreći treba da bude bar jedna crvena, zelena i plava, brojeve kuglica možemo prikazati kao
$$
r = 1 + r1,\quad g = 1+g1, \quad b = 1+b1,\quad r1,g1,b1\geq 0.
$$
Tada vaši sledeće:

$$
r1+g1+b1 = (r-1) + (g-1) + (b-1) = (r+g+b)-3 = N-3 = N1.
$$

Pored toga, polazne nejednakosti postaju:
$$
A\leq g+b+1 = (1+b1)+(1+b1)+1 = g1+b1+3,
$$
odnosno
$$
g1+b1 \geq A-3,
$$
ili preciznije
$$
g1+b1 \geq \max(A-3,0) = A1.
$$
Slično se dobija
$$
r1+b1 \geq \max(B-3,0)=B1
$$
i
$$
r1+g1 \geq \max(C-3,0) = C1.
$$
Sabiranjem poslednje tri nejednakosti dobijamo
$$
2r1+2g1+2b1=2N1\geq A1+B1+C1,
$$
i ovo je potreban uslov da bi postojalo rešenje.

Pokazuje se da je to i dovoljan uslov. Da bi odredili rešenje, primetimo da iz uslova
$$
r1+g1+b1 = N1\quad\text{i}\quad g1+b1\geq A1,
$$
dobijamo
$$
r1 = N1-(g1+b1) \leq N1-A1 = r1_{max},
$$
i slično:
$$
g1 \leq N1-B1= g1_{max}\quad\text{i}\quad b1 \leq N1-C1=b1_{max}.
$$
Za brojeve $r1$, $g1$ i $b1$ biramo najveće koji zadovoljavaju nejednakosti i u zbiru daju broj $N1$.
Primetimo da se mogu odabrati brojevi $r1$, $g1$ i $b1$ tako da zadovoljavaju gornje nejednakosti i zbir bude $N1$ zato što je zbir gornjih ograničenja 
$$
r1_{max}+g1_{max}+b1_{max} = (N1-A1)+(N1-B1)+(N1-C1) = 3N1 - (A1+B1+C1) \geq 3N1 - 2N1 = N1.
$$
Konačno, same vrednosti možemo izabrati na sledeći način:
$$
r1 = \min(N1,N1-A1),\quad
g1 = \min(N1-r1, N1-B1),\quad
b1=\min(N1-r1-g1,N-C1).
$$

Složenost ovog rešenja je $O(1)$.




``` cpp title="02_mladjionicar.cpp" linenums="1"
#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a < b ? b : a; }

int main() {
    int n, gb, rb, rg;
    scanf("%d %d %d %d", &n, &gb, &rb, &rg);

    // bez poslednje
    gb--; rb--; rg--;

    // smena da bi garantovali da imamo bar jednu od svake boje
    if(n < 3) {
        printf("nemoguce\n");
        return 0;
    }
    n -= 3;
    rg = max(0, rg - 2);
    gb = max(0, gb - 2);
    rb = max(0, rb - 2);

    /*
      r + g + b == n  (1)
      r + g >= rg     (2)
      g + b >= gb     (3)
      r + b >= rb     (4)

      (2) + (3) + (4):
      2(r + g + b) >= rg + gb + rb
      2n >= rg + gb + rb  (5)

      (5) je potreban uslov -- ako ne vazi nema resenja. Ako vazi, na
      sledeci nacin mozemo naci resenje, tako da je i dovoljan:

      (1) - (2):
      b <= n - rg  (6)
      slicno:
      r <= n - gb  (7)
      g <= n - rb  (8)

      Ako odaberemo bilo koja tri r, g, b za koje vazi (6--8) i (1),
      bice ispunjeni i uslovi (2--4) (npr (2) sledi iz (1)-(6)).
      Mozemo ih odabrati tako sto biramo redom najvece moguce
      vrednosti za koje zbir iz (1) nije premasen -- zbir ce uvek biti
      dostignut zbog sledeceg:

      rmax + gmax + bmax == (n-rg) + (n-gb) + (n-rb) == 3n - (rg + gb + rb)
      (5):
      rmax + gmax + bmax >= 3n - 2n == n
     */

    // NB: rg + gb + rb moze biti vece od INT_MAX
    long long rgb2 = (long long)rg + (long long)gb + (long long)rb;

    if(2*n < rgb2) {
        printf("nemoguce\n");
    } else {
        int r, g, b;
        r = min(n - gb, n);
        g = min(n - rb, n - r);
        b = min(n - rg, n - r - g);

        printf("moguce\n%d %d %d\n", r+1, g+1, b+1);
    }

    return 0;
}

```
