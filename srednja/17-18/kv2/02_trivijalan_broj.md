---
hide:
  - toc
---

# 2 - Trivijalan broj

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |

Mala Kaćolina je odavno svima nama poznata kao odličan matematičar. Kako je lako uspela da pomnoži sve moguće parove brojeva manjih od milijardu, rešila je da sebi malo oteža igru sa brojevima.

Definisaćemo trivijalnost broja $x$  kao količnik zbira njegovih pozitivnih delilaca i njega samog (na primer trivijalnost broja $6$ iznosi $\frac{1 + 2 + 3 + 6}{6} = 2$).

Za broj $x$ kažemo da je najtrivijalniji broj u intervalu $[l,r]$ (skupu brojeva $\{ l, l+1, \ldots, r-1, r \}$), ako pripada datom intervalu i njegova trivijalnost je najmanja od trivijalnosti svih brojeva na tom intervalu i ne postoji nijedan drugi broj manji od njega koji pripada intervalu i ima istu trivijalnost. 

Kaćolina je sebi zadala $T$ pitanja oblika :

- Naći najtrivijalniji broj u intervalu $[2, A_i]$

Da li možete odgovoriti na ove upite brže od Kaćoline (njoj otprilike treba dve sekunde da odgovori na sva pitanja)?

## Opis ulaza
Prva linija standardnog ulaza sadrži jedan prirodan broj $T$, koji predstavlja broj pitanja koje je Kaćolina zadala.

Svaka od narednih $T$ linija sadrži jedan broj, tačnije $i$-ta linija sadrži broj $A_i$.

## Opis izlaza
Za svaki od zadatih $T$ upita ispisati najtrivijalniji broj u zadatom intervalu, tačnije u $i$-toj liniji ispisati najtrivijalni broj u intervalu [$2$, $A_i$].

## Primer
### Ulaz
```
1
4
```

### Izlaz
```
3
```

## Objašnjenje primera
Dat je samo jedan upit i potrebno je naći najtrivijalniji broj u intervalu $[2, 4]$.

Trivijalnost broja 2 : $\frac{1 + 2}{2} = 1.50$.

Trivijalnost broja 3 : $\frac{1 + 3}{3} = 1.33$.

Trivijalnost broja 4 : $\frac{1+2+4}{4} = 1.75$.

Najmanju trivijalnost ima broj $3$, tako da je on rešenje ovog primera.

## Ograničenja

* $1 \leq T \leq 10$.
* $2 \leq A_i \leq  5 \cdot 10^6$.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim $10$ poena važi ograničenje $2\leq A_i \leq 20$.
* U test primerima vrednim $20$ poena važi ograničenje $2\leq A_i \leq 1000$.
* U test primerima vrednim $30$ poena važi ograničenje $2\leq A_i \leq 2\cdot 10^5$.
* U test primerima vrednim $40$ poena nema dodatnih ograničenja.


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Aleksa Plavšić | Dragan Urošević | Nikola Jovanović i Ivan Stošić |

Svakako najlakši način da se reši ovaj zadatak jeste da se odredi trivijalnost svakog od brojeva između $2$ i $N$ ($N$ je broj za koji se traži odgovor) i nakon toga odredi broj koji ima najmanju trivijalnost. Pri određivanju zbira delilaca koristimo činjenicu da u paru sa svakim deliocem $d_1 < \sqrt{N}$ ide i delilac $d_2 = \frac{N}{d_1}$. Zbog toga je dovoljno samo za brojeve između $1$ i $\sqrt{N}$ proveravati da li dele broj $N$ i za svaki broj $d<\sqrt{N}$ koji deli broj $n$ dodati zbiru delilaca vrednost $d + \frac{N}{d}$, ako je $\sqrt{N}$ ceo broj onda je i $\sqrt{N}$ takođe delilac broja $N$ i treba ga dodati zbiru (ali sa njim u paru ne ide drugi delilac). Prema tome, određivanje zbira svih delilaca za sve brojeve između $2$ i $N$ ima složenost $O(N\sqrt{N})$. Ako to treba da ponovimo $T$ puta (za $T$ različitih ulaznih vrednosti), onda je ukupna složenost $O(TN\sqrt{N})$.

Gornje rešenje možemo profiniti tako što bi samo jednom računali zbir delilaca za brojeve između $2$ i najvećeg od brojeva $A_i$, nakon toga za svaki pojedinačni $A_i$, određujemo broj sa najmanjom trivijalnošću, računajući količnike zbira delilaca i brojeva za odgovarajuće brojeve.

Određivanje zbira delilaca možemo ubrzati koristeći činjenicu da su svi brojevi $d, 2d, 3d, 4d, \ldots$ deljivi brojem $d$ i zbog toga zbiru delilaca za te brojeve treba dodati broj $d$. Prema tome za svaku vrednost $d=1, 2, 3, \ldots, N$ treba zbiru delilaca brojeva $d, 2d, 3d, \ldots, kd$ (gde je $k$ broj sa osobinom da je $kd \leq n < (k+1)d$) dodati broj tj. delilac $d$. Lako zaključujemo da za konkretno $d$ treba ažurirati (uvećati) zbir delilaca za $\frac{N}{d}$ brojeva, pa je složenost određivanja zbira delilaca za brojeve između $2$ i $N$ jednaka $O(N + \frac{N}{2} + \frac{N}{3} + \ldots + \frac{N}{N}) = O(N\log N)$.

Primetimo da je zbir delilaca za proste brojeve $p$ jednak $p+1$ i trivijalnost prostog broja je jednaka $1 + \frac{1}{p}$. S druge strane svaki složen broj $N$ ima osobinu da je zbir delilaca veći od $N + \sqrt{N}$, pa je trivijalnost veća od $1 + \frac{1}{\sqrt{N}}$. Nameće se da će najmanju trivijalnost u intervalu od $2$ do $N$ imati najveći prost broj koji nije veći od $N$.  Određivanje tog najvećeg prostog broja možemo izvesti tako što za brojeve $N, N-1, N-2, \ldots$ proveravamo da li su prosti i postupak prekidamo kada odredimo prvi broj koji jeste prost. Postupak možemo profiniti tako što bi testirali (proveravali) samo brojeve oblika $6k+1$ i $6k+5$ (naravno, izuzetak su $2$ i $3$).

Proveru da li je broj prost $N$ izvodimo proveravavajući da li ima delioce među brojevima između $2$ i $\sqrt{N}$. Ako među njima ima bar jedan delilac onda broj $N$ nije prost, u suprotnom jeste.

Postupak provere da li je broj prost možemo ubrzati tako što bi proveravali da li broj $N$ ima delioce samo među prostim brojevima između $2$ i $\sqrt{N}$. Zbog toga bi za početak trebalo da odredimo samo proste brojeve između $2$ i $\sqrt{N}$ (koristeći na primer Eratostenovo sito), a zatim da testiramo da li je neki broj prost tako što proveravamo da li je deljiv nekim prostim brojem koje smo prethodno izdvojili.

``` cpp title="02_trivijalan_broj.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;

const int maxi=5000001;

long long a[maxi];
long long s[maxi];

int main()
{

    for (int i=1; i<maxi; i++)
        for (int j=i; j<maxi; j+=i)
            s[j]+=i;

    int t,x;

    cin>>t;

    while(t--)
    {
        cin>>x;

        long long ans=2;
        for (int i=2; i<=x; i++)
            if (1.0*s[i]/i <1.0*s[ans]/ans) ans=i;

        cout<<ans<<"\n";
    }

    return 0;
}

```
