---
hide:
  - toc
---

# 4 - Čvrsti brojevi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |

Vračara Miljana je posle dugogodišnjeg putovanja po svetu na svojoj svetskoj turi odlučila da se vrati kući. Posle svih upoznatih obožavalaca, ludih predskazanja i nezaboravnih vragolija, shvatila je da joj je trenutno samo potrebna toplina sopstvenog doma i porodice. Tako je, posle oproštajnog predskazanja u Vuhanu, gde je predvidela neki viruščić, spakovala kofere i uputila se ka domovini svih vračara - Vračaru.

Kod kuće su je svi dočekali sa radošću, slavljem i raznim poklonima. Kako to obično biva, od jednog starog druga iz školske klupe je dobila omiljen poklon svih protagonista informatičkih zadataka - jedan broj. Kada je videla ovo odmah se setila da je negde na svojoj turi naučila o *čvrstim brojevima*. Broj je čvrst ukoliko važi sledeći uslov: ako su cifre na $i$-toj i $j$-toj poziciji, pri čemu $j>i$, jednake $c$, tada je cifra na $k$-toj poziciji takođe jedanka $c$, za svako $i\leq k\leq j$. Tako su na primer brojevi $233441$ i $335$ čvrsti, dok $121$ nije.

Da bi pokazala šta je naučila, odlučila je da promeni neke cifre poklonjenom broju tako da postane čvrst. Specijalno, ona može promeniti broj tako da ima vodeće nule, ali te cifre **se još uvek računaju** u uslov da je broj čvrst. To znači da ako je na poklon dobila broj $1210$, nije validno rešenje da prebaci prvu cifru u $0$ i dobije $0210$. Pomozite Miljani da nađe najmanji broj cifara koje je neophodno promeniti da bi broj bio čvrst.

## Opis ulaza
Prva i jedina linija ulaza sadrži prirodan broj $N$, koji predstavlja broj koji je Miljana dobila. Garantuje se da $N$ nema vodećih nula.

## Opis izlaza
U jedinu liniju izlaza ispišite najmanji broj cifara koje je potrebno promeniti da bi dobijeni broj postao čvrst.

## Ograničenja
-   $1 \leq N < 10^{100.000}$

Test primeri su podeljeni u 5 disjunktnih grupa:

-   U test primerima vrednim $10$ poena: $N \leq 10^6$
-   U test primerima vrednim $10$ poena: sve cifre početnog broja su $0$ ili $1$.
-   U test primerima vrednim $30$ poena: $N \leq 10^{100}$
-   U test primerima vrednim $30$ poena: $N \leq 10^{10.000}$
-   U test primerima vrednim $20$ poena: Bez dodatnih ograničenja

## Primeri
### Primer 1
#### Ulaz
```
202201
```

#### Izlaz
```
1
```

#### Objašnjenje
Moguće je promeniti drugu cifru u $2$, nakon čega broj postaje $222201$, koji je čvrst.

### Primer 2
#### Ulaz
```
10001
```

#### Izlaz
```
1
```

#### Objašnjenje
Moguće je promeniti prvu cifru u $0$ tako da broj postane $00001$, koji je čvrst. Primetimo da ovde nakon zamene i dalje računamo vodeće nule.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Pavle Martinović | Pavle Martinović | Tadija Šebez |

U ovom zadatku je potrebno  naći čvrst broj koji se na najmanje mesta razlikuje od zadatog broja. Broj je čvrst ako su sva pojavljivanja neke cifre uzastopna.

Neka je u svim podzadacima $M$ broj cifara broja $N$, a $d$ broj različitih cifara.

## Podzadatak 1: $N\le10^6$
Prostim prolaskom kroz sve brojeve sa šest ili manje cifara možemo da vidimo za svaki da li je čvrst i, ukoliko jeste, na koliko se pozicija razlikuje od početnog broja.

## Podzadatak 2: Sve cifre su $0$ ili $1$
Za svaki prefiks i sufiks je moguće jednim prolaskom kroz niz da odredimo broj poteza da bi sve cifre postale $0$ ili $1$, pa onda za svaku poziciju prelamanja možemo da vidimo koliko nam treba poteza (postoji samo $2M$ čvrstih brojeva sa samo jedinicima i nulama, proverimo koji od njih je optimalan).

## Podzadatak 3: $N\le 10^{100}$

Ovaj podzatak služi da se na njemu osvoje poeni koje koriste ideje u naredna dva, ali nisu dovoljno brza za veća ograničenja (npr. $O(M^2\cdot d\cdot2^d)$ ili $O(M\cdot d^2\cdot2^d)$)
### Podzadatak 4:  $N\le10^{10.000}$
Ovaj zadatak ćemo uraditi putem **dinamičkim programiranjem po bitmaskama**. Neka je $dp[i][c][mask]$ najbolje rešenje za prvih $i$ cifara, tako da je poslednja cifra $c$ i u $mask$ su na $1$ postavljene cifre koje odgovaraju ciframa koje smo već iskoristili (uključujući $c$).  Imaćemo i pomoćni niz $aux[i][mask]$ koji nam kaže najveću vrednost $dp[i][c][mask]$ za neko $0\le c\le 9$. Sada lako možemo računati vrednost $dp[i][c][mask]$ kao maksimum od $dp[i-1][c][mask]$ i $aux[i-1][mask \text{ xor } 2^c]$ i na to dodamo $1$ ako trenutna cifra nije $c$. Tako svako stanje $dp[i][c][mask]$ računamo u $O(1)$ i svaku od vrednosti $aux[i][mask]$ u $O(d)$, što nam daje rešenje u $O(M\cdot d\cdot 2^d)$.

## Podzadatak 5:  100 poena
U ovom podzadatku za sve poene ćemo promeniti perspektivu. Umesto što tražimo najmanji broj promena, tražićemo najveći broj cifara da ne menjamo. Da bismo to postigli, čuvaćemo dva niza $a[c][mask]$, koji je pandan nizu $dp$ iz prethodnog rešenja (kad obradimo $i$-tu cifru tu će se nalaziti najbolje rešenje za prvih $i$ cifara) i niz $max[mask]$ koji je pandan prethodnom nizu $aux$. Glavna razlika je što se većina ovih nizova sada neće menjati i onda možemo samo da ih pustimo da naslede vrednosti iz prethodne iteracije. Na primer: $a[c][mask]$ ima smisla ponovo računati za trenutnu cifru ($a[c][mask]$ postane maksimum od $a[c][mask]+1$ i $max[mask\text{ xor } 2^c]+1$), i pri tome promeniti $max[mask]$. Ovo nam dosta smanji broj operacija, tako da nam je složenost sada $O(M\cdot2^d)$ što lako prolazi za $100$ poena.


``` cpp title="04_cvrsti_brojevi.cpp" linenums="1"
#include <bits/stdc++.h>
using namespace std;
int dp[10][1024],mx[1024];
int main()
{
	string s;
	cin>>s;
	for(int i=0;i<1024;i++) {mx[i]=-1000000000; for(int j=0;j<10;j++) dp[j][i]=-1000000000;}
	mx[0]=0;
	for(int i=0;i<s.size();i++)
	{
		int c=s[i]-'0';
		for(int j=0;j<1024;j++) if((1<<c)&j)
		{
			dp[c][j]=max(dp[c][j],mx[j^(1<<c)])+1;
			mx[j]=max(mx[j],dp[c][j]);
		}
	}
	int x=0; for(int i=0;i<1024;i++) x=max(x,mx[i]);
	cout<<s.size()-x;
}

```
