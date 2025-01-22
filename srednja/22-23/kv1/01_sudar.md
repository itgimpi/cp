---
hide:
  - toc
---

# 1 - Sudar brojeva

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 100ms | 32MB |

Mala Danica, potpuno revoltirana odlukom Komisije da ove godine ukine jedan krug kvalifikacija, krenula je da razbija sve oko sebe, uključujući i brojeve koji joj padnu pod ruku. Naime, kada ugleda dva prirodna broja ona baci jedan broj na drugi tako da se brojevi sudare. Sudarom dva broja, nastaje nov prirodan broj.

Prilikom sudara dva prirodna broja $X$ i $Y$, svaka cifra jednog broja upoređuje se s odgovarajućom cifrom drugog broja, to jest, jedinica se uporedi s jedinicom, desetica s deseticom, stotina sa stotinom, itd. Manja od dve cifre u tom poređenju ispadne, dok veća ulazi u sastav novoformiranog broja. Ukoliko su odgovarajuće cifre jednake, prilikom sudara obe ulaze u novostvoreni broj te će stoga on imati više cifara od $X$ i $Y$. Ukoliko u nekom od dva prirodna broja koja se sudaraju nema odgovarajuće cifre, smatra se da ta cifra ne postoji te se bez poređenja uvek uzima cifra drugog broja, pa makar ona bila i nula.

Pošto je brojeva previše, mala Danica ne može sama da se izbori s njima, pa vas je zamolila da joj pomognete tako što ćete sudarati brojeve zajedno s njom. Da biste to učinili morate odgovoriti na pitanje koji će se broj stvoriti prilikom sudara dva prirodna broja?

## Opis ulaza
U prvom redu standardnog ulaza se nalaze prvi prirodan broj $X$, dok se u drugom redu standardnog ulaza nalazi drugi prirodan broj $Y$. Ova dva prirodna broja treba sudariti na način opisan u tekstu zadatka.

## Opis izlaza
U jedinom redu standardnog izlaza ispisati novostvoreni broj koji se dobija prilikom sudara dva broja sa ulaza.

## Primer 1
### Ulaz
```
73
28
```

### Izlaz
```
78
```

## Primer 2
### Ulaz
```
64
357
```

### Izlaz
```
367
```

## Primer 3
### Ulaz
```
234
135
```

### Izlaz
```
2335
```

## Primer 4
### Ulaz
```
99099
9999
```

### Izlaz
```
99999999
```

## Primer 5
### Ulaz
```
2
100
```

### Izlaz
```
102
```

## Objašnjenja primera
U prvom primeru se sudaraju brojevi $73$ i $28$. Oba broja su dvocifrena, te se međusobno upoređuju cifre desetica, odnosno $7$ i $2$, i cifre jedinica, odnosno $3$ i $8$, i od većih cifara stvara se novi broj koji ima vrednost $78$, pošto je $7$ veće od $2$, a $8$ veće od $3$.

U drugom primeru sudaraju se brojevi $64$ i $357$. Prvi broj je dvocifren, a drugi trocifren, pa se stoga cifra stotina, $3$, preuzima iz većeg broja. Zatim se prilikom sudara međusobno upoređuju cifre desetica, $6$ i $5$, kao i cifre jedinica $4$ i $7$, i od većih cifara formira se novi broj koji ima vrednost $367$, pošto je $3$ preuzeto, a $6$ veće od $5$ i $7$ veće od $4$.

U trećem primeru sudaraju se trocifreni brojevi $234$ i $135$. Međusobno se upoređuju cifre stotina, $2$ i $1$, cifre desetica $3$ i $3$, i konačno cifre jedinica $4$ i $5$. Pored odgovarajućih većih cifara koje sačinjavaju nov broj, a to su cifre $2$ i $5$, u sastav novog broja ulaze i sve međusobno jednake cifre na odgovarajućim mestima, odnosno u ovom konkretnom slučaju obe cifre $3$ s mesta desetica, pa je vrednost novostvorenog broja $2335$.

