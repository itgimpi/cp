---
hide:
  - toc
---

# 3 - Prepisivači

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 256MB |


Na prošlogodišnjem ciklusu takmičenja iz informatike primećen je broj prepisivača veći nego ikad. Stoga je Komisija ove godine jako zabrinuta zbog ovog problema. Paranoja je zavladala i članovi Komisije pronašli su način da pronađu prepisivače.

Naime, pretpostavićemo da će na predstojećm takmičenju učestvovati $N$ takmičara, i da će takmičar $i$ sedeti na mestu sa koordinatama $(x_i, y_i)$. Komisija smatra da je četvorka učenika sumnjiva ukoliko mesta na kojima sede formiraju trapez čija je jedna osnovica dvostruko duža od druge. 

Da bi procenili koliko kontrolora treba postaviti na takmičenje, Komisiju zanima broj sumnjivih četvorki među takmičarima. Pomozite Komisiji i izračunajte ovaj broj umesto njih, a oni će vas zauzvrat nagraditi poenima (ukoliko niste prepisivali, naravno).

Napomena: Trapez je četvorougao $ABCD$ u kome važi $AB||CD$. Osnovice ovog trapeza su duži $AB$ i $CD$. Četvorke sa istim skupom učenika a različitim redosledom smatramo istim četvorkama i ne brojimo ih zasebno.

## Opis ulaza

Na prvoj liniji standardnog ulaza nalazi se broj takmičara $N$, dok se u narednih $N$ linija redom daju koordinate takmičara $x_i$ i $y_i$.

## Opis izlaza

Na prvoj i jedinoj liniji standardnog izlaza treba ispisati broj sumnjivih četvorki među takmičarima.

## Primer 1

### Ulaz

```
4
1 1
1 -1
2 2
2 -2
```

### Izlaz

```
1
```

## Primer 2

### Ulaz

```
5
0 0
1 2
1 1
0 3
-2 1
```

### Izlaz

```
2
```

## Ograničenja

- $1\leq N\leq 1500$
- $-10^8\leq x_i\leq 10^8$
- $-10^8\leq y_i\leq 10^8$

- Garantuje se da nikoja dva takmičara neće sedeti na istom mestu, to jest za $i\neq j$ važi $(x_i, y_i)\neq (x_j, y_j)$, kao ni da nijedna tri takmičara neće sedeti na mestima čije koordinate predstavljaju kolinearne tačke.

Test primeri podeljeni su u pet disjunktnih grupa:

- U test primerima vrednim $10$ poena, $N\leq 4, -10\leq x_i\leq 10, -10\leq y_i\leq 10$.
- U test primerima vrednim $20$ poena, $N\leq 100$.
- U test primerima vrednim $20$ poena, $N\leq 400$.
- U test primerima vrednim $50$ poena, $N\leq 1500$.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Pavle Martinović | Aleksa Milojević | Momčilo Tošić | Vladimir Milenković |

Primetimo prvo da je udaljenost tačaka sa koordinatama $(x_A, y_A)$ i $(x_B, y_B)$ jednaka $\sqrt{(x_A-x_B)^2 + (y_B-y_A)^2}$, a provera da li su paralelne prave određena ovim dvema, i tačkama $(x_C, y_C)$ $(x_D, y_D)$ je provera jednakosti koeficijenta pravca ovih prava $\frac{y_A-y_B}{x_A-x_B}=\frac{y_C-y_D}{x_C-x_D}$, što kako bismo izbegli deljenje nulom možemo zapisati ovako: $(y_A-y_B)(x_C-x_D) = (x_A-x_B)(y_C-y_D)$.

## Slučaj $N \leq 4$

Ukoliko je $N$ manje od 4, jasno je da nema rešenja. Ukoliko je $N$ tačno 4, možemo pokušati da obeležimo unete tačke sa $A,B,C,D$ u svakom redosledu i da proverimo da li važi relacija data u zadatku (da su prave $AB$ i $CD$ paralelne i da je udaljenost između $A$ i $B$ dva puta manja od udaljenosti između $C$ i $D$ ili obratno).
## Slučaj $N \leq  100$

Možemo fiksirati bilo koje 4 tačke i proveriti da li važi relacija (prvu fiksiranu označimo sa $A$, drugu sa $B$ itd).
## Slučaj $N \leq  400$

Možemo primetiti da ako fiksiramo $A$, $B$, i $C$, tačka $D$ se nalazi na jedinstvenoj pravoj kroz C, i to na jedinstvenoj udaljenosti (dva puta manjoj od $\overline{CD}$), te treba posmatrati samo 2 mogućnosti za tačku $D$: tačka na toj pravoj na udaljenosti $\overline{AB}/2$ "levo" i "desno" od C. Ako dodamo te tačke u početni niz i sortiramo, svako dodatno pojavljivanje neke tačke $m$ puta znači da ta tačka može biti na kraćoj osnovici za $m$ trojki, te je rešenje zbir svih $m$ vrednosti za sve tačke, podeljeno sa 2 (jer smo uračunali obe tačke kraće osnovice).
## Svi poeni
Ako posmatramo primer sumnjivog četvorougla, može nam pasti na pamet da produžimo duž AC i BD, i dupliramo ih (inspiracija iz $AB=2\overline{CD})$, i tada ćemo zbog Talesove teoreme dobiti da je uslovu zadatka ekvivalentan uslov da se te dve duži seku u istoj tački (pokušajte da dokažete, zdravo je i zabavno). Ova tačka je slika tačke A u odnosu na C i tačke B u odnosu na D. Kako je $N<1500$, prirodno je razmišljati u smeru rešenja s kvadratnom složenošću, te i posmatranja svaka dva para tačaka. Ukoliko za svake dve tačke $X,Y$ pamtimo sve tačke koje se dobijaju kao slika X u odnosu na Y, vidimo da tačka koja se pojavljuje $k$ puta određuje $\binom{k}{2}$=$\frac{k*(k+1)}{2}$ sumnjivih četvorouglova, te za svaku upamćenu tačku treba sabrati ovu vrednost. Ovo je moguće implementirati sortiranjem slika tačaka predstavljenih kao par brojeva (koordinata) i brojanjem pojavljivanja svake.

``` cpp title="03_prepisivaci.cpp" linenums="1"
#include <bits/stdc++.h>
#define MAX_N 3005

using namespace std;

struct tacka{
	int x, y;
};

bool comp(tacka p1, tacka p2){
	return p1.x<p2.x or (p1.x==p2.x and p1.y<p2.y);
}

int N, x[MAX_N], y[MAX_N];//Podaci sa ulaza

vector<tacka> p;//Vektor u kome ce biti smestene preslikane tacke

int main(){
	ios::sync_with_stdio(false);
	cin>>N;
	for(int i=0; i<N; ++i){
		cin>>x[i]>>y[i];
	}
	//Racunanje slika tacaka pri preslikavanju preko druge tacke
	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			if(i==j)
				continue;
			tacka P;
			P.x=2*x[i]-x[j];
			P.y=2*y[i]-y[j];
			p.push_back(P);
		}
	}
	
	sort(p.begin(), p.end(), comp);
	
	long long total=0;//Ukupan broj sumnjivih cetvorki
	long long d=0;//Trenutna duzina niza istih elemenata u vektoru p
	
	int l=p.size();
	
	for(int i=0; i<l; ++i){
		d+=1;
		if(i==l-1 or p[i].x!=p[i+1].x or p[i].y!=p[i+1].y){
			total+=d*(d-1)/2;
			d=0;
		}
	}
	
	cout<<total;
	
	return 0;
}

```
