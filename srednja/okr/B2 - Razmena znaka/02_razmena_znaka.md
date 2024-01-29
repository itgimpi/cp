---
hide:
  - toc
---

# B2 - Razmena znaka

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 256MB |
	
Žika je za rođendan dobio ono što protagonisti informatičkih zadataka uvek dobiju kad pisci tekstova nemaju bolju ideju o čemu da naprave priču u svom zadatku - niz $A_i$ od $N$ celih brojeva. Međutim, ovaj fenomen je toliko čest, da je Žika i za prošli rođendan dobio niz dužine $N$ - niz $B_i$! Žika, kao i svaki normalan čovek, nema potrebe za dva različita niza dužine $N$, pa hoće da transformiše svoj novodobijeni niz $A_i$ u $B_i$. 
	
Pošto nam je potreban zadatak za svrhu drugog zadatka u B kategoriji, Žika je odlučio da jedina operacija koju može da izvrši na nizu $A$ je da izabere dva susedna broja u nizu i zameni im mesta, a zatim im promeni znakove. Ovo znači da ako je niz pre bio $A_1$, $A_2$, $\cdots$, $A_i$, $A_{i+1}$, $\cdots$, $A_N$, posle jedne operacije postaje $A_1$, $A_2$, $\cdots$, $-A_{i+1}$, $-A_i$, $\cdots$, $A_N$. Vaš zadatak je da kažete Žiki da li je moguće da ovim operacijama tranformiše niz $A_i$ tako da važi da je $A_i=B_i$ za svako $i\in\{1,2,\cdots,N\}$.
	
## Opis ulaza
Prva linija standardnog ulaza sadrži broj test primera $T$. U narednim redovima su opisani svaki od nezavisnih $T$ test primera. U prvom redu svakog test primera se nalazi jedan nenegativan ceo broj $N$ koji predstavlja dužine nizova $A_i$ i $B_i$. Zatim u naredna dva reda se nalazi po $N$ celih brojeva, koji predstavljaju vrednosti u nizovima $A_i$ i $B_i$, redom.
	
## Opis izlaza
U $i$-tom redu standardnog izlaza napisati odgovor  na $i$-ti test primer. Ako je moguće stići od niza $A_i$ do niza $B_i$ primenkom konačno mnogo opisanih operacija, napisati "DA" (bez navodnika), a u suprotnom "NE" (opet, bez navodnika).
	
## Primer
### Ulaz
```
3
2
1 2
-1 -2
2
1 2
-2 -1
4
1 2 3 4
-4 -3 -2 -1
```
	
### Izlaz
```
NE
DA
DA
```
	
## Objašnjenje primera
Ako je početni niz $1,2$, jedini drugi niz koji je moguće dobiti je $-2,-1$ (primenom još jedne zamene, vraća se na originalni niz), tako da je odgovor u test primeru upitu "NE", a u drugom "DA". U trećem primeru je moguće naći niz poteza koji $A_i$ pretvara u $B_i$ tako što redom radimo razmene na $(1,2)$, $(2,3)$, $(3,4)$, $(1,2)$, $(2,3)$, $(1,2)$. 
	
## Ograničenja
-   $1 \leq T \leq 10$.
-   $1 \leq N \leq 30.000$.
-   $0\leq |A_i|,|B_i|\leq 1.000.000.000$.
	
Test primeri su podeljeni u četiri disjunktne grupe:
	
-   U test primerima vrednim $15$ poena: U oba niza su sve vrednosti $0$ osim jedne.
-   U test primerima vrednim $25$ poena: $A_i,B_i\in\{-1,1\}$.
-   U test primerima vrednim $25$ poena: $|A_i|\neq|A_j|$ i $|B_i|\neq|B_j|$ za $i\neq j$.
-   U test primerima vrednim $35$ poena: Bez dodatnih ograničenja.
	