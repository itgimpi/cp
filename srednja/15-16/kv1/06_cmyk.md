---
hide:
  - toc
---

# 6 - CMYK

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1500ms | 512MB |


U vremenima neolitske Tajne Komisije, ljudi nisu mogli previše dobro da opišu koncept boje. Međutim, ono što se znalo je da je bela boja bila obožavana. Takođe, boje su bile mešane tako što se izvori te dve boje (uglavnom biljke) smrve toljagom i pomešaju—pošto različiti izvori imaju različita hemijska svojstva, ovo nije uvek garantovalo iste rezultate (npr. proizvod mešanja crvene i žute boje nije uvek narandžast).

Kao i u slučaju igre simbola, članovi savremene Tajne Komisije su uspeli da dođu do nekoliko nizova biljaka raznih boja iz tog perioda. Pretpostavka je da su tadašnji ljudi mogli samo da spajaju po dve susedne boje u nizu u jednu. Unajmljena je pomoć malog Davisa, poznatog (al)hemičara, da se ustanovi koje su sve kombinacije boja mogle da se dobiju mešanjem. Ispostavilo se, između
ostalog, da je redosled boja bitan (npr. mešanje plave i crvene ne mora biti isto kao mešanje crvene i plave), da je moguće da mešanje dve boje nema jedinstven rezultat, kao i da je moguće da neke dve boje ne možemo pomešati. Malog Pericu sada zanima da li je moguće dobiti samo nizove belih boja, prateći pravila koja je Davis generisao.

## Opis ulaza
U prvom redu standardnog ulaza nalazi se prirodan broj m, koji predstavlja broj pravila mešanja boja koje je mali Davis pronašao. U svakom od narednih m redova nalazi se po jedno pravilo, dato u formatu $XY$ -> $Z$ (gde su $X, Y$ i $Z$ velika slova engleske abecede), što znači da, ukoliko su nam boje $X$ i $Y$ susedne u nizu, možemo ih pomešati i dobiti boju $Z$ na tom mestu.
U narednom redu standardnog ulaza nalazi se prirodan broj $t$, koji predstavlja broj nađenih nizova boja, nakon čega je svaki niz zadat u dva reda; prvi red sadrži prirodan broj $n$, dužinu niza, a
drugi red sadrži niz od $n$ velikih slova engleske abecede, koji predstavlja sam niz boja.

## Opis izlaza
Za svaki od $t$ nizova, ispisati u zasebnom redu standardnog izlaza ili “YES” ili “NO” (bez navodnika), u zavisnosti od toga da li je moguće doći od početnog niza do niza u kome su sveboje bele (W).

## Primer 1
### Ulaz
```
2
RG -> B
BB -> W
2
9
RGBRGBRGB
4
RGBB
```

### Izlaz
```
YES
NO
```

## Objašnjenja primera
U prvom nizu možemo odraditi sledeće transformacije: RGBRGBRGB -> BBRGBRGB -> BBBBRGB -> BBBBBB -> WBBBB -> WWBB -> WWW, čime dobijamo niz samo bele boje. U drugom nizu moguće je doći do niza WB ili BW, posle čega nije moguće vršiti dalje transformacije.

## Ograničenja

* $1 ≤ m ≤ 100$
* $1 ≤ n ≤ 100$
* $1 ≤ t ≤ 10$
* Svi nizovi će sadržati samo velika slova engleske abecede.

## Napomena
Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima vrednim 20 poena važiće $m ≤ 15, n ≤ 10$.
* U test primerima vrednim 20 poena važiće $m ≤ 15$.
* U test primerima vrednim 25 poena važiće $m ≤ 75, n ≤ 75$.
* U test primerima vrednim 35 poena nema dodatnih ograničenja.

## Napomena 2
Moguće je da pravila mešanja za neke dve boje nisu jedinstvena, npr. moguće je
prisustvo XY -> Z i XY -> W u istom skupu pravila.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Petar Veličković | Nikola Jovanović | Nikola Jovanović | Petar Veličković |

