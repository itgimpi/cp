---
hide:
  - toc
---

# B2 - Preduzeće

=== "Zadatak"

 | Vremensko ograničenje | Memorijsko ograničenje |
 |:-:|:-:|
 | 1000ms | 256MB |

 U jednom preduzeću za proizvodnju sira nalazi se $N$ zaposlenih rapoređenih u hijerarhiji tako da svaki zaposleni osim šefa preduzeća (zaposlenog sa rednim brojem 1) ima tačno jednog nadređenog.

 Za svakog zaposlenog je poznat njegov doprinos preduzeću, $a_{i}$, koji predstavlja zbir razlika njegove kompetentnosti $k_{i}$ i kompetentnosti suseda. Dakle, $a_{i}=\sum_{j}(k_{i}-k_{s_{j}})$,  gde je $s$ niz suseda zaposlenog $i$. Dva zaposlena su susedna ako je jedan od njih nadređen onom drugom.

 Poznato je da je kompetentnost šefa preduzeća jednaka nuli ($k_{1}=0$), i da kompetentnosti nekih zaposlenih mogu biti negativne.

 Vaš zadatak je da na osnovu hijerarhije preduzeća i doprinosa svakog zaposlenog odredite kompetentnost svakog zaposlenog, ili da ispišete $-1$ ukoliko zaposlenima nije moguće dodeliti kompetentnosti koje zadovoljavaju sve uslove.

## Opis ulaza

 U prvoj liniji standardnog ulaza nalazi se prirodan broj $N$ - broj zaposlenih u preduzeću.  U narednom  redu nalazi se niz od $N$ brojeva $a_{i}$ - doprinos svakog od zaposlenih.  U sledećem redu nalazi se niz od $N-1$ brojeva $h_{i}$ - zaposleni $h_{i}$ je nadređen zaposlenom $i+1$ i važi $h_{i}\leq i$.

## Opis izlaza

 U jednoj liniji standardni izlaz ispišite niz od $N$ brojeva $k_{i}$ odvojenih razmakom - kompetentnosti svakog od zaposlenih, ili ispišite `-1` ukoliko takav niz ne postoji.

## Ograničenja

- $1 \leq N\leq 200.000$
- $1 \leq h_{i}\leq i\leq N-1$
- $-10^{9} \leq a_{i} \leq 10^{9}$

## Podzadaci

 1. (17 poena)  $h_{i}=i$
 2. (26 poena)  $h_{i}=(i+1)/2$
 3. (23 poena)  $N\leq 2000$
 4. (34 poena)  Nema dodatnih ograničenja

## Primeri

### Primer 1

#### Ulaz

 ```
 4
 2 -3 1 0
 1 2 2
 ```

#### Izlaz

 ```
 0 -2 -1 -2
 ```

#### Objašnjenje

 Zaposleni (1,2), (2,3), (2,4) su susedni.

 $a_{1}=k_{1}-k_{2}=0-(-2)=2$

 $a_{2}=k_{2}-k_{1}+k_{2}-k_{3}+k_{2}-k_{4}=-2-0+(-2)-(-1)+(-2)-(-2)=-3$

 $a_{3}=k_{3}-k_{2}=-1-(-2)=1$

 $a_{4}=k_{4}-k_{2}=-2-(-2)=0$

### Primer 2

#### Ulaz

 ```
 4
 2 -3 1 1
 1 2 2
 ```

#### Izlaz

 ```
 -1
 ```

#### Objašnjenje

 Ne postoji niz koji zadovoljava sve uslove.

=== "Rešenje"

 | Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
 |:-:|:-:|:-:|:-:|
 | Igor Pavlović | Igor Pavlović | Igor Pavlović | Aleksa Milojević |

