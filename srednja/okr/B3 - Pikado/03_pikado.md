---
hide:
  - toc
---

# B3 - Jednostavni pikado

=== "Zadatak"
	
	| Vremensko ograničenje | Memorijsko ograničenje |
	|:-:|:-:|
	| 2000ms | 512MB |
	
	Bane igra jednostavni pikado koji je organizovan tako da je tabla standardna $xy$ ravan sa nekoliko (konačno mnogo) takozvanih "kontrolnih tačaka" $(x_1, y_1)$, $(x_2, y_2)$, $\ldots$ sa celobrojnim koordinatama.
	
	Za ovaj pikado važe posebna pravila! Neka je broj kontrolnih tačaka $N$. Bane će baciti strelicu i ukoliko ta strelica pogodi ravan u tački sa koordinatama $(x_A, y_A)$, tada Bane osvaja poene na sledeći način:
	- Ako za svaku kontrolnu tačku $(x_i, y_i)$ važi da je $x_i \neq x_A$, Bane osvaja 0 poena;
	- Ako za svaku kontrolnu tačku $(x_i, y_i)$ važi da je $y_i \neq y_A$, Bane osvaja 0 poena; 
	- Inače (tj. ako među kontrolnim tačkama postoji bar jedna sa $x$ koordinatom jednakom $x_A$ i bar jedna sa $y$ koordinatom jednakom $y_A$) broj poena koje Bane osvaja je jednak 
	
	$$\sum_{i=1}^{N}|x_i-x_A|\cdot|y_i-y_A|$$
	
	Dat je niz od $M$ tačaka sa celobrojnim koordinatama $(x_1, y_1)$, $(x_2, y_2)$, $\ldots$ $(x_M, y_M)$. Za svako $i = 1,2, \ldots, M$ ispisati koji je najveći broj poena koji Bane može da dobije **u jednom bacanju** ukoliko skup kontrolnih tačaka sadrži samo prvih $i$ tačaka ovog niza. **Rezultate ispisivati po modulu $10^9 + 7$.**
	
	## Opis ulaza
	U prvoj liniji ulaza nalazi se ceo broj $M$ - ukupan broj tačaka u nizu
	
	U narednih $M$ linija nalaze se parovi celih brojeva odvojenih razmakom koji predstavljaju koordinate tačaka $x_i, y_i$
	
	## Opis izlaza
	U $M$ linija ispisati brojeve $R_1, R_2, ..., R_M$, redom, gde je $R_i$ najveći mogući broj poena **po modulu $10^9 + 7$** koji Bane može osvojiti ako skup kontrolnih tačaka sadrži isključivo prvih $i$ tačaka iz niza. 
	
	## Primer 1
	### Ulaz
	```
	3
	2 1
	1 2
	3 3
	```
	
	### Izlaz
	```
	0
	1
	4
	```
	
	## Primer 2
	### Ulaz
	```
	4
	1 2
	2 1
	5 4
	3 5
	```
	
	### Izlaz
	```
	0
	1
	17
	24
	```
	
	## Objašnjenje primera
	U prvom primeru, ako je kontrolna samo prva tačka, gde god da strelica pogodi, dobija se $0$ poena. Ako su nam kontrolne prve dve tačke možemo "pogoditi" $(1, 2)$, i dobiti rezultat $1\cdot1+0\cdot0=1$, a ako su sve tri tačke, optimalna je tačka $(1, 1)$, gde je rezultat $1\cdot 0+0\cdot 1+2\cdot 2=4$.
	
	## Ograničenja
	
	- $1 \leq M \leq 10^6$.
	- $|x_i|, |y_i| \leq 10^5$.
	  
	Test primeri su podeljeni u šest disjunktnih grupa:
	
	- U test primerima vrednim $10$ poena, $1 \leq M \leq 100$.
	- U test primerima vrednim $10$ poena, $1 \leq M \leq 500$.
	- U test primerima vrednim $15$ poena, $1 \leq M \leq 2000$.
	- U test primerima vrednim $15$ poena, $1 \leq M \leq 2\cdot 10^5$.
	- U test primerima vrednim $10$ poena, $1 \leq M \leq 10^5$ i $0 \leq x_i, y_i \leq 10$.
	- U test primerima vrednim $40$ poena nema dodatnih ograničenja.
	
	
