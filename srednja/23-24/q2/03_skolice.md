

# 3 - Školice


	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 2000ms | 256MB |
	
Perica je dečak koji slabo uči. Nakon dugačkog izmotavanja na času informatike, zazvonilo je za odmor. Izašao je napolje da se igra školica. Tu igru možemo zamisliti kao niz koji se sastoji od $M$ pozitivnih celih brojeva $B_1,B_2,\ldots B_M$. Perica se trenutno nalazi na poziciji $0$ i želi da stigne do pozicije $M+1$. Kako bi to učinio, on u jednom potezu može da skoči za jednu ili dve pozicije **udesno**. Kada stane na neku poziciju $i$ između $1$ i $M$, njegov skor se poveća za $B_i$. Cilj igre je takođe minimizovati skor.
	
	
	
Na početku je dat niz koji se sastoji od $N$ pozitivnih celih brojeva $A_1,A_2,\ldots A_N$. Međutim, perica ima $Q$ drugova. Svaki od njih je video novi Tik Tok prenk, i želi Perici da zagusti igru. Tačnije, $i$-ti drug je smislio dva broja $L_i$ i $R_i$ ($L_i < R_i$) i obrisao elemente niza $A_{L_i},A_{L_i+1},\ldots,A_{R_i}$. Ostatak niza je spojio. Preciznije, nakon što $i$-ti drug izvrši smicalicu, Peričin niz za igru je $B = A_1,A_2,\ldots,A_{L_i-1},A_{R_i+1},\ldots,A_{N-1},A_{N}$.
	
	
	
Napomenimo da su njegovi drugovi ipak pošteni. Oni svoje smicalice ne mešaju. Svaki od drugova će odmah nakon što Perica završi sa njegovom verzijom igre vratiti obrisane brojeve. Tačnije, smicalice drugova su **nezavisne**. Takođe, može se desiti $L_i=1$ ili $R_i=N$ za neko $i$. U tim slučajevima, nizovi za igru izgledaju kao $A_{R_i+1},\ldots,A_{N-1},A_N$ i $A_1,A_2,\ldots,A_{L_i-1}$, redom. Može se desiti $L_i=1$ i $R_i=N$ istovremeno, pri čemu je niz za igru prazan i skor uvek jednak $0$.
	
	
	
Perici je ovo sve postalo jako komplikovano i dosadno. Pošto nije pratio na časovima, upitao je Vas kao programera da mu pomognete u njegovoj nevolji tako što ćete mu za svaku smicalicu reći minimalan skor.
	
	
	
## Opis ulaza
	
	
	
U prvom redu standardnog ulaza, dat je ceo broj $N$ - veličina niza $A$.
	
	
	
U drugom redu standardnog ulaza dato je $N$ celih brojeva $A_1,A_2,\ldots,A_N$ - elementi niza.
	
	
	
U trećem redu standardnog ulaza dat je ceo broj $Q$ - broj Peričinih drugova koji izvršavaju smicalice.
	
	
	
U $i$-tom od narednih $Q$ redova data su dva cela broja $L_i$ i $R_i$. Oni opisuju uzastopne elemente niza koji $i$-ti drug briše (a potom ih nakon završetka njegove verzije igre vraća).
	
	
	
## Opis izlaza
	
	
	
Ispisati $Q$ redova. U $i$-tom od njih ispisati minimalan skor u verziji igre $i$-tog Peričinog druga. 
	
	
	
## Primer
	
	
	
### Ulaz
	
	
	
```
	7
	1 4 3 6 4 3 5
	3
	4 5
	3 6
	1 7
```
	
	
	
### Izlaz
	
	
	
```
	7
	4
	0
```
	
	
	
### Objašnjenje
	
	
	
U prvoj smicalici, niz za igru je $[1, 4, 3, 3, 5]$. Optimalno je skočiti na prvo, treće i četvrto polje (niza za igru).
	
	
	
U drugoj smicalici, niz za igru je $[1, 4, 5]$.
	
	
	
U trećoj smicalici, niz za igru je prazan te je odgovor $0$.
	
	
	
## Ograničenja
	
	
	
* $3 \leq N \leq 200\,000$
* $1 \leq Q \leq 200\,000$
* $1 \leq A_i \leq 10^9$
* $1 \leq L_i \leq R_i \leq N$
	
	
	
Test primeri su podeljeni u četiri disjunktne grupe:
	
	
	
* U testovima vrednim 10 poena: $A_i=1$ za svako $1 \leq i \leq N$.
* U testovima vrednim 10 poena: $N \leq 10, Q \leq 100$.
* U testovima vrednim 40 poena: $N,Q \leq 4\,000$.
* U testovima vrednim 40 poena: Bez dodatnih ograničenja.
	
Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksandar Višnjić | Aleksandar Višnjić | Aleksandar Višnjić | Igor Pavlović |
	
