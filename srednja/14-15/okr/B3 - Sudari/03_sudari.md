---
hide:
  - toc
---

# B3 - Sudari

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |


Mali Drejko je sinoć imao noćnu moru u kojoj se našao u lavirintu bez izlaza i, još gore, zaboravio sve što zna o algoritmima. U tom snu je pokušavao da nađe izlaz jednim neispravnim, pogrešno interpretiranim (odnosno nevešto prepisanim) postupkom: umesto rezona “drži levu ruku uz zid”, držao se heuristike “ići ću napred dok ne naletim na zid i, kad se to desi, skrenuću levo i ponoviti isti postupak”. Košmar je toliko potresao Drejka da je zaboravio detalje sna, ali se ipak seća nekih stvari.

Drejko je upamtio da je lavirint mogao da se predstavi kao pravougaona matrica $n\times m$, pri čemu su elementi te matrice ili zidovi ili slobodna polja, a uspeo je da se seti i svih polja u ovoj matrici. Drejko ne može da se seti koja je polja obišao u lavirintu, ali se seća svog početnog položaja, činjenice da se prvo kretao južno, da je $k$ puta udario glavom o zid i da se probudio neposredno nakon  $k$-tog sudara sa zidom. Čitajući sanovnik, shvatio je da je za potpuno tumačenje neophodno da zna tačan položaj u kom se nalazio neposredno pre buđenja.

Drejko je vrstan programer, ali je trenutno toliko uzbuđen i potresen da ne može da razmišlja o ovom zadatku. Pomozite Drejku da protumači svoj san.

## Ulaz
U prvom redu standardnog ulaza se nalaze prirodni brojevi $n$ i $m$, broj vrsta i kolona matrice, redom. 

U drugom redu se nalaze prirodni brojevi $y$ i $x$, gde $(y,x)$ predstavlja polje na kom se Drejko nalazio na početku sna ($(1,1)$ je gornji levi ugao matrice, a $(n,m)$ donji desni). 

U trećem redu se zadaje prirodan broj $k$ – ukupan broj sudara Drejkove glave sa zidom. U narednih $n$ redova standardnog ulaza se nalazi po m znakova ‘#’ ili ‘.’ (bez navodnika), gde ‘#’ predstavlja zid, a ‘.’ slobodno polje. Početno Drejkovo polje $(y,x)$ će uvek biti ‘.’. Smatrati da je sudar Drejka sa granicom matrice – sudar sa zidom.

## Izlaz
U prvom i jedinom redu standardnog izlaza ispisati koordinate $(y',x')$ poslednjeg polja na kome se Drejko našao u toku sna, razdvojene jednim znakom razmaka.

## Ograničenja:
- $1\leq n,m \leq 500$
- $1 \leq k \leq 10^{18}$ 

Test primeri su podeljeni u tri disjunktne grupe:

-   U test primerima vrednim 30 poena važi $1\leq k \leq 1000$.
-   U test primerima vrednim 40 poena važi $1 \leq k \leq 10^7$.
-   U test primerima vrednim 30 poena nema dodatnih ograničenja.


## Primeri:
### Primer 1
#### Ulaz
```
4 5  
2 1  
4  
...#.  
.#...  
....#  
#....
```

#### Izlaz
```
2 3
```

### Primer 2
#### Ulaz
```
3 5  
2 1  
3  
.....  
...#.  
....#
```

#### Izlaz
```
3 4
```




#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Andrej Ivašković | Dragan Urošević | Andrej Ivašković | Petar Veličković |

## Rešenje za $k\leq1000$:
U slučaju $k\leq1000$ je dovoljno da se primeti da će između svaka dva sudara biti najviše $\{ m,n \}$  koraka: u najgorem slučaju se Drejko kretao od jednog do drugog kraja matrice. Stoga je simulacija ovog kretanja prihvatljivo rešenje čija je vremenska složenost $O(k \cdot \{ m,n \} )$

Iako iza ovog rešenja ne postoji nikakva prava “ideja”, ono se pokazuje izuzetno teškim za ispravnu implementaciju. Konkretno, u jednom pristupu bismo morali da razmatramo sve moguće “režime” kretanja i, u zavisnosti od toga da li se Drejko kreće ka severu, jugu, zapadu ili istoku, imali bismo razne slučajeve. Pojedinačno oni nisu naročito teški, ali problem nastaje ukoliko želimo da uvedemo izmene u logiku, nakon čega moraju analogne (ali ne identične!) izmene da se uvedu u svim slučajevima – tada nastaju vrlo neprijatne greške. Zato ćemo predstaviti opis nekih uobičajenih tehnika koje sva četiri slučaja spajaju u jedan opšti.

Numerišimo režime kretanja brojevima $0, 1, 2, 3$  ($0$ – južno, $1$ – istočno, $2$ – severno, $3$ – zapadno). Tada je očigledno da se nakon svakog sudara numeracija našeg režima uveća za $1$ (po modulu $4$: prelaz $3 \rightarrow 0$).

