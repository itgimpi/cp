# A1 - Koncert (mehurić)

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |

Data je matrica sa n redova i m kolona, numerisana kao u matematici. Svako polje matrice je slobodno '0' ili zauzeto '1'. 
U matricu treba da se doda novi element '1'.
Dodavanje se vrši iz zadnjeg reda. Ako nema mesta u zadnjem redu, ništa. Ako ima, novi element se pomera:
1. Za jedno polje iznad (u red ispred) ako je to polje slobodno; ili
2. Za jedno polje ulevo ili udesno (u istom redu). Prilikom pomeranja ulevo/udesno može da se jednostavno postavi na slobodno polje ili da gura elemente u nekom smeru. 
Ako je snaga novog elementa k i ako je neposredno levo od elementa grupa od najviše k elemenata posle koje postoji bar jedno slobodno polje, pomera se ulevo za jedno polje, i cela grupa se takođe pomera za po jedno polje ulevo. Isto važi i za pomeranje udesno. Elementi ne smeju da idu van matrice.

Novi element treba da nizom poteza dođe do nekog polja u prvom redu ali da se nijedno polje ne poseti više od jednom. 

Koji je broj načina za postavljanje u prvi red po modulu $10^9+7$?


## Opis ulaza
U prvom redu su n, m и k, n i m su dimenzije matrice, k snaga novog elementa. U sledećih n redova je po m znakova, '0' ili '1'.
## Opis izlaza
Broj načina po modulu $10^9+7$.
## Primer1

### Ulaz

```
3 9 3
010001100
101011010
011101110
```

### Izlaz

```
7
```
## Objašnjenja primera
U 3 reda je po 9 polja; снага такмичара је 3. 
```
  123456789
  ---------
1|010001100
2|101011010
3|011101110
  ---------
  123456789
```
Neka je 'U' Up, 'L' Left i 'R' Right.
Novi element može da se doda na pozicije (3,1), (3,5) i (3,9) u zadnjem redu.
Ako se krene iz (3,1) posoje dva načina, prvi je:
```
  123456789
  ---------
1|010001100    010001100    010001100    010001100    01N001100
2|101011010 -> 101011010 -> 1N1011010 -> 10N111010 -> 100111010
3|N11101110    0N1111110    001111110    001111110    001111110
  gura 3 el    ide gore     gura 1 el    ide gore     kraj (prvi red)
  R->          U^           R->          U^  
```
Drugi način:
```
  123456789
  ---------
1|010001100    010001100    010001100    010001100    010001100    010N01100
2|101011010 -> 101011010 -> 1N1011010 -> 10N111010 -> 100N11110 -> 100011110
3|N11101110    0N1111110    001111110    001111110    001111110    001111110
  gura 3 el    ide gore     gura 1 el    gura 3 el    ide gore     kraj (prvi red)
  R->          U^           R->          R->          U^ 
```

Ako se krene iz (3,5), načini su: LUU, LULU, LURU.
Ako se krene iz (3, 9), načini su: UU и ULU. 
Ukupno 7 načina. 
Kretanji iz (3,1) RUU nije moguće, jer u trećem potezu ne može gore.
Ni RURRRU jer u petom potezu ne mogu da se guraju 4 elementa.

## Primer2

### Ulaz

```
4 5 1
11000
00110
01001
10001
```

### Izlaz

```
0
```
## Objašnjenja primera
...

## Ograničenja
-   $2 \leq n,m \leq 2000$
-   $0 \leq k \leq m$
-   Сви карактери матрице из улаза ће бити '0' или '1'.

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $7$ poena: Nema zauzetih polja, svi elementi su '0'.
-   U test primerima vrednim $11$ poena: $n, m \leq 7$
-   U test primerima vrednim $15$ poena: $k=0$
-   U test primerima vrednim $22$ poena: $n, m \leq 400$
-   U test primerima vrednim $45$ poena: Bez dodatnih ograničenja

