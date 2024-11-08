
# 5 - Pećinski zečevi


	
| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 6000ms | 512MB |
	
Kao što je opšte poznato u godini $3023$, zečevi nemaju brkove, oslepeli su, imaju tri puta veće uši i žive u pećinama. U jednoj pećini nalati se $N$ soba, a u svakoj se nalazi po jedan zec. Poznato je da su neke sobe povezane prolazima. Postoji $N-1$ parova takvih soba. $i$-ti par opisuje da je soba $U_i$ direktno iznad sobe $V_i$. Moguće je od sobe $V_i$ tim prolazom stići do sobe $U_i$. Soba $1$ je posebna. Iznad nje se ne nalazi nijedna soba, već izlaz iz pećine. Iznad svake ostale sobe se nalazi druga soba. Poznato je da je iz svake sobe moguće stići do sobe $1$ krećući se prolazima.
	
Promena magnetnih polova zemlje izazvala je nepreviđena seizmička dešavanja. Pećina je pod zemljotresom, i potrebno je evakuisati sve zečeve. Oni su numerisani brojevima od $1$ do $N$. $i$-ti zec se nalazi u sobi $i$ i ima snagu $i$. Kako bi zečevi izašli iz pećine, oni mogu da skaču nagore. Tačnije, mogu skočiti u bilo koju sobu koja je direktno iznad trenutne, na onu koja je iznad nje, na onu iznad nje itd. Uslov je da $i$-ti zec snage $i$ može skočiti najviše $i$ soba nagore (odjednom). Zečevi mogu skakati više puta, ali neophodno je u što manje skokova izaći iz pećine. Takođe, ako $i$-ta soba "nagore" ne postoji, to znači da zec odjednom može da skoči dovoljno jako da izađe iz pećine, te će to učiniti. Ako ovaj posao nije već bio dovoljno komplikovan, zemljotres je poremetio pristupačnosti soba. Tačnije, kroz svaku sobu je moguće proći, ali nije nužno moguće doskočiti na svaku sobu. Samo u nekim sobama se nalazi platforma za skakanje (i samo na nju je moguće doskočiti).
	
Da ne bi pravili gužvu, zečevi su se dogovorili da izlaze redom, od zeca $1$ do $N$. Pre nego što zec $i$ krene u svoj pohod, zbog nestabilnosti pećine, može se desiti jedna od narednih $N+1$ stvari:
	
* Promeni se stanje sobe $1$;
* Promeni se stanje sobe $2$;
* Promeni se stanje sobe $3$;
* $\ldots$
* Promeni se stanje sobe $N$;
* Ništa se ne menja.
	
Pod promenom stanja podrazumevamo da, ako je ranije postojala platforma u sobi, više ne postoji, a ako ranije nije postojala, sada postoji.
	
Za svakog zeca potrebno je pronaći najmanji broj skokova potreban da on izađe iz pećine. Može se desiti da to nije moguće i da će, nažalost, on ostati zaglavljen u pećini. Ukoliko se to desi, naknadno će doći ekipa evakuacionih glista i izbaviti sve zarobljene zečeve. Potrebno je objaviti posebnu poruku za sve takve.
	
**Napomena**: može se desiti da soba iz koje zec kreće nema platformu za skakanje. On i dalje može skakati na sobe iznad. Uslov je samo da nije moguće doskočiti na sobu bez platforme.
	
## Opis ulaza
U prvom redu standardnog ulaza, dat je ceo broj $N$ - broj soba i broj zečeva
	
U $i$-tom od narednih $N-1$ redova, data su dva cela broja $U_i$ i $V_i$ - on obeležava da postoji prolaz između te dve sobe, kao i da je soba $U_i$ iznad sobe $V_i$.
	
U pretpostlednjem redu standardnog ulaza, dato je $N$ celih brojeva $B_1, B_2, \ldots, B_N$. Ako je $B_i=1$, tada u sobi $i$ postoji platforma za skakanje (na početku). Ako je $B_i=0$, onda ne postoji u toj sobi.
	
U poslednjem redu standardnog ulaza, dato je $N$ celih brojeva $X_1,X_2,\ldots, X_N$.
* Ako je $X_N = 0$, pre skoka zeca $i$ ništa se ne menja.
* Inače, pre skoka zeca $i$ menja se stanje sobe $X_i$.
	
