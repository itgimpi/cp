# Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Jovan Bengin | Aleksa Milisavljević |
	
## Analiza
Primetimo prvo da nikada ne moramo napraviti potez sa nekim $X$ koje nije stepen dvojke. Naime, umesto jednog poteza sa $X = 2^{i_1} + 2^{i_2} + 2^{i_3} + .... + 2^{i_k}$, $i_1 < i_2 < ... < i_k$, možemo da napravimo $k$ poteza nad istim putem sa vrednostima $2^{i_1}, 2^{i_2}, ... , 2^{i_k}$. Dakle, možemo pretpostaviti da će $X$ koje biramo uvek biti oblika $2^j$. 
	
Pošto sada nijedan potez nad nekim bitom ne utiče na druge, možemo za svaki bit nezavisno naći optimalno rešenje i na kraju ih sva sumirati.
Formalnije, definišimo matrice $B_0, B_1, ... , B_K$, gde je $B_{x, i, j} = 1$ ako $A_{i, j}$ sadrži $x$-ti bit, u suprotnom je $B_{x, i, j} = 0$. Ako je $C_i$ optimalno rešenje za matricu $B_i$, onda je optimalno rešenje za matricu $A$ jednako $\sum\limits_{i=0}^{K} 2^i*C_i$. Pošto važi $A_{i,j} \leq 10^9 < 2^{30}$, dovoljno je uzeti $K = 29$ (jer bi matrice B_i za veće vrednosti $i$ sadržale samo nule, pa bi i $C_i$ bilo $0$).
	
Dalje ćemo razmatrati samo matrice čiji su svi članovi $0$ ili $1$, a poteze vršimo isključivo sa $X = 1$. Cilj nam je da dobijemo matricu sa minimalnim brojem jedinica.
	
## Rešenje kada je $N, M \leq 2$
Ako je $N = 1$ ili $M = 1$, postoji tačno jedan put od $(1, 1)$ do $(N, M)$. Ako je $N = M = 2$, postoje dva puta.
Pošto postoje najviše dva različita puta, time i najviše četiri različite kombinacije poteza (pošto se dva ista poteza skraćuju), možemo za svaku kombinaciju proveriti kako će matrica izgledati, i uzeti onu sa najmanjom rezultujućom sumom.
	
## Rešenje kada je $N = 1$
Pošto postoji samo jedan moguć put, postoje samo dva moguća niza poteza: jedan gde ne radimo ništa (tada će matrica sadržati $a$ jedinica), i drugi gde put prolazi kroz celu matricu (tada će matrica sadržati $M - a$ jedinica), pa će rešenje biti $min(a, M - a)$.
	
## Rešenje kada je $N = 2$
Grupisaćemo polja tako da sva polja sa istom $i + j$ vrednosti budu u istoj grupi. Svaka grupa će onda zapravo biti dijagonala koja ide od dole-levo ka gore-desno, i sadržaće najviše dva polja.
	
Primetimo da svaki put od  $(1, 1)$ do $(N, M)$ sadrži po tačno jedan element iz svake grupe. To znači da ako je ukupan *xor* svih elemenata neke grupe jednak $0$, posle jednog poteza biće $1$, i obrnuto. Neka na početku $a$ dijagonala ima *xor* jednak nuli, a $b$ dijagonala *xor* jednak jedinici. Onda će nakon jednog poteza biti $b$ dijagonala sa *xor* $0$, i $a$ sa $1$, nakon drugog poteza će ponovo biti $a$ sa $0$ i $b$ sa $1$ itd. Pošto svaka dijagonala koja ima *xor* jednak jedinici mora da sadrži barem jednu jedinicu, vidimo da je rešenje barem $min(a, b)$.
	
