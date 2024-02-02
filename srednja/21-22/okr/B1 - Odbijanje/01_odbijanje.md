---
hide:
  - toc
---

# B1 - Odbijanje

=== "Zadatak"
	
	| Vremensko ograničenje | Memorijsko ograničenje |
	|:-:|:-:|
	| 500ms | 512MB |
	
	Komisija je za ovo takmičenje ponovo spremila čudan uređaj i naizgled
	beskorisna pitanja o njemu: idealnu gumenu lopticu i stazu po kojoj se
	ona kotrlja. Stazu ćemo posmatrati kao pravu liniju, gde loptica počinje
	na poziciji $0$, krećući se brzinom 1 u desno, ka pozitivnim
	pozicijama (dakle, nakon jedne sekunde će biti na poziciji 1, nakon
	dve na poziciji 2, ...).
	
	Da bi staza bila zanimljivija, na njoj se nalazi $N$ zidova na
	pozicijama $X_i$ i stabilnostima $S_i$. Kada loptica udari u zid,
	odbija se i počinje da se kreće u suprotnom smeru. Kako je loptica
	idealna, nastaviće da se kreće istom brzinom $1$. Nakon sudara,
	stabilnost zida se smanjuje za $1$, i ako se smanjila na $0$, taj zid
	nestaje.
	
	Komisiju interesuje program koji će, za date pozicije i stabilnosti
	zidova, odrediti **koliko će vremena proći od početka kretanja loptice
	do poslednjeg sudara sa zidom**.
	
	## Opis ulaza
	
	U prvom redu dat je jedan prirodni broj, broj zidova $N$. U narednih
	$N$ redova su data po dva cela broja $X_i, S_i$, redom pozicija i
	stabilnost $i$-tog zida.
	
	## Opis izlaza
	
	U jedinom redu izlaza je potrebno ispisati broj sekundi od početka
	kretanja loptice do poslednjeg sudara sa zidom. Kako ovaj broj može biti
	veoma velik, ispišite njegov ostatak pri deljenju sa $10^9 + 7$.
	
	## Primer 1
	
	### Ulaz
	```
	3
	2 7
	-1 1
	-3 1
	```
	
	### Izlaz
	```
	18
	```
	
	### Objašnjenje primera
	
	Kuglica počinje na poziciji $0$, i za dve sekunde udara u zid na
	poziciji $2$, čija stabilnost se smanjuje na $7-1 = 6$. Odbija se i
	kreće u desno, i nakon tri sekunde se sudara sa zidom na poziciji
	$-1$, koji nakon sudara nestaje. Dalje se kuglica kreće tri sekunde
	desno, pa pet sekundi levo, i kada se odbije od zida na $-3$ taj zid
	nestaje. Konačno, kreće se još pet sekundi do zida na poziciji $2$,
	što je poslednje odbijanje jer nakon njega više nema zidova na putanji
	loptice.
	
	Ukupan broj sekundi od početka je $2 + 3 + 3 + 5 + 5 = 18$.
	
	## Primer 2
	
	### Ulaz
	
	```
	2
	10000000 1234567
	-10000000 12345678
	```
	
	### Izlaz
	
	```
	669654326
	```
	
	
	## Ograničenja:
	
	* $|X_i| \leq 10^9$, i sve pozicije $X_i$ su različite.
	* $1 \leq N \leq 5 \cdot 10^4$
	* $1 \leq S_i \leq 10^9$
	* Ne postoji zid na početnoj poziciji loptice ($X_i \neq 0$).
	* Garantuje se da će se loptica sudariti sa barem jednim zidom.
	
	Primeri su podeljeni u četiri disjunktne grupe: 
	
	* U test primerima vrednim 30 poena: $N \leq 100, S_i \leq 100, |X_i|
	  \leq 100$.
	* U test primerima vrednim 20 poena: $N \leq 1000, S_i \leq 1000$
	* U test primerima vrednim 20 poena: $N \leq 5000$
	* U test primerima vrednim 30 poena nema dodatnih ograničenja.
	
	
