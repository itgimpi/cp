#include <bits/stdc++.h>
using namespace std;
/* Neka je K broj zadataka, a M maksimalan broj bodova po zadatku. U situaciji opisanoj u zadatku imamo K = 6 i M = 7. 
Rezultatom cemo zvati proizvoljan niz koji se sastoji od K cijelih brojeva iz intervala [0,M]. 
Primijetimo da postoji (M + 1)K = 86 = 262144 mogucih rezultata. Minimum dvaju rezultata (ai)Ki =1 i (bi)Ki =1 
definiramo kao rezultat (min(ai, bi))Ki =1. Za niz (ai)Ki =1 reci cemo da dominira niz (bi)Ki =1 ako je ai  bi za svaki 1  i  K.
Trojke sa željenim svojstvom možemo prebrojiti tako da na sve moguce nacine odaberemo tri razlicita natjecatelja 
te ispitamo je li minimum rezultata prve dvojice jednak rezultatu trecega. Taj pristup ima složenost O(N3 · K) 
te je dovoljan za testne primjere u kojima vrijedi N  300.
U slucaju da se rezultat svakog natjecatelja sastoji iskljucivo od brojeva 0 i M, opisani pristup možemo 
ubrzati na sljedeci nacin. Rezultate pamtimo kao cijele brojeve u binarnom zapisu, pri cemu pojavljivanja
broja M zamjenjujemo brojem 1. Za svaki moguci rezultat najprije prebrojimo koliko se puta pojavljuje
u ulazu. Tada na sve moguce nacine odaberemo tri rezultata takva da je treci jednak minimumu prvih
dvaju te množenjem odgovarajucih brojaca izracunamo koliko ima trojki natjecatelja koji imaju upravo te
rezultate. Pritom treba paziti da brojimo samo one trojke u kojima su svi natjecatelji razliciti. Buduci da
imamo svega 2K mogucih rezultata, ovaj pristup ima složenost O(N + 23K · K). On se lako može ubrzati
do složenosti O(N + 22K · K) ukoliko iskoristimo zamjedbu da prva dva odabrana rezultata jedinstveno
odreuju treci, no to nije bilo nužno.
Pocetni pristup u opcenitom slucaju možemo ubrzati tako da, kada fiksiramo prva dva natjecatelja iz
trojke, rješenju pribrojimo broj natjecatelja ciji je rezultat jednak minimumu rezultatu odabrane dvojice.
Takav pristup podrazumijeva da smo prethodno za svaki moguci rezultat prebrojili koliko se puta on
pojavljuje u ulazu. To možemo efikasno uciniti tako da rezultate promatramo kao cijele brojeve zapisane
u sustavu s bazom M +1 te za svaki broj od 0 do (M +1)K −1 držimo odgovarajuci brojac. Na taj nacin
dobivamo algoritam složenosti O(N2 · K + (M + 1)K), što je dovoljno za testne primjere u kojima vrijedi N 3000.
Za sve bodove postupamo na obrnut nacin: na sve moguce nacine odaberemo treceg natjecatelja te brojimo
na koliko nacina možemo odabrati prva dva. U tu svrhu koristimo formulu ukljucivanja-iskljucivanja.
Preciznije, za fiksnog treceg natjecatelja C, oznacimo sa S skup svih ureenih parova (A,B) ostalih
natjecatelja koji su na svakom zadatku ostvarili više ili jednako bodova nego C, tj. ciji rezultati dominiraju
rezultat od C. Nadalje, za 1  i  K oznacimo sa Si skup parova iz S u kojima oba natjecatelja na
i-tom zadatku imaju strogo više bodova nego C. Tada je traženi broj parova jednak TKi=1 Sci,gdje jeSci = S \ Si komplement skupa Si u skupu S. 
Prema formuli ukljucivanja-iskljucivanja imamo K\i=1Sci=X{1,...,K}(−1)|I|\i2ISi,
stoga se problem svodi na odreivanje kardinalnosti skupa T i2I Si, za proizvoljan I  {1, . . . ,K}.
Oznacimo rezultat natjecatelja C s (ci)Ki =1 te indikatorsku funkciju skupa I s 1I (1I (i) = 1 ako je i 2 I te
1I (i) = 0 inace). Tada je lako vidjeti da vrijedi | T i2I Si| = v(v − 1), gdje je v broj natjecatelja razlicitih
od C koji su na i-tom zadatku ostvarili barem ci + 1I (i) bodova, za svaki 1  i  K.
Dakle, problem smo sveli na odreivanje, za svaki moguci rezultat, koliko natjecatelja ima rezultat koji
ga dominira. To možemo uciniti koristeci dinamicko programiranje i formulu ukljucivanja-iskljucivanja,
po analogiji s uobicajenim nacinom racunanja dvodimenzionalnih prefiks-suma. Preciznije, za fiksan
rezultat r = (ri)Ki =1, oznacimo s T skup natjecatelja ciji rezultat dominira r. Takoer, oznacimo s Ti skup
natjecatelja iz T koji na i-tom zadatku imaju strogo više od ri bodova. Tada je T disjunktna unija skupa
natjecatelja koji imaju rezultat r i skupa SK i=1 Ti. Po formuli ukljucivanja-iskljucivanja znamo da vrijedi
K[i=1Ti=XI{1,...,K}, I6=?(−1)|I|−1\i2ITi.
Primijetimo da je Ti2I Ti jednako broju natjecatelja koji su na i-tom zadatku ostvarili barem ri + 1I (i)
bodova, za svaki 1 i K. Iz tog se razloga prirodno namece sljedeci pristup. Neka je x = (xi)K i=1 niz
cijelih brojeva u intervalu [0,M + 1] te oznacimo s f(x) broj natjecatelja ciji rezultat dominira x. Ako x
nije rezultat, odnosno sadrži broj M + 1, tada je f(x) = 0. U suprotnome, iz gornjih zamjedbi slijedi
f(x) = g(x) + X I{1,...,K}, I6=? (−1)|I|−1f(x + 1I ),
gdje smo s g(x) oznacili broj natjecatelja s rezultatom jednakim x. Dakle, vrijednosti funkcije f možemo
izracunati dinamickim programiranjem. Uz pažljivu implementaciju, ukupna složenost rješenja postaje
O(N + (M + 1)K · 2K). 

Za kraj, spomenimo još da je zadatak moguce riješiti i u boljoj složenosti O(N + (M + 1)K · K), koristeci
pristup slican tzv. SOS (eng. sum over subsets) dinamici. Razradu tog rješenja ostavljamo citateljici za
vježbu. */

