---
hide:
  - toc
---

# 3 - Rokada

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Perica voli da igra šah, ali često gubi stvari i zaboravlja pravila. Roditelji su mu zbog toga kupili mnogo garnitura i tabli za šah, međutim on ih je sve izgubio, osim topova koji su mu omiljene figure pa ih zbog toga drži u posebnoj fioci.

Perica je odlučio da se igra i pokušao da se seti pravila šaha, za početak seća se da je postojala tabla pa je zbog toga na kartonu nacrtao tablu sa $N$ vrsta i $M$ kolona. Odlučio je da svako polje ili ostavi prazno ili da u njega stavi tačno jednu od šest vrsta igračaka kojih najviše ima, naime ili autić ili kockicu na kojoj je napisan neki od brojeva 0 do 4.

Nažalost, jedini deo šaha kog se Perica seća, sem pomenutih, je način na koji se pomera top, to mu je ipak omiljena figura (za one koji ni to ne znaju, top se u jednom potezu može pomeriti na neko drugo polje u svojoj koloni ili vrsti). Zato je odlučio da postavi izvestan broj topova na prazna polja svoje table i pomera ih, naravno bez podizanja sa table, pa top ne može da pređe preko polja na kom se već nalazi neka igračka. Dok je to činio shvatio je da igra nije previše zanimljiva ako je na tabli previše topova, jer se često nalaze jedan drugome na putu, a ni ako je na tabli premalo topova jer u tom slučaju nema čime da se igra, pa je uveo sledeća pravila:

1. Ni jedan top se ne sme nalaziti na polju na koje drugi top može da dođe u jednom potezu.
2. Ukoliko je na nekom polju kockica sa brojem $K$, na njemu susednim poljima mora da se nalazi tačno $K$ topova. (Polja su susedna ako dele stranicu, dakle svako polje ima najviše četiri susedna polja.)
3. Za svako polje koje je na početku igre bilo prazno mora na tabli postojati top koji u najviše jednom potezu može da dođe na to polje.

Perica je brzo primetio da pre nego što počne da se igra mora prvo da pronađe početnu postavku topova, ukoliko takva uopšte postoji, a koja poštuje navedena pravila za njegovu tablu. Vaš zadatak je da pomognete Perici da počne da se igra tako što ćete za zadatu početnu tablu pronaći postavku topova koja poštuje sva zadata pravila, ili zaključiti da takva tabla ne postoji.

## Opis ulaza

U prvoj liniji ulaza nalaze se dva cela broja, $N$ - broj vrsta i $M$ - broj kolona table.
U svakoj od narednih $N$ linija ulaza nalazi se po $M$ znakova ('.', '#', '0', '1', '2', '3' ili '4'), koji označavaju da se u odgovarajućem polju 
'.' - ne nalazi ništa (prazno je)
'#' - nalazi autić
'0', '1', '2', '3' ili '4' - nalazi kockica koja pokazuje odgovarajući broj.

## Opis izlaza

Ukoliko tražena konfiguracija ne postoji ispisati $-1$, dok ukoliko postoji potrebno je ispisati matricu dimenzija ulazne matrice, čija su polja ista kao odgovarajuća polja u ulaznoj matrici, s tim da se prazno polje, '.', može zameniti sa 'C' ukoliko na to polje treba staviti topa u postavci.

## Primer 1

### Ulaz

~~~
5 6
.#01.1
2.....
0.....
......
#...2.

~~~

### Izlaz

~~~
C#01C1
2C....
0.....
..C...
#..C2C
~~~

## Primer 2

### Ulaz

~~~
2 2
0.
.2
~~~

### Izlaz

~~~
-1
~~~

## Ograničenja

U svim primerima važi $1 \leq N, M \leq 10$.

* U test primerima vrednim 10 poena: Sva polja su prazna na početku.
* U test primerima vrednim 20 poena: $1 \leq N, M \leq 2$.
* U test primerima vrednim 30 poena: $1 \leq N, M \leq 5$.
* U test primerima vrednim 40 poena: Nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Duško Obradović | Nikola Spasić | Dragan Urosević | Momčilo Topalović |

## Analiza

Ovaj problem se može rešiti primenom bektreka (backtracking). Ali da bi se bektrek ubrzao (tj. bio efikasniji), na početku se uradi preprocesiranje u kome se za svako polje na kome se nalaѕi kockica odredi koliko u njegovom susedstvu ima slobodnih polja ili polja na koja je već postavljen top i ako se taj broj poklapa sa brojem na kockici, onda se i na preostala slobodna polja postave topovi. Pri postavljanju topova markiraju se sva slobodna polja do kojih može stići taj top (to će nam kasnije omogućiti efikasnu proveru da li do svakog slobodnog polja može stići neki top). Nakon toga se proveri da li postoji polje na kome se nalazi kockica takvo da je broj susednih polja koja su slobodna ili se na njima nalazi top manji od broja na kockici. Ako takvo polje postoji onda nije moguće rasporediti topove na tu tablu tako da zadovoljavaju sva ograničenja, ispisuje broj $-1$ i prekida izvršavanje programa.

