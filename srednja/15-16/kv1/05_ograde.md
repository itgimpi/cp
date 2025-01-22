---
hide:
  - toc
---

# 5 - Ograde

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |


Pre oko dvadeset hiljada godina, praistorijski ljudi (pećinci) su usavršili veštinu izrade drvenih ograda kako bi zadržali dobre stvari blizu sebe i loše stvari daleko od sebe. Pećinac Dimitrije je stručnjak u izradi konveksnih ograda (pećincima nikada nije bilo jasno šta ovo znači) i svima je poznato da on pravi najbolje ograde u plemenu. Najveći neprijatelj pećinačkih ograda su džinovski praistorijski crvi. Džinovski praistorijski crvi imaju naviku da s vremena na vreme izađu na površinu zemlje i krenu ka severu ili ka jugu rušeći sve pred sobom pre nego što se vrate pod zemlju. Dimitrije je upravo dobio poruku od Pećinca Njuškala da su prethodne noći džinovski praistorijski crvi opet izronili na površinu i potencijalno uništili jednu od Dimitrijevih ograda. Zajedno sa ovom porukom dobio je i sve putanje džinovskih praistorijskih crva prethodne noći. Dimitrija sada interesuje koliko stabala sekvoje on mora da poseče u strašnoj šumi, ako se zna da je za svaki uništeni segment ograde potrebno po jedno stablo sekvoje. On vas moli da mu vi kažete minimalan broj ovih stabala kako bi on proveo što manje vremena u strašnoj šumi.

## Opis ulaza
 Prva linija standardnog ulaza sadrži prirodan broj $N$ - broj segmenata od kojih je Dimitrijeva ograda izgrađena. Narednih $N$ linija sadrže po 2 cela broja $x_i$ i $y_i$ koji označavaju krajeve svih segmenata ograde (dati su redom u smeru kazaljke na satu i uvek formiraju konveksni mnogougao), tj $i$-ti segment počinje na poziciji $(x_i,y_i)$ i završava se na poziciji (xi+1,yi+1) pri čemu $N$-ti segment počinje na poziciji $(x_N ,y_N)$ i završava se na poziciji $(x_1,y_1)$. Naredna linija sadrži broj $M$ - broj putanja džinovskih praistorijskih crva. Narednih $M$ linija sadrže po 3 cela broja $a_i , p_i$ i $k_i$ koji opisuju kretanje jednog od džinovskih praistorijskih crva tj. da se crv kretao između tačaka $(a_i,p_i)$ i $(a_i,k_i)$. Segment ograde se smatra uništenim ako se u bar jednoj tački seče sa putanjamadžinovskih praistorijskih crva, dakle ako crvi prođu kroz zajedničku tačku dva segmenta, oba segmenta se smatraju uništenima. Takođe, ako crvi izađu na površinu tačno na mestu gde je ograda, ili se vrate nazad u zemlju u tački koja pripada segmentu ograde, taj segment se takođe smatra srušenim. Krajevi segmenata ograde zadovoljavaju uslov da nikoja tri nisu kolinearna.

## Opis izlaza
Prva i jedina linija izlaza treba da sadrži tačno jedan ceo broj - broj stabala koji Dimitrije mora da poseče u strašnoj šumi.

## Primer 1
### Ulaz
```
-11 0
-8 2
-3 4
6 3
8 2
11 0
-1 -4
3
3 2 -3
-5 -4 8
0 8 1
```

### Izlaz
```
4
```


## Objašnjenja primera
U prvom primeru su uništena 4 segmenta: segment sa krajnjim tačkama u (-3, 4) i
(-8, 2), segment sa krajnjim tačkama u (-11, 0) i (-1, -4), segment sa krajnjim tačkama (-1, -4) i (11,0), kao i segment sa krajnjim tačkama (6, 3) i (-3, 4).

## Ograničenja

* $3 ≤ N ≤ 10^5$
* $1 ≤ M ≤ 10^5$
* $−10^7 ≤ x_i, y_i, a_i, p_i, k_i ≤ 10^7$


## Napomena
Test primeri su podeljeni u 3 grupe:

* u 20% test primera ograda će biti u obliku jednakokrakog pravouglog trougla čija je hipotenuza paralelna x osi ili u obliku kvadrata čije su stranice zarotirane za 45◦ u odnosu na koordinatne ose
* u 40% test primera važiće da je $N · M ≤ 10^6$
* ostali primeri nemaju ograničenja

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Demjan Grubić | Lazar Milenković | Aleksandar Višnjić | Demjan Grubić |

