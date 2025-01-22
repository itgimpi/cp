---
hide:
  - toc
---

# 3 - Palindrom šafl

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |


Većina ljubitelja košarke je čula za novi potez na košarkaškim terenima, takozvani Sombor šafl. Zato je Komisija odlučila da uvede novi potez u svet programiranja, Palindrom šafl. Palindrom šafl je potez u kom izaberete nepraznu podnisku uzastopnih slova u niski $T$ i ispremeštate slova u toj podniski tako da cela niska postane palindrom. Raspored slova van te podniske ostaje nepromenjen.

U ovom zadatku data je niska $T$ i potrebno je da odgovorite na pitanje koja je minimalna dužina podniske koju možete izabrati tako da uspešno izvršite Palindrom šafl.

Podsećamo vas da za nisku $T$ kažemo da je palindrom ako se čita isto s leve i desne strane.

## Opis ulaza
U jedinom redu standardnog ulaza nalazi se niska $T$, koja se sastoji isključivo od malih slova engleskog alfabeta.

## Opis izlaza
U jedinoj liniji standardnog izlaza ispisati ceo broj koji predstavlja minimalnu dužinu podniske na kojoj može da se izvrši Palindrom šafl. Garantuje se da je niska takva da uvek postoji bar jedna odgovarajuća podniska za Palindrom šafl.

## Primer 1
#### Ulaz
```
abbaaca
```

#### Izlaz
```
4
```

#### Objašnjenje
Najkraća podniska uzastopnih slova koju možemo izabrati za šafl je od 3. do 6. karaktera. Tada nisku možemo promeniti u $abacaba$.

## Primer 2
#### Ulaz
```
abcba
```

#### Izlaz
```
1
```

#### Objašnjenje
Niska $T$ sa ulaza je palindrom, najkraća neprazna podniska za šafl je dužine $1$.

## Ograničenja

- Dužina niske $T$ je makar $1$, a najviše $2\cdot 10^5$.
- Sva slova u niski $T$ su mala slova engleskog alfabeta.

Test primeri su podeljeni u četiri disjunktne grupe:

- U testovima vrednim 15 poena: Niska $T$ sadrži tačno dva slova $b$ i ostala slova su $a$.
- U testovima vrednim 20 poena: Dužina niske $T$ nije veća od $50$.
- U testovima vrednim 25 poena: Dužina niske $T$ nije veća od $3000$.
- U testovima vrednim 40 poena: Bez dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Aleksa Plavšić | Aleksa Plavšić | Lazar Milenković | Aleksa Milisavljević |


Sa $N$ ćemo označiti dužinu date niske, sa $\Sigma$ broj karaktera u alfabetu, u našem slučaju $26$.

## Rešenje kada su dva slova 'b', a ostala ‘a’

Optimalno rešenje u ovom slučaju je ili pomeriti oba slova na dva centralna polja ili pomeriti jedno slovo na poziciju simetričnu poziciji drugog slova.

## Rešenje kada $N \leq 50$

Zadatak možemo rešiti tako što pretpostavimo levu i desnu granicu optimalne podniske, $i$ i $j$, respektivno (broj mogućnosti je $\Theta(N^2)$). Za svaku mogućnost $(i,j)$, u linearnom vremenu proverimo da li je moguće izvršiti šafl tako da je rezultujuća niska palindrom. Posmatramo interval $[i,j]$ i simetrični interval $[n-j+1, n-i+1]$. Ukoliko izvan ova dva intervala, ulazna niska nije palindromska, tada je nemoguće promeniti bilo šta u $[i,j]$ tako da rešenje postane palindrom. Drugim rečima, pretpostavka $[i,j]$ nije validna. U suprotnom, kada interval $[i,j]$ ne sadrži sredinu niske, dovoljno je proveriti da za svako slovo važi da je njegova učestanost u $[i,j]$ ista kao i njegova učestanost u $[N-j+1, N-i+1]$. Kada $[i,j]$ sadrži sredinu niske, provera je slična, samo u obzir treba uzeti i preklapanja intervala $[i,j]$ i $[N-j+1, N-i+1]$.

