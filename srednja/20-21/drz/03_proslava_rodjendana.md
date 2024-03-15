---
hide:
  - toc
---

# B3 - Proslava rođendana

=== "Zadatak"

 | Vremensko ograničenje | Memorijsko ograničenje |
 |:-:|:-:|
 | 2000ms | 256MB |

 Katarina planira proslavu rođendana. Postoji $N$ ljudi koje razmatra da pozove u goste. Katarina je veoma popularna i zna da će joj na rođendan doći svi gosti koje pozove. Ona takođe zna i da bi joj $i$-ti od tih gostiju doneo $a_i$ poklona, ukoliko ga pozove. Međutim Katarina je sujeverna i želela bi da i broj gostiju i broj poklona bude deljiv sa brojem $M$. Koliko najviše poklona Katarina može dobiti?

## Opis ulaza

 U prvom redu standardnog ulaza nalaze se celi brojevi $N$ i $M$, gde je $N$ broj ljudi koje Katarina razmatra da pozove. U narednom redu, nalazi se $N$ celih brojeva, od kojih je $i$-ti broj baš $a_i$, broj poklona koje bi joj doneo $i$-ti gost ukoliko ga pozove na rođendan.

## Opis izlaza

 U jedinom redu standardnog izlaza ispisati jedan broj - koliko najviše poklona Katarina može dobiti, ukoliko pozove broj gostiju deljiv sa $M$, tako da oni zajedno donesu broj poklona deljiv sa $M$.

## Ograničenja

- $1 \leq N \leq 1.000.000$
- $1 \leq M \leq 100$
- $0 \leq a_i \leq 1.000.000.000$, za svako $1 \leq i \leq N$

## Podzadaci

 1. (7 poena) $1 \leq N \leq 20$
 2. (12 poena) $M = 2$
 3. (12 poena) $1 \leq a_i \leq 2$, za svako $1 \leq i \leq N$.
 4. (23 poena) $1 \leq N \leq 10.000$
 5. (46 poena) Bez dodatnih ograničenja.

## Primeri

### Primer 1

#### Ulaz

 ```
 3 2
 5 4 1
 ```

#### Izlaz

 ```
 6
 ```

#### Objašnjenje

 Ukoliko pozovemo prvog i trećeg gosta, pozvaćemo ukupno $2$ gosta, koji će ukupno doneti $5+1 = 6$ poklona. Kako su brojevi $2$ i $6$ deljivi sa $2$, to je ovo jedno validno rešenje. Može se proveriti da ne postoji način da dobijemo više poklona.

## Napomena

 Katarina ne mora da pozove ni jednog gosta, u tom slučaju smatramo da je i broj gostiju i broj poklona $0$.  Primetite da je ovo jedno validno rešenje za svako $M$.

=== "Rešenje"

 | Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
 |:-:|:-:|:-:|:-:|
 | Aleksa Milisavljević | Aleksa Milisavljević | Mladen Puzić | Igor Pavlović |

## Rešenje za $N \leq 20$

 Možemo probati svaki podskup gostiju. Uzmemo maksimalan odgovarajući podskup. Vremenska složenost: $O(2^N\cdot N)$, memorijska složenost: $O(N)$.

## Rešenje za $M=2$

 Želimo da odaberemo paran broj ljudi i da oni ukupno donesu paran broj poklona. Podelimo ljude u dve grupe, one koje donose paran broj poklona i one koji donose neparan broj poklona. Sortirajmo ljude u obe grupe opadajuće po broju poklona. Ako imamo najmanje dve osobe u nekoj grupi, sigurno ćemo moći bez konflikta da pozovemo dve osobe iz te grupe, a naravno mi ćemo odabrati dve osobe sa najviše poklona. Ovaj proces ponavljamo dok nam u obe grupe ostane $0$ ili $1$ osoba. Tada stajemo, jer te ljude ne možemo pozvati - ili broj zvanica neće biti paran, ili ukupan broj njihovih poklona. Vremenska složenost: $O(NlogN)$, memorijska složenost: $O(N)$.

## Rešenje za $1\leq a_i\leq 2$

 Postoje samo dve vrste ljudi: ljudi koji donose jedan poklon i ljudi koji donose dva poklona. Označimo sa $k$ broj pozvanih ljudi koji donose jedan poklon, a sa $t$ broj pozvanih ljudi koji donose dva poklona. Mora važiti da su $t+k$ i $2\cdot t + k$ deljivi sa $M$. Fiksirajmo ostatak pri deljenju $t$ sa $M$ i ostatak pri deljenju $k$ sa $M$. Ukoliko važe naši uslovi, uzećemo što veće $t$ i $k$ koje zadovoljava date ostatke. Uzimamo maksimum od svih kombinacija ostataka. Vremenska složenost: $O(M^2)$, memorijska složenost: $O(1)$.