Ispostavlja se da je ovaj minimum uvek moguće postići. Bez umanjenja opštosti, neka je $a \geq b$ ($b < a$ se radi na isti način, samo što se na početku uradi bilo koji potez). Pokazaćemo da je dijagonale sa *xor*-om $1$ (kojih ima $b$) moguće transformisati tako da imaju tačno jednu jedinicu, a one sa *xor*-om $0$ tako da nemaju nijednu.
	
Za dijagonale koje sadrže jedno polje je očigledno: ako im je *xor* $0$, onda je njihov jedini element $0$, uostalom je $1$.
Dijagonale koje sadrže dva polja i imaju *xor* $1$ takoće sadrže tačno jednu jedinicu.
Ostalo nam je da pokažemo da, ako imamo dijagonalu koja sadrži dve jedinice, možemo obe pretvoriti u nule a da ne menjamo ostale elemente. Neka su elementi te dijagonale $(2, i)$ i $(1, i + 1)$. Napravićemo dva poteza: u prvom biramo put $(1, 1), (1, 2), ... , (1, i), (1, i+1), (2, i+1), (2, i+2), ..., (2, M)$, a u drugom put $(1, 1), (1, 2), ... , (1, i), (2, i), (2, i+1), (2, i+2), ... , (2, M)$. Primetimo da su jedina polja koja se nalaze u tačno jednom putu baš $(2, i)$ i $(1, i + 1)$. To znači da su to jedina dva polja čija će se vrednost obrnuti, pa tako od dve jedinice dobijamo dve nule.
	
## Rešenje kada su sve početne vrednosti $0$ ili $1$
Pošto smo početnu matricu $A$ podelili na matrice sa vrednostima $0$ i $1$, ovaj podzadatak se rešava na isti način kao glavno rešenje. Ipak, moguće ga je uraditi i bez znanja da možemo nezavisno nalaziti rešenje za svaki bit.
	
## Glavno rešenje
Slično kao u rešenju za $N = 2$, grupisaćemo polja po dijagonali. Ovde se takođe ispostavlja da, ako imamo $a$ dijagonala sa *xor* $0$ i $b$ sa *xor* $1$, rešenje je $min(a, b)$. Ovo možemo pokazati na sličan način kao za $N = 2$, samo što sada moramo za svaku dijagonalu sa neparnim brojem jedinica dokazati da je možemo transformisati da ima jednu jedinicu, a za one sa parnim brojem jedinica da nemaju nijednu.
	
Na sličan način kao u slučaju $N = 2$, možemo u dva poteza obrnuti vrednosti neka dva polja $(i, j)$ i $(i -1, j + 1)$. Ako dijagonalu predstavimo kao niz, ova operacija nam zapravo znači da obrćemo vrednosti neka dva susedna polja. Upotrebom ove operacije treba da dobijemo minimalan broj jedinica.
	
Ovo se može uraditi na sledeći način: iteriramo kroz niz sleva nadesno, i ako naiđemo na neki element koji je $1$ (a nije poslednji), jednom operacijom obrćemo njega i sledeći element.
Na kraju će svi elementi niza biti $0$, sem eventualno poslednjeg. Pošto naša operacija ne menja parnost broja jedinica, ako je na početku bio neparan broj jedinica, poslednji element će biti $1$, uostalom će biti $0$, pa smo dokazali da je moguće dostići željeni minimum.
	
Ukupna složenost će biti $O(NMlog(max(A_{i,j}))$, jer za svaki bit rešenje nalazimo u $O(NM)$.
	
``` cpp title="06_sdneirf.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAXN 1507
using namespace std;
int a[MAXN][MAXN],cnt[2*MAXN];
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	long long ans=0;
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>a[i][j];
	for(int x=0;x<30;x++)
	{
	    for(int i=0;i<m+n-1;i++) cnt[i]=0;
	    for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(a[i][j]&(1<<x)) cnt[i+j]^=1;
	    int br=0;
	    for(int i=0;i<n+m-1;i++) if(cnt[i]==1) br++;
	    ans+=(1LL<<x)*min(br,n+m-1-br);
	}
	cout<<ans;
}
```