## Opis izlaza
U jednoj liniji ispisati $N$ brojeva. $i$-ti broj predstavlja najmanji broj skokova potreban da $i$-ti zec izađe iz pećine. Ukoliko to ne može učiniti, za $i$-ti broj postaviti vrednost $-1$.
	
## Ograničenja
- $2 \leq N \leq 500\,000$
- $1 \leq U_i,V_i \leq N$, $U_i \neq V_i$, važe dodatni uslovi povezanosti soba opisani u postavci zadatka.
- $B_i \in \{ 0,1 \}$
- $0 \leq X_i \leq N$
	
Test primeri su podeljeni u pet disjunktnih grupa:
	
- U testovima vrednim 8 poena: Svaka soba ima najviše jednu ispod nje, $X_i = 0$ za svako $i$.
- U testovima vrednim 24 poena: Svaka soba ima najviše jednu ispod nje.
- U testovima vrednim 20 poena: $X_i = 0$ za svako $i$.
- U testovima vrednim 32 poena: $N \leq 100\,000$
- U testovima vrednim 16 poena: Bez dodatnih ograničenja.
	
## Primer 1
### Ulaz
```
	3
	1 3
	3 2
	1 1 1
	0 0 0
```
	
### Izlaz
```
	1 2 1
```
	
### Objašnjenje
	U svakoj sobi nalazi se platforma za skakanje i važi $X_1 = X_2 = X_3 = 0$. Tj. nema promena. Zec $1$ jednim skokom može izaći iz pećine. Zec $2$ može prvo skočiti u sobu $3$ koja je iznad njegove. Zatim, može napraviti skok dužine dva i iskočiti iz pećine. Za to mu je ukupno potrebno dva skoka. Treći zec može odjednom napraviti skok kojim izlazi iz pećine.
	
## Primer 2
### Ulaz
```
	5
	1 5
	5 4
	4 3
	4 2
	0 0 0 0 0
	1 1 2 3 2
```
	
### Izlaz
```
	1 -1 -1 1 1 
```
	
### Objašnjenje
U ovom primeru ima promena. Na početku se ni u jednoj sobi ne nalazi platforma za skakanje. Pre pohoda prvog zeca menja se stanje sobe $1$, i time ona dobija platformu za skakanje. Pre pohoda drugog zeca opet se menja stanje sobe $1$, čime ona gubi platformu. Kada dođe red na zeca broj $2$ da izlazi iz pećine, on neće imati sobu na koju može doskočiti, a izlaz iz pećine mu je predalek. On ne stiže da izađe iz pećine, te će ga sačekati ekipa evakuacionih glista. Pre pohoda zeca $3$ menja se stanje sobe $2$. Međutim, soba iznad njega, druga soba iznad njega, kao i treća soba iznad njega ostaju bez platforme za skakanje. To znači da ni on ne može izaći iz pećine. Zečevi $4$ i $5$ mogu odmah izaći iz pećine, te je odgovor za njih $1$.
	
## Primer 3
### Ulaz
```
	2
	1 2
	0 0
	1 1
```
	
### Izlaz
```
	1 1 
```
	
### Objašnjenje
U ovom primeru svaki zec može odmah izaći iz pećine.
	
## Primer 4
### Ulaz
```
	16
	1 16
	16 7
	16 8
	7 15
	15 14
	14 13
	13 12
	12 11
	12 10
	10 9
	10 5
	10 6
	6 2
	6 3
	14 4
	0 1 0 1 1 0 1 0 1 1 1 0 1 1 0 0
	1 16 15 12 13 14 9 4 6 7 12 15 13 13 16 15
```
	
### Izlaz
```
	1 6 4 2 2 2 1 1 1 1 1 1 1 1 1 1
```
	
Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksandar Višnjić | Aleksandar Višnjić | Jovan Bengin i Aleksandar Višnjić | Nikola Pešić i Jovan Bengin |
	
## Prvi podzadatak
	
	  
	
U ovim testovima pećina se može predstaviti kao niz, i skok nagore kao prelazak na levi element niza.
	
	  
	