Rešenje možete naći na sledećem linku: 

``` cpp title="06_cmyk.cpp" linenums="1"
// RandomUsername (Nikola Jovanovic)
// Quals 2016
// CMYK cyk tiles

#include <bits/stdc++.h>
using namespace std;

// symbols: 'A'..'Z'
const int MAX_STRING_LEN = 105, MAX_SYMBOLS = 30, MAX_GRAMMAR_SZ = 105, MAX_RULE_LEN = 10;

struct productionRule
{
    int L, R1, R2;
};

// vars
int testCases, stringLen, grammarSz, symbolNo;
char str[MAX_STRING_LEN];
bool DP[MAX_STRING_LEN][MAX_STRING_LEN][MAX_SYMBOLS]; // DP[length][index][symbol]
productionRule grammar[MAX_STRING_LEN];

// input vars
char temp[MAX_RULE_LEN];
char L, R1, R2;

// parts of the string that can be formed from a single 'W'
vector< pair<int, int> > blocks;
// parts of the string that can be tiled using 'W' chars
bool tiled[MAX_STRING_LEN];

// sort by the endpoints
bool compair(pair<int, int> a, pair<int, int> b)
{
    return (a.second == b.second) ? (a.first < b.first) : (a.second < b.second);
}

void solveCYK()
{
    // init
    for(int l = 1; l <= stringLen; l++)
    {
        for(int i = 1; i <= stringLen; i++)
        {
            for(int symb = 0; symb <= symbolNo; symb++)
            {
                if(l == 1)
                {
                    DP[l][i][symb] = (symb == (str[i] - 'A'));
                }
                else
                {
                    DP[l][i][symb] = false;
                }
            }
            if(DP[l][i]['W' - 'A'])
            {
                blocks.push_back({i, i});
            }
        }
    }

    // actual DP
    for(int l = 2; l <= stringLen; l++)
    {
        for(int i = 1; i <= stringLen - l + 1; i++)
        {
            for(int k = 1; k <= l - 1; k++)
            {
                for(int idx = 1; idx <= grammarSz; idx++)
                {
                    // s[i..i+l-1] (L) -> s[i..i+k-1] (R1) + s[i+k..stringLen] (R2)
                    DP[l][i][ grammar[idx].L ] |= DP[k][i][ grammar[idx].R1 ] & DP[l-k][i+k][ grammar[idx].R2 ];
                }
            }
            if(DP[l][i]['W' - 'A'])
            {
                blocks.push_back({i, i + l - 1});
            }
        }
    }
}

void SolveTiling()
{
    tiled[0] = true;
    for(int i = 1; i <= stringLen; i++)
    {
        tiled[i] = false;
    }
    sort(blocks.begin(), blocks.end());
    for(int i = 0; i < blocks.size(); i++)
    {
        tiled[ blocks[i].second ] |= tiled[ blocks[i].first - 1 ];
    }
}

int main()
{
    double start = clock();
    // input
    symbolNo = 25;
    scanf("%d", &grammarSz);
    for(int i = 1; i <= grammarSz; i++)
    {
        scanf("\n%c%c -> %c", &R1, &R2, &L);
        grammar[i] = { (L - 'A'), (R1 - 'A'), (R2 - 'A') };
    }
    scanf("%d", &testCases);
    for(int tc = 1; tc <= testCases; tc++)
    {
        blocks.clear();
        scanf("%d", &stringLen);
        scanf("%s", str+1);
        // CYK
        solveCYK();
        // we have to tile the string using blocks
        SolveTiling();
        printf("%s\n", tiled[stringLen] ? "YES" : "NO" );
    }
    double stop = clock();
    fprintf(stderr, "Time: %.2f\n", (stop - start) / CLOCKS_PER_SEC);
    return 0;
}

```