=== "Rešenje"
	
	| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
	|:-:|:-:|:-:|:-:|
	| Momčilo Tošić | Momčilo Tošić | Momčilo Tošić | Aleksa Milisavljević |
	
	## Analiza
	Uočimo da Bane dobija poene samo ako izabere tačku sa $x$ koordinatom među unetim $x$ koordinatama, i sa $y$ koordinatom koja takođe pripada nekoj od kontrolnih tačaka.
	Dakle, za rešenje za prvih $i$ tačaka biramo $x_A$ iz skupa $x_1,x_2,\ldots x_i$ i $y_A$ iz skupa $y_1,y_2,\ldots y_i$ takve da je opisana suma maksimalna.
	
	## Rešenje u $O(M^4)$
	Za svako $i \leq M$ potrebno je iterirati kroz sve moguće parove $x_A,y_A$ iz pomenutih skupova (kvadratna složenost) i pronaći zbir iz zadatka (linearna složenost).
	Ukupno je potrebno $O(M^4)$ koraka.
	
	## Rešenje u $O(M^3)$
	Fiksirajmo $x$ koordinatu. Tada je formula za broj poena koji maksimizujemo u obliku $\sum_{j=1}^{i} const*|y_j-y_A|$
	
	Intuicija nam govori da ova suma "odlazi u beskonačnost" kada izabrana ipsilon koordinata ili velika (ka beskonačnosti) ili mala (ka minus beskonačnosti) te možemo pokušati samo vrednost najvećeg $y_j$ i najmanjeg $y_j$, što daje brže rešenje jer radimo isto kao u prošlom podzadatku samo proveravamo dve vrednosti za $y$ (minimum i maksimum
	ažuriramo kako se unose nove tačke). 
	
	## Rešenje u $O(M^2)$
	Dokažimo intuiciju iz prethodnog rešenja. Dokazaćemo gramziv pristup tako što dokažemo da uvek možemo dobiti rešenje koje nije lošije tako što umesto neke ipsilon koordinate izaberemo neku manju ili veću (i stoga je najbolje birati najmanju ili najveću).
	
	Neka su svi $y$ jednako razmaknuti (ovo nije problematična pretpostavka, naime, ako nisu, dodavanjem fiktivnih međuvrednosti ništa ne menjamo jer ove vrednosti daju skor 0).
	Fiksijarmo $x$ koordinatu i posmatrajmo rešenje za $N$ tačaka i odabrano $y=y_i$. Tada posmatrajmo kako se suma menja ako odaberemo $y$ koordinatu levo, odnosno desno, od
	$y_i$.
	Naime, ako je fiksirano $x$, suma je u obliku $\sum_{j=1}^{N} const*|y_j-y_i|$
	
	Pokušajmo sada da vidimo šta se dešava kada
	izabranu ipsilon koordinatu "pomerimo" za $\Delta y$ koje je razlika dveju ipsilon koordinata (dalje formule ne zavise od toga da li je pozitivno ili negativno). 
	
	Neka su i bez gubljenja opštosti ipsilon koordinate uređene tako da je prvih $i-1$ manje od $y_i$, a između $i$ i $k$ su jednake, dok su nakon $k$ veće. 
	Tada će suma biti ($const$ predstavljaju pozitivne konstante - apsolutne razlike $x$ koordinata i fiksirane $x$ koord.)
	
	$$
	\sum_{j=1}^{N} const*|y_j+\Delta y-y_i| = \sum_{j=1}^{i-1} const*(y_i-y_j-\Delta y)+\sum_{j=k}^{N} const*(y_j+\Delta y-y_i) + (k-i)*const*|\Delta y|
	$$
	
	Izdvojimo prethodnu sumu:
	
	$$
	\sum_{j=1}^{N} const*|y_j-y_i| - \sum_{j=1}^{k} const*\Delta y + \sum_{j=k+1}^{i} const*\Delta y + const*|\Delta y| = \sum_{j=1}^{i} const*|y_j-y_A| + P_i*\Delta y + Q_i*|\Delta y| 
	$$
	
	Vidimo da se Banetov skor promenio za $P_i*\Delta y + Q_i*|\Delta y|$.
	
	Da li je $P_i$ pozitivan, negativan, ili nula ne zavisi od toga da li pokušavamo da se "pomerimo" u levo ili u desno već samo od iks vrednosti. Kako je $Q_i$ uvek nenegatino,
	to je $P_i*\Delta y + Q_i*|\Delta y|$ u zavisnosti od znaka $\Delta y$ (pozitivno predstavlja pomeranje u desno, ka najvećem $y$, a negativno u levo, ka najmanjem) ili u oba slučaja nenegativna vrednost, ili u jednom slučaju negativna, a u drugom nenegativna. Svakako, možemo odabrati ono $y$ za koje je ova vrednost nenegativna, odnosno Banetov skor nije manji, i stoga se "pomeriti" ka najvećem ili najmanjem $y$. Induktivno sledi da najveće ili najmanje $y$ koje možemo da odaberemo i daju najbolje rešenje.
	
	Ako sada fiksiramo $y$, zbog potpuno simetričnog izraza, analogno dokazujemo da treba odabrati najmanje ili najveće $x$.
	Izbor jedne koordinate ne zavisi od izbora druge, te dolazimo do zaključka da postoji samo 4 mogućnosti za $x_A,y_A$ a to su najveća i najmanja $x$ i $y$ koordinata.
	
	Ove četiri sume možemo izračunati za svaki prefiks niza tačaka, ili iskoristiti ideju razdvajanja na dve sume iz dokaza za pun broj poena.
	
	## Rešenje u $O(M)$
	Uočimo da ako biramo ekstremne vrednosti $x$ i $y$ koordinata sume gube apsolutne zagrade i mogu se raspisati tako da u njima faktorišu 
	$\sum_{i=1}^{N}x_i*y_i$, 
	$x_A*\sum_{i=1}^{N}y_i$, 
	$y_A*\sum_{i=1}^{N}y_i$ i 
	$y_A*x_A$, te se 4 moguće sume mogu izračunati u konstantoj složenosti ako se sume iz ovih faktora ažuriraju prilikom unosa svake nove tačke.
	
	``` cpp title="03_pikado.cpp" linenums="1"
	#include <iostream>
	#include <vector>
	
	using namespace std;
	
	const int mod = 1000000007;
	
	int main(){
	    ios_base::sync_with_stdio(false);
	    cin.tie(0);
	    cout.tie(0);
	
	    int m;
	    cin >> m;
	
	    long long ans = 0;
	    long long maxX = -2e6, minX = 2e6, maxY = -2e6, minY = 2e6, xS=0, yS = 0, pS = 0;
	
	    for(int i = 0; i < m; ++i){
	        long long xT, yT;
	        cin >> xT >> yT;
	        minY = min(minY, yT);
	        maxY = max(yT, maxY);
	        maxX = max(xT, maxX);
	        minX = min(minX, xT);
	        xS += xT;
	        pS += xT*yT;
	        yS += yT;
	        ans = max(ans, pS - minX*yS - minY*xS + (i+1)*minX*minY);
	        ans = max(ans, -1*pS + minX*yS + maxY*xS - (i+1)*minX*maxY);
	        ans = max(ans, -1*pS + maxX*yS + minY*xS - (i+1)*maxX*minY);
	        ans = max(ans, pS - maxX*yS - maxY*xS + (i+1)*maxX*maxY);
	
	        cout << ans%mod << "\n";
	    }
	}

	```