Najjednostavnije rešenje je da se simuliraju skokovi svakog zeca: krenemo iz njegove početne pozicije, i svaki put idemo u najlevlju dostižnu poziciju. Drugim rečima, ako je $i$-ti zec ternutno na $v$-tom mestu sleva, on će u sledećem koraku otići na najlevlju poziciju sa platformom u intervalu $[v-i, v)$ (naravno, ako takva pozicija ne postoji, onda $i$-ti zec ne može da izađe). Ovo se lako nalazi ako imamo niz pozicija sa platformom, jer onda u tom nizu možemo binarnom pretragom naći najmanju poziciju veću ili jednaku $v-i$.
	
Primetimo da u ovako traženom rešenju suma visina bilo koja dva uzastopna skoka $i$-tog zeca mora biti veća od $i$ (inače bi se oni mogli zameniti jednim skokom), pa je i broj njegovih skokova ograničen odozgo sa $2\lceil  \frac{N}{i} \rceil$. Ukupan broj skokova svih zečeva biće ograničen odozgo sa $2  \sum  \limits_{i=1}^n \lceil \frac{N}{i} \rceil$, što je $O(NlogN)$ (suma harmonijskog reda), a pošto svaki skok tražimo u vremenskoj složenosti $O(logN)$, ukupna vremenska složenost algoritma biće $O(Nlog^2N)$.
	
	  
	  
	
## Prva dva podzadatka
	
	  
	
Umesto niza, koristićemo strukturu *std::set* da čuvamo pozicije soba sa platformom. Umesto binarne pretrage možemo onda koristiti funkciju *lower_bound*, koja takođe radi u $O(logN)$.
	
## Rešenje kada je $X_i = 0$ za svako $i$
	
	  
	
U ovom zadatku dato je stablo, ali bez promena stanja čvorova (soba). Slično kao ranije, potrebno je pronaći najvišu slobodnu sobu od prvih nekoliko soba iznad date (i to uraditi puno puta). Pošto nema promena, to je moguće uraditi binarnim podizanjem (binary lifting). Čuvamo dve sparse tabele, jednu sa informacijom o $2^k$-tom pretku, a drugu sa informacijom koliko među $2^k$ predaka (računajući sam taj čvor u njih) postoji soba sa platformom. Ove informacije čuvamo za svaki čvor i svako $k = 0,1,2,\ldots,\lfloor  \log N \rfloor$.
	
	  
	
## Rešenje kada je $N \leq 100.000$
	
	  
	
Ove testove prolaze sporije implementacije glavnog rešenja.
	
	  
	
## Glavno rešenje
	
	  
	
Prisetimo se ranijih zaključaka. Potrebno je $O(N\log N)$ puta naći prvu slobodnu sobu među $x$ predataka datog čvora. Takođe, sada je potrebno i podržati $O(N)$ promena soba. Standardna ideja je upotreba teško-lake dekompozicije stabla, koja je od ove godine u programu takmičenja. Stablo particionišemo u lance na poseban način. Prvi lanac kreće iz korena i nastavlja u čvor koji ima najviše dece (računajući decu na svim dubinama). Ponavljamo postupak sa novim krajem dok ne dođe do lista stabla, čime smo tada napravili ceo lanac. Izbacivanjem ovog lanca nastaju nova podstabla, svaki sa svojim korenom. Algoritam se vrši za svaki od njih.
	
	  
	
Na upite odgovaramo tako što napravimo Fenvikovo stablo za svaki lanac, a potom preko šetnje nađemo poslednji potreban slobodan čvor. Promene su podržane pomenutom strukturom.
	
	  
	
Za dat početni čvor, tvrdimo da prolazimo kroz $O(\log N)$ lanaca dekompozicije prilikom cele šetnje (do izlaska iz pećine, tj. stabla). Neka je $s_p$ veličina podstabla čvora $p$. Razmotrimo algoritam koji, počev od datog čvora, u svakom trenutku podiže trenutni za jedan iznad njega. Ako promenimo lanac dekompozicije, brojač (inicijalno $0$) se poveća za $1$. Posmatrajmo situaciju promene. Neka je prethodni čvor $u$, naredni $v$, a $w$ čvor u kome se lanac od $v$ nastavlja. Zbog načina izbora dekompozicije, važi $s_w \geq s_u$. Odavde je jasno $s_v > 2\cdot s_u$. Dakle, $s$-vrednost trenutnog čvora se poveća barem duplo. To se najviše desi $O(\log N)$ puta, odakle sledi tvrdnja.
	
	  
	
