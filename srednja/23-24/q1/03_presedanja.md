

# 3 - Presedanja


	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |
	
U gradu $17$ postoji sistem gradskog prevoza. Na početku je postojalo $N$ stanica, numerisanih od $1$ do $N$, i $M$ parova stanica između kojih postoji direktna i dvosmerna autobuska linija. Međutim, zbog učestalog stajanja, troškovi goriva su eksplodirali.
	
	
	
Volis Brin, ugledni gradonačelnik grada $17$, smislio je novi plan. Uveo je nove parove stanica između kojih prolaze autobusi. Tačnije, sada između dve stanice postoji dvosmerna autobuska linija ako i samo ako je u starom planu postojala međustanica između njih. Formalnije, stanice $A$ i $B$ su povezane linijama ako i samo ako postoji stanica $C$ takva da su u starom planu $A$ i $C$, kao i $B$ i $C$, bile povezane.
	
	
	
Aliks, junakinja našeg zadatka, trenutno se nalazi kod stanice $S$. Potrebno joj je da što pre stigne do tajne laboratorije koja se nalazi kod stanice $T$. Tačnije, Aliks može da putuje autobusima opisanim parovima u novom planu (jer je on aktuelan). Ona želi da iskoristi najmanji broj presedanja. Napomenimo da u gradu $17$ autobusi idu toliko često da su presedanja između konkretnih linija zanemarljiva.
	
	
	
Nažalost, Aliks je ostala bez signala i nema uvid u novi plan gradskog prevoza. Na svu sreću, seća se starog plana do detalja. Zato je upitala Vas, kao programera, za pomoć. Potrebno je da joj kažete najmanji broj autobusa koje mora iskoristiti da bi stigla do svog cilja.
	
	
	
## Opis ulaza
	
	
	
U prvom redu standardnog ulaza, nalaze se četiri cela broja $N$, $M$, $S$ i $T$. Oni označavaju broj stanica, broj parova u starom planu, početnu stanicu na kojoj se nalazi Aliks i njenu destinaciju.
	
	
	
U $i$-tom od narednih $M$ redova, nalaze se po dva cela broja $U_i$ i $V_i$. Oni označavaju da su u starom planu stanice $U_i$ i $V_i$ bile povezane autobuskom linijom.
	
	
	
## Opis izlaza
	
	
	
U prvom i jedinom redu standardnog izlaza, ispisati ceo broj koji predstavlja minimalan broj autobusa koje mora iskoristiti da bi Aliks stigla do svog cilja. Poznato je da će ulaz biti takav da ona to uvek može učiniti u konačnom broju presedanja i koristeći samo autobuse.
	
	
	
## Primer 1
	
	
### Ulaz
	
```
	8 9 5 8
	1 2
	1 3
	1 4
	3 5
	3 6
	4 6
	2 5
	6 7
	7 8
```
	
### Izlaz
	
```
	2
```
	
## Primer 2
	
### Ulaz
	
```
	5 5 1 4
	1 2
	2 3
	3 4
	4 5
	5 1
```
	
### Izlaz
	
```
	1
```
	
## Ograničenja
	
	
	
* $3 \leq N,M \leq 2\cdot 10^5$
* $1 \leq U_i, V_i, S,T \leq N$
	
	
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
	
	
* U testovima vrednim 10 poena: $N=M-1$ i $U_i = i, V_i = i+1$.
* U testovima vrednim 25 poena: $N=M-1$ i garantuje se da je u starom planu bilo moguće stići od svake stanice do svake druge stanice.
* U testovima vrednim 25 poena: Garantuje se da je u starom planu Aliks mogla od svoje početne stanice stići do više drugih stanica krećući se autobusima nego što može sada (naravno, ostaje uslov da Aliks može stići do svog cilja).
* U testovima vrednim 20 poena: $N,M \leq 500$.
* U testovima vrednim 20 poena: Bez dodatnih ograničenja.
	
Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Aleksandar Višnjić | Aleksandar Višnjić | Pavle Martinović |
	
