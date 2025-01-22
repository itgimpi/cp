---
hide:
  - toc
---

# 2 - Transfuzija krvi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 256MB |


Lokalna bolnica vas je zamolila da pomognete oko planiranja transfuzija
krvi. Trenutno imaju $N$ pacijenata koji čekaju transfuziju, i za
svakog od njih je poznata krvna grupa i broj jedinica krvi koje su mu
potrebne. Interesuje ih da li je, sa zalihama koje su na raspolaganju,
moguće svakom od ovih pacijenata dati transfuziju sa odgovarajućom
količinom krvi grupe koja je kompatibilna sa njegovom.

Za potrebe ovog zadatka, postoje četiri krvne grupe: O, A, B i AB (u
stvarnosti, klasifikacija je komplikovanija).

Prilikom transfuzije važe sledeća pravila:

* Pacijent čija je krvna grupa O može primiti samo krv grupe O.
* Pacijent čija je krvna grupa A ili B može primiti krv čija je grupa
  ista kao njegova, ili krv grupe O.
* Pacijent čija je krvna grupa AB može primiti bilo kakvu krv.
* Pacijent može da primi više različitih krvnih grupa. Na primer,
  pacijent B grupe kom su potrebne dve jedinice može primiti jednu O
  grupe i jednu B grupe.
* Jedinice se ne mogu razdvajati: broj jedinica krvi bilo koje grupe
  koje pacijent primi mora biti ceo broj.

Od vas se traži da za svakog pacijenta date spisak jedinica koje će
primiti, tako da su data pravila ispunjena, svaki pacijent dobije
onoliko jedinica koliko mu je potrebno, i da je broj iskorišćenih
jedinica manji ili jednak od onog u zalihama. Ukoliko ovo nije moguće,
vaš program treba da samo ispiše `nemoguce`.

## Opis ulaza

U prvom redu se nalazi jedan ceo broj $N$: broj pacijenata u bolnici.

U drugom redu se nalazi četiri broja $O, A, B, AB$: broj jedinica krvi
u zalihama bolnice za svaku od četiri krvne grupe. Redom, ovi brojevi
predstavljaju zalihe O, A, B i AB grupe.

U narednih $N$ redova se nalaze opisi pojedinačnih pacijenata, koji se
sastoje od stringa sa njegovom krvnom grupom (jedan od `O`, `A`, `B`,
`AB`) i broja jedinica (ceo broj) koji mu je potreban razdvojenih
razmakom.

## Opis izlaza

Ukoliko je moguće rasporediti zalihe krvi tako da svaki pacijent
dobije odgovarajući broj jedinica poštujući data pravila, u prvi red
izlaza ispisati `moguce`. Zatim, u narednih $N$ redova ispisati
jedinice dodeljene pacijentima, u istom redosledu kojim su pacijenti
dati na ulazu. U svakom redu ovo ispisati kao četiri cela broja: broj
jedinica svake od grupa dodeljen tom pacijentu, istim redosledom kojim
su date u zalihama (O, A, B, AB).

Ukoliko nije moguće rasporediti zalihe, u prvi i jedini red izlaza
ispisati `nemoguce`.

Ako postoji više rasporeda koji zadovoljavaju pravila, ispisati bilo
koji.

## Ograničenja

* $0 \leq N \leq 10^4$
* Ukupan broj jedinica krvi u zalihama je najviše $10^6$.
* Ukupan broj jedinica krvi potrebnih pacijentima je najviše $10^6$.

Test primeri su podeljeni u tri disjunktne grupe:

* U test primerima vrednim 30 poena: pacijenti imaju samo krvne grupe
  O ili A. U zalihama postoje samo jedinice krvi ovih grupa.
* U test primerima vrednim 30 poena: pacijenti imaju samo krvne grupe
  O, A ili B. U zalihama postoje samo jedinice krvi ovih grupa.
* U test primerima vrednim 40 poena nema dodatnih ograničenja.

## Primer 1

### Ulaz

~~~
3
2 0 2 2
A 1
B 1
AB 3
~~~

### Izlaz

~~~
moguce
1 0 0 0
0 0 1 0
1 0 0 2
~~~

### Objašnjenje