typedef long long ll;
const int MAX = 1 << 18; // 2 na 19

int N;
int cnt[MAX];
vector <pair <int, int>> adj[MAX];

inline ll choose2(int n) {
    return (ll)n * (n - 1); }

int get_sevens(int x) {
    int res = 0;
    for (int i = 5; i >= 0; i--) {
        if (x % 8 == 7)
            res |= 1 << i;
        x /= 8; }
    return res; }

ll solve() {
    vector <int> trans;
    for (int i = 0; i < 1 << 6; i++) {
        int tmp = 0;
        for (int j = 0; j < 6; j++)
            tmp = 8 * tmp + (i >> j & 1);
        trans.push_back(tmp); }
    for (int i = 0; i < MAX; i++) {
        int mask = get_sevens(i);
        for (int j = 1; j < 1 << 6; j++)
            if (!(mask & j))
                adj[i].push_back({i + trans[j], __builtin_popcount(j) % 2 ? -1 : 1}); }
    ll sol = 0;
    for (int i = MAX - 1; i >= 0; i--) {
        int tmp = cnt[i];
        for (auto it : adj[i])
            cnt[i] -= it.second * cnt[it.first];
        ll pairs = choose2(cnt[i] - 1);
        for (auto it : adj[i])
            pairs += it.second * choose2(cnt[it.first]);
        sol += tmp * pairs; }
    return sol; }

int main() {
    scanf("%d", &N);
    while (N--) {
        int mask = 0;
        for (int i = 0; i < 6; i++) {
            int x; scanf("%d", &x);
            mask = 8 * mask + x; }
        cnt[mask]++; }
    printf("%lld\n", solve());
    return 0; }