Posle ove pripremne faze započinje se raspoređivanje preostalih topova. To se izvodi tako što se obrađuje jedno po jedno polje table (na primer, vrsta po vrsta). Obrada narednog polja se obavlja pozivom funkcije, koja kao argumente dobija vrstu i kolonu u kojoj se nalazi to polje, a kao rezultat vraća informaciju da li je ostatak table uspešno obrađen/popunjen. Ako je polje koje trenutno obrađujemo zauzeto ili se na njega ne može postaviti top zato što bi onda oko neke kockice bilo previše topova, prelazi se na sledeće polje (tj. poziva funkcija za obradu sledećeg polja). U suprotnom se za to polje probaju dve varijante. Prva varijanta je da se na to polje postavi top, markiraju polja do kojih može stići taj top i nastavi sa obradom sledećeg polja na tabli. Ta obrada se obavlja tako što se rekurzivno poziva funkcija za obradu polja koja kao argumente dobija koordinate (vrstu i kolonu) polja koje se obrađuje. Ako je ostatak table uspešno popunjen, druga varijanta se ne razmatra već se prekida izvršavanje i vraća informacija da je uspešno popunjena tabla. U suprotnom, ako ostatak table nije uspešno popunjen, razmatra se druga varijanta, u kojoj se na to polje ne raspoređuje top, već se prelazi na naredno polje table, tj. rekurzivno poziva  funkcija za rešavanje sledećeg polja. Ako se rešavanje ostatka table uspešno završi, onda funkcija vraća informaciju da je ostatak table uspešno rešen, u suprotnom, vraća informaciju da ostatak table nije uspešno rešen. 

Kada se obrade sva polja table, tj. pozove funkcija za obradu polja koje se nalai vrsti broj $M+1$ i koloni broj $1$, proverava se da li je popunjavanje korektno/ispravno: broj topova oko svake kockice se poklapa sa brojem na kockici i do svakog slobodnog polja može stići neki od topova. Ako je popunjavanje table ispravno funkcija vraća informaciju da je tabla popunjena ispravno, u suprotnom, vraća informaciju da tabla nije uspešno popunjena. 
Da bi se dodtno ubrzao postupak, može se pri svakom pozivu funkcije za obradu polja proveravati da li postoji kockica takva da je zbir broja postavljenih topova na susednim poljima i broja slobodnih susednih polja manji od broja na kockici. Ako takva kockica postoji, nije moguće rasporediti topove prema zahtevima, pa se prekida obrada tog polja i vraća nazad (tj. na obradu prethodnog polja).
 