## Rešenje kada $A_i = 1$
Stajanje na bilo koji stepenik ima istu "cenu". Potrebno je stati na ukupno što je manje moguće stepenika. Rešenje zavisi samo od dužine niza za igru. Za svaki upit je zasebno računamo i neka ona iznosi $M_i$ kod $i$-tog druga. Rešenje kod istog je $\lfloor \frac{M_i}{2} \rfloor$.
	
## Rešenje kada $N\leq 10, Q\leq 100$
Svaki niz za igru nema veličinu veću od $10$. Ukupan broj načina skakanja nije velik, te ih možemo simulirati rekurzijom. Biramo onaj način koji daje najmanji rezultat.
	
## Rešenje kada $N,Q \leq 4\, 000$
Saznajmo prvo kako rešavamo zadatak za jedan određen niz za igru. Neka je taj niz $B_1,B_2,\ldots B_M$. Ovo predstavlja klasičan zadatak iz dinamičkog programiranja. Neka je ${dp}_i$ minimalna cena stajanja na polje $i$ (počev od $0$, zajedno uz sve skokove do tog polja). Početne vrednosti su ${dp}_0 = 0$ i ${dp}_1 = B_1$. Za $i>1$ rekurentna veza je 
	
$$
	{dp}_i = \min({dp}_{i-1},{dp}_{i-2})  + B_i
$$
	
Odgovor na traženo pitanje je ${dp}_{M+1}$. Neophodno je zasebno razmatrati slučaje $M=0$ (niz za igru je prazan) i $M=1$. U njima je odgovor uvek $0$.
	
Složenost algoritma po smicalici je $O(N)$. Dakle, ukupno $O(Q\cdot N)$.
	
## Glavno rešenje
	
Neophodno je brže nalaziti odgovore za svaku smicalicu. Dozvoljeno nam je da pre njihovih traženja izračunamo neke vrednosti u nizu $A_1,A_2,\ldots , A_N$. Od koristi će biti slično dinamičko programiranje kao u prethodnom podzadatku. U ovom čuvamo i prefiks i sufiks. Tačnije, neka ${pref}_i$ predstavlja najmanju cenu potrebnu za stajanje na polje $i$ počev od polja $0$. A neka ${suf}_i$ predstavlja najmanju cenu potrebnu za stajanje na polje $i$ počev od polja $N+1$. Ova dva niza se računaju na analogan način sa dinamičkim programiranjem iz prethodnog podzadatka.
	
Prećimo sad na smicalice. Dajemo postupak za rešavanje slučaja $1 < L \leq R < N$. Ivične slučaje ostavljamo čitaocu za vežbu. Primetimo da, koristeći indekse iz niza $A$, Perica mora stati na barem jedno od polja $L-1$ i $R+1$ (jer je u nizu za igru njihovo rastojanje zapravo $1$) . Formalno, postoje $3$ slučaja:
	
1. Perica je prošao samo kroz polje $L-1$;
2. Perica je prošao samo kroz polje $R+1$;
3. Perica je prošao kroz oba polja.
	
Kad spojimo sve slučaje, odgovor na smicalicu postaje 
	
$$
	\min({pref}_{L-1}+{suf}_{R+2}, \ \ {pref}_{L-2}+{suf}_{R+1},\ \ {pref}_{L-1}+{suf}_{R+1})
$$
	
Prefiksne i sufiksne nizove računamo u složenosti $O(N)$. Za svaku smicalicu nalazimo rešenje u $O(1)$. Ukupna složenost je $O(N+Q)$.
	
``` cpp title="03_skolice.cpp" linenums="1"
	#include <bits/stdc++.h>
	
	using namespace std;
	long long int typedef li;
	
	int a[200005];
	li pre[200005];
	li suf[200005];
	
	int main()
	{
	    ios_base::sync_with_stdio(false);
	    cin.tie(0),cout.tie(0);
	
	    int n; cin>>n;
	    for (int i=1;i<=n;i++) cin>>a[i];
	    pre[1]=a[1];
	    for (int i=2;i<=n;i++) pre[i]=min(pre[i-1],pre[i-2])+a[i];
	    suf[n]=a[n];
	    for (int i=n-1;i>=1;i--) suf[i]=min(suf[i+1],suf[i+2])+a[i];
	
	    int q; cin>>q;
	    while (q--)
	    {
	        int l,r; cin>>l>>r;
	        if (l==1) cout<<min(suf[r+1],suf[r+2])<<"\n";
	        else if (r==n) cout<<min(pre[l-1],pre[l-2])<<"\n";
	        else cout<<min(min(pre[l-2]+suf[r+1],pre[l-1]+suf[r+2]),pre[l-1]+suf[r+1])<<"\n";
	    }
	}
```
