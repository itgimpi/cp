---
hide:
  - toc
---

# B1 - Kvadrati uzvraćaju udarac

=== "Zadatak"

 | Vremensko ograničenje | Memorijsko ograničenje |
 |:-:|:-:|
 | 500ms | 256MB |

 Mile je video $N$ tačaka u ravni, od kojih $i$-ta ima koordinate $(x_i,y_i)$. Odmah je sebi postavio najprirodnije pitanje: "Na koliko načina se mogu izabrati dve različite tačke, tako da prva bude donje levo teme, a druga gornje desno teme nekog kvadrata sa stranicama paralelnim koordinatnim osama?".

 Pri tome se pod donjim levim temenom kvadrata smatra ono teme koje ima najmanju $x$ koordinatu i najmanju $y$ koordinatu, a pod gornjim desnim temenom ono teme koje ima najveću $x$ i najveću $y$ koordinatu.

 Međutim, tačaka ima puno i Mile je brzo odustao. Pomozite mu i odgovorite na pitanje umesto njega.

## Opis ulaza

 U prvom redu standardnog ulaza nalazi se ceo broj $N$, broj tačaka u ravni. U narednih $N$ redova, nalaze se po dva cela broja, $x_i$ i $y_i$, koji predstavljaju koordinate $i$-te tačke.

## Opis izlaza

 U jedini red standardnog izlaza ispisati jedan broj - koliko različitih parova tačaka možemo izabrati, tako da prva bude donje levo teme, a druga gornje desno teme nekog kvadrata sa stranicama paralelnim koordinatnim osama.

## Ograničenja

- $1 \leq N \leq 100.000$
- $0 \leq x_i, y_i \leq 1.000.000.000$, za svako $1 \leq i \leq N$
- Garantuje se da važi $x_i \neq x_j$ ili $y_i \neq y_j$ za svako $i \neq j$

## Podzadaci

 1. (18 poena) $x_i = y_i$, za svako $1 \leq i \leq N$, $1 \leq N \leq 20.000$.
 2. (16 poena) $1 \leq N \leq 1.000$.
 3. (29 poena) $0 \leq x_i, y_i \leq 1.000$, za svako $1 \leq i \leq N$.
 3. (37 poena) Bez dodatnih ograničenja.

## Primeri

### Primer 1

#### Ulaz

 ```
 4
 0 0
 2 3
 5 6
 4 4
 ```

#### Izlaz

 ```
 2
 ```

#### Objašnjenje

 Ukoliko izaberemo prvu i četvrtu tačku, postoji kvadrat stranice dužine $4$, kojem je donje levo teme baš prva tačka, a gornje desno baš četvrta tačka.  Slično, ukoliko izaberemo drugu i treću tačku, postoji kvadrat stranice dužine $3$, kojem je donje levo teme baš druga tačka, a gornje desno baš treća tačka. Dakle, odgovor je $2$.

### Primer 2

#### Ulaz

 ```
 3
 0 0
 0 2
 2 0
 ```

#### Izlaz

 ```
 0
 ```

#### Objašnjenje

 Koje god dve tačke da izaberemo, ne postoji kvadrat kojem je donje levo teme prva od tih tačaka, a gornje desno teme druga od tih tačaka. Zbog toga je odgovor $0$.

=== "Rešenje"

 | Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
 |:-:|:-:|:-:|:-:|
 | Aleksa Milisavljević | Aleksa Milisavljević | Aleksa Milojević | Vladimir Milenković |

## Podzadatak 1

 U ovom podzadatku svake dve tačke mogu formirati kvadrat opisan u zadatku, pa treba izbrojati broj svih parova tačaka. Odgovor je $\frac{N(N-1)}{2}$.

## Podzadatak 2

 Nije teško primetiti da tačke $(x_1, y_1)$ i $(x_2, y_2)$ mogu biti donje levo i gornje desno teme kvadrata čije su stranice paralelne osama ako i samo ako duž koja spaja ove dve tačke gradi ugao od $45$ stepeni sa $x$ osom u pozitivnom smeru (tj. paralelna je pravoj $y=x$ u koordinatnom sistemu). Ako pretvorimo izrazimo ovaj uslov pomoću koordinata, vidimo da opisani kvadrat postoji ako i samo ako važi $x_1-y_1=x_2-y_2$.

 Dakle, neophodno je izračunati broj parova tačaka $\{(x_i, y_i), (x_j, y_j)\}$ datog skupa za koje važi $x_i-y_i=x_j-y_j$. Da bismo ovo efikasno uradili, imamo više pristupa. Da bismo rešili ovaj podzadatak, nije neophodno biti previše pažljiv, pa za svaki par tačaka možemo proveriti da li važi dati uslov. Složenost ovog rešenja je $O(N^2)$.

## Podzadatak 3

 U ovom podzadatku moramo pažljivije izbrojati parove za koje važi gornji uslov. Dovoljno je napraviti matricu $A$ dimenzija $1001\times 1001$ takvu da $A_{i, j}=1$ ako i samo ako je tačka $(i, j)$ u skupu zadatih tačaka, gde su $i, j=0, 1, \dots, 1000$. Tada, za svaku moguću vrednost $x_i-y_i$, možemo izbrojati koliko se tačaka nalazi na odgovarajućoj dijagonali matrice. Neka je za dijagonalu sa $x_i-y_i=t$ ovaj broj jednak $k_t$. Tada je odgovor $\sum_{t=-1000}^{1000}\frac{k_t(k_t-1)}{2}$.

 Alternativno, ne moramo formirati matricu, već je dovoljno da za svaku moguću razliku $x_i-y_i$ prođemo kroz sve tačke skupa, za svaku od njih proveravajući da li ima odgovaraju razliku koordinata, i na taj način odredimo broj $k_t$. Odgovor je isti kao i u prethodnom pasusu. Složenost ovog pristupa je $O(\max\{|x_i-y_i|\}\times N)$.

## Podzadatak 4

 U ovom delu zadatka moramo efikasno odrediti brojeve $k_t$ definisane gore. Ovo možemo uraditi sortirajući niz tačaka po razlici $x_i-y_i$, a zatim prolaskom kroz niz utvrditi koliko tačaka međusobno ima istu razliku $x_i-y_i$ (pri čemu nije od naročitog značaja konkretna vrednost te razlike). Odgovor je isti kao i u prethodnom podzadatku.

## Smernice za implementaciju

 Zbog veličine brojeva u zadatku (a i potencijalne veličine odgovora), potrebno je koristiti 64-bitne brojeve, da ne bi došlo do prekoračenja i pogrešnog odgovora.

 ``` cpp title="01_kvadrati_uzvracaju_udarac.cpp" linenums="1"
 #include<bits/stdc++.h>
 using namespace std;
 long long ans=0;
 int n;
 int x,y;
 map<long long,int> m;
 int main() {
     scanf("%d",&n);
     for(int i=0;i<n;i++) {
         scanf("%d %d",&x,&y);
         ans+=m[x-y];
         m[x-y]++;
     }
     printf("%lld",ans);
     return 0;
 }

 ```