## Rešenje za $1\leq N\leq 10000$

 Koristimo dinamičko rešenje, stanje je $dp[i][j][k]$ i označava najbolje rešenje posmatrajući prvih $i$ ljudi, tako da je ostatak pri deljenju broja odabranih ljudi sa $M$ baš $j$, a ostatak pri deljenju zbira njihovih poklona sa $M$ baš $k$. Za $i$-ti element važi da možemo ili da ga uzmemo ili ne, pa je rekurentna veza:
 $$
 dp[i][j][k] = max(dp[i-1][j][k], dp[i-1][j-1][k-a_i] + a_i).
 $$
 Bitno je napomenuti da je oduzimanje u ovoj rekurentnoj vezi sprovedeno po modulu $M$, na primer $2-5$ po modulu $7$ je $4$. Poslednji korak nam je da rešenje optimizujemo memorijski, pošto nam trenutno zauzima previše memorije. To možemo uraditi tako što primetimo da kad računamo stanja za $i$, koristimo isključivo stanja za $i-1$, pa je uvek dovoljno čuvati samo prethodna stanja. Vremenska složenost: $O(NM^2)$, memorijska složenost: $O(M^2)$.

## Glavno rešenje

 Odvojimo goste u grupe po ostatku pri deljenju njihovog broj poklona sa $M$. Imamo $M$ takvih grupa, jednu za ostatak $0$, jednu za ostatak $1$, ..., jednu za ostatak $M-1$. Sortirajmo opadajuće po broju poklona svaku grupu.

 Za svaku grupu, najviše $M-1$ ljudi neće biti pozvani (ukoliko je makar $M$ ljudi nepozvano, možemo da pozovemo bilo kojih $M$ nepozvanih ljudi, a da ne narušimo ostatke pri deljenju). To nam govori da će svi gosti u grupi koji nisu u najmanjih $M-1$ sigurno biti pozvani, za ostale moramo naći optimalno rešenje.

 U svakoj grupi imamo najviše $M-1$ elemenata koje posmatramo, ukupno nemamo više od $M^2$ elemanata. Na tom broju elemenata možemo primeniti rešenje za prethodni podzadatak. Vremenska složenost: $O(NlogN + M^4)$, memorijska složenost: $O(M^2)$.

 ``` cpp title="03_proslava_rodjendana.cpp" linenums="1"
 #include<bits/stdc++.h>
 #define maxn 2000000
 #define maxm 200
 using namespace std;
 vector<int> v[maxm];
 long long dp[maxm][maxm];
 long long ndp[maxm][maxm];
 long long ans=0;
 int n,m;
 int a[maxn];
 int x,y;
 int main() {
     scanf("%d %d",&n,&m);
     for(int i=0;i<n;i++) {
         scanf("%d",&a[i]);
         v[a[i]%m].push_back(a[i]);
         ans+=a[i];
     }
     x=n%m;
     y=ans%m;
     n=0;
     for(int i=0;i<m;i++) {
         sort(v[i].begin(),v[i].end());
         for(int j=0;j<min((int)v[i].size(),m);j++) {
             a[n++]=v[i][j];
         }
     }
     for(int i=0;i<m;i++) {
         for(int j=0;j<m;j++) {
             dp[i][j]=1e18;
         }
     }
     dp[0][0]=0;
     for(int k=0;k<n;k++) {
         for(int i=0;i<m;i++) {
             for(int j=0;j<m;j++) {
                 ndp[i][j]=dp[i][j];
             }
         }
         int dif=a[k]%m;
         for(int i=0;i<m;i++) {
             int ni=i+1;
             if(ni==m) ni=0;
             for(int j=0;j<m;j++) {
                 int nj=j+dif;
                 if(nj>=m) nj-=m;
                 ndp[ni][nj]=min(ndp[ni][nj],dp[i][j]+a[k]);
             }
         }
         for(int i=0;i<m;i++) {
             for(int j=0;j<m;j++) {
                 dp[i][j]=ndp[i][j];
             }
         }
     }
     printf("%lld",ans-dp[x][y]);
     return 0;
 }

 ```
