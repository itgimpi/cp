---
hide:
  - toc
---

# 1 - Spojler

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 256MB |

Na tvoju adresu stigla je misteriozna poruka od nepoznatog pošiljaoca. Ono što je posebno neobično jeste da je poruka poslata početkom 2023. godine, a ova poruka stiže sredinom decembra 2022. godine. Otvorivši poruku, vidiš da je u prilogu video zapis finala svetskog prvenstva u fudbalu, koje će tek biti odigrano, i učestvovaće reprezentacije Argentine i Francuske. Poruka takođe sadrži i "spojlovan" konačan rezultat utakmice. Ipak, odlučuješ da pogledaš ovaj neobičan video zapis iz budućnosti.

Na poluvremenu utakmice, pogledaš trenutni rezultat utakmice $x:y$ i setiš se najavljenog konačnog rezultata $a:b$ iz poruke. Tog trenutka pomisliš da li je moguće odrediti koji tim će sledeći dati gol, pretpostavljajući da je konačan rezultat naveden u misterioznoj poruci ispravan.

## Opis ulaza
U prvom redu standardnog ulaza se nalaze dva prirodna broja $a$ i $b$ (spojlovan rezultat),
dok se u drugom redu standardnog ulaza nalaze dva prirodna broja $x$ i $y$ (rezultat na poluvremenu).

## Opis izlaza
U jedinom redu standardnog izlaza ispisati: 

* `prvi` ukoliko je moguće zaključiti da će prvi tim (opisan brojevima $a$ i $x$) dati sledeći gol
* `drugi` ukoliko je moguće zaključiti da će drugi tim (opisan brojevima $b$ i $y$) dati sledeći gol
* `nijedan` ukoliko je moguće zaključiti da u nastavku utakmice neće biti više nijednog gola
* `?` ukoliko nije moguće jednoznačno zaključiti koji tim će postići naredni gol

## Primer 1
### Ulaz
```
1 2
1 0
```

### Izlaz
```
drugi
```

## Primer 2
### Ulaz

```
1 1
1 1
```

### Izlaz
```
nijedan
```

## Primer 3
### Ulaz
```
4 4
3 2
```

### Izlaz
```
?
```

## Objašnjenje primera
U prvom primeru je prvi tim već postigao sve golove u toj utakmici, a drugi nije.
Jedini mogući dalji ishod utakmice je $1:0 \to 1:1 \to 1:2$.
Prema tome, drugi tim je sledeći koji će dati gol.

U drugom primeru su na poluvremenu dati svi golovi koji će biti ostvareni tokom utakmice.
Prema tome, nijedan tim neće postići još jedan gol.

U trećem primeru nije moguće odrediti koji tim će dati sledeći gol -- mogući dalji ishodi
utakmice su:
* $3:2 \to 4:2 \to 4:3 \to 4:4$
* $3:2 \to 3:3 \to 4:3 \to 4:4$
* $3:2 \to 3:3 \to 3:4 \to 4:4$

tim već postigao sve golove u toj utakmici, a drugi nije.
Prema tome, drugi tim je sledeći koji će dati gol.

## Ograničenja

* $0 \leq a, b \leq 100$
* $0 \leq x \leq a$
* $0 \leq y \leq b$

Test primeri su podeljeni u tri disjunktne grupe:

* U testovima vrednim 20 poena: na osnovu konačnog rezultata $a:b$ se vidi da je ukupno dat jedan gol.
* U testovima vrednim 20 poena: na osnovu konačnog rezultata $a:b$ se vidi da jedan tim nije dao nijedan gol.
* U testovima vrednim 60 poena: nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Andrej Ivašković | Vladimir Milovanović | Vladimir Milovanović |

## Glavno rešenje
Nije teško uočiti da na osnovu rezultata $a:b$ na kraju utakmice, kao i rezultata $x:y$ na poluvremenu, postoji četiri različita slučaja:

- $x = a$ i $y = b$, odnosno da je rezultat na kraju jednak rezultatu na poluvremenu, pa u nastavku neće biti golova;
- $x < a$ i $y < b$, što dalje znači da će obe ekipe postići gol, pa na osnovu rezultata nije moguće utvrditi koja će ekipa zabiti naredni;
- $x < a$ i $y = b$, što implicira da će prva ekipa postići naredni gol;
- $x = a$ i $y < b$, što znači da će druga ekipa postići naredni gol.

Jednostavnim postavljanjem ova četiri uslova i odgovarajućim ispisima dolazi se do traženog rešenja u konstantnoj vremenskoj složenosti $\mathcal{O}(1)$.

``` cpp title="01_spojler.cpp" linenums="1"
#include <iostream>

void write_sol(std::ostream& f, int a, int b, int x, int y) {
  if (a == x && b == y) {
    f << "nijedan" << std::endl;
  } else if (a == x) {
    f << "drugi" << std::endl;
  } else if (b == y) {
    f << "prvi" << std::endl;
  } else {
    f << "?" << std::endl;
  }
}

int main() {
  int a, b, x, y;
  std::cin >> a >> b;
  std::cin >> x >> y;
  write_sol(std::cout, a, b, x, y);
  return 0;
}


```