Režim kretanja može da se opiše time što u svakom režimu postoji zajedničko ponašanje: napravićemo korak $(x,y) \rightarrow (x+dx,y+dy)$ ukoliko je polje $(x+dx,y+dy)$ slobodno; u suprotnom, menja se režim kretanja jer je došlo do sudara. Očigledno $(dx,dy)$ varira u zavisnosti od režima kretanja, te su nam neophodna dva niza $dx$ i $dy$.

## Rešenje za $k\leq10^7$: 
Očigledno je da u ovom slučaju tražimo rešenje koje je linearno po promenljivoj $k$. Dakle, ukoliko bismo iterirali “po sudarima”, između svaka dva sudara želimo da imamo konstantan broj operacija koje nam govore do kog polja stižemo. Ovo nagoveštava neko preprocesiranje.

Primetimo da je jedno Drejkovo stanje opisano položajem i aktuelnim režimom kretanja i da jedinstveno određuje stanje nakon sledećeg sudara sa zidom. Konkretno, imamo nekoliko slučajeva:

-   očigledno je nemoguće da se Drejko nađe „u zidu“, pa nas takvi slučajevi ne zanimaju;
-   ako je Drejko odmah pored nekog zida i ukoliko je usmeren ka njemu, stanje će odgovarati samo promenjenom režimu kretanja;  
-   u suprotnom, sudar (tj. stanje nakon narednog sudara) do kog nas vodi trenutno kretanje odgovara sudaru do kog nas vodi polje na kom ćemo se nalaziti u sledećem koraku.
- 
Poslednja činjenica je najvažnija i poprilično usložnjava rešenje. Dakle, neophodno je odrediti za svaki par režim,položaj naredno stanje. Ovo očigledno može da se predstavi pomoću tri niza sa po tri koordinate (koordinate su režim, $x$ i $y$), ali kako ih izračunati? Rekurentna veza je postavljena, odakle početi?

Primetimo da nam pri izračunavanju parametara narednog stanja pri fiksiranom režimu uopšte ne utiču rezultati iz drugih režima. Dakle, odgovore za “severno”, “južno”, “istočno” i “zapadno” možemo da računamo potpuno nezavisno. Iz definicije režima kretanja dolazimo do zaključaka:

-   naredno stanje ukoliko je režim kretanja “južno” će prvo biti izračunato u smeru jug–sever;    
-   naredno stanje ukoliko je režim kretanja “severno” će prvo biti izračunato u smeru sever–jug;
-   naredno stanje ukoliko je režim kretanja “istočno” će prvo biti izračunato u smeru istok–zapad;   
-   naredno stanje ukoliko je režim kretanja “južno” će prvo biti izračunato u smeru zapad–istok.

Dakle, možemo da popunjavamo stanja u četiri matrice (u nekim implementacijama možda i osam matrica – Drejkova usmerenost i vrsta koordinate na koju se odnosi)

Sada je uopštavanje svih ovih slučajeva nešto komplikovanije i jedna procedura koja bi generisala naredna stanja pri fiksnom režimu bi bila imala nešto nerazumljiviji oblik. Zato se predlaže da se u ovom rešenju “žrtvuje” modularnost koda zarad jednostavnosti.

Dakle, za rešenje u kom se najpre preprocesiraju “lanci” stanja u $O(nm)$, nakon čega se u $O(k)$ razmotre svi sudari.

## Glavno rešenje:
Uvedimo pojam stanja kao u prethodnom podzadatku. Primetimo da ih nema više od $O(4mn)$: za svaki položaj postoje četiri režima kretanja. Ukoliko je dat bilo koji dovoljno dugačak niz stanja (dužine bar $4mn+1$), u njemu će se neko stanje sigurno naći bar dva puta (Dirihleov princip). Međutim, pošto je naredno stanje uvek unapred određeno, zaključujemo da je niz stanja periodičan.

Ova činjenica nije toliko neobična, ali nam pomaže da dođemo do rešenja čija vremenska složenost neće zavisiti od $k$. Dovoljno je da se simulira kretanje sve dok ne stignemo do $k$-tog sudara ili ne naiđemo na polje koje smo već obišli (voditi računa o oba slučaja!).

U pomenutom drugom slučaju, za simulaciju može da se koristi rešenje prethodnog podzadatka, ali nije nužno zbog prirode problema – dovoljno je koristiti prostu simulaciju iz prvog podzadatka (pomenutih $O(4mn)$ stanja nisu samo ona kada se menja režim kretanja!).

Nakon određivanja perioda i rednog broja sudara koji je prvi u ciklusu, uz malo modularne aritmetike se jednostavno odredi završno stanje. Konkretno, ukoliko je redni broj prvog sudara u ciklusu $p$, dužina ciklusa $T$, a tražimo $k$-ti položaj, tada je redni broj sudara koji nas zanima u ovom ciklusu $k-p \mod T$. Pokušajmo da opravdamo: prvih $p$ koraka u simulaciji su pre ciklusa, stoga smo u toku cikličnog obilaska imali $k-p$ koraka; nulto i $T$-to stanje u ciklusu su identični, te je dovoljno posmatrati modul $T$.

