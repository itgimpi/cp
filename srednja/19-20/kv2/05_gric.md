---
hide:
  - toc
---

# 5 - Gric

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 512MB |


Kao nagradu za izuzetan uspeh na prvom krugu kvalifikacija, Aleksa je dobio na poklon parče keksa u obliku pravougaonika dimenzija $W \times H$, i postavio ga je u ravan tako da mu se temena nalaze na koordinatama $(0, 0), (W, 0), (W, H)$ i $(0, H)$. Njegov arhineprijatelj Pavle se nameračio na ovo parče keksa i planira da ga pojede. Pavletova vilica se može opisati krugom poluprečnika $R$. Tokom $i$-tog minuta desi se jedan od sledeća dva događaja:

* $1$ $x_i$ $y_i$: Pavle pozicionira svoju vilicu tako da se centar kruga nalazi u tački sa koordinatama $(x_i, y_i)$, zatim grize keks odnosno uklanja sav sadržaj keksa koji se nalazi u njegovoj vilici,

* $2$ $x_i$: Aleksa uzima lenjir, postavlja ga tako da bude paralelan sa $y$-osom, tako da prolazi kroz tačku $(x_i, 0)$ i meri dužinu trenutno preostalog parčeta keksa koje se preklapa sa ivicom lenjira.

Da li možete da predvidite koje rezultate merenja će Aleksa dobiti?

## Opis ulaza

U prvoj liniji standardnog ulaza nalaze se četiri prirodna broja, odvojena razmakom: $W, H, R, Q$. U narednih $Q$ linija, nalaze se dva ili tri broja: $1, x_i, y_i$ ili $2, x_i$, odvojena razmakom, koji opisuju $i$-ti događaj.

## Opis izlaza

Za svaki događaj tipa $2$ ispisati jedan realan broj - rezultat odgovarajućeg merenja. Ukoliko je tačno rešenje tog merenja $b$, a vaš program ispisuje broj $a$, vaš izlaz će se smatrati tačnim ukoliko važi $\frac{|a-b|}{\max(1,b)} \leq 10^{-6}$.

## Primer 1

### Ulaz

```
3 2 2 5
2 1
1 2 3
2 0
2 1
2 2
```

### Izlaz

```
2.000000000000
2.000
1.267949192431
1
```

### Objašnjenje primera

Pre nego što je Pavle odgrizao parče keksa, na bilo kojoj $x$-koordinati bila bi izmerena vrednost $H = 2$. Nakon što je odgrizao parče keksa, na koordinati $x = 0$ je dužina $2$, na $x = 1$ je $3 - \sqrt{3} \approx 1.268$ a na $x = 2$ je $1$ (videti sliku).

