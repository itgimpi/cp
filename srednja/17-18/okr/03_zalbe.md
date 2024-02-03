---
hide:
  - toc
---

# B3 - Žalbe

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Poznato je da se Komisijska komisija za žalbe sastoji od $n$ članova koji rade za $n$ stolova numerisanih, s leva udesno, brojevima od $1$ do $n$. Svaki član komisije za žalbe poseduje pravednost, "Ja $\heartsuit$ Petlja" šolju i "Mrzim žalbe" majicu. Kad god neki takmičar uobrazi da je oštećen na takmičenju, on predaje žalbu nekom članu komisije i nada se najboljem.

Međutim, čudni su putevi žalbi. Kada neki član dobije žalbu, on se zgrozi, baca novčić i, ukoliko padne pismo, prosleđuje žalbu nekom članu komisije levo od sebe koji nije već dobio ovu žalbu; ukoliko padne glava, prosleđuje žalbu nekom članu komisije desno od sebe koji nije već dobio ovu žalbu. Članovi komisije su navežbani u bacanju novčića - žalba na ovaj način uvek prođe sve članove komisije i, nakon $n-1$ prosleđivanja, član koji poslednji dobije ovu žalbu je baca u kantu za smeće i šalje mejl "žalba je odbijena".

Zli takmičar Bežal Everfor je dobio "žalba je odbijena" mejl (tužna priča) i on želi da ispita zašto je do toga došlo. On je prevarantskim metodama saznao svih $n-1$ rezultata bacanja novčića i cilj mu je da na osnovu toga rekonstruiše redosled prosleđivanja žalbe tj. da pronađe permutaciju $(p_1, p_2, \ldots, p_n)$ brojeva koja označava da je žalbu prvo dobio član $p_1$ koji je prosledio članu $p_2$ koji je prosledio $\ldots$ koji je prosledio članu $p_n$. **Takva permutacija mora biti u skladu sa bacanjem novčića** (npr. ako je u $i$-tom bacanju palo pismo, član $p_{i+1}$ mora imati manji redni broj od člana $p_i$); nazovimo sve takve permutacije (redoslede) **dobrim**. 

Osim žalbi, Bežal mnogo voli leksikografske poretke i konkretan broj $k$. Zato vas je zamolio da mu pomognete u rekonstrukciji redosleda prosleđivanja žalbi:

 - Ukoliko pronađete **leksikografski najmanju** od svih dobrih permutacija **koje počinju brojem $k$** (tj. za koje važi $p_1 = k$) dobijate **sve poene** na odgovarajućem test-primeru. 
 - Ukoliko pronađete bilo koju dobru permutaciju koja ne zadovoljava sve gore pomenute uslove **dobijate 60% poena** na odgovarajućem test-primeru. (dakle, u ovom slučaju ne treba obraćati pažnju na broj $k$ i leksikografski poredak ali permutacija i dalje mora biti u skladu sa bacanjem novčića).

Ukoliko pomognete Bežalu, dobijate polovinu usvojenih poena sa njegove žalbe!

## Opis ulaza
U prvom redu standardnog ulaza nalaze se prirodni brojevi $n$ i $k$, odvojeni razmakom. U drugom redu nalazi se $n-1$ karaktera koji su ili 'P' (pismo, označava prosleđivanje žalbe ulevo) ili 'G' (glava, označava prosleđivanje žalbe udesno). Između karaktera nema razmaka.

## Opis izlaza
U prvi i jedini red standardnog izlaza ispisati $n$ različitih prirodnih brojeva od $1$ do $n$ - traženu permutaciju $p$. **Ulazni podaci će biti takvi da će rešenje (za maksimalan broj poena) uvek postojati** - to rešenje je (jasno) uvek jedinstveno dok je za 60% poena dozvoljeno ispisati bilo koje (tačno) rešenje.

## Primer 1
### Ulaz
```
5 2
GPPG
```

### Izlaz
```
2 4 3 1 5
```

## Primer 2
### Ulaz
```
3 3
PP
```

### Izlaz
```
3 2 1
```

## Objašnjenje primera
U prvom primeru je $n = 5$, $k = 2$ a bacanje novčića kaže da je žalba putovala desno-levo-levo-desno. Tražena leksikografski minimalna permutacija koja počinje od $k$-tog člana je $(2, 4, 3, 1, 5)$ tj. član $2$ prosleđuje (udesno) članu $4$, ovaj prosleđuje (ulevo) članu $3$, ovaj prosleđuje (ulevo) članu $1$, ovaj prosleđuje (udesno) članu $5$. Ovo rešenje osvaja sve poene dok neka od rešenja koja osvajaju $60\%$ poena mogu biti $(3, 5, 2, 1, 4)$ (ne počinje od $k$-tog člana) i $(2, 5, 4, 1, 3)$ (nije leksikografski minimalna permutacija koji počinje brojem $k$).