## Podzadatak 1

 U ovom podazadatku možemo iskoristiti činjenicu da važi $k_{i+1}=2*k_{i}-k_{i-1}-a_{i}$ (osim ѕa ѕaposlene 1 i $n$ koji imaju samo jednog suseda). Dakle da bismo našli kompetentnost $i+1$-og zaposlenog dovoljno je da nađemo kompetentnost prvih $i$ zaposlenih. Počev od $k_{1}=0$ možemo rekostruisati čitav niz. Nakon toga je potrebno proveriti da li dobijeni niz zadovoljava svih $n$ jednačina i ispisati -1 ukoliko one nisu zadovoljene.

## Podzadatak 2

 U ovom podzadatku treba primetiti da nam je dovoljno samo da kontruišemo niz razlika kompetentosti susednih zaposlenih. Na osonovu tih razlika i uslova $k_{1}=0$ možemo rekostruisati traženi niz. Posmatrajmo doprinos nekog para zaposlenih $x$ i $y$ kao protok intenziteta $k_{x}-k_{y}$ koji teče od zaposlenog $x$ ka zaposlenom $y$. Ako zamislimo da u svakog zaposlenog $x$ ulazi neki protok intenziteta $a_{x}$ sa strane možemo obezbediti da je ukupan protok svakog zaposlenog nula.

 Vrednosti svih protoka možemo odrediti tako što iz svakog zaposlenog pustimo da teče protok intenziteta $a_{x}$ od njega pa sve do šefa. Protok kroz neki par susednih zaposlenih je ukupan protok koji prelazi preko te grane na kraju. Primetimo takođe da je ukupan protok kroz zaposlenog 1 jednak zbiru doprinosa svih zaposlenih. Na osnovu toga se može pokazati da rešenje postoji ako i samo ako je zbir svih doprinosa nula. Pošto je udaljenost svakog zaposlenog od šefa u ovom podzadatku najviše $log(N)$ ukupna složenost je $O(N*log(N))$.

## Podzadatak 3

 U ovom podzadatku možemo primeniti isti algoritam kao za prošli podzadatak. U ovom podzadatku složenost takvog algoritma je $O(N^2)$.

## Podzadatak 4

 Za maksimalan broj poena potrebno je rekostruisati niz razlika kompetentnosti susednih zaposlenih u linearnoj složenosti. Ovo možemo uraditi tako što za svakog zaposlenog zapamtimo one zaposlene kojima je on nadrećen i traženi niz razlika rekostruišemo sa desna na levo.
 Ako razliku zaposlenog $i$ označimo sa $r_{i}=k_{i}-k_{h_i}$ možemo primetiti da važi $r_{i}=a_{i}-s$ gde je $s$ suma razlika svih zaposlenih kojima je on nadređen. Pošto se njegovi podređeni nalaze posle njega u nizu možemo smatrati da su njihove razlike već izračunate (jer razlike računamo sa desna na levo) pa je moguće odrediti $r_{i}$. Primetimo da je svaki zaposleni podređen najviše jednom zaposlenom pa je ukupna složenost ovog algoritma $O(N)$.

 ``` cpp title="02_preduzece.cpp" linenums="1"
 #include <bits/stdc++.h>
 #define maxN 2000005
 
 using namespace std;
 
 long long a[maxN],p[maxN],d[maxN],ans[maxN],n,i,j;
 vector<int> adj[maxN];
 
 int main()
 {
     std::ios_base::sync_with_stdio(false);
     cin>>n;
     for(i=0;i<n;i++) cin>>a[i];
     for(i=1;i<n;i++){
         cin>>p[i];
         p[i]--;
         adj[p[i]].push_back(i);
     }
     for(i=n-1;i>=0;i--){
         d[i]=a[i];
         for(j=0;j<adj[i].size();j++){
             d[i]+=d[adj[i][j]];
         }
     }
     ans[0]=d[0];
     for(i=1;i<n;i++) ans[i]=ans[p[i]]+d[i];
     if(ans[0]!=0) cout<<-1<<endl;
     else{
         for(i=0;i<n;i++) cout<<ans[i]<<" ";
     }
     return 0;
 }

 ```
