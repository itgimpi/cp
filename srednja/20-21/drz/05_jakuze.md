---
hide:
  - toc
---

# A2 - Jakuze

=== "Zadatak"

 | Vremensko ograničenje | Memorijsko ograničenje |
 |:-:|:-:|
 | 2000ms | 256MB |

 U dalekom Japanu haraju mnogobrojne kriminalne grupe, poznate kao jakuza klanovi. Njihovi članovi, jakuze, lede krv u žilama svima koji su te loše sreće da ih sretnu. U glavnom gradu Japana, Tokiju, se među jakuzama trenutno odvija bitka za vlast. Od raznih strašnih kriminalaca, kao najjači i najopasniji se izdvaja Moma, koji želi da osvoji ceo Tokio.

 Tokio se može zamisliti kao matrica dimenzija $M\times N$. Prvog dana će Moma zauzeti jedno (bilo koje) polje te matrice. U svakom narednom danu, on može zauzeti bilo koje polje koje je susedno nekom polju koje je već zauzeo. Dva polja su susedna ako dele stranu. Kako je Moma najopasniji jakuza, on svako polje može osvojiti za dan, pa će posle $MN$ dana ceo Tokio biti njegov.

 Međutim, iako ga nijedna jakuza ne može pobediti, postoji jedna stvar koja može - njegovo sujeverje. On poseduje svoju mapu Tokija, i na svakom polju je napisao jedan broj od $1$ do $MN$, tako da je svaki broj napisan tačno jednom. On smatra da je jedini način da osvoji ceo Tokio da **baš u $i$-tom danu osvoji polje na kojem je napisao broj $i$.** Međutim, on je promenljivog raspoloženja, pa će $Q$ puta promeniti brojeve na svojoj mapi tako što zameni brojeve u neka dva polja. Vaš zadatak je da za svaih $Q+1$ stanja mape (na početku i posle svakog upita) odredite da li je moguće da Moma ispuni svoj cilj.

## Opis ulaza

 U prvoj liniji standardnog ulaza nalazi se tri prirodna broja $N,M,Q$ - dimenzije Tokija i broj promena Momine mape. U $i$-toj od narednih $N$ linija se nalazi po $M$ prirodnih brojeva, gde $j$-ti predstavlja vrednost $A_{ij}$ - broj koji stoji na početku u polju $(i,j)$ na Mominoj mapi. U $i$-toj od narednih $Q$ linija se nalaze po $4$ cela broja $xa$, $ya$, $xb$, $yb$ koji označavaju da će u $i$-toj promeni zameniti vrednosti na poljima $(xa,ya)$ i $(xb,yb)$.

## Opis izlaza

 Na standardni izlaz ispišite $Q+1$ linija: u $i$-toj liniji treba da piše `DA` ako Moma može da osvoji Tokio u $i$-tom stanju mape, a `NE` u suprotnom.

## Ograničenja

- $1 \leq N\cdot M\leq 300.000$
- $1 \leq Q\leq 300.000$
- $1 \leq A_{ij} \leq NM$
- Svaka vrednost od $1$ do $NM$ se pojavljuje tačno jednom u nizu $A_{ij}$.
-

 Dodatno, za svaki od $Q$ upita važi:

- $1 \leq x_a,x_b \leq N$
- $1 \leq y_a,y_b \leq M$
- $(x_a,y_a)\neq(x_b,y_b)$

## Podzadaci

 1. (11 poena)  $N=1$, $Q\leq200$
 2. (17 poena)  $Q\leq200$
 3. (34 poena)  $N=1$
 4. (38 poena)  Nema dodatnih ograničenja

## Primeri

### Primer 1

#### Ulaz

 ```
 3 3 1
 1 2 3
 4 5 6
 7 8 9
 1 2 2 2
 ```

#### Izlaz

 ```
 DA
 NE
 ```

#### Objašnjenje

 U početnom izgledu Tokija Moma će u prvom danu osvojiti polje $(1,1)$. Narednih dana će osvajati polja $(1,2)$, $(1,3)$, $(2,1)$, $(2,2)$, $(2,3)$, $(3,1)$, $(3,2)$, $(3,3)$, koja su redom susedna poljima $(1,1)$, $(1,2)$, $(1,1)$, $(1,2)$, $(1,3)$, $(2,1)$, $(2,2)$, $(2,3)$, koja već poseduje u tom trenutku. Međutim, nakon zamene neće moći posle osvajanja polja označenog sa $1$ da u sledećem potezu osvoji polje označeno sa $2$.

