На столу је попуњена матрица димензије $n\ m$. На столу је и провидна матрица димензије $r\ s$. На столу је и празна матрица.
Провидна матрица се стави на прву тако да им се горња лева поља поклапају. Највећи елемент у провидној матрици иде горе лево у празној матрици. 

Провидна матрица се транслира у све могуће положаје и највећи број из ње иде у празну на позицију где почиње преклапање.

Како изгледа трећа матрица?

# Опис улаза
У првом реду су $n, m$, димензије прве матрице.
У следећих $n$ редова је $m$ целих бројева $a_{i,j}$, $a_{i,j}$ је број у  i-том реду и j-тој колони.
У задњем реду су $r, s$, димензије провидне матрице.

# Опис излаза
Трећа матрица.

# Пример 1
## Улаз
<pre>
3 3
1 1 2
2 3 4
4 3 2
3 3
</pre>

## Излаз
```
4
```

## Објашњење примера

Прва и празна су истих димензија, највећи број је 4.
# Пример 2
## Улаз
<pre>
3 3
1 1 2
2 3 4
4 3 2
2 1
</pre>
## Излаз
```
2 3 4
4 3 4
```
## Објашњење примера
Сви положаји провидне матрице:

$\color{red}112\ \ \ 1\color{red}12\ \ \ 11\color{red}2$<br>
$\color{red}234\ \ \ 2\color{red}34\ \ \ 23\color{red}4$ <br>
$432\ \ \ 432\ \ \ 432$<br><br>
$112\ \ \ 112\ \ \ 112$<br>
$\color{red}234\ \ \ 2\color{red}34\ \ \ 23\color{red}4$ <br>
$\color{red}432\ \ \ 4\color{red}32\ \ \ 43\color{red}2$<br>
# Пример 3
## Улаз
<pre>
5 5
-1 -3 -4 -2 4
-8 -7 -9 -10 11
5 2 -8 -2 1
13 -3 -2 -6 -9
11 6 2 7 4
2 3
</pre>
## Излаз
```
-1 -2 11
5 2 11
13 2 1
13 7 7
```
# Ограничења:
$1 ≤ n,m ≤ 4000, |ai,j | ≤ 10000, 1 ≤ r ≤ n, 1 ≤ s ≤ m$ 

Примери су подељени у 4 дисјунктне групе:<br>
* У тест примерима вредним 10 поена: n,m ≤ 40, r = n, s = m.
* У тест примерима вредним 10 поена: n,m ≤ 40.
* У тест примерима вредним 20 поена: n,m ≤ 1 000.
* У тест примерима вредним 60 поена нема додатних ограничења.