## Ograničenja

* $2 \leq n \leq 200.000$.
* $1 \leq k \leq n$.
* Svih $n-1$ karaktera na ulazu pripadaju skupu $\{'P', 'G'\}$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U test primerima koji vrede $10$ poena važiće $n \leq 4$.
* U test primerima koji vrede $15$ poena važiće $n \leq 10$.
* U test primerima koji vrede $15$ poena važiće $n \leq 5.000$.
* U test primerima koji vrede $30$ poena garantuje se da najmanja leksikografska permutacija koja je saglasna sa rezultatima bacanja novćića počinje upravo brojem $k$.
* U test primerima koji vrede $30$ poena nema dodatnih ograničenja.

## Napomena

Niz $(a_1, a_2, a_3, \ldots, a_n)$ je leksikografski manji od niza  $(b_1, b_2, b_3, \ldots, b_n)$ ako postoji indeks $i$ sa osobinom da je $a_1 = b_1, a_2 = b_2, \ldots, a_{i-1} = b_{i-1}$ i $a_{i} < b_{i}$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nikola Milosavljević | Andrej Ivašković |

Prvi podzadatak se može rešiti jednostavnom analizom slučajeva: za $n \leq 4$ posle fiksiranja $p_1 = k$ ostaje nam najviše $3 \cdot 2$ mogućih rasporeda koje treba proveriti. Drugi (istovremeno i prvi) podzadatak se može rešiti u složenosti $O(n! \cdot n)$ proveravanjem svih permutacija dužine $n$ za ukupno $25$ poena.

Analizirajmo sada kako generisati *bilo koju* dobru permutaciju, ne obraćajući pažnju na broj $k$ i na leksikografski poredak (rešenje za $60$ poena). Jedan od načina je 
sledeći: redom ćemo postavljati vrednosti $p_1, p_2, \ldots, p_n$ tako da se nakon $i$ postavljanja na pozicijama $p_1, p_2, \ldots, p_i$ nalaze uzastopne vrednosti iz segmenta $[l, r]$ za neke $l,r$ (gde je $l - r + 1 = i$). U $(i+1)$-vom potezu, ukoliko je odgovarajući karakter `P`, dovoljno je postaviti $p_{i+1} = l - 1$, odnosno $p_{i+1} = r+1$ u suprotnom (naredni postavljeni broj je uvek ili trenutni najmanji broj - 1 ili trenutni najveći broj + 1); na početku postavljamo $p_1 = x$ (za neki prirodan broj $x$). Na primer, za ulaz 
`PPGPGGGPP` i npr. $x = 1$, dobijamo 

$$
(1) \rightarrow (1, 0) \rightarrow (1, 0, -1) \rightarrow (1, 0, -1, 2) \rightarrow (1, 0, -1, 2, -2) \rightarrow (1, 0, -1, 2, -2, 3) \rightarrow 
$$

$$
(1, 0, -1, 2, -2, 3, 4) \rightarrow (1, 0, -1, 2, -2, 3, 4, 5) \rightarrow (1, 0, -1, 2, -2, 3, 4, 5, -3) \rightarrow
$$

$$
(1, 0, -1, 2, -2, 3, 4, 5, -3, -4).
$$

Pomenuti postupak se može implementirati u složenosti $O(n)$. Jasno, dobijena "permutacija" je u skladu sa bacanjem novčića ali dobijeni brojevi nisu nužno iz segmenta $[1, n]$. Ovo možemo rešiti na $2$ načina: $1$) dodati svim elementima permutacije $p$ apsolutnu vrednost najmanjeg elementa + $1$ ili $2$) izabrati $x$ kao 1 + broj pojavljivanja karaktera `P`. Npr. prvi način primenjen na pomenuti primer daje 

$$
(1, 0, -1, 2, -2, 3, 4, 5, -3, -4) + 5 = (6, 5, 4, 7, 3, 8, 9, 10, 2, 1)
$$

Dakle, (bar jedna) dobra permutacija uvek postoji. U četvrtom podzadatku se traži leksikografski najmanja dobra permutacija (bez uslova za početni broj $k$) -- sada je neophodno težiti da $p_1$ bude najmanje moguće, zatim da $p_2$ bude najmanje moguće za izabrano $p_1$ itd. Ukoliko na početku imamo $m \geq 0$ uzastopnih karaktera `P`, tada mora biti $p_1 = m + 1$. Zaista, ukoliko bi bilo $p_1 < m + 1$ ne bismo imali dovoljno mesta za pomeranje ulevo; sa druge strane, postoji dobra permutacija koja počinje sa $(m + 1, m, m - 1, \ldots, 2, 1)$ a zatim neki skok udesno preko $m+1$ (moguće je nastaviti, npr. na osnovu konstrukcije za 60%). Nastavljanjem ovog postupka za niz $(m+2, m+3, \ldots, n)$ i preostale karaktera dolazimo do optimalnog rešenja. 