=== "Rešenje"
	
	| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
	|:-:|:-:|:-:|:-:|
	| Andrej Ivašković | Dimitrije Erdeljan | Andrej Ivašković | Andrej Ivašković |
	
	## Rešenje za 30 poena
	
	Dovoljna je prosta simulacija ovog kretanja: dok god kuglica ima apsolutnu vrednost svoje pozicije ne veću od 100, svaka sekunda kretanja se simulira. Vodi se računa o trenutnoj poziciji $x$, vremenu od početka $t$, brzini $\mathit{dx}$ (koja je ili $1$ ili $-1$) i trenutku najskorijeg sudara $T$. U svakom koraku se ažurira pozicija ($x := x + \mathit{dx}$) i proveri da li pozicija odgovara nekoj od prepreka – a u tom slučaju se ažuriraju otpornost prepreke, brzina i vreme najskorijeg sudara. Ovo rešenje daje tačan odgovor u vremenskoj složenosti $O(N \cdot \max_i S_i \cdot \max_i |X_i|)$.
	
	## Rešenje za 50 poena
	
	Reč je o jednostavnoj optimizacija prethodnog pristupa. Umesto da se u svakom koraku pozicija promeni za 1, dovoljno je voditi računa o narednoj udarenoj prepreci sa leve i sa desne strane. Vreme između dva sudara je tada jednako apsolutnoj vrednosti razlike između pozicija te dve prepreke. Najpre treba podeliti prepreke u dva niza: prepreke sa negativnom pozicijom i prepreke sa pozitivnom pozicijom. U ta dva niza se zatim odrede prepreke najbliže kuglici i vrši se simulacija kretanja. Kada otpornost neke prepreke postane jednaka nuli, tada se ta prepreka označi kao nepostojeća i bira se najbliža prepreka sa nenultom otpornosti. Vremenska složenost ovog pristupa je $O(N \cdot \max_i S_i \cdot \max_i |X_i|)$.
	
	## Rešenja za 70 i 100 poena
	
	Ova dva rešenja su maltene identična i razlikuju se po tome što koriste različite algoritme sortiranja: $O(N^2)$ vremenske složenosti i $O(N \log N)$ vremenske složenosti. Najpre se, kao u prethodnom rešenju, razdvoje nizovi prepreka levo od nule i prepreka desno od nule. Zatim se ti nizovi sortiraju po apsolutnoj vrednosti pozicije i tako se određuje redosled kojim se kuglica sudara sa preprekama. Da li je poslednje odbijanje sa nekim levim zidom ili desnim zidom se određuje poređenjem ukupnih otpornosti desnih zidova i levih zidova:
	* ako je ukupna otpornost desnih zidova $r$ manja ili jednaka ukupnoj otpornosti levih $l$, tada sa leve strane imamo $l$ odbijanja, a sa desne $l+1$ odbijanje;
	* u suprotnom, sa leve strane i desne strane imamo po $r$ odbijanja.
	Na osnovu ukupnog broja odbijanja sa obe strane je moguće odrediti za svaku “deonicu” (prostor između dve uzastopne prepreke) koliko je puta pređena. Na primer, ako je došlo do $m$ odbijanja sa leve strane, tada je prva deonica (od 0 do prvog zida) pređena $2m$ puta, druga $2(m-\mathit{otp\_levih}[0])$ puta itd, dokle god preostali broj odbijanja ne postane negativan. Neophodno je posvetiti pažnju poslednjem sudaru i oduzeti $1$ od broja prelazaka poslednje deonice.
	
	``` cpp title="01_odbijanje.cpp" linenums="1"
	#include <cstdio>
	#include <algorithm>
	
	const int N = 500005;
	const long long MOD = 1000000007;
	
	struct wall {
	    int x, hp;
	} ;
	
	wall left[N], right[N];
	
	long long totalside(wall *walls, int n, long long todo, bool exit) {
	    long long res = 0;
	
	    for(int i = 0; i < n; i++) {
	        int take = std::min(todo, (long long)walls[i].hp);
	        walls[i].hp -= take; todo -= take;
	        
	        long long mult = (todo == 0 && take > 0 && exit) ? (2*take - 1) : 2*take;
	        res += mult * walls[i].x;
	        res %= MOD;
	    }
	
	    return res;
	}
	
	int main() {
	    int n, nleft = 0, nright = 0;
	    scanf("%d", &n);
	    for(int i = 0; i < n; i++) {
	        int x, hp;
	        scanf("%d %d", &x, &hp);
	        if(x < 0) {
	            left[nleft++] = {x, hp};
	        } else {
	            right[nright++] = {x, hp};
	        }
	    }
	
	    std::sort(left, left + nleft, [](wall a, wall b) { return a.x > b.x; });
	    std::sort(right, right + nright, [](wall a, wall b) { return a.x < b.x; });
	
	    long long l = 0, r = 0;
	    for(int i = 0; i < nleft; i++) l += left[i].hp;
	    for(int i = 0; i < nright; i++) r += right[i].hp;
	
	    bool exitright = r <= l;
	    if(r > l) r = l + 1;
	    else if(r < l) l = r;
	
	    long long res = totalside(right, nright, r, !exitright) - totalside(left, nleft, l, exitright);
	    res = (res + MOD) % MOD;
	    printf("%lld\n", res);
	
	    return 0;
	}

	```
