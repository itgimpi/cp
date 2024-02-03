---
hide:
  - toc
---

# B3 - Grupe

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 128MB |

Dat je niz $A$ dužine $N$. Takođe, dat je prirodan broj $L$, tako da je $N$ uvek deljivo sa $L$.  Niz $A$ podelimo na $L$ grupa, gde je svaka grupa sačinjena od elemenata čiji indeksi daju iste ostatke pri deljenju sa $L$.

Na koliko načina se mogu izabrati indeksi $i$ i $j$, gde važi $1 \leq i < j \leq N$, tako da nakon što razmenimo elemente niza $A$ sa ovim indeksima, važi da je suma svih grupa jednaka?

## Opis ulaza

Prva linija standardnog ulaza sadrži dva prirodna broja $N$, $L$ odvojena razmakom. Naredna linija sadrži $N$ elemenata odvojenih razmakom - niz $A$.

## Opis izlaza

U prvu i jedinu liniju standardnog izlaza ispisati traženo rešenje.

## Primer 1

### Ulaz

~~~
4 2
1 5 3 3
~~~

### Izlaz

~~~
2
~~~

## Primer 2

### Ulaz

~~~
6 2
1 2 3 4 5 6
~~~

### Izlaz

~~~
0
~~~

### Objašnjenje primera

U prvom primeru jednu grupu čine elementi čiji indeksi daju ostatak $0$ pri deljenju sa $2$, i to su indeksi $2,4$ na kojima se nalaze brojevi $A_2=5,A_4=3$, dok drugu grupu čine elementi čiji indeksi daju ostatak $1$ pri deljenju sa $2$, i to su indeksi $1,3$ na kojima se nalaze brojevi $A_1=1,A_3=3$. Možemo razmeniti elemente sa indeksima 2 i 3, ili elemente sa indeksima 1 i 4.

U drugom primeru ne postoji ni jedan način da razmenom dva elementa dobijemo da dve grupe imaju jednaku sumu.

## Ograničenja

U svim test primerima važi:

* $1 \leq N \leq 200000$
* $0 \leq A_i \leq 2 \cdot 10^6$.

Test primeri su podeljeni u 4 disjunktne grupe:

* U test primerima vrednim 20 poena: $N \leq 10$ i $A_i \leq 500$.
* U test primerima vrednim 20 poena: $N \leq 100$ i $A_i \leq 500$.
* U test primerima vrednim 20 poena: $A_i \leq 500$.
* U test primerima vrednim 40 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksandar Zlateski | Dragan Urošević | Ivan Stošić |

## Analiza

Primetimo da ako zbir svih elemenata niza nije deljiv brojm $L$, onda ne postoji rešenje, jer se niz ne može podeliti u $L$ grupa koji imaju jednake zbirove. Znači u tom slučaju je rešenje nula (0).
Ako je $S$ zbir svih elemenata niza $S$ i ako je $S$ deljivo brojem $L$, onda zbir svake od grupa mora biti $S/L$. Neka je $L'$ broj grupa za koje važi da je zbir različit od $S/L$. Tada važi sledeće:
Ako $L'\not\in\{0,2\}$, onda ne postoji niti jedna razmena kojom bi se izjednačio zbir elemenata u svim grupama, pa je rešenje nula.
Ako je $L'=0$, onda sve grupe već imaju jednak zbir, pa zbog toga razmena bilo kog para elemenata iz iste grupe ili bilo kog para elemenata koji imaju istu vrednost dovodi do niza koji zadovoljava uslov (da sve grupe imaju isti zbir). Broj razmena u kojima se razmenjuju elementi iz iste grupe je

$$
L \times \frac{N/L(N/L-1)}{2}.
$$

Broj razmena u kojima se razmenjuju jednaki elementi se dobija tako što se prebroji broj pojavljivanja svake od vrednosti. Ako su $V_1, V_2, V_3, ..., V_K$ različite vrednosti koji se pojavljuju u nizu $a$, a $n_{V_1}, n_{V_2}, n_{V_3}, ..., n_{V_K}$, brojevi pojavljivanja tih vrednosti onda je broj razmena elemenata koji imaju istu vrednost jednak:

$$
\frac{n_{V_1}(n_{V_1}-1)}{2} + \frac{n_{V_2}(n_{V_2}-1)}{2} + ... + \frac{n_{V_K}(n_{V_K}-1)}{2}.
$$

Međutim, u ovom izrazu figurišu i razmene jednakih koji se nalaze u istoj grupi. Zbog toga te razmene treba oduzeti, a to ćemo izvesti tako što ćemo isti postupak prebrajanja vrednosti izvesti za svaku grupu i izračunati vrednost odgovarajućeg izraza (ekvivalentnog gornjem).
Ako je $L'=2$, onda postoje dve grupe u kojima se zbir ne poklapa sa prosečnom vrednošću (tj. sa $S/L$). U jednoj grupi je zbir veći od proseka, a u drugoj je manji od proseka (pri čemu su apsolutne razlike tih suma i proseka jednake). Označimo sa $d$ apsolutnu razliku sume jedne od tih grupa i proseka $S/L$. Tada se može razmeniti bilo koji par elemenata iz te dve grupe za koji važi da je razlika elementa koji se nalazi grupi sa većim zbirom i elementa koji se nalazi u grupi u kojoj je manji zbir jednak $d$. Znači, potrebno je prebrojati broj pojavljivanja pojedinih vrednosti u dve grupe, nakon toga izmnožiti odgovarajuće brojeve pojavljivanja i proizvode sabrati.
   

##  Smernice za algoritam
Budući da su vrednosti elementa manje od ili jednake $10^6$, može se formirati niz u kome će se računati brojevi pojavljivanja pojedinih vrednosti. Zbog toga brojeve pojavljivanja pojedinih vrednosti možemo odrediti jednim prolazom kroz niz. Pored toga potreban je jedan prolaz kroz niz kako bi se odredili zbirovi elemenata po grupama. Ali kako se u oba slučaja radi o jednom prolazu kroz niz, algoritam ima linearnu složenost.


``` cpp title="03_grupe.cpp" linenums="1"
#include <cstdint>
#include <iostream>
#include <map>
#include <vector>

using std::int64_t;

int main()
{
    int64_t N, K, sum = 0;
    std::cin >> N >> K;

    std::vector<std::map<int64_t, int64_t>> distributions(K);
    std::vector<int64_t>                    groups(K);
    std::map<int64_t, int64_t>              frequencies;

    for (int64_t i = 0; i < N; ++i)
    {
        int64_t w;
        std::cin >> w;
        sum += w;
        groups[i % K] += w;
        ++distributions[i % K][w];
        ++frequencies[w];
    }

    if (sum % K)
    {
        std::cout << "0\n";
        return 0;
    }

    auto average = sum / K;

    std::vector<int64_t> not_average;
    for (int64_t i = 0; i < K; ++i)
    {
        if (groups[i] != average)
            not_average.push_back(i);
    }

    int64_t solution = 0;

    // Mozemo da zamenimo bilo koji par elemenata iste vrednosti, ili
    // bilo koja dva elementa iz iste grupe
    if (not_average.size() == 0)
    {
        solution = K * (N / K) * (N / K - 1) / 2;
        for (auto const& f : frequencies)
            solution += (f.second * (f.second - 1)) / 2;
        // Neke smo racunali duplo (iste vrednosti iz istih grupa)
        for (auto const& d : distributions)
            for (auto const& f : d)
                solution -= (f.second * (f.second - 1)) / 2;
    }
    // Moramo da zamenimo elemente iz ove dve grupe
    else if (not_average.size() == 2)
    {
        auto const& distribution_a = distributions[not_average[0]];
        auto&       distribution_b = distributions[not_average[1]];

        int64_t delta = average - groups[not_average[0]];

        for (auto const& d : distribution_a)
        {
            solution += d.second * distribution_b[d.first + delta];
        }
    }

    std::cout << solution << "\n";
}

```