## Rešenje kada $N \leq 3000$
Prethodna ideja se može ubrzati ako primetimo da kada fiksiramo dva kraja proveru možemo izvršiti u vremenskoj složenosti $O(\Sigma)$.

## Glavno rešenje
Posmatrajmo najpre najveći broj $l$, takav da je prefiks niske dužine $l$ jednak sufiksu dužine $l$ u obrnutom redosledu. Optimalno rešenje nikada neće sadržati prvih $l$ i poslednjih $l$ slova niske. Najpre ćemo proveriti da li je moguće izvršiti šafl na samo levoj polovini niske. To proveravamo tako što tražimo najmanji indeks $i_1 \le |T|/2$ takav da za svako slovo važi da je njegova učestanost u intervalu $[l+1,i_1]$ ista kao i njegova učestanost u intervalu $[N-i_1+1, N-l]$ i da je ulazna niska palindrom u intervalu $[i_1, N-i_1]$. Ukoliko takav indeks postoji kandidat za rešenje je interval $[l,i_1]$.

U nastavku ćemo pretpostaviti da optimalno rešenje sadrži središnji deo niske i počinje od indeksa $l+1$. (Pošto su po definiciji vrednosti $l$ slova u nisci na pozicijama $l+1$ i $N-l$ različita, optimalna podniska mora uvek sadržati bar jednu od ove dve pozicije. U implementaciji je potrebno proveriti oba slučaja pojedinačno.) Tražimo najmanji indeks $i_2 > N/2$ takav da za svako slovo važi da je njegova učestanost u intervalu $[i_2+1, N-l]$ manja ili jednaka njegovoj učestanosti u intervalu $[l+1, i_2]$. Ukoliko takav indeks postoji, kandidat za rešenje je interval $[l+1, i_2]$. Ovo možemo garantovati, jer nam se garantuje da će postojati takav interval. Iz toga možemo zaključiti da će i ,,centralni deo’’ moći da se ispremešta da bude palindrom.

Učesestanost slova u intervalima možemo odrediti korišćenjem prefiksnih suma i opisano rešenje je moguće implementirati u vremenskoj složenosti od $O(N \cdot \Sigma)$. Malo pažljivija implementacija daje vremensku složenost od $O(N)$. Postoje i alternativna rešenja zadatka koja koriste binarnu pretragu ili pretraživačka stabla i rade u složenosti $O(N \log N)$, što je takođe dovoljno za sve poene na ovom zadatku.

``` cpp title="03_palindrom_safl.cpp" linenums="1"
#include<bits/stdc++.h>

using namespace std;


const int maxN = 2e5;
const int maxS = 26;
string s;
int n;
int p[maxN + 10][maxS + 1];

bool compare(int l, int r) {
	int l1 = n - r + 1;
	int r1 = n - l + 1;

	for (int i = 0; i < 26; i++) {
		if (p[r][i] - p[l - 1][i] != p[r1][i] - p[l1 - 1][i]) {
			return false;
		}
	}
	
	return true;
}

bool palindrom_shuffle(int l, int r) {
	int odd = 0;

    for (int i = 0; i < 26; i++) {
    	if (2 * p[r][i] - p[l - 1][i] - p[n - l + 1][i] < 0) {
    		return false;
    	}
    }

	return true;
}

int solve() {
	n = s.size();

	for (int i = 0; i < 26; i++) {
		p[0][i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 26; j++) {
			p[i][j] = p[i - 1][j];
		}
		p[i][s[i - 1] - 'a']++;
	}

	int d = 1;
	while (s[d - 1] == s[n - d] && d <= n / 2) d++;

	if (d > n / 2) {
		return 1;
	}
    
    int d1 = n / 2;

    while(s[d1 - 1] == s[n - d1]) {
    	d1--;
    }


    if (compare(d, d1)) {
    	return d1 - d + 1;
    }

    for (int i = n/2 + 1; i <= n - d; i++) {
    	if (palindrom_shuffle(d, i)) {
    		return i - d + 1;
    	}
    }

    return n - 2 * d + 2;    
}

int main() {
	cin>>s;
    
    int ans = solve();
    reverse(s.begin(), s.end());
    ans = min(ans, solve());

    cout<<ans<<endl;
}
```
