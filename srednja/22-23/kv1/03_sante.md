---
hide:
  - toc
---

# 3 - Sante

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Mali Mika se nalazi na Severnom polu i stoji na jednoj od mnogobrojnih santi leda. On želi da dođe do svog prijatelja Laze koji se nalazi na drugoj santi. Između nekih parova santi se nalazi voda koja je ili u potpunosti tečna, ili puna malih komada leda (teško je proći kroz nju). Mika ima mašinu koja uništava male komade leda (samo njih, ne i sante), i ona je **na početku ugašena**, a on može da je pali i gasi proizvoljan broj puta.

Sve dok je mašina upaljena, on može preći put između dve sante koji ima komadiće leda (koji se nakon njegovog prolaska misteriozno vrate), a ne sme da prelazi put koji nema (jer bi se mašina pokvarila), te je mora ugasiti za ovakav put (i ne treba da je pali dok ne dođe ponovo do nekog puta sa ledom).

Potrebno je naći način da Mika dođe do Laze tako da **najmanji broj puta menja stanje** svoje mašine (*napomena: mašina može biti u bilo kom stanju kada Mika dođe do Lazine sante*).

## Opis ulaza
U prvoj liniji dati su broj santi $N$, broj puteva između santi $M$ (ako ne postoji put između neke dve sante smatramo da je previše neprohodan i da Mika ne može direktno doći od jedne do druge).

Zatim je dato $M$ linija gde su $a$, $b$, i $t$ razdvojeni razmakom, ovi brojevi znače da postoji put između $a$-te sante i $b$-te sante, dok broj $t$ predstavlja tip puta - $1$ ako je pun leda, a $0$ ako nije.

Na kraju se učitavaju dva broja $u,v$ koja predstavljaju redni broj sante gde se nalaze Mika i Laza (redom).

## Opis izlaza
Na standardnom izlazu ispisati jedan broj - najmanji mogući broj promena stanja mašine. **Ukoliko ne postoji način da Mika dođe do Laze, ispisati -1.**

## Primer 1
### Ulaz
```
4 4
1 2 1
1 3 1
2 3 0
3 4 0
1 4
```

### Izlaz
```
2
```

## Primer 2
### Ulaz
```
7 6
1 2 0
1 3 1
2 4 1
3 5 0
5 6 1
6 7 0
1 7
```

### Izlaz
```
4
```

## Objašnjenje primera
U prvom test primeru možemo otići u santu $2$ ili $3$ (što svakako zahteva paljenje mašine), a kasnije ili iz $2$ u $3$ i dalje u $4$ (što zahteva $1$ gašenje), ili iz $3$ u $4$ (što takođe zahteva gašenje), i da tako promenimo stanje dva puta.

Jedino smer posećivanja $1-3-5-6-7$ nas dovodi do sante broj $7$.

## Ograničenja

- $N,M \leq 200000$.
- $1 \leq a,b,u,v \leq N$.
- $t = 0 \lor t = 1$.

Test primeri su podeljeni u sledećih pet grupa:

- U testovima vrednim $10$ poena - $M=N-1$, iz svake sante ide najviše $2$ puta.
- U testovima vrednim $10$ poena - svi putevi su teško prohodni.
- U testovima vrednim $25$ poena - $M=N-1$ i od svake sante se može doći do svake druge (korišćenjem jednog ili više puteva između dve sante).
- U testovima vrednim $30$ poena - $N,M \leq 5000$.
- U testovima vrednim $25$ poena - nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Momčilo Tošić | Momčilo Tošić | Momčilo Tošić | Marko Milenković |

Korisno je uočiti da sante formiraju graf od $N$ čvorova i $M$ grana, gde svaka grana ima težinu 0 ili 1. Moguće je bez promene stanja mašine kretati se samo preko grana one težine koje je trenutno stanje (0 - mašina ne radi, 1 - mašina radi). Početno stanje je 0.

## Rešenje kada $M = N-1$ i iz svake sante ide jedna ili dve grane
Ovako zadate sante formiraju niz gde je svaka povezana sa prethodnom i sledećom (osim prve i poslednje).
Možemo doći od jedne do druge sante na jedinstven način (pokušamo da idemo levo od Mike dok ne stignemo do kraja, ili do Laze, i isto tako na desno), i simulirati promene
stanja.

## Rešenje kad je put između svake dve sante teško prohodan
Ovde je jedini mogući odgovor 1 ili -1, zavisno od toga da li je moguće doći od Mikine do Lazine sante. Ovo možemo proveriti nekim algortimom poput $DFS$-a (rekurzivni obilazak svake sante sa pamćenjem posećenih).

