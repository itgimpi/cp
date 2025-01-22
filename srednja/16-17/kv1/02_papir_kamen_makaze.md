---
hide:
  - toc
---

# 2 - Papir, kamen, makaze

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 1000ms | 64MB |

Neša i Luka na časovima informatike najviše vole da igraju poznatu igru **"papir, kamen, makaze"**. Nakon 1024 odigrane partije Nešu su bolele ruke i igra mu je dosadila, a čas je još uvek trajao. Zbog toga je odlučio da osmisli svoju, malo komplikovaniju verziju ove igre.

U Nešinoj verziji on je napadač i ima vojsku sačinjenu od tri divizije: $Na$ vojnika koji za borbu koriste papir (da zbune protivnika), $Nb$ vojnika koji su spretni u bacanju kamenja, i $Nc$ vojnika kojima su oružje makaze. Lukin cilj u igri je da se odbrani i njegova vojska izgleda slično: $La$ vojnika u "papir" diviziji, $Lb$ vojnika u "kamen" diviziji i $Lc$ vojnika u "makaze" diviziji. 

Luka treba da rasporedi svoju vojsku tj. da **za svakog svog vojnika odredi sa kojom Nešinom divizijom će se boriti**, tako da što više Nešinih vojnika bude poraženo. Pri tome važe sledeća pravila koja se odnose na Lukinu "papir" diviziju:

* Ako se **jedan** Lukin vojnik iz "papir" divizije bori sa Nešinom "kamen" divizijom, može da porazi **dva** vojnika. 
* Ako se **jedan** Lukin vojnik iz "papir" divizije bori sa Nešinom "papir" divizijom, može da porazi **jednog** vojnika.
* Ako se **dva** Lukina vojnika iz "papir" divizije bore sa Nešinom "makaze" dizivijom, mogu da poraze **jednog** vojnika.

Iz pravila se vidi (iako je to poznata činjenica) da je papir jači od kamena a slabiji od makaza. Analogna pravila važe i za druge dve Lukine divizije: kamen je jači od makaza a slabiji od papira, makaze su jače od papira a slabije od kamena.

Pošto nije pratio na času, Luka ne ume sam da dođe do najboljeg rasporeda, pa mu treba vaša pomoć. Koji je najveći broj Nešinih vojnika koje on može da porazi?

## Opis ulaza
U prvoj liniji standardnog ulaza nalaze se tri nenegativna cela broja: $Na$ - broj Nešinih vojnika u "papir" diviziji, $Nb$ - broj Nešinih vojnika u "kamen" diviziji, $Nc$ - broj Nešinih vojnika u "makaze" diviziji. U drugoj liniji standardnog ulaza nalaze se tri nenegativna cela broja: $La$ - broj Lukinih vojnika u "papir" diviziji, $Lb$ - broj Lukinih vojnika u "kamen" diviziji, $Lc$ - broj Lukinih vojnika u "makaze" diviziji.

## Opis izlaza
U prvom i jedinom redu standardnog izlaza ispisati jedan nenegativan ceo broj koji predstavlja maksimalan broj Nešinih vojnika koje Luka može da porazi.

## Primer 1
### Ulaz
```
21 20 30
10 17 10
```

### Izlaz
```
71
```

## Primer 2
### Ulaz
```
1 1 3
0 4 0
```

### Izlaz
```
4
```

## Objašnjenje primera
U prvom primeru Luka može da porazi celu Nešinu vojsku ako svoje vojnike rasporedi na sledeći način: 

* Svih 10 vojnika iz njegove "papir" divizije se bori sa Nešinom "kamen" divizijom.
* 15 vojnika iz njegove "kamen" divizije se bori sa Nešinom "makaze" divizijom.
* 2 vojnika iz njegove "kamen" divizije se bore sa Nešinom "papir" divizijom.
* Svih 10 vojnika iz njegove "makaze" divizije se bori sa  Nešinom "papir" divizijom.

U drugom primeru Luka može da porazi najviše 4 Nešina vojnika. Jedan od rasporeda kojim je ovo moguće postići:

* 2 vojnika iz njegove "kamen" divizije se bore sa Nešinom "makaze" divizijom.
* 1 vojnik iz njegove "kamen" divizije se bori sa Nešinom "kamen" divizijom.
* 1 vojnik iz njegove "kamen" divizije se ne bori.

## Ograničenja
* $0 \leq Na, Nb, Nc, La, Lb, Lc \leq 10^8$.

Test primeri su podeljeni u četiri disjunktne grupe:

* U test primerima koji vrede 15 poena najviše jedan od $Na, Nb, Nc$ je različit od nule.
* U test primerima koji vrede 15 poena najviše jedan od $La, Lb, Lc$ je različit od nule.
* U test primerima koji vrede 15 poena važi $0 \leq Na, Nb, Nc, La, Lb, Lc \leq 10$.
* U test primerima koji vrede 55 poena nema dodatnih ograničenja.

#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Dimitrije Erdeljan | Nikola Jovanović | Aleksandar Višnjić | Nikola Spasić |

## Prvi podzadatak:
Kako je najviše jedna Nešina divizija po broju različita od $0$, to nije bitno kako je napadamo pošto će na kraju biti isti broj vojnika poraženo. Potrebno je samo implementirati ovo.

## Drugi podzadatak:
Zadatak pristupamo pohlepno. Lukina jedina divizija prvo napada Nešinu protiv koje on ima prednost. Zatim, ako preostane vojnika, napada onu protiv koje gubi jednak broj vojnika. Na kraju, ako opet ostane vojnika, napada Nešinu diviziju protiv koje nema prednost.

## Glavno rešenje:
Slično kao ranije, odvija se $3$ koraka, u svakom po $3$ borbe. Prvo, sve Lukine divizije se prvo bore protiv onih prema kojima imaju prednost. Zatim, $3$ borbe se odvijaju između divizija jednakih snaga. Na kraju se Lukine divizije bore protiv Nešinih prema kojima nemaju prednost.

``` cpp title="02_papir_kamen_makaze.cpp" linenums="1"
#include <bits/stdc++.h>

using namespace std;

int n[3], l[3];

int Stage2()
{
	int neutral[3];
	int score = 0;
	for(int i = 0; i <= 2; i++)
	{
		neutral[i] = min(l[i], n[i]);
		score += neutral[i];
	}
	for(int i = 0; i <= 2; i++)
	{
		int j = (i + 2) % 3;
		int bad = min((l[i] - neutral[i]) / 2, (n[j] - neutral[j]));
		score += bad;
	}
	return score;
}

int Branch(int i)
{
	if(i == 3)
	{
		return Stage2();
	}
	int score_stage2 = Branch(i + 1);
	int j = (i + 1) % 3;
	if(l[i] > 0 && n[j] == 1)
	{
		l[i]--;
		n[j]--;
		score_stage2 = max(score_stage2, 1 + Branch(i + 1));
		l[i]++;
		n[j]++;
	}
	return score_stage2;
}

int main()
{
	scanf("%d %d %d", &n[0], &n[1], &n[2]);
	scanf("%d %d %d", &l[0], &l[1], &l[2]);
	int score = 0;
	for(int i = 0; i <= 2; i++)
	{
		int j = (i + 1) % 3;
		int good = min(l[i], n[j] / 2);
		l[i] -= good;
		n[j] -= good * 2;
		score += good * 2;
	}
	score += Branch(0);
	printf("%d\n", score);
	return 0;
}
```
