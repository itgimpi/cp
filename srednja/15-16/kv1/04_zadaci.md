---
hide:
  - toc
---

# 4 - Zadaci

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 32MB |

Poznato je da je jedno od prvih većih takmičenja koje je organizovano na prostoru Balkanskog poluostrva bila jedna informatička olimpijada pre oko dvadeset hiljada godina (kada su jedini dozvoljeni programski jezici bili Fortran i COBOL). Ono što je manje poznato jeste činjenica da je tada sama organizacija takmičenja bila drugačija. Arheolozi su otkrili da je Tajna Komisija imala predloženih N zadataka i procenila težinu svakog od njih nekim nenegativnim celim brojem ne većim od $10^9$ (veći brojevi su odgovarali težim zadacima). Tajna Komisija je nakon procesa predlaganja zadataka održala sastanak na kom se raspravljalo o organizaciji takmičenja
i bio je napravljen odabir zadataka koji su se posle pojavili na olimpijadi, pri čemu su se zadaci na takmičenju rasporedili u onom redosledu u kom su bili na spisku predloga. Međutim, nije poznato koji zadaci su bili odabrani, kao ni koliko je bilo zadataka (jasno, bio je odabran bar jedan zadatak).
$Q$ arheologa, u saradnji sa sadašnjom Tajnom Komisijom, započelo je istraživanje koje bi otkrilo nešto više o prirodi prve informatičke olimpijade. Nijedan arheolog nije uspeo da otkrije broj zadataka, ali su svi postavili teorije o tome koja je bila procenjena težina najtežeg zadatka. Pre nego što se napravi plan daljeg istraživanja, neophodno je svim arheolozima odgovoriti koliko postoji potencijalnih lista zadataka na olimpijadi (uzimajući u obzir teoriju o težini najtežeg zadatka). Pomozite Tajnoj Komisiji i arheolozima da odgovore na ovo pitanje od istorijskog značaja.

## Opis ulaza
U prvom redu standardnog ulaza se nalazi prirodan broj $N$, koji predstavlja ukupan broj zadataka sa spiska predloženih zadataka. U drugom redu se nalazi $N$ nenegativnih celih brojeva, gde $k$-ti broj predstavlja procenjenu težinu $k$-tog zadatka. U trećem redu se nalazi prirodan broj $Q,$ broj arheologa. U narednih $Q$ redova standardnog ulaza se nalazi po jedan nenegativan ceo broj $x$ koji predstavlja teoriju odgovarajućeg arheologa, odnosno upit "Koliko je takmičenja moglo da se organizuje ako je težina najtežeg zadatka bila tačno $x$?"

## Opis izlaza
U $Q$ redova standardnog izlaza ispisati po jedan ceo broj, gde se u $k$-tom redu nalazi odgovor na upit $k$-tog arheologa. Rešenja ispisivati po modulu $10^9 + 7$.


## Primer 1
### Ulaz
```
5
8 1 3 9 3
2
8
3
```

### Izlaz
```
8
6
```

## Objašnjenja primera
U slučaju teorije da je najteži zadatak imao težinu 8, znamo da je prvi zadatak
sa spiska predloženih bio na takmičenju. Moguća takmičenja su: samo prvi zadatak; prvi i drugi zadatak; prvi i treći; prvi i peti; prvi, drgi i treći; prvi, drugi i peti; prvi, treći i peti; prvi, drugi, treći i peti. U slučaju druge teorije, postojalo je šest mogućih takmičenja: drugi i treći zadatak; drugi i peti zadatak; drugi, treći i peti; treći i peti; samo treći; samo peti.

## Ograničenja.

* $1 ≤ N ≤ 10^5$.
* $1 ≤ Q ≤ 10^5$.
*  Težine zadataka su nenegativni celi brojevi koji nisu veći od $10^9$.
* Svi arheolozi su predložili težine koji su nenegativni celi brojevi koji nisu veći od $10^9$.

## Napomena. 
Rešenje ovog zadatka će biti testirano na test primerima koji mogu da se podele u nekoliko skupova koji nisu disjunktni (odnosno, postoje preklapanja):