## Rešenje kad je $M = N-1$ i uvek se može doći od jedne do druge sante
Graf koji sante opisuju u ovoj grupi primera je stablo. Kao u prvom podzadatku, jedinstven je način da se dođe od jedne sante do druge (osobina stabla), samo je ovaj put
potrebno koristiti neki algoritam za nalaženje puta (ovde je put skup grana, a ne termin iz teksta) između dva čvora (kao $BFS$), i simulirati promene stanja mašine na njemu.

## Rešenje za pun broj poena
Primetimo da ukoliko je stanje mašine $s$, a nalazimo se u čvoru $u$, moguće je slobodno (bez povećanja konačnog odgovora) se kretati po svim čvorovima
do kojih se granama težine $s$ može doći iz $u$. Dakle, konstrukcija našeg rešenja može izgledati tako što prvo obiđemo sve čvorove do kojih se može doći iz početnog koristeći grane
težine 0, zatim promeniti težinu i naći sve dostižne preko grana težine jedan od prethodno dostignutih itd. (naravno ne obilazeći već posećene čvorove).<br>
Elegantnu implementaciju ove ideje nam pruža takozvani $0-1$ $BFS$. U redu sa dva kraja (double ended queue) pamtimo čvor kao i stanje u kom se nalazimo kad ga posećujemo (na početku dodamo Mikinu santu i 0),
i na početak reda dodajemo one čvorove koji su povezani granama težine koja odgovara stanju čvora, 
dok se na kraj dodaju čvorovi povezani granama suprotne težine (i u oba slučaja ažuriramo cenu dolaska do nekog čvora). Ovako smo se osigurali da prvo prolazimo kroz
sve dostupne iz prvog čvora bez promene stanja, a da dalje ne menjamo stanje dok nismo obišli sve koji se dostižu jednom promenom stanja, itd.<br>
Na kraju jednostavno proverimo da li je obiđen Lazin čvor, i koja je cena njegovog obilaska.<br> Vremenska i memorijska složenost su $O(N+M)$.<br>

## Rešenje 2 (za pun broj poena)
Kako je moguće slobodno se kretati od nekog čvora po određenoj grupi čvorova, možemo grupisati čvorove u 0-komponente i 1-komponente (zavisno od toga kakvim se granama krećemo) $DFS$-om,
a zatim formirati novi graf u kom povezujemo dve komponente ukoliko ne postoji čvor preko kog je moguće preći iz jedne u drugu (u ovom čvoru menjamo stanje mašine). Kasnije nalazimo najkraći put između odgovarajućih
komponenti u ovom grafu $BFS$-om (s tim što je početna udaljenost 1 ukoliko krećemo od 1-komponente). Svaka komponenta je ili 1 ili 0 komponenta i ima najmanje jedan čvor, te 
njih ima reda veličine $N$, dok grana između njih ima najviše $N$ (jer jedan čvor predstavlja granu između komponenti) - dakle red veličine složenosti je ponovo linearan.

*Napomena: sporija implementacija ideje za 100 poena (npr Dajkstrin algoritam u kvadratnoj složenosti umesto 0-1 BFS) će raditi za vrednosti N i M do 5000*

``` cpp title="03_sante.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<pair<int, bool>>> gr;

int main(){
    cin >> n >> m;
    gr.clear();
    gr.resize(n);
    for(int i = 0; i < m; ++i){
        int x, y, t;
        cin >> x >> y >> t;
        --x;
        --y;
        gr[x].push_back({y,t});
        gr[y].push_back({x,t});
    }
    int u, v;
    cin >> u >> v;
    --u,--v;
    deque<pair<int, int> > dq;
    dq.push_back({u,0});
    vector<int> was(n,-1);

    was[u] = 0;
    vector<int> par(n);
    while(!dq.empty()){
        auto x = dq.front();
        dq.pop_front();
        int x1 = x.first;
        for(auto i : gr[x1]){
            if(i.second == x.second and (was[i.first]==-1 or was[i.first] > was[x1])){
                dq.push_front({i.first, x.second});
                was[i.first] = was[x1];
                par[i.first] = x1;
            } else if(i.second != x.second and (was[i.first]==-1 or was[i.first] > (was[x1]+1))){
                dq.push_back({i.first, i.second});
                was[i.first] = was[x1]+1;
                par[i.first] = x1;
            }
        }
    }
    cout << was[v] << "\n";
}

```
