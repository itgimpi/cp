---
hide:
  - toc
---

# B2 - Fotografisanje

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Anastasija je kupila nov fotoaparat i želi da postane fotograf. Kako bi započela svoju fotografsku karijeru odlučila je da prvog dana fotografiše svoje drugare, besplatno. 

Ona ima ukupno $N$ drugara koje će fotografisati tog dana i oni su numerisani brojevima od $1$ do $N$. Svako od njenih drugara joj je rekao vreme u tom danu kada bi on želeo da ga Anastasija fotografiše. Dan ima $10^9$ trenutaka koji su označeni celim brojevima od $1$ do $10^9$. Ona u jednom trenutku može fotografisati više ljudi, ako su svi oni izrazili želju da se fotografišu u istom trenutku. 

Anastasija želi da poboljša ovaj raspored. Pošto nema mnogo vremena ona bira samo jednog drugara i briše njegov termin za fotografisanje. Ona zatim bira novi termin za njega istog dana u intervalu od $1$ do $10^9$, takav da najveća pauza između dva uzastopna fotografisanja bude što manja. Pritom, dozvoljeno je da upiše isti termin kao onaj koji je prethodno bio upisan.

Pomozite Anastasiji i umesto nje odaberite kom drugaru će da promeni termin i koje je vreme novog fotografisanja, kako ona ne bi gubila vreme i pripremila se što bolje za naporan prvi radni dan.

Ako ima više rešenja ispisati bilo koje. 

## Opis ulaza

U prvoj liniji standardnog ulaza se nalazi jedan ceo broj, $N$, koji predstavlja broj Anastasijinih drugara koji će se fotografisati. U narednoj liniji se nalazi niz $T$ od $N$ celih broejeva, gde $T_i$ predstavlja vreme za fotografisanje $i$-tog drugara. Niz $T$ je dat u neopadajućem poretku.

## Opis izlaza

U jedinoj liniji standardnog izlaza se nalaze dva cela broja $X$ i $Y$ gde $X$ predstavlja indeks drugara koji menja termin, a $Y$ novo vreme za njegovo fotografisanje.

## Primer 1

### Ulaz

~~~
3
2 6 7
~~~

### Izlaz

~~~
1 5
~~~

## Primer 2

### Ulaz

~~~
3
2 4 4
~~~

### Izlaz

~~~
1 4
~~~

## Primer 3

### Ulaz

~~~
3
28 28 28
~~~

### Izlaz

~~~
2 28
~~~


## Objašnjenje primera

U prvom primeru je najbolje prvog drugara premestiti u trenutak 5 i tada je minimalna pauza 1. Moguće je i premestiti ga u trenutak 6 ili 7, ali opet je minimalna pauza 1.

U drugom primeru je najbolje prvog drugara premestiti u trenutak 4 i tako neće biti pauze između termina za fotografisanje.

U trećem primeru nema pauze između fotografisanja i najbolje je sve ostaviti kako je bilo.


## Ograničenja

U svim test primerima važi:

* Niz $T$ je sortiran neopadajuće.
* $2 \leq N \leq 2 \cdot 10^5$
* $1 \leq T_i \leq 10^9$

Test primeri su podeljeni u 4 disjunktne grupe:

* U test primerima vrednim 20 poena: $N = 3$.
* U test primerima vrednim 20 poena: Razlika najmanjeg i najvećeg člana niza $T$ je $1$.
* U test primerima vrednim 20 poena: $N \leq 100$
* U test primerima vrednim 40 poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Marko Savić | Filip Ćosović | Vladimir Milovanović | Vladimir Milenković |

## Analiza

Praktično je u zadatku dat sortiran niz od $N$ prirodnih brojeva i zahteva se promena najviše jednog člana tog niza tako da se minimizuje najveća razlika članova koji su susedni ne po indeksima, već po vrednostima.

Da bi se to postiglo, potrebno u jednom prolasku kroz niz odrediti najveću razliku između dva susedna člana. Ta najveća razlika može biti jedinstvena ili nejedinstvena, a može se pojavljivati na rubovima (početak i/ili kraj) niza i/ili u sredini niza.

Ukoliko se najveća razlika susednih članova niza pojavljuje na početku, odnosno na kraju niza, moguće je prostim izjednačavanjem prvog sa drugim članom niza, odnosno poslednjeg sa pretposlednjim članom u potpunosti eliminisati tu razliku.

Međutim, za razliku od unutrašnjih članova niza, pažljivom promenom rubnih članova ne može doći do povećanja maksimalne razlike. Ova činjenica može se iskoristiti za smanjenje još neke razlike unutar ili na drugom kraju niza. Naime, umesto izjednačavanja rubnog člana niza sa njegovim susedom, ovaj član se može iskoristiti za potiranje druge najveće razlike. Na taj način, praktično je u pojedinim slučajevima moguće eliminisati prve dve najveće razlike pod uslovom da se jedna od njih nalazi na rubu niza.

Konkretno, nije teško pokazati da se do optimalnog rešenja uvek dolazi promenom najmanjeg ili najvećeg člana niza. Od ova dva člana neophodno je izmeniti onaj čija je razlika s njegovim jedinim susedom veća. Izmenjena vrednost treba da umanji najveću razliku u ostatku niza, a to je ispravno učiniti promenom na vrednost aritmetičke sredine susednih članova niza među kojima je razlika najveća.

## Smernice za algoritam

Može se prvo ispitati granični slučaj od dva člana koji se jednostavno rešava izjednačavanjem vrednosti bilo prvog člana sa drugim, bilo drugog sa prvim. Ukoliko se pak niz sastoji od tri i više članova treba odrediti da li je veća razlika između prvog i drugog ili pretposlednjeg i poslednjeg člana niza. Potom u jednom prolasku kroz ostatak niza (kome ne pripada rub niza sa većom razlikom) odrediti najveću razliku između susednih članova. Jednostavnom promenom vrednosti rubnog člana na vrednost aritmetičke sredine dva susedna člana s najvećom razlikom dolazimo do rešenja zadatka. Kako u zadatku imamo jedan prolazak kroz niz u kojoj se traži najveća razlika susednih članova složenosti $\mathcal{O}(N)$, to je ukupna vremenska složenost algoritma linearna.

``` cpp title="02_fotografisanje.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

const int MAXN=int(2e5+50);

int main()
{
    int n;
    pair <int,int> a[MAXN];

    scanf("%d",&n);

    for (int i=1; i<=n; i++)
    {
        scanf("%d",&a[i].first);
        a[i].second=i;
    }

    if (n==2)
    {
        printf("1 %d\n",a[2].first);
        return 0;
    }

    sort(a+1,a+n+1);

    if (a[2].first-a[1].first>a[n].first-a[n-1].first)
    {
        int mx=-1;
        for (int i=3; i<=n; i++)
            if (mx==-1 || a[i].first-a[i-1].first > a[mx].first-a[mx-1].first)
                mx=i;
        printf("%d %d\n",a[1].second,(a[mx].first+a[mx-1].first)/2);
    }
    else
    {
        int mx=-1;
        for (int i=2; i<=n-1; i++)
            if (mx==-1 || a[i].first-a[i-1].first > a[mx].first-a[mx-1].first)
                mx=i;
        printf("%d %d\n",a[n].second,(a[mx].first+a[mx-1].first)/2);
    }

    return 0;
}

```