Pravilna implementacija dovodi do rešenja složenosti $O(N\log ^2 N)$. Komisija tvrdi da postoji i rešenje bolje složenosti. Takmičaru ostavljamo za vežbu da ga pronađe.
	
	  
	
## Alternativno glavno rešenje
	
	  
	
Prvo, razmotrimo alternativno rešenje za niz. Postoji drugačiji način da nađemo najlevlju slobodnu poziciju u $[v-i, v)$: to je ujedno i najlevlja pozicija $x$ za koju je broj slobodnih pozicija od $1$ do $x$ strogo veći od broja slobodnih pozicija od $1$ do $v - i - 1$. Upiti "broj slobodnih pozicija od $1$ do $x$", kao i promene vrednosti neke pozicije, mogu se rešiti segmentnim ili Fenvikovim stablom. Najlevlja slobodna pozicija može se ponovo naći binarnom pretragom, samo što sada na ovaj način u $O(logN)$ odgovaramo na upit "postoji li slobodna pozicija u $[v-i, x]$". Dakle, ukupna vremenska složenost ovog rešenja bi bila $O(Nlog^3N)$.
	
	  
	
Ovo rešenje možemo da uopštimo i na stablo, samo nam je potrebno da možemo da nađemo sumu elemenata na putu od korena do proizvoljnog čvora.
	
	  
	
Razmislimo kako bismo mogli da to uradimo kada ne postoje promene. Možemo da prođemo kroz stablo pretragom u dubinu iz korena, i čuvamo promenljivu $x$ koja predstavlja sumu od korena do trenutnog čvora. Kada uđemo u čvor, dodajemo njegovu vrednost (u ovom slučaju, $1$ ako ima platformu, $0$ ako nema) u $x$. Kada izlazimo iz čvora, oduzimamo njegovu vrednost od $x$. Ovakvim postupkom za svaki čvor imamo sumu elemenata od korena do njega.
	
	  
	
Kako se ovde mogu primeniti promene? Konstruišemo niz $b$ veličine $2N$ koji odgovara gorenavedenom postupku: kada ulazimo u čvor, na kraj niza dodajemo njegovu vrednost, a kada izlazimo, dodajemo minus od te vrednosti. Neka su $in_v$ i $out_v$ pozicije u nizu $b$ koje odgovaraju ulasku u čvor $v$ i izlasku iz njega, redom. Tada je suma elemenata u stablu od korena do $v$ zapravo suma elemenata u nizu $b$ od 1 do $in_v$.
	
	  
	
Sada se rešenje za stablo svodi na rešenje za niz, jedino što pri promeni vrednosti čvora $v$ moramo u nizu promeniti vrednosti u $in_v$ i $out_v$, što ponovo možemo uraditi segmentnim ili Fenvikovim stablom (mada je u ovom slučaju, radi brzine i jednostavnosti, bolje koristiti Fenvikovo). Takođe, potrebno nam je da brzo nalazimo $k$-tog roditelja proizvoljnog čvora, što se lako može uraditi metodom *binary lifting*.
	
	  
	
Vremenska složenost ovog rešenja je $O(Nlog^3N)$, mada je u praksi dosta brže: delom jer je binarna pretraga uglavnom radi na manjim skokovima (jer sa većim skokovima završavamo brže), delom jer su operacije nad Fenvikovim stablom vrlo brze. U svakom slučaju, konstanta rešenja je jako mala, i komisijina implementacija prolazi za 2.5s.
	