## Prvi podzadatak
Sve stanice možemo smestiti na brojevnu pravu. Korišćenjem jedne autobuske linije u novom planu gradskog prevoza možemo se kretati za $2$ stanice ulevo ili za $2$ stanice udesno. Samim tim, rešenje zadatka je $\frac{|S-T|}{2}$.
	
## Drugi podzadatak
Originalan plan gradskog prevoza možemo da modelujemo kao *stablo*. Stablo je povezan graf takav da između svaka dva čvora postoji jedinstven nesamopresecajući put. Stanice su u stvari čvorovi, dok su autobuske linije grane. U novom planu, između dva čvora postoji grana ako i samo ako je njihova udaljenost $2$. Primetimo da graf novog plana ne mora biti stablo. 
	
Potrebno je odrediti dužinu puta u originalnom planu između čvorova $S$ i $T$, a zatim je podeliti sa $2$. Nju određujemo primenom algoritma za pretragu grafa poput DFS, odnosno pretragom u dubinu. Ako je ta dužina $D$, odgovor na zadatak je $\frac{D}{2}$.
	
Ukupna složenost je $O(N)$.
	
## Treći podzadatak
Nastavljamo sa jezikom teorije grafova. Ranije smo primetili da u novom grafu između dva čvora postoji grana ako i samo ako je u starom grafu njihova udaljenost bila $2$. Da bi svaki čvor koji je u starom planu bio dostižan iz $S$ bio i dalje dostižan, potrebno je da u njegovom grafu postoji ciklus neparne dužine. Kako to nije slučaj po uslovu podzadatka, možemo zaključiti da taj graf nema neparan ciklus. Takav graf još nazivamo i *bipartitivnim*. To znači da svaki čvor možemo obojiti u dve boje na način da nikoja dva čvorova iste boje nisu povezani. Traženje najkraćeg puta od $S$ do $T$ je pravolinijski. Možemo primeniti $BFS$ algoritam direktno, tj. pretragu u širinu. Ako algoritam u originalnom grafu odredi dužinu $D$, odgovor na zadatak je $\frac{D}{2}$.
	
Ukupna složenost je $O(N+M)$.
	
## Glavno rešenje
Podrebno je nastaviti u generalnom grafu koji može imati neparne cikluse. Tražimo najkraći put *parne* dužine između čvorova $S$ i $T$. Potrebno je da na neki način ne računamo puteve neparne dužine ka rešenju, ali da ih u isto vreme ne zanemarimo pri nalaženju istog. Jedan način da to učinimo je da za svaki čvor napravimo i njegov "neparni" parnjak. Dakle, svaki čvor ima "parnu" i "neparnu" verziju, tj. duplirali smo ga. Grane postoje samo između čvorova različite parnosti. Sada primećujemo da prilikom prelaženja iz jednog čvora u drugi menjamo trenutnu parnost čvora. Ovim je jasno da je u ovakvom grafu dovoljno naći put od "parnog" $S$ do "parnog" $T$, jer od parnosti poslednjeg čvora u kome smo završili zavisi i parnost puta.
	
Ukupna složenost je $O(N+M)$.
	
``` cpp title="03_presedanja.cpp" linenums="1"
	#include <bits/stdc++.h>
	
	using namespace std;
	
	vector<vector<int>> g(400005);
	bool vis[400005];
	
	int main()
	{
	    ios_base::sync_with_stdio(false);
	    cin.tie(0),cout.tie(0);
	    
	    int n,m,s,t; cin>>n>>m>>s>>t;
	    while (m--)
	    {
	        int u,v; cin>>u>>v;
	        g[u].push_back(v+n);
	        g[v].push_back(u+n);
	        g[u+n].push_back(v);
	        g[v+n].push_back(u);
	    }
	    
	    queue<pair<int,int>> bfs;
	    bfs.push({s,0});
	    while (!bfs.empty())
	    {
	        int p=bfs.front().first;
	        int d=bfs.front().second;
	        bfs.pop();
	        if (vis[p]) continue;
	        vis[p]=true;
	        
	        if (p==t)
	        {
	            cout<<d/2<<"\n";
	            break;
	        }
	        
	        for (auto it : g[p]) bfs.push({it,d+1});
	    }
	}
```