![](https://petljamediastorage.blob.core.windows.net/competitions/gric.svg)

## Ograničenja

* $1 \leq W, H, R, Q \leq 10^5$
* $0 \leq x_i \leq W$
* $H \leq y_i \leq H+R$

Test primeri su podeljeni u 5 disjunktnih grupa:

* U test primerima vrednim 10 poena: $R = 1$.
* U test primerima vrednim 10 poena: $R = 2$.
* U test primerima vrednim 10 poena: $Q \times W \leq 10^6$.
* U test primerima vrednim 20 poena: Svaki događaj tipa $2$ se javlja nakon svih događaja tipa $1$.
* U test primerima vrednim 50 poena: Bez dodatnih ograničenja.

## Napomena

Da biste izbegli probleme sa preciznošću, koristite tipove `double` ili `long double` u jeziku `C++`, i ispisujte rešenje na bar $9$ decimala.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Ivan Stošić | Ivan Stošić | Ivan Stošić | Nikola Pešić |


Na osnovu ograničenja $y_i \geq H$ možemo zaključiti da će, ukoliko posmatramo proizvoljnu vertikalnu pravu koja prolazi kroz keks, u svakom trenutku, presek preostalog keksa sa tom pravom biti ili prazan, ili će biti jedna duž. Kad ovo ograničenje ne bi postojalo, bilo bi moguće da Pavle pojede parče iz "sredine" keksa, u tom slučaju bi taj presek mogao da se sastoji iz više duži. Osnovna ideja koja je zajednička svim rešenjima jeste da se održava niz $b$, gde je $b_i$ preostalo parče keksa na poziciji $x = i$. U početku, pre svih upita imamo $b_i = 0$ za svako $i \in [0, W]$. Treba obratiti pažnju pri implementaciji da se ne štampa negativan broj, odnosno, ako neki krug prelazi iks-osu, ne treba smanjivati $b_i$ ispod $0$.

U prvom podzadatku, radijus kruga je $1$, pa su izmene na nizu $b$ trivijalne - ukoliko krug ima $y=H$, stavljamo $b_{x} = H-1$.

U drugom podzadatku, postavljamo $b_x = \min(b_x, y-2)$ i $b_{x-1} = \min(b_{x-1}, y - \sqrt{3})$, slično za $b_{x+1}$, naravno, ukoliko su ove $x$-koordinate u segmentu $[0, W]$. Vremenska složenost rešenja prva dva podzadatka je $O(Q + W)$.

Treći podzadatak je uopštenje prethodne ideje. Tačna vrednost na koju treba postaviti broj $b_i$ je $\min(b_i, y - \sqrt{(R+i-x)(R-i+x)})$ za sve $i \in [0, W] \cap [x-R, x+R]$. Ova formula se može izvesti geometrijski, pomoću Pitagorine teoreme. Vremenska složenost je $O(W + QR)$.

Za rešavanje četvrtog i petog podzadatka neophodne su nam sledeće opservacije. Prva je ta da je dovoljno posmatrati oblik koji formiraju donji polukružni lukovi dodatih krugova. Druga, ključna je da se nijedna dva takva luka ne mogu seći više od jednom, osim ako se ne poklapaju. Ovo se može dokazati na sledeći način: Posmatrajmo neka dva kruga. Ukoliko se oni ne poklapaju, oni se mogu seći na najviše dva mesta. Na osnovu toga što imaju isti radijus, tačke preseka su centralno simetrično raspoređene u odnosu na tačku koja se nalazi na sredini duži koja spaja centre ta dva kruga. Kako ovaj centar ima $y$-koordinatu veću nego "niži" od ta dva kruga, i jedna od presečnih tačaka sigurno isto ima veću $y$-koordinatu od centra nižeg druga, pa ne učestvuje u preseku donjih polukružnica.

Četvrti podzadatak se može rešiti tako što se eksplicitno izračuna oblik keksa. Sortiramo sve krugove po $x$-koordinati i obrađujemo ih u ovom redosledu. Pomoću steka održavamo skup polukružnica koje učestvuju u konačnom obliku keksa, kao i pozicije preseka susednih polukružnica. Odgovor na neki upit možemo naći binarnom pretragom po dobijenom nizu polukružnica, ili jednostavnije, obradom celog niza polukružnica tj. eksplicitnim nalaženjem svih vrednosti $b_i$, u jednom prolazu kroz niz. Ovo rešenje je primenljivo upravo zato što se svake dve polukružnice seku najviše jednom. Ovu ideju nije moguće primeniti ukoliko to ne bi važilo, na primer, ako bi se radijusi datih kružnica razlikovali. Vremenska složenost je $O(W + Q \log Q)$.

Odavde je jasno da rešenje četvrtog podzadatka podseća na ono što se zove "trik sa konveksnim omotačem", gde se nalazi oblik koji formira presek poluravni. Drugi način da se izračuna ovaj presek poluravni jeste pomoću takozvanog *LiChao* segmentnog stabla, pa je prirodno pokušati prilagoditi tu strukturu podataka za ovaj problem.

Naime, formirajmo segmentno stablo, gde se u svakom čvoru nalazi opis jedne polukružnice, koja cela pokriva pridruženi segment u stablu, odnosno, takva da ako je čvor odgovoran za segment $[x_l, x_r]$, tada za kružnicu važi $x-R \leq x_l \leq x_r \leq x+R$ *(uslov 1)*, gde je $(x,y)$ njen centar. Dodatno, namećemo ograničenje da za list, tj. čvor koji odgovara segmentu $[x, x]$, put u stablu od tog lista do korena sadrži krug koji u $x$ dostiže najmanju $y$-koordinatu, u svakom trenutku. Ako ovo važi, jasno je da na upit možemo odgovoriti u $O(\log W)$, samo posmatranjem tih $O(\log W)$ čvorova na putu od lista do korena.

Kako dodati novi krug? Posmatrajmo rekurzivnu funkciju koja polazi od korena stabla, koji odgovara čvoru koji čuva segment $[0, W]$. Ukoliko za trenutni čvor ne važi *uslov 1*, i segmenti koji odgovaraju krugu i čvoru se ne seku, možemo odmah izaći, inače rekurzivno dodajemo krug u oba čvora deteta trenutnog čvora. Na dalje pretpostavimo da *uslov 1* važi. Ako u trenutnom čvoru nema nikakvog kruga, slobodno možemo staviti u taj čvor novi krug i izaći iz funkcije. Još jedan slučaj gde možemo odmah staviti krug i izaći jeste ako je novi polukrug ceo ispod starog na celom segmentu trenutnog čvora $[x_l, x_r]$, što se može jednostavno proveriti ako izračunamo $y$-koordinate preseka polukrugova sa $[x_l, x_r]$, kao po formuli datoj u rešenju podzadatka 3. Ukoliko je novi polukrug ceo iznad starog na tom segmentu, ne moramo da ga dodajemo, već odmah izlazimo iz funkcije. Inače, ova dva polukruga se seku na tačno jednom mestu, unutar segmenta. U taj čvor možemo upisati onaj od ta dva kruga koji je "dominantan" na bar jednoj polovini segmenta, dok drugi možemo rekurzivno ubaciti u drugo dete trenutnog čvora. Vremenska složenost ovog postupka se razlikuje od onog za obično segmentno stablo. U toku rekurzije dolazimo do $O(\log W)$ čvorova za koje važi *uslov 1*, a za svaki od njih imamo po jedan rekurzivni put koji se može sastojati iz najviše $O(\log W)$ čvorova, pa je vremenska složenost dodavanja jednog kruga $O(\log^2W)$, a celog rešenja $O(W + Q \log^2 W)$.


``` cpp title="05_gric.cpp" linenums="1"
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

typedef long double ld;
const int maxn = 131072;

int h, w, r, q;

struct krug {
	int x, y;

	krug(int x=1e8, int y=1e8) : x(x), y(y) {}

	ld operator* (int t) const {
		if (t < x-r || t > x+r)
			return 1e50;
		return y - sqrt(ld(r+t-x)*(r-t+x));
	}
};

krug b[2*maxn];

void dodaj(krug v, int x, int xl, int xr) {
	if (v.x + r < xl || xr < v.x - r)
		return;
	if (v.x - r <= xl && xr <= v.x + r) {
		ld vl = v * xl, vr = v * xr;
		ld bl = b[x] * xl, br = b[x] * xr;
		if (vl <= bl && vr <= br) {
			b[x] = v;
			return;
		}
		if (vl >= bl && vr >= br)
			return;
		if (vl < bl)
			swap(b[x], v);
	}
	int xm = (xl+xr) >> 1;
	dodaj(v, 2*x, xl, xm);
	dodaj(v, 2*x+1, xm+1, xr);
}

ld racunaj(int p, int x, int xl, int xr) {
	ld sol = b[x] * p;
	if (xl != xr) {
		int xm = (xl+xr) >> 1;
		if (p <= xm)
			sol = min(sol, racunaj(p, 2*x, xl, xm));
		else
			sol = min(sol, racunaj(p, 2*x+1, xm+1, xr));
	}
	return sol;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << setprecision(12) << fixed;
	
	cin >> w >> h >> r >> q;
	for (int i=0; i<=w; i++)
		dodaj(krug(i, h+r), 1, 0, w);
	while (q--) {
		int t;
		cin >> t;
		if (t == 2) {
			int x;
			cin >> x;
			cout << max(ld(0), racunaj(x, 1, 0, w)) << '\n';
		} else if (t == 1) {
			int x, y;
			cin >> x >> y;
			dodaj(krug(x, y), 1, 0, w);
		}
	}
}


```