U četvrtom primeru sudaraju se brojevi $99099$ i $9999$. Kako je prvi petocifreni, a drugi četvorocifreni, porede se četiri najniže cifre, a po najviša se cifra preuzima iz prvog broja. Prilikom upoređivanja postoje samo dva slučaja: u prvom se poredi $9$ i $0$ te se u novoformiranom broju prenosi jedna devetka, a u drugom slučaju se poredi $9$ i $9$ pa u novostvoreni broj ulaze obe devetke. Stoga je rezultat sudara $99999999$ jer u dva početna broja imamo ukupno osam devetki i sve one ulaze u sastav rezultujućeg broja.

Najzad, u petom test primeru sudaraju se brojevi $2$ i $100$. Pošto je prvi broj jednocifren, a drugi trocifren, to se prve dve cifre $1$ i $0$ svakako preuzimaju iz drugog broja, a u poređenju cifara jedinica, $2$ je veće od $0$, te se konačno dobija vrednost $102$.

## Ograničenja

* $1 \leq X, Y \leq 10^9$.

Test primeri su podeljeni u pet disjunktnih grupa:

* U testovima vrednim $10$ poena: $1 \leq X, Y < 10$, odnosno $X$ i $Y$ su jednocifreni.
* U testovima vrednim $15$ poena: $10 \leq X, Y < 100$, odnosno $X$ i $Y$ su dvocifreni.
* U testovima vrednim $15$ poena: $100 \leq X, Y < 1000$, odnosno $X$ i $Y$ su trocifreni.
* U testovima vrednim $20$ poena: $10^3 \leq X, Y \leq 10^9$ i da $X$ i $Y$ imaju jednak broj cifara.
* U testovima vrednim $40$ poena: Bez dodatnih ograničenja.

## Napomena
Zadati i ispisani brojevi su uvek u dekadnom zapisu bez vodećih nula.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Vladimir Milovanović | Vladimir Milovanović | Vladimir Milovanović | Igor Pavlović |

## Glavno rešenje
Zadatak je najlakše rešiti posmatrajući date prirodne brojeve $X$ i $Y$ kao niske. Naime, u jednoj petlji treba porediti znakove (karaktere) niski $X$ i $Y$, koji zapravo predstavljaju cifre brojeva na odgovarajućim indeksima. Krećući se unazad, počevši od cifara najmanje težine i idući ka cifrma najveće težine, ideja je dodavati veću od njih u neku novostvorenu nisku. Ukoliko se pak desi da su cifre odgovarajuće težine jednake, neophodno ih je obe dodati u pomenutu novoformiranu nisku, to jest tu jednu cifru dva puta. Nisku napravljenu u prethodnom postupku na kraju zadatka potrebno je ispisati. Slučajevi kada su zadati ulazni brojevi različitih dužina rešava se tako da kada se tokom prolaska kroz opisanu petlju broj cifara jednog od brojeva iscrpi, rezultujuću nisku samo treba dopuniti preostalim ciframa većeg broja koje nisu bile iskorišćene u poređenju.

Pod pretpostavkom da se zadat broj $X$ sastoji iz $M$ cifara, dok zadati broj $Y$ sadrži $N$ cifara, složenost opisanog algoritma je $\mathcal{O}(M+N)$, odnosno linearna po broju cifara.

``` cpp title="01_sudar.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

long long a, b;
string A, B, res="";

int main() {
	cin >> a>>b;

	if(b>a) swap(a,b);

	A = to_string(a);
	B = to_string(b);

	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());

	for(int i=0;i<A.size();i++){
        if(i>=B.size()){
            res+=A[i];
            continue;
        }
		if(A[i]>=B[i]) res+=A[i];
		if(A[i]<=B[i]) res+=B[i];
	}

	reverse(res.begin(),res.end());

	cout<<res<<endl;
	return 0;
}

```