## Prvi i drugi podzadatak:
Za svakog crva i ogradu proveravamo da li je taj crv uništio tu ogradu, odnosno da li se njihove duži seku. To je moguće uraditi preko mešovitog proizvoda vektora, odnosno orijentacije trougla. Duži $AB$ i $CD$ se seku akko trouglovi $ABC$ i $ABD$ imaju suprotnu orijentaciju. Složenost je $O(N\cdot M)$.

## Glavno rešenje:
Sortiramo sve crve po $x$ koordinati i segmente ograde podelimo u dva sortirana niza (isto po $x$ koordinati levog kraja) - "gornji omotač" i "donji omotač". Zadatak rešavamo prvo za jedan, pa onda za drugi omotač. To radimo tehnikom ***two pointers***. Za svaki segment ograde odredimo koji crvi zadovoljavaju to da se njihova $x$ koordinata nalazi između $x$ koordinata krajeva segmenta. Nakon toga, imamo skup crva koji mogu seći dati segment. Ostalo je to još samo proveriti. Složenost je $O(NlogN)$ zbog sortiranja i zato što po svakom crvu prolazimo najviše $4N$ puta.



``` cpp title="05_ograde.cpp" linenums="1"
#include <iostream>
#include <fstream>

using namespace std;

const int MAXN = 100000;
const int MAXQ = 100000;

int sign(long long x)
{
    if (x == 0)
    {
        return 0;
    }
    return x < 0 ? -1 : 1;
}

bool intersects(pair<int, pair<int, int>> segment, long long x1, long long y1, long long x2, long long y2)
{
    if (x1 < x2 && (segment.first < x1 || segment.first > x2))
    {
        return false;
    }
    if (x2 < x1 && (segment.first < x2 || segment.first > x1))
    {
        return false;
    }
    int sign1 = sign((y2 - y1) * (segment.first - x1) - (segment.second.first - y1) * (x2 - x1));
    int sign2 = sign((y2 - y1) * (segment.first - x1) - (segment.second.second - y1) * (x2 - x1));
    return sign1 != sign2;
}

int main(int argc, char *argv[])
{
    string inFileName = argv[1];
    string outFileName = inFileName.substr(0, inFileName.length() - 3) + ".out";
    fstream ifs, ofs;
    ifs.open(inFileName, fstream::in);
    ofs.open(outFileName, fstream::out);
    int n;
    ifs >> n;
    int x[MAXN], y[MAXN];
    pair<int, pair<int, int>> segments[MAXQ];
    int st = 0, ed = 0;
    for (int i = 0; i < n; i++)
    {
        ifs >> x[i] >> y[i];
        if (x[i] < x[st])
        {
            st = i;
        }
        if (x[i] > x[ed])
        {
            ed = i;
        }
    }
    int q;
    ifs >> q;
    for (int i = 0; i < q; i++)
    {
        ifs >> segments[i].first >> segments[i].second.first >> segments[i].second.second;
    }
    sort(segments, segments + q);
    int ret = 0;
    for (int i = st, idx = 0, save = 0; i != ed; i = (i + 1) % n)
    {
        int j = (i + 1) % n;
        int valid = save;
        save = 0;
        while (segments[idx].first <= x[j])
        {
            if (idx < q && intersects(segments[idx], x[i], y[i], x[j], y[j]))
            {
                if (segments[idx].first == x[j])
                {
                    save = 1;
                }
                valid = 1;
            }
            idx++;
        }
        ret += valid;
    }
    for (int i = ed, idx = q - 1, save = 0; i != st; i = (i + 1) % n)
    {
        int j = (i + 1) % n;
        int valid = save;
        save = 0;
        while (idx >= 0 && segments[idx].first >= x[j])
        {
            if (intersects(segments[idx], x[i], y[i], x[j], y[j]))
            {
                if (segments[idx].first == x[j])
                {
                    save = 1;
                }
                valid = 1;
            }
            idx--;
        }
        ret += valid;
    }
    ofs << ret << endl;
    //cerr << inFileName << " " << 1.0 * ret / n << endl;
    ifs.close();
    ofs.close();
    return 0;
}
```