Dakle, rešenje prvog podzadatka je dovoljno proširiti uvođenjem pomoćnih matrica koje nam govore kada smo prvi put došli do nekog stanja. Vodeći se idejom kompaktnosti zapisa, predlaže se da se i dalje koristi jedna jedina matrica, ali će imati tri dimenzije – dodatna koordinata je indeks smera! Pre nego što se prvi put dospe u neko stanje, vreme neophodno da se do njega dođe se najpre podesi na neko nemoguće (na primer, $-1$). Pri obilasku nekog stanja se najpre ispita da li je reč o nekom ranije obiđenom stanju (tako što se vidi da li je u tom polju pomenuta „nemoguća“ vrednost), nakon čega nije teško odrediti period.

Opet, neophodno je obratiti pažnju na slučaj kada do traženog sudara dođe pre ulaska u ciklus!

``` cpp title="03_sudari.cpp" linenums="1"
# include <stdio.h>
# include <stdlib.h>

# define MAXN 510

long long k;
int m, n;
int ip, jp;
int op[MAXN][MAXN];
int zid[4][MAXN][MAXN];
int bio[4][MAXN][MAXN];

void citaj() {
  char zn;
  int i, j;
  scanf("%d%d", &n, &m);
  scanf("%d%d", &ip, &jp);
  scanf("%lld", &k);
  for (j = 0; j <= m+1; j++) 
    op[0][j] = op[n+1][j] = 1;
  for (i = 0; i <= n+1; i++) 
    op[i][0] = op[i][m+1] = 1;
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
      zn = getchar();
      if (zn == '#') op[i][j] = 1; else op[i][j] = 0;
    }
    if (i < n)
      while ((zn = getchar()) != '\n');
  }
}

void pripremi() {
  int p;
  int i, j;
  int ip, jp;
  for (j = 1; j <= m; j++) {
    i = n;
    while ((i >= 1) && op[i][j]) {
      zid[0][i][j] = -1; 
      i--;
    }
    ip = i+1;
    while (i >= 1) {
      if (op[i][j] == 0) {
        zid[0][i][j] = ip-1;
      } else {
        zid[0][i][j] = -1;
        ip = i;
      }
      i--;
    }
  } 
  for (i = 1; i <= n; i++) {
    j = m;
    while ((j >= 1) && op[i][j]) {
      zid[1][i][j] = -1;
      j--;
    }
    jp = j+1;
    while (j >= 1) {
      if (op[i][j] == 0) {
        zid[1][i][j] = jp-1;
      } else {
        zid[1][i][j] = -1;
        jp = j;
      }
      j--;
    }
  }
  for (j = 1; j <= m; j++) {
    i = 1;
    while ((i <= n) && op[i][j]) {
      zid[2][i][j] = -1; 
      i++;
    }
    ip = i-1;
    while (i <= n) {
      if (op[i][j] == 0) {
        zid[2][i][j] = ip+1;
      } else {
        zid[2][i][j] = -1;
        ip = i;
      }
      i++;
    }
  } 
  for (i = 1; i <= n; i++) {
    j = 1;
    while ((j <= m) && op[i][j]) {
      zid[3][i][j] = -1;
      j++;
    }
    jp = j-1;
    while (j <= m) {
      if (op[i][j] == 0) {
        zid[3][i][j] = jp+1;
      } else {
        zid[3][i][j] = -1;
        jp = j;
      }
      j++;
    }
  }
  for (p = 0; p < 4; p++)
    for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++)
        bio[p][i][j] = -1;
  bio[3][ip][jp] = 0;
}

void obidji() {
  long long kt; 
  int pt, ps;
  int it, jt, is, js;      
  pt = 0; it = ip; jt = jp;
  kt = 0;
  while (kt < k) {
    kt++;
    switch (pt) {
      case 0:
        is = zid[0][it][jt];
        js = jt;
        ps = 1;
        break;
      case 1:
        is = it;
        js = zid[1][it][jt];
        ps = 2;
        break;
      case 2:
        is = zid[2][it][jt];
        js = jt;
        ps = 3;
        break;
      case 3:
        is = it;
        js = zid[3][it][jt];
        ps = 0;
        break;
    }
    it = is;
    jt = js;
    pt = ps;
//    printf("%d %d\n", it, jt);
    if (bio[pt][it][jt] >= 0) break;
    bio[pt][it][jt] = kt;
  }        
//  printf("%d\n", kt);
  if (kt == k) {
    printf("%d %d\n", it, jt);
  } else {
    long long kp;
    kp = kt - bio[pt][it][jt];
    kt = kt + (k - kt) / kp * kp;
    while (kt < k) {
      kt++;
      switch (pt) {
        case 0:
          is = zid[0][it][jt];
          js = jt;
          ps = 1;
          break;
        case 1:
          is = it;
          js = zid[1][it][jt];
          ps = 2;
          break;
        case 2:
          is = zid[2][it][jt];
          js = jt;
          ps = 3;
          break;
        case 3:
          is = it;
          js = zid[3][it][jt];
          ps = 0;
          break;
      }
      it = is;
      jt = js;
      pt = ps;
    }
    printf("%d %d\n", it, jt);
  }      
}

int main() {
  citaj();
  pripremi();
  obidji();
//  system("pause");
  return 0;
}

        

```