=== "Rešenje"

 | Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
 |:-:|:-:|:-:|:-:|
 | Pavle Martinović | Pavle Martinović | Pavle Martinović | Aleksa Milisavljević |

## $N=1,Q\leq200$

 Ovaj podzadatak je samo najprostija simulacija. Primetimo da je Moma u svakom trenutku osvojio neki interval i da su jedina nova polja koje može osvojiti ona dva na krajevima intervala. Sada u svakom trenutku vidimo da li je jedno od ta dva susedna polja baš ono koje nam treba i ako jeste osvojimo ga. Složenost $O(QMN)$.

## $Q\leq200$

 I ovaj podzadatak je obična simulacija, ali se mora generalizovati na dvodimenzione table. Pamtićemo za svako $i$ da li je polje označeno sa tim brojem susedno nekome od trenutno osvojenih polja. Onda, kada to polje osvojimo označićemo njegove susede kao moguće za osvajanje. Tako, iterirajući po vrednostima od $2$ do $MN$ možemo da utvrdimo da li je moguće da Moma ispuni zadatak. Složenost $O(QMN)$.

## Puno rešenje

 Primetimo sledeći potreban i dovoljan uslov da Moma ispuni zadatak:
 Neka kažemo da je polje *loše* ako su mu svi susedi označeni sa vrednostima većim od njegove vrednosti. Moma može da ispuni svoj zadatak ako i samo ako postoji tačno jedno loše polje.
 Dokažimo ovo. Primetimo da je polje označeno sa brojem $1$ svakako loše. Ako je moguće da Moma ispuni zadatak onda svako drugo polje ima nekog suseda kojeg je Moma već osvojio u tom trenutku - to jest. nekog suseda sa manjim indeskom od njega, pa je jedan smer dokazan. U drugom smeru, ako pretpostavimo da svako polje sa indeksom $>1$ ima suseda manjeg indeksa od njega, onda možemo lakom indukcijom da dokažemo da Moma može da ispuni svoj cilj: po hipotezi, Moma može da osvoji prvih $k$ polja, a polje sa indeksom $k+1$ ima nekog suseda sa manjim indeksom, to jest neko već osvojeno polje, stoga Moma može da nastavi osvajanje.
 Sada kad smo dokazali ovo, potrebno je u svakom trenutku paziti koliko postoji loših polja. Na početku prebrojimo koliko je loših polja i primetimo da kad zamenimo dva polja, to može jedino da promeni "lošost"  najviše $10$ polja: ta dva što smo zamenili i njihovih suseda. Onda naprosto ažuriramo da li su ona postala loša sad i ispišemo "DA" ukoliko imamo samo jedno loše polje i "NE" u suprotnom. Složenost $O(NM+Q)$.

 ``` cpp title="05_jakuze.cpp" linenums="1"
 #include <bits/stdc++.h>
 using namespace std;
 vector<int> a[300007];
 int cnt,dx[4]={0,1,0,-1},dy[4]={1,0,-1,0},n,m;
 vector<bool> bad[300007];
 inline bool valid(int x,int y) {return x>=0 && x<n && y>=0 && y<m;}
 inline void check(int x,int y)
 {
     if(!valid(x,y)) return;
     if(bad[x][y]) cnt--;
     bad[x][y]=false;
     bool dobar = false;
     for(int i=0;i<4;i++) if(valid(x+dx[i],y+dy[i]) && a[x+dx[i]][y+dy[i]]<a[x][y]) dobar = true;
     if(!dobar) {bad[x][y]=true; cnt++;}
 }
 int main()
 {
     int q;
     scanf("%d%d%d",&n,&m,&q);
     for(int i=0;i<n;i++) for(int j=0;j<m;j++)
     {
         int t;
         scanf("%d",&t);
         a[i].push_back(t);
         bad[i].push_back(false);
     }
     for(int i=0;i<n;i++) for(int j=0;j<m;j++) check(i,j);
     if(cnt==1) printf("DA\n");
     else printf("NE\n");
     while(q--)
     {
         int xa,ya,xb,yb;
         scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
         xa--; xb--; ya--; yb--;
         swap(a[xa][ya],a[xb][yb]);
         check(xa,ya); check(xb,yb);
         for(int i=0;i<4;i++) check(xa+dx[i],ya+dy[i]);
         for(int i=0;i<4;i++) check(xb+dx[i],yb+dy[i]);
         if(cnt==1) printf("DA\n");
         else printf("NE\n");
     }
 }

 ```
