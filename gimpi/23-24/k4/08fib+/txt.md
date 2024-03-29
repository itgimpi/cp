Фибоначијев хор је низ: $x1 = a1, x2 = a2, \dots xk = ak, x_n = x_{n-1}\oplus x_{n-2} \oplus \dots \oplus x_{n-k}, n > k$

Треба да се одреди вредност од леве до десне границе $x_l \oplus x_{l+1} \oplus \dots  \oplus  x_{r-1} \oplus {x_r}$. $q$ пута.


# Опис улаза

У првом реду је $k$.
У следећем реду је $k$ бројева, првих $k$ бројева Фибоначијевог хора.
У следећем реду је $q$, број упита.
У следећих $q$ редова је по два броја, $l_i, r_i$, лева и десна граница.


# Опис излаза
$q$ одговора на $q$ упита у $q$ редова.

# Пример 1
## Улаз
<pre>
4
1 3 5 7
3
2 2
2 5
1 5
</pre>

## Излаз
```
3
1
0
```
## Објашњење примера
$k=4, x_1=1, x_2=3, x_3=5, x_4=7$

$a5 (n=5) = x4 \oplus x3 \oplus x2 \oplus x1(од n-1 до n-k) = 0$

$l=2, r=2, x_2=3$

$l=2, r=5, x_2 \oplus x_3 \oplus x_4 \oplus x_5 = 3 \oplus 5 \oplus 7 \oplus 0 = 1$

$l=1, r=5, x_1 \oplus x_2 \oplus x_3 \oplus x_4 \oplus x_5 = 1 \oplus 3 \oplus 5 \oplus 7 \oplus 0 = 1$

# Пример 2
## Улаз
<pre>
5
3 3 4 3 2
4
1 2
1 3
5 6
7 9
</pre>
## Излаз
```
0
4
7
4
```
## Објашњење примера

# Пример 3
## Улаз
<pre>

</pre>
## Излаз
1
# Ограничења:
$1 \le k \le 10^5, 1 \le q \le 10^5, 1 \le k \le l_i \le r_i \le 10^{18}, a_i \lt 10^{18}$

Примери су подељени у 3 дисјунктне групе:<br>
* У тест примерима вредним 20 поена: k, q, ai, li, ri ≤ 50000.
* У тест примерима вредним 30 поена: q ≤ 50000, ai ≤ 5000, li, ri ≤ 500000.
* У тест примерима вредним 50 поена нема додатних ограничења.