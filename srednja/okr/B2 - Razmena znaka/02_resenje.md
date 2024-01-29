# Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Dragan Urošević | Dragan Urošević |
	
## Analiza
Pretpostavimo za trenutak da se operacija koju izvršava Žika sastoji samo od zamene mesta dva susedna elementa, tj. da se ne izvršava promena znaka. Može se pokazati da se primenom takve operacije, od polaznog niza može dobiti bilo koji niz sastavljen od elemenata niza $A$, tj. bilo koji raspored elemenata niza $A$:
$$
A_{i_1}, A_{i_2}, A_{i_3}, \dots, A_{i_n}. 
$$
	
Ako operacija koju izvodi Žika sastoji i od promene znaka, onda je za određivanje vrednosti nekog elementa nakon izvođenja svih operacija dovoljno da znamo njegovu početnu poziciju i njegovu poziciju na kraju (tj. nakon svih izvedenih operacija). Naime, čak i u slučaju da se isti element pomerao levo-desno (prema početku i prema kraju), njegov znak na kraju će biti određen samo rastojanjem između početne o krajnje pozicije (zato što se pri svakom pomeranju levo-desno ili desno-levo izvodi paran broj operacija, pa element niza promeni znak paran broj puta, a to znači da ima isti znak kao da to pomeranje levo-desno nije ni izvodio).
	
Prema tome, ako se element $A_i$ premestio sa pozicije $i$ na poziciju $j$ ($j\lt i$), onda će njegova vrednost biti  $B_j = (-1)^{i-j}A_i$, tj. $B_j = (-1)^i : (-1)^j A_i$, odnosno važiće $(-1)^j B_j = (-1)^i A_i$. Slično, ako se element $A_i$ premestio sa pozicije $i$ na poziciju $j$ ($j>i$), onda će njegova vrednost biti  $B_j = (-1)^{j-i}A_i = (-1)^{i-j}A_i$, tj. $B_j = (-1)^i : (-1)^j A_i$, odnosno važiće $(-1)^j B_j = (-1)^i A_i$.   Odavde zaključujemo da Žika od niza $A$ može dobiti niz $B$ ako i samo ako se nizovi $C$ ($C_i = (-1)^iA_i$) i $D$ ($D_i = (-1)^iB_i$) sastoje od istih elemenata (naravno, ne nužno na istim pozicijama).
	
## Rešenje prvog podzadatka
U ovom slučaju je dovoljno odrediti pozicije elemenata koji su različiti od nule. Ako je $A_i \ne 0$ i $B_j \ne 0$, tada mogu nastupiti tri slučaja
	 
-   Ako je $A_i = B_j$ i $2 | (i-j)$, onda se od niza $A$ može dobiti niz $B$;
-   Ako je $A_i = -B_j$ i $2 \not | (i-j)$, onda se od niza $A$ može dobiti niz $B$;
-   Ako ne važi nijedan od dva gornja uslova, onda od niza $A$ nije moguće dobiti niz $B$.
	
Složenost opisanog rešenja je $\Theta(n)$.
	
## Rešenje drugog podzadatka
Prema analizi, niz $B$ se može dobiti od niza $A$ ako i samo ako se nizovi $C$ ($C_i = (-1)^iA_i$) i $D$ ($D_i = (-1)^iB_i$) sastoje od istih elemenata. Međutim svi elementi nizova $C$ i $D$ imaju vrednost $1$ ili $-1$ i dovoljno je izbrojati da li nizovi $C$ i $D$ imaju isti broj elemenata čija je vrednost $1$ (odnosno isti broj elemenata čija je vrednost $-1$),
Složenost opisanog rešenja je $\Theta(n)$.
	
## Rešenje trećeg podzadatka
U ovom slučaju možemo sortirati nizove parova $E$ $(E_i = (|A_i|, i))$ i $F$  $(F_i=(|B_i|, i))$, pri čemu parove poredimo po vrednosti prvog elementa (komponente) para. Tada od niza $A$ možemo dobiti niz $B$, ako i samo ako za sve odgovarajuće parove važi
-   prvi elementi parova moraju biti jednaki (jer oni predstavljaju apsolutne vrednosti odgovarajućih elemenata nizova $A$ i $B$);
-   drugi elementi parova predstavljaju pozicije tih elemenata u nizovima $A$ i $B$; na osnovu pozicija možemo saznati i odgovarajuće elemente nizova $A$ i $B$; oni treba da budu jednaki (ako je razlika pozicija parna) ili suprotnih znakova (ako je razlika pozicija neparna).
	
Složenost opisanog rešenja je $\Theta(n\log n)$, zbog sortiranja nizova.
	 
## Glavno rešenje
Koristimo činjenicu da nizovi $C$ i $D$, opisani u Analizi, treba da sadrže iste elemente (naravno, ako se od niza $A$  može dobiti niz $B$). Ako te nizove sortiramo, onda odgovarajući elementi imaju jednake vrednosti. Zbog toga možemo srtirati nizove $C$ i $D$ i proveriti da li su odgovarajući elementi jednaki. Složenost opisanog rešenja je $\Theta(n\log n)$, zbog sortiranja nizova.
	
``` cpp title="02_razmena_znaka.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 30007
using namespace std;
int a[MAXN],b[MAXN];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
	    int n;
	    cin>>n;
	    for(int i=0;i<n;i++) cin>>a[i];
	    for(int i=0;i<n;i++) cin>>b[i];
	    for(int i=0;i<n;i++) if(i&1) a[i]=-a[i];
	    for(int i=0;i<n;i++) if(i&1) b[i]=-b[i];
	    sort(a,a+n);
	    sort(b,b+n);
	    bool ok=true;
	    for(int i=0;i<n;i++) if(a[i]!=b[i]) ok=false;
	    if(ok) cout<<"DA\n";
	    else cout<<"NE\n";
	}
}

```