* U test primerima ukupno vrednim 20 poena će biti zadovoljena ograničenja $N \leq 15, Q \leq 1000$.
* U test primerima ukupno vrednim 45 poena je poznato da će težine zadataka bili nenegativni celi brojevi koji nisu veći od $10^6$.
* U test primerima ukupno vrednim 50 poena će važiti ograničenja $N \leq 5000, Q \leq 5000$.
* U test primerima koji ukupno vrede 30 poena ne postoje dodatna ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Andrej Ivašković | Andrej Ivašković | Marko Ilić | Dragan Urošević |

## Rešenje i analiza

Ovom problemu je moguće pristupiti na dosta načina, koji se poprilično razlikuju po efikasnosti (samim tim i broju poena predviđenom za taj pristup). Ono što je uvek koristan prvi korak jeste sastavljanje apstraktne postavke problema. U ovom slučaju, ova postavka bi bila:
za dati niz $A$ od $N$ nenegativnih celih brojeva, odgovoriti na $Q$ upita predstavljenih jednim nenegativnim prirodnim brojem $x$ sa značenjem "koliko postoji podnizova (ne nužno uzastopnih
elemenata) niza $A$ čiji je maksimum $k$?"

## Pretraga svih mogućnosti
Najjednostavnije rešenje (ovde "najjednostavnije" znači "najlakše je smisliti ga") je primena grube sile. Ovo znači da se razmatraju svi podnizovi $A$ i za svaki podniz se odredi da li je maksimum zaista jednak $k$. Broj rešenja predstavlja vrednost jednog brojača koji je na početku postavljen na 0 i koji se inkrementira svaki put kada se nađe podniz sa datim svojstvom.
Načina za generisanje svih mogućih podnizova $A$ ima nekoliko, ali su takmičari najverovatnije najbolje upoznati sa rekurzivnim bektrekingom. U ovom konkretnom slučaju, piše se rekurzivna procedura čije je osnovno značenje "razmatranje" nekog člana niza, nakon čega se rekurzivno poziva
"razmatranje" za sledeći član niza dva puta: prvi put, kada aktuelni element nije u podnizu; drugi put, kada aktuelni element jeste u podnizu. Kada više ne postoje članovi niza za razmatranje, dolazi trenutak "ispitivanja maksimuma".
Ovakvo rešenje nije komplikovano: štaviše, očekuje se da su svi takmičari koji su ranije videli bektreking rešenja zadataka u mogućnosti da ovo uspešno implementiraju. Međutim, ono je veoma neefikasno: vremenska složenost ovog rešenja je čak $O(2^N)$
za jedan upit (odnosno, ukupno $O(Q2^N)$, što se može zaključiti iz činjenice da postoji  $2^N$ podnizova nekog niza dužine $N$ (standardan rezultat kombinatorike). Postoje neke varijante ovog rešenja koje u opštem slučaju
neznatno poboljšavaju složenost, ali se ne očekuje da će takmičarima doneti mnogo više od 20 poena, koliko je predviđeno za ovakav pristup.

## Primena kombinatorike
U prethodnom rešenju je u pomenuto da jedan niz od $N$ elemenata ima $2^N$ podnizova. Ispostavlja se da ova činjenica itekako pomaže pri daljem razvoju rešenja. Pridržavamo se istih oznaka kao i pre, tako da razmatramo situaciju kada upit ima argument $k$. Podnizovi koji će se računati u rešenju sigurno neće sadržati elemente niza $A$ koji su veći od $k$, ali svi ostali elementi će sigurno biti u nekom podnizu. Ako $A$ sadrži $p$ elemenata koji su jednaki $k$ i $q$ elemenata koji su manji od $k$ (gde $p, q > 0$), tada se u nekom od odabranih podnizova javlja bar jedan od elemenata jednakih k i možda neki od elemenata manjih od $k$. Broj podnizova formiranih od pomenutih q elemenata je zato $2^q$ , dok je broj nepraznih podnizova formiranih od p elemenata jednak $(2^p − 1)$ (neophodno je "odbiti" prazan podniz). Stoga je odgovor na jedan upit jednak $(2^{p} − 1) · 2^q$.

Ukoliko takmičari ispravno implementiraju ovo rešenje (uz posebnu pažnju na ispisivanje
rezultata "po modulu"), čija je vremenska složenost $O (QN)$, predviđen broj poena je 50. Međutim,
ono se u osnovi ne razlikuje mnogo od rešenja koje donosi 100 poena, kao što ćemo kasnije videti.

## Vrednosti, preprocesiranje stepena dvojke
U jednom od "podzadataka" postoji ograničenje za vrednosti elemenata u $A$: nijedan element nije veći od $10^6$. Ovo omogućava primenu ideje slične ovoj u prethodno navedenom "podzadatku", ali zahteva i jedan "trik" ukoliko želimo da postignemo dobru složenost. Primetimo da određivanje koliko postoji elemenata niza A koji su jednaki x zahteva $O (N)$ operacija u svakom upitu. Osnovna ideja je da se na svaki upit odgovori u konstantnom vremenu tako što će se najpre vršiti preprocesiranje, odnosno biće pripremljeni delovi konačnog odgovora odmah po učitavanju niza. Ovo zahteva da formiramo dva pomoćna niza, C i D, čije su dužine 106 (uz pažnju oko granica), pri čemu im je značenje sledeće:

* $C [i]$: broj pojavljivanja vrednosti $i$ u nizu $A$;
* $D [i]$: broj elemenata u nizu $A$ koji su manji od $i$.

Ovi nizovi mogu jednostavno da se izračunaju na početku programa. Zato je odgovor na upit $k$ jednak $(2^{C[k]} − 1)2^{D[k]}$.

Međutim, neophodan nam je još jedan "trik" da bismo dobili efikasno rešenje: preprocesiranje svih stepena dvojke. Tačnije, na početku možemo da napravimo niz $S$ takav da je $S [i] = 2i$ (uz pažnju oko modula). Time smo uspeli da smanjimo broj operacija na $O (N + Q)$ ukupno. Za ovo rešenje je predviđeno 45 poena. Uz malo pažnje oko rada sa slučajevima, ukoliko se ovo rešenje
ukombinuje sa prethodnim, moguće je ostvarili 70 poena na zadatku.

## Konačno rešenje
Sada predstavljamo rešenje u složenosti $O ((N + Q) log N)$, za koje su predviđeni svi poeni. Moguće je dobiti 100 poena na ovom zadatku primenom nekog rešenja koje ovde nije opisano, ali iste/slične složenosti. Koristan dodatni zadatak za takmičare je da otkriju što je moguće više ovakvih algoritama, budući da neke od tih ideja mogu da posluže u daleko težim i komplikovanijim zadacima!

Za potrebe ovog rešenja ćemo koristiti neke ideje iz rešenja prethodnih "podzadataka": postojanje niza $S$ koji sadrži stepene dvojke, formulu za broj podnizova. Međutim, za dolazak do rešenja je neophodno uočiti jedno ključno svojstvo: redosled elemenata koji nam je zadat u $A$ nije bitan. Ovo neće biti formalno dokazano, ali bi neki "intuitivni" argument bio taj da se zadaci različite težine i dalje razlikuju po tome na kom su mestu u $A$, tako da su svi redosledi ekvivalentni. Pošto je redosled nebitan, možemo da sortiramo niz $A$ u rastućem (u drugoj terminologiji: neopadajućem) poretku. Ovo je korisno jer su tada svi zadaci koji su iste težine uzastopni, a ovo nam omogućava da iskoristimo algoritam binarne pretrage. Algoritam binarne pretrage može da se napiše u nekoliko varijanti. U uobičajenom obliku, rezultat binarne pretrage je samo $true$ ili $false$ i ovaj povratni rezultat ima značenje "ova vrednost se nalazi u ovom sortiranom nizu". Međutim, možemo da insistiramo na tome da nas binarna pretraga na neki način informiše o položaju elementa ukoliko on postoji u nizu. Postavlja se
pitanje: šta se radi ukoliko se elementi niza ponavljaju? U tom slučaju, možemo da posmatramo
dve korisne funkcije:

* $binpretl (v)$: određuje indeks prvog elementa u nizu $A$ koji nije veći od $v$;
* $binpretd (v)$: određuje indeks poslednjeg elementa u nizu $A$ koji nije manji od $v$.

Ove dve varijante binarne pretrage imaju slične implementacije, neophodno je adekvatno izmeniti korak u kom se "pomeraju granice".

Na osnovu ovoga možemo da zaključimo da je broj pojavljivanja $k$ u sortiranom nizu $A$ jednak $binpretd (k) − binpretl(k) + 1$, a da je $binpretl(k)$ broj elemenata koji su stogo manji od $k$ (pod pretpostavkom da je niz indeksiran od 0, $binpretl(k)−1$ ukoliko je indeksiran od 1). Nakon ovoga možemo da primenimo formulu koja je ranije bila navedena da bismo došli do rezultata.

Složenost ovog pristupa zavisi od složenosti algoritma sortiranja. Postoje algoritmi sortiranja koji zahtevaju $O (N log N)$ operacija, poput Quick sort, Merge sort (uz pažnju da je izbor pivota u Quick sort kritičan i da može da dovede do kvadratne složenosti u lošim slučajevima). Složenost binarne pretrage je $O (log N)$, te je ukupna vremenska složenost $O ((N + Q) log N)$, uz
svega $O (N)$ pomoćnog prostora.

``` cpp title="04_zadaci.cpp" linenums="1"
/*
    ZADATAK:       zadaci (Kvalifikacije, 4)
    AUTOR ZADATKA: Andrej Ivaskovic
    AUTOR KODA:    Andrej Ivaskovic

    Za ovo resenje je predvidjeno 100 poena. Zasniva se na kombinatornoj logici
    i binarnoj pretrazi. Konkretno, svi podnizovi ciji je maksimum neko k imaju
    odredjen nenulti broj pojavljivanja k i sastoje se od nekog broja
    (potencijalno nula) elemenata polaznog niza koji su manji od k. Broj nacina
    na koji ovo moze da se postigne je (2^p - 1) * 2^q, gde je p broj
    pojavljivanja vrednosti p u A, a q broj elemenata niza A koji su manji od
    k.
    
    Stepeni dvojke mogu da se preprocesiraju, a odredjivanje p i q se odredjuje
    pri svakom upitu na efikasan nacin. Ako se A najpre sortira u (ne strogo)
    rastucem poretku, tada je moguce odrediti prvo i poslednje pojavljivanje k
    u sortiranom nizu A binarnom pretragom (uz dve njene standardne varijante),
    na osnovu cega mogu da se odrede vrednosti p i q.

    Slozenost ovog pristupa je O((Q + N) log N).
*/

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_DUZ 200005
#define MOD 1000000007

int N, Q;
int A[MAX_DUZ];
int k;
long long broj_res;
long long stepen[MAX_DUZ];
int p, q;
int prvo_poj, posl_poj;

// Preprocesiranje stepena dvojke
void generisi_stepene(void)
{
    stepen[0] = 1L;
    for (int i = 1; i <= N; i++) {
        stepen[i] = (stepen[i - 1] * 2) % MOD;
    }
}

// Odredjuje indeks prvog pojavljivanja elementa koji je >= v u A
int bin_pret_l(int v)
{
    int l = 0, d = N - 1, s;
    while (l < d) {
        s = (l + d) / 2;
        if (v == A[s]) {
            d = s;
        } else if (v > A[s]) {
            l = s + 1;
        } else if (v < A[s]) {
            d = s - 1;
        }
    }
    return l;
}

// Odredjuje indeks poslednjeg pojavljivanja elementa koji je <= v u A
int bin_pret_d(int v)
{
    int l = 0, d = N - 1, s;
    while (l < d) {
        s = (l + d + 1) / 2;
        if (v == A[s]) {
            l = s;
        } else if (v > A[s]) {
            l = s + 1;
        } else if (v < A[s]) {
            d = s - 1;
        }
    }
    return l;
}

int main(void)
{
    // Ulaz
    scanf("%d", &N);
    generisi_stepene();              // neophodno zbog efikasnosti
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    sort(A, A + N);                 // omogucava binarnu pretragu
    // Upiti
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d", &k);
        // Prvo i poslednje pojavljivanje k u nizu
        prvo_poj = bin_pret_l(k);
        posl_poj = bin_pret_d(k);
        if (A[prvo_poj] == k) {          // postoji neko pojavljivanje k
            p = posl_poj - prvo_poj + 1;
            q = prvo_poj;
            broj_res = ((stepen[p] - 1) * stepen[q]) % MOD;
        } else {                        // ne postoji pojavljivanje k
            broj_res = 0L;
        }
        printf("%lld\n", broj_res);
    }
    return 0;
}

```
