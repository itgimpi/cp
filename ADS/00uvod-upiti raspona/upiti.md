https://petlja.org/biblioteka/r/Zbirka2/01%20slozenost/04%20prefiksni_zbirovi_i_razlike_susednih

**Statički upiti raspona**

Dat je niz od n celih brojeva. Slede q upita tipa, koji je zbir brojeva u opsegu od donje do gornje granice?

Dva cela broja n i q, broj elemenata i upita.
U drugom redu je n celih, x1, x2, …, xn, elementi niza.
q redova sa upitima. U svakom redu su dva broja, a i b. Koji je zbir u opsegu [a,b]?

$1 \le n, q \le 2\cdot10^5,$
$1 ≤ x_i ≤ 10^9,$
$1 ≤ a ≤ b ≤n$

Reši q upita u q redova.

https://www.hackerrank.com/contests/efikasnost/challenges/staticki-upit-raspona

BF
BF подразумева да се бројеви учитају у низ, и за сваки упит рачуна збир одговарајућег сегмента низа.
``` cpp title="bf" linenums="1"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; cin >> n;   // ucitavamo niz
    vector<int> brojevi(n);
    for (int i = 0; i < n; i++)
        cin >> brojevi[i];
    
    // ucitavanje granica segmenata i racunanje zbirova
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        int zbir = 0;
        for (int j = a; j <= b; j++)
            zbir += brojevi[j];
        cout << zbir << endl;   }
    return 0; }
```
Сложеност оваквог приступа је O(nq).

Пошто се фаза учитавања и исписа података преплићу, учитавање и испис треба додатно убрзати, али то не може поправити неефикасност овог наивног алгоритма.

**Збирови префикса**

Једноставно ефикасно решење је засновано на идеји: уместо чувања елемената низа, чува се низ збирова префикса низа. Збир сваког сегмента [l, d] може да серазложи на разлику збира префикса до елемента d и префикса до елемента l−1.

```
На пример за низ:  2, 13,  0,  3, -5,  6
префиксне суме су: 2, 15, 15, 18, 13, 19
```
Сад је лако да се одреди збир од леве до десне границе збира.
Збирови свих префикса се могу израчунати и сместити у додатни (ако је уштеда меморије битна, онда у оригинални) низ. Дакле, током учитавања елемената се формира низ збирова префикса (рачунају се их инкрементално, јер се сваки наредни збир префикса добија увећавањем претходног збира префикса за текући елемент низа). Нека zi означава збир елемената префикса одређеног позицијама из интервала [0,i). Формирамо, дакле, низ zi=∑i−1k=0ak (при чему је z0=0, збир празног префикса). Тада збир елемената у сегменту позиција [l,d] израчунавамо као zd+1−zl.

``` cpp title="src.cpp" linenums="1"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> zbirovi_prefiksa(n+1);
    zbirovi_prefiksa[0] = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        zbirovi_prefiksa[i+1] = zbirovi_prefiksa[i] + x; }

    // za granice segmenata se racunaju i ispisuju njihovi zbirovi
    int q; cin >> q;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        cout << zbirovi_prefiksa[b+1] - zbirovi_prefiksa[a] << '\n'; }
  
  return 0; }
```

За учитавање бројева и формирање низа збирова префикса потребно је O(n) корака. Након оваквог претпроцесирања, збир сваког сегмента се може израчунати у времену O(1), па је укупна сложеност O(n+q).

Пошто се у овом задатку преплићу фаза учитавања и фаза исписа података на стандардни улаз и излаз, потребно је обратити пажњу на неефикасност која настаје због честог пражњења излазног бафера. Потребно је развезати cin и cout коришћењем cin.tie(0) и уместо помоћу endl у нови ред прелазити помоћу \n. Ово има смисла само у случају аутоматске примене програма на велике улазе и излазе - овим изменама програм престаје да ради коректно у интерактивном режиму.