Nije teško doći do sledećeg algoritma složenosti $O(n)$ koji realizuje pomenuti postupak: dodati 'veštački' karakter `G` na početak stringa; podeliti string na uzastopne podstringove čiji je prvi karakter `G`; u permutaciji $(1, 2, \ldots, n)$ obrnuti redosled uzatopnim elementima koji odgovaraju odgovarajućim podstringovima i vratiti dobijenu permutaciju. Na primer, PPGPGGGPP $\rightarrow$ **G**PPGPGGGPP $\rightarrow$ GPP|GP|G|G|GPP $\rightarrow$ 1 2 3 | 4 5 | 6 | 7 | 8 9 10 $\rightarrow$ 3 2 1 | 5 4 | 6 | 7 | 10 9 8 $\rightarrow$ (3, 2, 1, 5, 4, 6, 7, 10, 9, 8). Ovaj algoritam osvaja 72 poena.

Konačno, za maksimalan broj poena treba modifikovati prethodni algoritam tako da permutacija uvek počinje brojem $k$. Neka na početku stringa ide prvo $a \geq 0$ 'G'-ova a zatim $b \geq 0$ 'P'-ova. Uzimajući u obzir leksikografsku minimalnost, razlikujemo dva slučaja: 1) Ukoliko je $b < k$ (ima mesta ulevo) tražena permutacija počinje sa $(k, k+1, \ldots, k + a)$ a ostatak dobijamo traženjem minimalne dobre permutacije preostalog skupa vrednosti $(\{1, 2, \ldots, n\} \setminus \{k, k+1, \ldots, k + a\})$ za preostali niz karaktera; 2) Ukoliko je $b \geq k$ (nema mesta ulevo) tražena permutacija počinje sa $(k, k+1, \ldots, k + a - 1, k + a + (b - k + 1))$ a ostatak dobijamo traženjem minimalne dobre permutacije preostalog skupa vrednosti za preostali niz karaktera. Naravno, u oba slučaja za ostatak permutacije koristimo algoritam iz četvrtog podzadatka.

Neefikasna implementacija prethodnih algoritama (npr. u $O(n^2)$) dovoljna je za prva tri podzadatka tj. za oko 40 poena. 



``` cpp title="03_zalbe.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

const int MAX_N = 200010;

int p[MAX_N], a[MAX_N], blockLen[MAX_N];
char s[MAX_N];
bool mark[MAX_N];

int n, k, bNum;

int main()
{
	scanf("%d%d", &n, &k);
	scanf("%s", s + 1);

	// podela stringa s na blokove oblika GPPP...P (uz vestacko 'G' na pocetku)
	bNum = 0;
	blockLen[0] = 1;
	for (int i = 1; i < n; i++)
	{
		if (s[i] == 'P')
			blockLen[bNum]++;
		else
			blockLen[++bNum] = 1;
	}
	
	int curr = 0;
	while (curr <= bNum && blockLen[curr] == 1) curr++;
	// curr simbola 'G' (ne ukljucujuci vestacki) pa onda PPP.. => permutacija sigurno krece (k, k+1, ..., k+curr-1)
	// a naredni korak zavisi od duzine niza PPP... (pomeranje ulevo) - ako nije predugacak, pomeraj na k+curr a inace mora 'desnije'
	for (int i = 0; i < curr; i++)
		mark[k + i] = true;
	if (curr <= bNum)
	{
		if (blockLen[curr] <= k)
			mark[k + curr] = true;
		else
			mark[blockLen[curr] + curr] = true;
		blockLen[curr]--;
	}

	// ubaciti markirane elemente na pocetak permutacije p[] i napraviti niz a preostalih slobodnih elemenata;
	int m = 0;
	int currP = 0;
	for (int i = 1; i <= n; i++)
	{
		if (mark[i])
			p[++currP] = i;
		else
			a[++m] = i;
	}
	
	// sada resavamo subtask 4 gde je niz (a[1], a[2], ..., a[m]) pocevsi od bloka curr
	int pos = 0;
	for (int i = curr; i <= bNum; i++)
	{
		pos = pos + blockLen[i];
		for (int j = 0; j < blockLen[i]; j++)
			p[++currP] = a[pos - j];
	}

	for (int i = 1; i < n; i++)
		printf("%d ", p[i]);
	printf("%d\n", p[n]);
	
	return 0;
}
```