``` cpp title="05_pecinski_zecevi.cpp" linenums="1"
	#include <bits/stdc++.h>
	
	using namespace std;
	long long int typedef li;
	
	vector<vector<int>> g(500005);
	int up[500005];
	int siz[500005];
	int dub[500005];
	
	void dfs(int p, int q)
	{
	    up[p]=q,siz[p]=1,dub[p]=dub[q]+1;
	    for (auto it : g[p]) if (it!=q) dfs(it,p),siz[p]+=siz[it];
	}
	
	int chin[500005]; //kom chain-u pripada
	int president[500005]; //najvisi u chain-u
	int chnt[500005]; //koliko dat chain ima elemenata
	vector<int> podub[500005]; //za svaki chain, njegovi cvorovi izlistani po dubinskom redu
	
	int idx=0;
	void hfs(int p, int cc, int r)
	{
	    chin[p]=cc,president[p]=r,chnt[cc]++,podub[cc].push_back(p);
	    if (g[p].empty()) return;
	    int gde=0;
	    for (auto it : g[p]) if (siz[it]>siz[gde]) gde=it;
	    hfs(gde,cc,r);
	    for (auto it : g[p]) if (it!=gde) hfs(it,++idx,it);
	}
	
	bool ima[500005]; //korisna informacija za imati
	int fwtsiz[500005];
	int logsiz[500005]; //floor(log(fwtsiz))
	vector<int> fwt[500005]; //za dat chain fenwick (po dubini, offest-ovan)
	void add(int c, int i)
	{
	    for (;i<=fwtsiz[c];i+=(i&-i)) fwt[c][i]++;
	}
	void rmv(int c, int i)
	{
	    for (;i<=fwtsiz[c];i+=(i&-i)) fwt[c][i]--;
	}
	int pre(int c, int i)
	{
	    int ret=0;
	    for (;i;i-=(i&-i)) ret+=fwt[c][i];
	    return ret;
	}
	int walk(int c, int x) //prvi index sa tom vrednoscu...
	{
	    int i=0,cur=0;
	    for (int k=logsiz[c];k>=0;k--) if (i+(1<<k)<=fwtsiz[c])
	    {
	        int sta=fwt[c][i+(1<<k)];
	        if (cur+sta<x) i+=(1<<k),cur+=sta;
	    }
	    return i+1;
	}
	
	int MaxUpwalk(int p, int k)
	{
	    int r=president[p];
	    if (dub[p]-dub[r]+1<=k)
	    {
	        int sta=MaxUpwalk(up[r],k-(dub[p]-dub[r]+1));
	        if (sta==-1)
	        {
	            int c=chin[p];
	            int F=walk(c,1);
	            if (F-1>dub[p]-dub[r]) return -1;
	            return podub[c][F-1];
	        }
	        return sta;
	    }
	
	    int c=chin[p];
	    int F=walk(c,pre(c,dub[p]-dub[r]-k)+1);
	    if (F-1>dub[p]-dub[r]) return -1;
	    return podub[c][F-1];
	}
	
	int main()
	{
	    ios_base::sync_with_stdio(false);
	    cin.tie(0),cout.tie(0);
	
	    int n; cin>>n;
	    for (int i=1;i<n;i++)
	    {
	        int u,v; cin>>u>>v;
	        g[u].push_back(v);
	    }
	    dfs(1,0);
	    hfs(1,++idx,1);
	
	    for (int c=1;c<=idx;c++)
	    {
	        int temp=chnt[c]+1;
	        fwtsiz[c]=temp;
	        fwt[c].resize(temp+1);
	        int lele=0;
	        while (temp>1)
	        {
	            temp>>=1;
	            lele++;
	        }
	        logsiz[c]=lele;
	    }
	
	    for (int i=1;i<=n;i++)
	    {
	        cin>>ima[i];
	        if (ima[i])
	        {
	            add(chin[i],dub[i]-dub[president[i]]+1);
	        }
	    }
	
	    vector<int> cvormenjaniz(n);
	    for (int i=0;i<n;i++) cin>>cvormenjaniz[i];
	
	    for (int i=1;i<=n;i++)
	    {
	        int cvormenja=cvormenjaniz[i-1];
	        if (cvormenja)
	        {
	            if (ima[cvormenja]) rmv(chin[cvormenja],dub[cvormenja]-dub[president[cvormenja]]+1);
	            else add(chin[cvormenja],dub[cvormenja]-dub[president[cvormenja]]+1);
	            ima[cvormenja]=!ima[cvormenja];
	        }
	
	        int p=i; //pocetni cvor
	        int k=i; //jacina skoka
	        int skokova=0;
	        while (true)
	        {
	            skokova++;
	            if (dub[p]<=k) break;
	            int newp=MaxUpwalk(p,k);
	            if (newp==-1 || newp==p) goto nemoze;
	            p=newp;
	        }
	
	        cout<<skokova<<" ";
	        continue;
	        nemoze: cout<<-1<<" ";
	
	        //cout<<endl<<endl;
	    }
	}
```