Bolnica u zalihama ima po dve jedinice krvi O, B i AB grupe. Jedno
moguće rešenje je da pacijent grupe A kom je potrebna jedna jedinicia
dobije O, pacijent grupe B dobije B, a pacijent grupe AB kom su
potrebne tri jedinice dobije jednu O i dve AB.

## Primer 2

### Ulaz

~~~
3
1 0 4 0
A 1
AB 2
O 1
~~~

### Izlaz

~~~
nemoguce
~~~

### Objašnjenje

Bolnica u zalihama ima jednu jedinicu O krvi i četiri B. Pošto imamo
pacijenta A grupe i O grupe, koji mogu od ove dve da prime samo O krv,
nema je dovoljno i nije moguće zadovoljiti sve potrebe.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Andrej Ivašković | Dimitrije Erdeljan | Dimitrije Erdeljan | Andrej Ivašković |

Za početak, pacijenti O grupe su jednostavni: mogu da prime samo krv O
grupe, tako da kod njih nemamo nikakvih odluka. U prvom prolazu kroz
pacijente, možemo njima dodeliti odgovarajuće količine O krvi, i
zatim u sledećem prolazu razmatrati samo pacijente A, B i AB grupe.

U sledećem prolazu možemo dodeliti krv pacijentima A grupe. Kod njih
imamo izbor između A i O, ali je odluka jednostavna: sada kada nema
više pacijenata O grupe, krv A grupe je strogo "manje korisna" od O,
jer svi koji mogu da je prime mogu da prime i krv O grupe. Dakle, ako
možemo, bolje je da dodeljujemo krv A grupe i čuvamo O, koju ćemo
koristiti samo ako više uopšte nema krvi A grupe.

Dalje, dodeljivanje krvi pacijentima B grupe možemo uraditi na isti način
kao za A. Na kraju, ostaju samo pacijenti AB-grupe, tako da više nije
bitno koju krvnu grupu koristimo i možemo im dodeliti proizvoljnu koje
je preostalo u zalihama.

Ako je u bilo kom trenutku u zalihama nedovoljno krvi za nekog
pacijenta, prekidamo program i ispisujemo "`nemoguce`". U suprotnom,
potrebno je da za svakog pacijenta sačuvamo dodeljene jedinice krvi
(npr. u nizu) i ispišemo ih na kraju.

``` cpp title="02_transfuzija.cpp" linenums="1"
#include <cstdio>
#include <cstdlib>

enum GROUP { O, A, B, AB } ;

GROUP parse_group(const char *s) {
    if(s[0] == 'O') return O;
    else if(s[0] == 'A') return s[1] == 'B' ? AB : A;
    else return B;
}

struct patient {
    int use[4], todo;
    GROUP group;
} ;

const int N = 10005;
patient patients[N];
int have[4];

void transfer(int i, int type, int amount) {
    if(amount > have[type]) {
        printf("nemoguce\n");
        exit(0);
    }

    patients[i].todo -= amount;
    patients[i].use[type] += amount;
    have[type] -= amount;
}

void transfer_upto(int i, int type, int amount) {
    transfer(i, type, amount > have[type] ? have[type] : amount);
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < 4; i++)
        scanf("%d", &have[i]);
    
    for(int i = 0; i < n; i++) {
        char group[10];
        scanf(" %s %d", &group, &patients[i].todo);
        patients[i].group = parse_group(group);
    }

    for(int i = 0; i < n; i++)
        if(patients[i].group == O)
            transfer(i, O, patients[i].todo);

    for(int i = 0; i < n; i++)
        if(patients[i].group == A || patients[i].group == B) {
            transfer_upto(i, patients[i].group, patients[i].todo);
            transfer(i, O, patients[i].todo);
        }
    
    for(int i = 0; i < n; i++)
        if(patients[i].group == AB) {
            transfer_upto(i, O, patients[i].todo);
            transfer_upto(i, A, patients[i].todo);
            transfer_upto(i, B, patients[i].todo);
            transfer(i, AB, patients[i].todo);
        }

    printf("moguce\n");
    for(int i = 0; i < n; i++)
        printf("%d %d %d %d\n", patients[i].use[O], patients[i].use[A], patients[i].use[B], patients[i].use[AB]);

    return 0;
}

```