``` cpp title="03_rokada.cpp" linenums="1"
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define maxd 12
using namespace std;
int N,M;
struct slog{
  char G[maxd][maxd];
}game;
char A[maxd][maxd],B[maxd][maxd],C[maxd][maxd];
bool imaresenja;

void ispisiresenje(){
  for (int i=1; i<=N; i++){
    for (int j=1; j<=M; j++)
      cout<<A[i][j];
    cout << endl;
  }
}
int brojpoljaoko(int r, int c, char z){
  return (A[r-1][c]==z and B[r-1][c]!='x')+(A[r+1][c]==z and B[r+1][c]!='x')+(A[r][c-1]==z and B[r][c-1]!='x')+(A[r][c+1]==z and B[r][c+1]!='x');
}
void blokiraj(){                   /// obelezavanje polja oko stubova na kojima ne moze biti svetiljka
  for (int i=1; i<=N; i++)
    for (int j=1; j<=M; j++)
      if (A[i][j]>='0' and A[i][j]<='4')
       if (brojpoljaoko(i,j,'C')==A[i][j]-48){
        if (A[i-1][j]=='.') B[i-1][j]='x';
        if (A[i+1][j]=='.') B[i+1][j]='x';
        if (A[i][j-1]=='.') B[i][j-1]='x';
        if (A[i][j+1]=='.') B[i][j+1]='x';
      }
}
void osvetli(int r, int c){
  int x;
  x=r-1; while (A[x][c]=='.' or A[x][c]=='!') {A[x][c]='!';x--;}
  x=r+1; while (A[x][c]=='.' or A[x][c]=='!') {A[x][c]='!';x++;}
  x=c-1; while (A[r][x]=='.' or A[r][x]=='!') {A[r][x]='!';x--;}
  x=c+1; while (A[r][x]=='.' or A[r][x]=='!') {A[r][x]='!';x++;}
}
void upisisvetiljkeokopolja(int r, int c){
  if (A[r-1][c]=='.' and B[r-1][c]!='x') {A[r-1][c]='C';osvetli(r-1,c);}
  if (A[r+1][c]=='.' and B[r+1][c]!='x') {A[r+1][c]='C';osvetli(r+1,c);}
  if (A[r][c-1]=='.' and B[r][c-1]!='x') {A[r][c-1]='C';osvetli(r,c-1);}
  if (A[r][c+1]=='.' and B[r][c+1]!='x') {A[r][c+1]='C';osvetli(r,c+1);}
}
bool sigurica(){ /// dovodjenje pocetnog stanja u bolju poziciju za backtracking
  blokiraj();
  bool bilopromene=false;
  for (int i=1; i<=N; i++)
    for (int j=1; j<=M; j++)
      if (A[i][j]>='1' and A[i][j]<='4') {
        int btacaka=brojpoljaoko(i,j,'.');
        int bsvetiljki=brojpoljaoko(i,j,'C');
        if (btacaka>0 and btacaka+bsvetiljki==A[i][j]-48){
          upisisvetiljkeokopolja(i,j);
          bilopromene=true;
        }
      }
  return bilopromene;
}
bool uslovok(int r, int c){
  int x=0;
  x+=(A[r][c+1]=='C');
  x+=(A[r][c-1]=='C');
  x+=(A[r+1][c]=='C');
  x+=(A[r-1][c]=='C');
  return x==A[r][c]-48;
}
bool svejeok(){
  for (int r=1; r<=N; r++)
    for (int c=1; c<=M; c++){
      if (A[r][c]>='0' and A[r][c]<='4')
        if (!uslovok(r,c))
          return false; /// provera broja svetiljki koje su zapisane na stubu
    }
  memcpy(C,A,sizeof(C));
  for (int r=1; r<=N; r++)
    for (int c=1; c<=M; c++)
      if (A[r][c]=='C'){
        int x=r-1; while (A[x][c]=='.' or A[x][c]=='!'){C[x][c]='!';x--;}  /// markiranje osvetljenih polja
            x=r+1; while (A[x][c]=='.' or A[x][c]=='!'){C[x][c]='!';x++;}
            x=c-1; while (A[r][x]=='.' or A[r][x]=='!'){C[r][x]='!';x--;}
            x=c+1; while (A[r][x]=='.' or A[r][x]=='!'){C[r][x]='!';x++;}
      }
  for (int r=1; r<=N; r++)  /// provera da li je sve osvetljeno
    for (int c=1; c<=M; c++)
      if (C[r][c]=='.') return false;
  for (int r=1; r<=N; r++)
    for (int c=1; c<=M; c++)
      if (A[r][c]=='!') A[r][c]='.';
  return true;
}
void solve(int r, int c){
  if (r==N+1){
    if (svejeok()) imaresenja=true;
    return;
  }
  if (A[r][c]!='.' or A[r][c]=='.' and B[r][c]=='x'){
    if (c==M) solve(r+1,1);
    else solve(r,c+1);
    if (imaresenja) return;
  }
  else {
    /// postavljam svetiljku na ovo polje
    A[r][c]='C';
    char D[maxd][maxd];
    char E[maxd][maxd];
    memcpy(D,A,sizeof(D));
    memcpy(E,B,sizeof(E));
    osvetli(r,c);
    while (sigurica());
    if (c==M) solve(r+1,1);
    else solve(r,c+1);
    if (imaresenja) return;
    memcpy(A,D,sizeof(A));
    memcpy(B,E,sizeof(B));
    A[r][c]='.';
    /// ne postavljam svetiljku na ovo polje
    if (c==M) solve(r+1,1);
    else solve(r,c+1);
    if (imaresenja) return;
  }
}
bool protivurecnost(){
  for (int i=1; i<=N; i++)
    for (int j=1; j<=M; j++)
      if (A[i][j]>='0' and A[i][j]<='4')
        if (brojpoljaoko(i,j,'.')+brojpoljaoko(i,j,'C')<A[i][j]-48)
          return true;
  return false;
}
int main(){
//  freopen("svetla.dummy.02.in","r",stdin);
//  freopen("lightsout.txt","w",stdout);
  cin>>N>>M;
  for (int i=1; i<=N; i++)
    for (int j=1; j<=M; j++)
      cin>>A[i][j];
  memcpy(B,A,sizeof(B));

  while (sigurica());

  if (protivurecnost()){cout << -1 << endl;return 0;}

  solve(1,1);

  if (imaresenja) ispisiresenje();
  else cout << -1 << endl;

  return 0;
}

```
