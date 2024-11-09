Видели смо да низ збирова префикса, омогућава ефикасно постављање упита над сегментима низа, али не омогућава ефикасно ажурирање елемената низа, јер је потребно ажурирати све збирове префикса након ажурираног елемента, што је нарочито неефикасно када се ажурирају елементи близу почетка низа (сложеност најгорег случаја је $O(n)$. Низ разлика суседних елемената допушта стална ажурирања низа, међутим, извршавање упита очитавања стања низа подразумева реконструкцију низа, што је сложености $O(n).$

Разматраћемо проблеме у којима је потребно да се упити ажурирања низа и очитавања његових статистика јављају испреплетано. За разлику од претходних, статичких упита над распонима (енгл. static range queries), овде ћемо разматрати тзв. _динамичке упите над распонима_ (енгл. dynamic range queries), тако да је потребно развити напредније структуре података које омогућавају извршавање оба типа упита ефикасно. На пример, размотримо прoблем имплементације структуре података која обезбеђује ефикасно израчунавање збирова сегмената датог низа одређених интервалима позиција $[a, b]$, при чему се појединачни елементи низа могу често мењати.

У наставку ћемо видети две различите, али донекле сличне структуре података које дају ефикасно решење претходног проблема и њему сличних.

Једна структура података која омогућава прилично једноставно и ефикасно решавање овог проблема су _сегментна дрвета_. Опет се током фазе препроцесирања израчунавају збирови одређених сегмената полазног низа, а онда се збир елемената произвољног сегмента полазног низа изражава у функцији тих унапред израчунатих збирова.Рецимо и да сегментна дрвета нису специфична само за сабирање, већ се могу користити и за друге статистике сегмената које се израчунавају асоцијативним операцијама (на пример за одређивање најмањег или највећег елемента, нзд-а свих елемената и слично).

Претпоставимо да је дужина низа степен броја 2 (ако није, низ се може допунити до најближег степена броја 2, најчешће нулама). Чланови низа представљају листове дрвета. Групишемо два по два суседна чвора и на сваком наредном нивоу дрвета чувамо родитељске чворове који чувају збирове своја два детета. Ако је дат низ $(3, 4, 1, 2, 6, 5, 1, 4)$, сегментно дрво за збирове изгледа овако.
```
              26
      10              16
  7       3       11      5
3   4   1   2   6   5   1   4
```
Пошто је дрво потпуно, најједноставнија имплементација је да се чува имплицитно у низу (слично као у случају хипа). Претпоставићемо да елементе дрвета смештамо од позиције $1$, јер је тада аритметика са индескима мало једноставнија (елементи полазног низа могу бити индексирани класично, кренувши од нуле).
```
0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
-  26 10 16 7  3  11 5  3  4  1  2  6  5  1  4 
```
Уочимо неколико карактеристика овог начина смештања. Корен је смештен на позицији 1. Елементи полазног низа налазе се на позицијама $[n,2n-1]$. Елемент који се у полазном низу налази на позицији $p$, се у сегментном дрвету налази на позицији $p+n$. Лево дете чвора $k$ налази се на позицији $2k$, а десно на позицији $2k+1$. Дакле, на парним позицијама се налазе лева деца својих родитеља, а на непарним десна. Родитељ чвора $k$ налази се на позицији $(\lfloor{\frac{k}{2}}\rfloor)$.

Размотримо сада како бисмо нашли збир елемената на позицијама из сегмента $[2, 6]$, тј. збир елемената $1, 2, 6, 5, 1$. У сегментном дрвету тај сегмент је смештен на позицијама $[2+8, 6+8] = [10,14]$. Збир прва два елемента $1, 2$ се налази у чвору изнад њих, збир наредна два елемента $6, 5$ такође, док се у родитељском чвору елемента $1$ налази његов збир са елементом $4$, који не припада сегменту који сабирамо. Зато збир елемената на позицијама $[10, 14]$ у сегментном дрвету можемо разложити на збир елемената на позицијама $[5, 6]$ и елемента на позицији $14$.

Размотримо и како бисмо рачунали збир елемената на позицијама из сегмента $[3, 7]$, тј. збир елемената $2, 6, 5, 1, 4$. У сегментном дрвету тај сегмент је смештен на позицијама $[3+8, 7+8] = [11, 15]$. У родитељском чвору елемента $2$ налази се његов збир са елементом $1$ који не припада сегменту који сабирамо. Збирови елемената $6$ и $5$ и елемената $1$ и $4$ се налазе у чворовима иза њих, а збир сва четири дата елемента у чвору изнад њих.

Уместо операције којом се мења члану низа на позицији $i$ додељује вредност $v$, често се разматра функција која елемент низа на позицији $i$ полазног низа увећава за дату вредност $v$ и у складу са тим ажурира сегментно дрво. Свака од ове две функције се лако изражава преко оне друге.

Имплементација сегментног дрвета за друге асоцијативне операције је скоро идентична, осим што се оператор `+` мења другом операцијом.

https://petlja.org/biblioteka/r/Zbirka3/00%20napredne_strukture_podataka/03%20upiti_raspona/02%20segmentna_stabla

<h1 id="суме-сегмената-променљивог-низа">Суме сегмената променљивог
низа</h1>
<p>Напиши програм који израчунава збирове датих сегмената низа
(поднизова узастопних елемената), при чему се током рада програма
поједини елементи низа могу мењати.</p>
<h2 id="улаз">Улаз</h2>
<p>У првој линији стандардног улаза налази се број <span
class="math inline">\(n\)</span> (<span class="math inline">\(1 \leq n
\leq 100000\)</span>), а у наредној линији низ од <span
class="math inline">\(n\)</span> елемената (елементи су цели бројеви
између 0 и 10, раздвојени са по једним размаком). У наредној линији
налази се број <span class="math inline">\(m\)</span> (<span
class="math inline">\(1 \leq m \leq 100000\)</span>), а у наредних <span
class="math inline">\(m\)</span> линија упити. Подржане су две врсте
упита:</p>
<ul>
<li><code>p</code> <span class="math inline">\(i\)</span> <span
class="math inline">\(v\)</span> – извршавање овог упита подразумева да
се у низ на позицију <span class="math inline">\(i\)</span> упише
вредност <span class="math inline">\(v\)</span> (<span
class="math inline">\(0 \leq i &lt; n\)</span>, <span
class="math inline">\(0 \leq v \leq 10\)</span>).</li>
<li><code>z</code> <span class="math inline">\(a\)</span> <span
class="math inline">\(b\)</span> – извршавање овог упита подразумева да
се израчуна и на стандардни излаз испише збир елемената низа који су на
позицијама <span class="math inline">\([a, b]\)</span>.</li>
</ul>
<h2 id="излаз">Излаз</h2>
<p>Стандардни излаз садржи резултате <code>z</code> упита (сваки у
посебној линији).</p>
<h2 id="пример">Пример</h2>
<h3 id="улаз-1">Улаз</h3>
<pre><div class='verbatim-text'>5
1 2 3 4 5
5
z 0 4
z 2 3
p 2 5
p 3 6
z 0 4</div></pre>
<h3 id="излаз-1">Излаз</h3>
<pre><div class='verbatim-text'>15
7
19</div></pre>

<h1 id="суме-сегмената-променљивог-низа---решење">Суме сегмената
променљивог низа - Решење</h1>
<!--- sol:ex2 --->
<p>Решење грубом силом подразумева да се одржава низ, да се упити
<code>p</code> извршавају директном променом елемената низа (то се ради
у <span class="math inline">\(O(1)\)</span>), а да се упити
<code>z</code> извршавају сабирањем елемената низа (то се ради у времену
<span class="math inline">\(O(n)\)</span>). Укупна сложеност таквог
приступа је <span class="math inline">\(O(mn)\)</span>.</p>
<div class="sourceCode" id="cb1"><pre
class="sourceCode cpp"><code class="sourceCode cpp"><span id="cb1-1"><a href="#cb1-1" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;iostream&gt;</span></span>
<span id="cb1-2"><a href="#cb1-2" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;vector&gt;</span></span>
<span id="cb1-3"><a href="#cb1-3" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;numeric&gt;</span></span>
<span id="cb1-4"><a href="#cb1-4" aria-hidden="true" tabindex=""></a></span>
<span id="cb1-5"><a href="#cb1-5" aria-hidden="true" tabindex=""></a><span class="kw">using</span> <span class="kw">namespace</span> std<span class="op">;</span></span>
<span id="cb1-6"><a href="#cb1-6" aria-hidden="true" tabindex=""></a></span>
<span id="cb1-7"><a href="#cb1-7" aria-hidden="true" tabindex=""></a><span class="dt">int</span> main<span class="op">()</span> <span class="op">{</span></span>
<span id="cb1-8"><a href="#cb1-8" aria-hidden="true" tabindex=""></a>  ios_base<span class="op">::</span>sync_with_stdio<span class="op">(</span><span class="kw">false</span><span class="op">);</span> cin<span class="op">.</span>tie<span class="op">(</span><span class="dv">0</span><span class="op">);</span></span>
<span id="cb1-9"><a href="#cb1-9" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n<span class="op">;</span></span>
<span id="cb1-10"><a href="#cb1-10" aria-hidden="true" tabindex=""></a>  cin <span class="op">&gt;&gt;</span> n<span class="op">;</span></span>
<span id="cb1-11"><a href="#cb1-11" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> niz<span class="op">(</span>n<span class="op">);</span></span>
<span id="cb1-12"><a href="#cb1-12" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> n<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb1-13"><a href="#cb1-13" aria-hidden="true" tabindex=""></a>    cin <span class="op">&gt;&gt;</span> niz<span class="op">[</span>i<span class="op">];</span></span>
<span id="cb1-14"><a href="#cb1-14" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> m<span class="op">;</span></span>
<span id="cb1-15"><a href="#cb1-15" aria-hidden="true" tabindex=""></a>  cin <span class="op">&gt;&gt;</span> m<span class="op">;</span></span>
<span id="cb1-16"><a href="#cb1-16" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> m<span class="op">;</span> i<span class="op">++)</span> <span class="op">{</span></span>
<span id="cb1-17"><a href="#cb1-17" aria-hidden="true" tabindex=""></a>    string upit<span class="op">;</span></span>
<span id="cb1-18"><a href="#cb1-18" aria-hidden="true" tabindex=""></a>    cin <span class="op">&gt;&gt;</span> upit<span class="op">;</span></span>
<span id="cb1-19"><a href="#cb1-19" aria-hidden="true" tabindex=""></a>    <span class="cf">if</span> <span class="op">(</span>upit <span class="op">==</span> <span class="st">&quot;p&quot;</span><span class="op">)</span> <span class="op">{</span></span>
<span id="cb1-20"><a href="#cb1-20" aria-hidden="true" tabindex=""></a>      <span class="dt">int</span> i<span class="op">,</span> v<span class="op">;</span></span>
<span id="cb1-21"><a href="#cb1-21" aria-hidden="true" tabindex=""></a>      cin <span class="op">&gt;&gt;</span> i <span class="op">&gt;&gt;</span> v <span class="op">&gt;&gt;</span> ws<span class="op">;</span></span>
<span id="cb1-22"><a href="#cb1-22" aria-hidden="true" tabindex=""></a>      niz<span class="op">[</span>i<span class="op">]</span> <span class="op">=</span> v<span class="op">;</span></span>
<span id="cb1-23"><a href="#cb1-23" aria-hidden="true" tabindex=""></a>    <span class="op">}</span> <span class="cf">else</span> <span class="cf">if</span> <span class="op">(</span>upit <span class="op">==</span> <span class="st">&quot;z&quot;</span><span class="op">)</span> <span class="op">{</span></span>
<span id="cb1-24"><a href="#cb1-24" aria-hidden="true" tabindex=""></a>      <span class="dt">int</span> a<span class="op">,</span> b<span class="op">;</span></span>
<span id="cb1-25"><a href="#cb1-25" aria-hidden="true" tabindex=""></a>      cin <span class="op">&gt;&gt;</span> a <span class="op">&gt;&gt;</span> b<span class="op">;</span></span>
<span id="cb1-26"><a href="#cb1-26" aria-hidden="true" tabindex=""></a>      cout <span class="op">&lt;&lt;</span> accumulate<span class="op">(</span>next<span class="op">(</span>begin<span class="op">(</span>niz<span class="op">),</span> a<span class="op">),</span> next<span class="op">(</span>begin<span class="op">(</span>niz<span class="op">),</span> b<span class="op">+</span><span class="dv">1</span><span class="op">),</span> <span class="dv">0</span><span class="op">)</span> <span class="op">&lt;&lt;</span> <span class="ch">&#39;</span><span class="sc">\n</span><span class="ch">&#39;</span><span class="op">;</span></span>
<span id="cb1-27"><a href="#cb1-27" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb1-28"><a href="#cb1-28" aria-hidden="true" tabindex=""></a>  <span class="op">}</span></span>
<span id="cb1-29"><a href="#cb1-29" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb1-30"><a href="#cb1-30" aria-hidden="true" tabindex=""></a><span class="op">}</span></span></code></pre></div>
<!--- sol:end --->
<!--- sol:ex0 --->
<p>Задатак можемо ефикасније решити ако збирове одржавамо у сегментном
дрвету. Операције над дрветом можемо реализовати навише (од листова
према корену).</p>
<p>Формирање сегментног дрвета на основу датог низа је веома
једноставно. Прво се елементи полазног низа прекопирају у дрво, кренувши
од позиције <span class="math inline">\(n\)</span>. Затим се сви
унутрашњи чворови дрвета (од позиције <span
class="math inline">\(n-1\)</span>, па уназад до позиције <span
class="math inline">\(1\)</span>) попуњавају као збирови своје деце (на
позицију <span class="math inline">\(k\)</span> уписујемо збир елемената
на позицијама <span class="math inline">\(2k\)</span> и <span
class="math inline">\(2k+1\)</span>). Сложеност ове операције је
очигледно линеарна у односу на дужину низа <span
class="math inline">\(n\)</span>.</p>
<p>За све унутрашње елементе сегмента смо сигурни да се њихов збир
налази у чворовима изнад њих. Једини изузетак могу да буду елементи на
крајевима сегмента. Ако је елемент на левом крају сегмента лево дете
(што је еквивалентно томе да се налази на парној позицији) тада се у
његовом родитељском чвору налази његов збир са елементом десно од њега
који такође припада сегменту који треба сабрати (осим евентуално у
случају једночланог сегмента). У супротном (ако се налази на непарној
позицији), у његовом родитељском чвору је његов збир са елементом лево
од њега, који не припада сегменту који сабирамо. У тој ситуацији, тај
елемент ћемо посебно додати на збир и искључити из сегмента који
сабирамо помоћу родитељских чворова. Ако је елемент на десном крају
сегмента лево дете (ако се налази на парној позицији), тада се у његовом
родитељском чвору налази његов збир са елементом десно од њега, који не
припада сегменту који сабирамо. И у тој ситуацији, тај елемент ћемо
посебно додати на збир и искључити из сегмента који сабирамо помоћу
родитељских чворова. На крају, ако се крајњи десни елемент налази у
десном чвору (ако је на непарној позицији), тада се у његовом
родитељском чвору налази његов збир са елементом лево од њега који
припада сегменту који сабирамо (осим евентуално у случају једночланог
сегмента). Пошто се у сваком кораку дужина сегмента <span
class="math inline">\([a, b]\)</span> полови, а она је у почетку сигурно
мања или једнака <span class="math inline">\(n\)</span>, сложеност ове
операције је <span class="math inline">\(O(\log{n})\)</span>.</p>
<p>Приликом ажурирања неког елемента потребно је ажурирати све чворове
на путањи од тог листа до корена. С обзиром да знамо позицију родитеља
сваког чвора и ова операција се може веома једноставно имплементирати.
Пошто се <span class="math inline">\(k\)</span> полови у сваком кораку
петље, а крећа од вредности највише <span
class="math inline">\(2n-1\)</span>, и сложеност ове операције је <span
class="math inline">\(O(\log{n})\)</span>.</p>
<div class="sourceCode" id="cb2"><pre
class="sourceCode cpp"><code class="sourceCode cpp"><span id="cb2-1"><a href="#cb2-1" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;iostream&gt;</span></span>
<span id="cb2-2"><a href="#cb2-2" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;algorithm&gt;</span></span>
<span id="cb2-3"><a href="#cb2-3" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;vector&gt;</span></span>
<span id="cb2-4"><a href="#cb2-4" aria-hidden="true" tabindex=""></a></span>
<span id="cb2-5"><a href="#cb2-5" aria-hidden="true" tabindex=""></a><span class="kw">using</span> <span class="kw">namespace</span> std<span class="op">;</span></span>
<span id="cb2-6"><a href="#cb2-6" aria-hidden="true" tabindex=""></a></span>
<span id="cb2-7"><a href="#cb2-7" aria-hidden="true" tabindex=""></a><span class="co">// najmanji stepen dvojke veci ili jednak od n</span></span>
<span id="cb2-8"><a href="#cb2-8" aria-hidden="true" tabindex=""></a><span class="dt">int</span> stepenDvojke<span class="op">(</span><span class="dt">int</span> n<span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-9"><a href="#cb2-9" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> s <span class="op">=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb2-10"><a href="#cb2-10" aria-hidden="true" tabindex=""></a>  <span class="cf">while</span> <span class="op">(</span>s <span class="op">&lt;</span> n<span class="op">)</span></span>
<span id="cb2-11"><a href="#cb2-11" aria-hidden="true" tabindex=""></a>    s <span class="op">&lt;&lt;=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb2-12"><a href="#cb2-12" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> s<span class="op">;</span></span>
<span id="cb2-13"><a href="#cb2-13" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb2-14"><a href="#cb2-14" aria-hidden="true" tabindex=""></a></span>
<span id="cb2-15"><a href="#cb2-15" aria-hidden="true" tabindex=""></a><span class="co">// na osnovu datog niza a dužine n </span></span>
<span id="cb2-16"><a href="#cb2-16" aria-hidden="true" tabindex=""></a><span class="co">// u kom su elementi smešteni od pozicije 0</span></span>
<span id="cb2-17"><a href="#cb2-17" aria-hidden="true" tabindex=""></a><span class="co">// formira se segmentno drvo i elementi mu se smeštaju u niz</span></span>
<span id="cb2-18"><a href="#cb2-18" aria-hidden="true" tabindex=""></a><span class="co">// drvo krenuvši od pozicije 1</span></span>
<span id="cb2-19"><a href="#cb2-19" aria-hidden="true" tabindex=""></a>vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> formirajDrvo<span class="op">(</span><span class="at">const</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> a<span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-20"><a href="#cb2-20" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n <span class="op">=</span> stepenDvojke<span class="op">(</span>a<span class="op">.</span>size<span class="op">());</span></span>
<span id="cb2-21"><a href="#cb2-21" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> drvo<span class="op">(</span><span class="dv">2</span><span class="op">*</span>n<span class="op">,</span> <span class="dv">0</span><span class="op">);</span></span>
<span id="cb2-22"><a href="#cb2-22" aria-hidden="true" tabindex=""></a>  <span class="co">// kopiramo originalni niz u listove</span></span>
<span id="cb2-23"><a href="#cb2-23" aria-hidden="true" tabindex=""></a>  copy<span class="op">(</span>begin<span class="op">(</span>a<span class="op">),</span> end<span class="op">(</span>a<span class="op">),</span> next<span class="op">(</span>begin<span class="op">(</span>drvo<span class="op">),</span> n<span class="op">));</span></span>
<span id="cb2-24"><a href="#cb2-24" aria-hidden="true" tabindex=""></a>  <span class="co">// ažuriramo roditelje već upisanih elemenata</span></span>
<span id="cb2-25"><a href="#cb2-25" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> k <span class="op">=</span> n<span class="op">-</span><span class="dv">1</span><span class="op">;</span> k <span class="op">&gt;=</span> <span class="dv">1</span><span class="op">;</span> k<span class="op">--)</span></span>
<span id="cb2-26"><a href="#cb2-26" aria-hidden="true" tabindex=""></a>    drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb2-27"><a href="#cb2-27" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> drvo<span class="op">;</span></span>
<span id="cb2-28"><a href="#cb2-28" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb2-29"><a href="#cb2-29" aria-hidden="true" tabindex=""></a></span>
<span id="cb2-30"><a href="#cb2-30" aria-hidden="true" tabindex=""></a><span class="co">// izračunava se zbir elemenata polaznog niza dužine n koji se </span></span>
<span id="cb2-31"><a href="#cb2-31" aria-hidden="true" tabindex=""></a><span class="co">// nalaze na pozicijama iz segmenta [a, b] na osnovu segmentnog drveta</span></span>
<span id="cb2-32"><a href="#cb2-32" aria-hidden="true" tabindex=""></a><span class="co">// koje je smešteno u nizu drvo, krenuvši od pozicije 1</span></span>
<span id="cb2-33"><a href="#cb2-33" aria-hidden="true" tabindex=""></a><span class="dt">int</span> zbirSegmenta<span class="op">(</span><span class="at">const</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span> <span class="dt">int</span> a<span class="op">,</span> <span class="dt">int</span> b<span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-34"><a href="#cb2-34" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span>size<span class="op">()</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb2-35"><a href="#cb2-35" aria-hidden="true" tabindex=""></a>  a <span class="op">+=</span> n<span class="op">;</span> b <span class="op">+=</span> n<span class="op">;</span></span>
<span id="cb2-36"><a href="#cb2-36" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> zbir <span class="op">=</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb2-37"><a href="#cb2-37" aria-hidden="true" tabindex=""></a>  <span class="cf">while</span> <span class="op">(</span>a <span class="op">&lt;=</span> b<span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-38"><a href="#cb2-38" aria-hidden="true" tabindex=""></a>    <span class="cf">if</span> <span class="op">(</span>a <span class="op">%</span> <span class="dv">2</span> <span class="op">==</span> <span class="dv">1</span><span class="op">)</span> zbir <span class="op">+=</span> drvo<span class="op">[</span>a<span class="op">++];</span></span>
<span id="cb2-39"><a href="#cb2-39" aria-hidden="true" tabindex=""></a>    <span class="cf">if</span> <span class="op">(</span>b <span class="op">%</span> <span class="dv">2</span> <span class="op">==</span> <span class="dv">0</span><span class="op">)</span> zbir <span class="op">+=</span> drvo<span class="op">[</span>b<span class="op">--];</span></span>
<span id="cb2-40"><a href="#cb2-40" aria-hidden="true" tabindex=""></a>    a <span class="op">/=</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb2-41"><a href="#cb2-41" aria-hidden="true" tabindex=""></a>    b <span class="op">/=</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb2-42"><a href="#cb2-42" aria-hidden="true" tabindex=""></a>  <span class="op">}</span></span>
<span id="cb2-43"><a href="#cb2-43" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> zbir<span class="op">;</span></span>
<span id="cb2-44"><a href="#cb2-44" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb2-45"><a href="#cb2-45" aria-hidden="true" tabindex=""></a></span>
<span id="cb2-46"><a href="#cb2-46" aria-hidden="true" tabindex=""></a><span class="co">// ažurira segmentno drvo smešteno u niz drvo od pozicije 1</span></span>
<span id="cb2-47"><a href="#cb2-47" aria-hidden="true" tabindex=""></a><span class="co">// koje sadrži elemente polaznog niza a dužine n u kom su elementi</span></span>
<span id="cb2-48"><a href="#cb2-48" aria-hidden="true" tabindex=""></a><span class="co">// smešteni od pozicije 0, nakon što se na poziciju i polaznog</span></span>
<span id="cb2-49"><a href="#cb2-49" aria-hidden="true" tabindex=""></a><span class="co">// niza upiše vrednost v</span></span>
<span id="cb2-50"><a href="#cb2-50" aria-hidden="true" tabindex=""></a><span class="dt">void</span> postavi<span class="op">(</span>vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span> <span class="dt">int</span> i<span class="op">,</span> <span class="dt">int</span> v<span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-51"><a href="#cb2-51" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span>size<span class="op">()</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb2-52"><a href="#cb2-52" aria-hidden="true" tabindex=""></a>  <span class="co">// prvo ažuriramo odgovarajući list</span></span>
<span id="cb2-53"><a href="#cb2-53" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> k <span class="op">=</span> i <span class="op">+</span> n<span class="op">;</span></span>
<span id="cb2-54"><a href="#cb2-54" aria-hidden="true" tabindex=""></a>  drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> v<span class="op">;</span></span>
<span id="cb2-55"><a href="#cb2-55" aria-hidden="true" tabindex=""></a>  <span class="co">// ažuriramo sve roditelje izmenjenih čvorova</span></span>
<span id="cb2-56"><a href="#cb2-56" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span>k <span class="op">/=</span> <span class="dv">2</span><span class="op">;</span> k <span class="op">&gt;=</span> <span class="dv">1</span><span class="op">;</span> k <span class="op">/=</span> <span class="dv">2</span><span class="op">)</span></span>
<span id="cb2-57"><a href="#cb2-57" aria-hidden="true" tabindex=""></a>    drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb2-58"><a href="#cb2-58" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb2-59"><a href="#cb2-59" aria-hidden="true" tabindex=""></a></span>
<span id="cb2-60"><a href="#cb2-60" aria-hidden="true" tabindex=""></a><span class="dt">int</span> main<span class="op">()</span> <span class="op">{</span></span>
<span id="cb2-61"><a href="#cb2-61" aria-hidden="true" tabindex=""></a>  ios_base<span class="op">::</span>sync_with_stdio<span class="op">(</span><span class="kw">false</span><span class="op">);</span> cin<span class="op">.</span>tie<span class="op">(</span><span class="dv">0</span><span class="op">);</span></span>
<span id="cb2-62"><a href="#cb2-62" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n<span class="op">;</span></span>
<span id="cb2-63"><a href="#cb2-63" aria-hidden="true" tabindex=""></a>  cin <span class="op">&gt;&gt;</span> n<span class="op">;</span></span>
<span id="cb2-64"><a href="#cb2-64" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> a<span class="op">(</span>n<span class="op">);</span></span>
<span id="cb2-65"><a href="#cb2-65" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> n<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb2-66"><a href="#cb2-66" aria-hidden="true" tabindex=""></a>    cin <span class="op">&gt;&gt;</span> a<span class="op">[</span>i<span class="op">];</span></span>
<span id="cb2-67"><a href="#cb2-67" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> drvo <span class="op">=</span> formirajDrvo<span class="op">(</span>a<span class="op">);</span></span>
<span id="cb2-68"><a href="#cb2-68" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> m<span class="op">;</span></span>
<span id="cb2-69"><a href="#cb2-69" aria-hidden="true" tabindex=""></a>  cin <span class="op">&gt;&gt;</span> m<span class="op">;</span></span>
<span id="cb2-70"><a href="#cb2-70" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> m<span class="op">;</span> i<span class="op">++)</span> <span class="op">{</span></span>
<span id="cb2-71"><a href="#cb2-71" aria-hidden="true" tabindex=""></a>    string upit<span class="op">;</span></span>
<span id="cb2-72"><a href="#cb2-72" aria-hidden="true" tabindex=""></a>    cin <span class="op">&gt;&gt;</span> upit<span class="op">;</span></span>
<span id="cb2-73"><a href="#cb2-73" aria-hidden="true" tabindex=""></a>    <span class="cf">if</span> <span class="op">(</span>upit <span class="op">==</span> <span class="st">&quot;p&quot;</span><span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-74"><a href="#cb2-74" aria-hidden="true" tabindex=""></a>      <span class="dt">int</span> i<span class="op">,</span> v<span class="op">;</span></span>
<span id="cb2-75"><a href="#cb2-75" aria-hidden="true" tabindex=""></a>      cin <span class="op">&gt;&gt;</span> i <span class="op">&gt;&gt;</span> v <span class="op">&gt;&gt;</span> ws<span class="op">;</span></span>
<span id="cb2-76"><a href="#cb2-76" aria-hidden="true" tabindex=""></a>      postavi<span class="op">(</span>drvo<span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb2-77"><a href="#cb2-77" aria-hidden="true" tabindex=""></a>    <span class="op">}</span> <span class="cf">else</span> <span class="cf">if</span> <span class="op">(</span>upit <span class="op">==</span> <span class="st">&quot;z&quot;</span><span class="op">)</span> <span class="op">{</span></span>
<span id="cb2-78"><a href="#cb2-78" aria-hidden="true" tabindex=""></a>      <span class="dt">int</span> a<span class="op">,</span> b<span class="op">;</span></span>
<span id="cb2-79"><a href="#cb2-79" aria-hidden="true" tabindex=""></a>      cin <span class="op">&gt;&gt;</span> a <span class="op">&gt;&gt;</span> b<span class="op">;</span></span>
<span id="cb2-80"><a href="#cb2-80" aria-hidden="true" tabindex=""></a>      cout <span class="op">&lt;&lt;</span> zbirSegmenta<span class="op">(</span>drvo<span class="op">,</span> a<span class="op">,</span> b<span class="op">)</span> <span class="op">&lt;&lt;</span> <span class="ch">&#39;</span><span class="sc">\n</span><span class="ch">&#39;</span><span class="op">;</span></span>
<span id="cb2-81"><a href="#cb2-81" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb2-82"><a href="#cb2-82" aria-hidden="true" tabindex=""></a>  <span class="op">}</span></span>
<span id="cb2-83"><a href="#cb2-83" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb2-84"><a href="#cb2-84" aria-hidden="true" tabindex=""></a><span class="op">}</span></span></code></pre></div>
<!--- sol:end --->
<!--- sol:ex1 --->
<p>Претходни приступ формира дрво одоздо навише (прво се попуне листови,
па онда корен). Још један начин је да се дрво формира рекурзивно, одозго
наниже. Иако је ова имплементација компликованија и мало неефикаснија,
приступ одозго наниже је у неким каснијим операцијама неизбежан, па га
илуструјемо на овом једноставном примеру. Сваки чвор дрвета представља
збир одређеног сегмента позиција полазног низа. Сегмент је једнозначно
одређен позицијом <span class="math inline">\(k\)</span> у низу који
одговара сегментном дрвету, али да бисмо олакшали имлементацију границе
тог сегмента можемо кроз рекурзију прослеђивати као параметар функције,
заједно са вредношћу <span class="math inline">\(k\)</span> (нека је то
сегмент <span class="math inline">\([x, y]\)</span>). Дрво крећемо да
градимо од корена где је <span class="math inline">\(k=1\)</span> и
<span class="math inline">\([x,y] = [0, n-1]\)</span>. Ако родитељски
чвор покрива сегмент <span class="math inline">\([x, y]\)</span>, тада
лево дете покрива сегмент <span class="math inline">\([x,
\lfloor{\frac{x+y}{2}}\rfloor]\)</span>, а десно дете покрива сегмент
<span class="math inline">\([\lfloor{\frac{x+y}{2}}\rfloor+1,
y]\)</span>. Дрво попуњавамо рекурзивно, тако што прво попунимо лево
поддрво, затим десно и на крају вредност у корену израчунавамо као Дрво
попуњавамо рекурзивно, тако што прво попунимо лево поддрво, затим десно
и на крају вредност у корену израчунавамо као збир вредности у левом и
десном детету. Излаз из рекурзије представљају листови, које
препознајемо по томе што покривају сегменте дужине 1, и у њих само
копирамо елементе са одговарајућих позиција полазног низа.</p>
<p>И за операцију сабирања можемо направити и рекурзивну имплементацију
која врши израчунавање одозго наниже. За сваки чвор у сегментном дрвету
функција враћа колики је допринос сегмента који одговара том чвору и
његовим наследницима траженом збиру елемената на позицијама из сегмента
<span class="math inline">\([a, b]\)</span> у полазном низу. На почетку
крећемо од корена и рачунамо допринос целог дрвета збиру елемената из
сегмента <span class="math inline">\([a, b]\)</span>. Постоје три
различита могућа односа између сегмента <span class="math inline">\([x,
y]\)</span> који одговара текућем чвору и сегмента <span
class="math inline">\([a,b]\)</span> чији збир елемената тражимо. Ако су
дисјунктни, допринос текућег чвора збиру сегмента <span
class="math inline">\([a, b]\)</span> је нула. Ако је <span
class="math inline">\([x, y]\)</span> у потпуности садржан у <span
class="math inline">\([a, b]\)</span>, тада је допринос потпун, тј. цео
збир сегмента <span class="math inline">\([x, y]\)</span> (а то је број
уписан у низу на позицији <span class="math inline">\(k\)</span>)
доприноси збиру елемената на позицијама из сегмента <span
class="math inline">\([a, b]\)</span>. На крају, ако се сегменти секу,
тада је допринос текућег чвора једнак збиру доприноса његовог левог и
десног детета. Иако није сасвим очигледно, и ова процедура ће имати
сложност <span class="math inline">\(O(\log{n})\)</span>.</p>
<p>И операцију промене вредности елемената можемо имплементирати одозго
наниже. Сложеност је опет <span
class="math inline">\(O(\log{n})\)</span>, јер се дужина интервала <span
class="math inline">\([x, y]\)</span> у сваком кораку бар два пута
смањује.</p>
<div class="sourceCode" id="cb3"><pre
class="sourceCode cpp"><code class="sourceCode cpp"><span id="cb3-1"><a href="#cb3-1" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;iostream&gt;</span></span>
<span id="cb3-2"><a href="#cb3-2" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;vector&gt;</span></span>
<span id="cb3-3"><a href="#cb3-3" aria-hidden="true" tabindex=""></a><span class="pp">#include </span><span class="im">&lt;algorithm&gt;</span></span>
<span id="cb3-4"><a href="#cb3-4" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-5"><a href="#cb3-5" aria-hidden="true" tabindex=""></a><span class="kw">using</span> <span class="kw">namespace</span> std<span class="op">;</span></span>
<span id="cb3-6"><a href="#cb3-6" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-7"><a href="#cb3-7" aria-hidden="true" tabindex=""></a><span class="co">// od elemenata niza a sa pozicija [x, y]</span></span>
<span id="cb3-8"><a href="#cb3-8" aria-hidden="true" tabindex=""></a><span class="co">// formira se segmentno drvo i elementi mu se smeštaju u niz</span></span>
<span id="cb3-9"><a href="#cb3-9" aria-hidden="true" tabindex=""></a><span class="co">// drvo krenuvši od pozicije k</span></span>
<span id="cb3-10"><a href="#cb3-10" aria-hidden="true" tabindex=""></a><span class="dt">void</span> formirajDrvo<span class="op">(</span><span class="at">const</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> a<span class="op">,</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span></span>
<span id="cb3-11"><a href="#cb3-11" aria-hidden="true" tabindex=""></a>                  <span class="dt">size_t</span> k<span class="op">,</span> <span class="dt">size_t</span> x<span class="op">,</span> <span class="dt">size_t</span> y<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-12"><a href="#cb3-12" aria-hidden="true" tabindex=""></a>  <span class="cf">if</span> <span class="op">(</span>x <span class="op">==</span> y<span class="op">)</span></span>
<span id="cb3-13"><a href="#cb3-13" aria-hidden="true" tabindex=""></a>    <span class="co">// u listove prepisujemo elemente polaznog niza</span></span>
<span id="cb3-14"><a href="#cb3-14" aria-hidden="true" tabindex=""></a>    drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> x <span class="op">&lt;</span> a<span class="op">.</span>size<span class="op">()</span> <span class="op">?</span> a<span class="op">[</span>x<span class="op">]</span> <span class="op">:</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb3-15"><a href="#cb3-15" aria-hidden="true" tabindex=""></a>  <span class="cf">else</span> <span class="op">{</span></span>
<span id="cb3-16"><a href="#cb3-16" aria-hidden="true" tabindex=""></a>    <span class="co">// rekurzivno formiramo levo i desno poddrvo</span></span>
<span id="cb3-17"><a href="#cb3-17" aria-hidden="true" tabindex=""></a>    <span class="dt">int</span> s <span class="op">=</span> <span class="op">(</span>x <span class="op">+</span> y<span class="op">)</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb3-18"><a href="#cb3-18" aria-hidden="true" tabindex=""></a>    formirajDrvo<span class="op">(</span>a<span class="op">,</span> drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">,</span> x<span class="op">,</span> s<span class="op">);</span></span>
<span id="cb3-19"><a href="#cb3-19" aria-hidden="true" tabindex=""></a>    formirajDrvo<span class="op">(</span>a<span class="op">,</span> drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">,</span> s<span class="op">+</span><span class="dv">1</span><span class="op">,</span> y<span class="op">);</span></span>
<span id="cb3-20"><a href="#cb3-20" aria-hidden="true" tabindex=""></a>    <span class="co">// izračunavamo vrednost u korenu</span></span>
<span id="cb3-21"><a href="#cb3-21" aria-hidden="true" tabindex=""></a>    drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb3-22"><a href="#cb3-22" aria-hidden="true" tabindex=""></a>  <span class="op">}</span></span>
<span id="cb3-23"><a href="#cb3-23" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-24"><a href="#cb3-24" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-25"><a href="#cb3-25" aria-hidden="true" tabindex=""></a><span class="co">// najmanji stepen dvojke veci ili jednak od n</span></span>
<span id="cb3-26"><a href="#cb3-26" aria-hidden="true" tabindex=""></a><span class="dt">int</span> stepenDvojke<span class="op">(</span><span class="dt">int</span> n<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-27"><a href="#cb3-27" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> s <span class="op">=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb3-28"><a href="#cb3-28" aria-hidden="true" tabindex=""></a>  <span class="cf">while</span> <span class="op">(</span>s <span class="op">&lt;</span> n<span class="op">)</span></span>
<span id="cb3-29"><a href="#cb3-29" aria-hidden="true" tabindex=""></a>    s <span class="op">&lt;&lt;=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb3-30"><a href="#cb3-30" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> s<span class="op">;</span></span>
<span id="cb3-31"><a href="#cb3-31" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-32"><a href="#cb3-32" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-33"><a href="#cb3-33" aria-hidden="true" tabindex=""></a><span class="co">// na osnovu datog niza a duzine n u kom su elementi smesteni od</span></span>
<span id="cb3-34"><a href="#cb3-34" aria-hidden="true" tabindex=""></a><span class="co">// pozicije 0 formira se segmentno drvo i elementi mu se smeštaju u</span></span>
<span id="cb3-35"><a href="#cb3-35" aria-hidden="true" tabindex=""></a><span class="co">// niz drvo krenuvši od pozicije 1</span></span>
<span id="cb3-36"><a href="#cb3-36" aria-hidden="true" tabindex=""></a>vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> formirajDrvo<span class="op">(</span><span class="at">const</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> a<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-37"><a href="#cb3-37" aria-hidden="true" tabindex=""></a>  <span class="co">// niz implicitno dopunjujemo nulama tako da mu duzina postane</span></span>
<span id="cb3-38"><a href="#cb3-38" aria-hidden="true" tabindex=""></a>  <span class="co">// najblizi stepen dvojke</span></span>
<span id="cb3-39"><a href="#cb3-39" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n <span class="op">=</span> stepenDvojke<span class="op">(</span>a<span class="op">.</span>size<span class="op">());</span></span>
<span id="cb3-40"><a href="#cb3-40" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> drvo<span class="op">(</span>n <span class="op">*</span> <span class="dv">2</span><span class="op">);</span></span>
<span id="cb3-41"><a href="#cb3-41" aria-hidden="true" tabindex=""></a>  <span class="co">// krećemo formiranje od korena koji se nalazi u nizu drvo</span></span>
<span id="cb3-42"><a href="#cb3-42" aria-hidden="true" tabindex=""></a>  <span class="co">// na poziciji 1 i pokriva elemente na pozicijama [0, n-1]</span></span>
<span id="cb3-43"><a href="#cb3-43" aria-hidden="true" tabindex=""></a>  formirajDrvo<span class="op">(</span>a<span class="op">,</span> drvo<span class="op">,</span> <span class="dv">1</span><span class="op">,</span> <span class="dv">0</span><span class="op">,</span> n <span class="op">-</span> <span class="dv">1</span><span class="op">);</span></span>
<span id="cb3-44"><a href="#cb3-44" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> drvo<span class="op">;</span></span>
<span id="cb3-45"><a href="#cb3-45" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-46"><a href="#cb3-46" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-47"><a href="#cb3-47" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-48"><a href="#cb3-48" aria-hidden="true" tabindex=""></a><span class="co">// izračunava se zbir onih elemenata polaznog niza koji se</span></span>
<span id="cb3-49"><a href="#cb3-49" aria-hidden="true" tabindex=""></a><span class="co">// nalaze na pozicijama iz segmenta [a, b] koji se nalaze u </span></span>
<span id="cb3-50"><a href="#cb3-50" aria-hidden="true" tabindex=""></a><span class="co">// segmentnom drvetu koje čuva elemente polaznog niza koji se </span></span>
<span id="cb3-51"><a href="#cb3-51" aria-hidden="true" tabindex=""></a><span class="co">// nalaze na pozicijama iz segmenta [x, y] i smešteno je u nizu</span></span>
<span id="cb3-52"><a href="#cb3-52" aria-hidden="true" tabindex=""></a><span class="co">// drvo od pozicije k</span></span>
<span id="cb3-53"><a href="#cb3-53" aria-hidden="true" tabindex=""></a><span class="dt">int</span> zbirSegmenta<span class="op">(</span><span class="at">const</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span> <span class="dt">int</span> k<span class="op">,</span> <span class="dt">int</span> x<span class="op">,</span> <span class="dt">int</span> y<span class="op">,</span> <span class="dt">int</span> a<span class="op">,</span> <span class="dt">int</span> b<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-54"><a href="#cb3-54" aria-hidden="true" tabindex=""></a>  <span class="co">// segmenti [x, y] i [a, b] su disjunktni</span></span>
<span id="cb3-55"><a href="#cb3-55" aria-hidden="true" tabindex=""></a>  <span class="cf">if</span> <span class="op">(</span>b <span class="op">&lt;</span> x <span class="op">||</span> a <span class="op">&gt;</span> y<span class="op">)</span> <span class="cf">return</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb3-56"><a href="#cb3-56" aria-hidden="true" tabindex=""></a>  <span class="co">// segment [x, y] je potpuno sadržan unutar segmenta [a, b]</span></span>
<span id="cb3-57"><a href="#cb3-57" aria-hidden="true" tabindex=""></a>  <span class="cf">if</span> <span class="op">(</span>a <span class="op">&lt;=</span> x <span class="op">&amp;&amp;</span> y <span class="op">&lt;=</span> b<span class="op">)</span></span>
<span id="cb3-58"><a href="#cb3-58" aria-hidden="true" tabindex=""></a>      <span class="cf">return</span> drvo<span class="op">[</span>k<span class="op">];</span></span>
<span id="cb3-59"><a href="#cb3-59" aria-hidden="true" tabindex=""></a>  <span class="co">// segmenti [x, y] i [a, b] se seku</span></span>
<span id="cb3-60"><a href="#cb3-60" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> s <span class="op">=</span> <span class="op">(</span>x <span class="op">+</span> y<span class="op">)</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb3-61"><a href="#cb3-61" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> zbirSegmenta<span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">,</span> x<span class="op">,</span> s<span class="op">,</span> a<span class="op">,</span> b<span class="op">)</span> <span class="op">+</span> </span>
<span id="cb3-62"><a href="#cb3-62" aria-hidden="true" tabindex=""></a>         zbirSegmenta<span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">,</span> s<span class="op">+</span><span class="dv">1</span><span class="op">,</span> y<span class="op">,</span> a<span class="op">,</span> b<span class="op">);</span></span>
<span id="cb3-63"><a href="#cb3-63" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-64"><a href="#cb3-64" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-65"><a href="#cb3-65" aria-hidden="true" tabindex=""></a><span class="co">// izračunava se zbir elemenata polaznog niza dužine n koji se </span></span>
<span id="cb3-66"><a href="#cb3-66" aria-hidden="true" tabindex=""></a><span class="co">// nalaze na pozicijama iz segmenta [a, b] na osnovu segmentnog drveta</span></span>
<span id="cb3-67"><a href="#cb3-67" aria-hidden="true" tabindex=""></a><span class="co">// koje je smešteno u nizu drvo, krenuvši od pozicije 1</span></span>
<span id="cb3-68"><a href="#cb3-68" aria-hidden="true" tabindex=""></a><span class="dt">int</span> zbirSegmenta<span class="op">(</span><span class="at">const</span> vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span> <span class="dt">int</span> a<span class="op">,</span> <span class="dt">int</span> b<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-69"><a href="#cb3-69" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span>size<span class="op">()</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb3-70"><a href="#cb3-70" aria-hidden="true" tabindex=""></a>  <span class="co">// krećemo od drveta smeštenog od pozicije 1 koje</span></span>
<span id="cb3-71"><a href="#cb3-71" aria-hidden="true" tabindex=""></a>  <span class="co">// sadrži elemente polaznog niza na pozicijama iz segmenta [0, n-1]</span></span>
<span id="cb3-72"><a href="#cb3-72" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> zbirSegmenta<span class="op">(</span>drvo<span class="op">,</span> <span class="dv">1</span><span class="op">,</span> <span class="dv">0</span><span class="op">,</span> n<span class="op">-</span><span class="dv">1</span><span class="op">,</span> a<span class="op">,</span> b<span class="op">);</span></span>
<span id="cb3-73"><a href="#cb3-73" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-74"><a href="#cb3-74" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-75"><a href="#cb3-75" aria-hidden="true" tabindex=""></a><span class="co">// ažurira segmentno drvo smešteno u niz drvo od pozicije k</span></span>
<span id="cb3-76"><a href="#cb3-76" aria-hidden="true" tabindex=""></a><span class="co">// koje sadrži elemente polaznog niza a dužine n sa pozicija iz</span></span>
<span id="cb3-77"><a href="#cb3-77" aria-hidden="true" tabindex=""></a><span class="co">// segmenta [x, y], nakon što se na poziciju i niza upiše vrednost v</span></span>
<span id="cb3-78"><a href="#cb3-78" aria-hidden="true" tabindex=""></a><span class="dt">void</span> postavi<span class="op">(</span>vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span> <span class="dt">int</span> k<span class="op">,</span> <span class="dt">int</span> x<span class="op">,</span> <span class="dt">int</span> y<span class="op">,</span> <span class="dt">int</span> i<span class="op">,</span> <span class="dt">int</span> v<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-79"><a href="#cb3-79" aria-hidden="true" tabindex=""></a>   <span class="cf">if</span> <span class="op">(</span>x <span class="op">==</span> y<span class="op">)</span></span>
<span id="cb3-80"><a href="#cb3-80" aria-hidden="true" tabindex=""></a>     <span class="co">// ažuriramo vrednost u listu</span></span>
<span id="cb3-81"><a href="#cb3-81" aria-hidden="true" tabindex=""></a>     drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> v<span class="op">;</span></span>
<span id="cb3-82"><a href="#cb3-82" aria-hidden="true" tabindex=""></a>   <span class="cf">else</span> <span class="op">{</span></span>
<span id="cb3-83"><a href="#cb3-83" aria-hidden="true" tabindex=""></a>     <span class="co">// proveravamo da li se pozicija i nalazi levo ili desno</span></span>
<span id="cb3-84"><a href="#cb3-84" aria-hidden="true" tabindex=""></a>     <span class="co">// i u zavisnosti od toga ažuriramo odgovarajuće poddrvo</span></span>
<span id="cb3-85"><a href="#cb3-85" aria-hidden="true" tabindex=""></a>     <span class="dt">int</span> s <span class="op">=</span> <span class="op">(</span>x <span class="op">+</span> y<span class="op">)</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb3-86"><a href="#cb3-86" aria-hidden="true" tabindex=""></a>     <span class="cf">if</span> <span class="op">(</span>x <span class="op">&lt;=</span> i <span class="op">&amp;&amp;</span> i <span class="op">&lt;=</span> s<span class="op">)</span></span>
<span id="cb3-87"><a href="#cb3-87" aria-hidden="true" tabindex=""></a>       postavi<span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">,</span> x<span class="op">,</span> s<span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb3-88"><a href="#cb3-88" aria-hidden="true" tabindex=""></a>     <span class="cf">else</span></span>
<span id="cb3-89"><a href="#cb3-89" aria-hidden="true" tabindex=""></a>       postavi<span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">,</span> s<span class="op">+</span><span class="dv">1</span><span class="op">,</span> y<span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb3-90"><a href="#cb3-90" aria-hidden="true" tabindex=""></a>     <span class="co">// pošto se promenila vrednost u nekom od dva poddrveta</span></span>
<span id="cb3-91"><a href="#cb3-91" aria-hidden="true" tabindex=""></a>     <span class="co">// moramo ažurirati vrednost u korenu</span></span>
<span id="cb3-92"><a href="#cb3-92" aria-hidden="true" tabindex=""></a>     drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb3-93"><a href="#cb3-93" aria-hidden="true" tabindex=""></a>   <span class="op">}</span></span>
<span id="cb3-94"><a href="#cb3-94" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-95"><a href="#cb3-95" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-96"><a href="#cb3-96" aria-hidden="true" tabindex=""></a><span class="co">// ažurira segmentno drvo smešteno u niz drvo od pozicije 1</span></span>
<span id="cb3-97"><a href="#cb3-97" aria-hidden="true" tabindex=""></a><span class="co">// koje sadrži elemente polaznog niza a dužine n u kom su elementi</span></span>
<span id="cb3-98"><a href="#cb3-98" aria-hidden="true" tabindex=""></a><span class="co">// smešteni od pozicije 0, nakon što se na poziciju i polaznog</span></span>
<span id="cb3-99"><a href="#cb3-99" aria-hidden="true" tabindex=""></a><span class="co">// niza upiše vrednost v</span></span>
<span id="cb3-100"><a href="#cb3-100" aria-hidden="true" tabindex=""></a><span class="dt">void</span> postavi<span class="op">(</span>vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;&amp;</span> drvo<span class="op">,</span> <span class="dt">int</span> i<span class="op">,</span> <span class="dt">int</span> v<span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-101"><a href="#cb3-101" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span>size<span class="op">()</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb3-102"><a href="#cb3-102" aria-hidden="true" tabindex=""></a>  <span class="co">// krećemo od drveta smeštenog od pozicije 1 koje</span></span>
<span id="cb3-103"><a href="#cb3-103" aria-hidden="true" tabindex=""></a>  <span class="co">// sadrži elemente polaznog niza na pozicijama iz segmenta [0, n-1]</span></span>
<span id="cb3-104"><a href="#cb3-104" aria-hidden="true" tabindex=""></a>  postavi<span class="op">(</span>drvo<span class="op">,</span> <span class="dv">1</span><span class="op">,</span> <span class="dv">0</span><span class="op">,</span> n<span class="op">-</span><span class="dv">1</span><span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb3-105"><a href="#cb3-105" aria-hidden="true" tabindex=""></a><span class="op">}</span></span>
<span id="cb3-106"><a href="#cb3-106" aria-hidden="true" tabindex=""></a></span>
<span id="cb3-107"><a href="#cb3-107" aria-hidden="true" tabindex=""></a><span class="dt">int</span> main<span class="op">()</span> <span class="op">{</span></span>
<span id="cb3-108"><a href="#cb3-108" aria-hidden="true" tabindex=""></a>  ios_base<span class="op">::</span>sync_with_stdio<span class="op">(</span><span class="kw">false</span><span class="op">);</span> cin<span class="op">.</span>tie<span class="op">(</span><span class="dv">0</span><span class="op">);</span></span>
<span id="cb3-109"><a href="#cb3-109" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> n<span class="op">;</span></span>
<span id="cb3-110"><a href="#cb3-110" aria-hidden="true" tabindex=""></a>  cin <span class="op">&gt;&gt;</span> n<span class="op">;</span></span>
<span id="cb3-111"><a href="#cb3-111" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> a<span class="op">(</span>n<span class="op">);</span></span>
<span id="cb3-112"><a href="#cb3-112" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> n<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb3-113"><a href="#cb3-113" aria-hidden="true" tabindex=""></a>    cin <span class="op">&gt;&gt;</span> a<span class="op">[</span>i<span class="op">];</span></span>
<span id="cb3-114"><a href="#cb3-114" aria-hidden="true" tabindex=""></a>  vector<span class="op">&lt;</span><span class="dt">int</span><span class="op">&gt;</span> drvo <span class="op">=</span> formirajDrvo<span class="op">(</span>a<span class="op">);</span></span>
<span id="cb3-115"><a href="#cb3-115" aria-hidden="true" tabindex=""></a>  <span class="dt">int</span> m<span class="op">;</span></span>
<span id="cb3-116"><a href="#cb3-116" aria-hidden="true" tabindex=""></a>  cin <span class="op">&gt;&gt;</span> m<span class="op">;</span></span>
<span id="cb3-117"><a href="#cb3-117" aria-hidden="true" tabindex=""></a>  <span class="cf">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> m<span class="op">;</span> i<span class="op">++)</span> <span class="op">{</span></span>
<span id="cb3-118"><a href="#cb3-118" aria-hidden="true" tabindex=""></a>    string upit<span class="op">;</span></span>
<span id="cb3-119"><a href="#cb3-119" aria-hidden="true" tabindex=""></a>    cin <span class="op">&gt;&gt;</span> upit<span class="op">;</span></span>
<span id="cb3-120"><a href="#cb3-120" aria-hidden="true" tabindex=""></a>    <span class="cf">if</span> <span class="op">(</span>upit <span class="op">==</span> <span class="st">&quot;p&quot;</span><span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-121"><a href="#cb3-121" aria-hidden="true" tabindex=""></a>      <span class="dt">int</span> i<span class="op">,</span> v<span class="op">;</span></span>
<span id="cb3-122"><a href="#cb3-122" aria-hidden="true" tabindex=""></a>      cin <span class="op">&gt;&gt;</span> i <span class="op">&gt;&gt;</span> v <span class="op">&gt;&gt;</span> ws<span class="op">;</span></span>
<span id="cb3-123"><a href="#cb3-123" aria-hidden="true" tabindex=""></a>      postavi<span class="op">(</span>drvo<span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb3-124"><a href="#cb3-124" aria-hidden="true" tabindex=""></a>    <span class="op">}</span> <span class="cf">else</span> <span class="cf">if</span> <span class="op">(</span>upit <span class="op">==</span> <span class="st">&quot;z&quot;</span><span class="op">)</span> <span class="op">{</span></span>
<span id="cb3-125"><a href="#cb3-125" aria-hidden="true" tabindex=""></a>      <span class="dt">int</span> a<span class="op">,</span> b<span class="op">;</span></span>
<span id="cb3-126"><a href="#cb3-126" aria-hidden="true" tabindex=""></a>      cin <span class="op">&gt;&gt;</span> a <span class="op">&gt;&gt;</span> b<span class="op">;</span></span>
<span id="cb3-127"><a href="#cb3-127" aria-hidden="true" tabindex=""></a>      cout <span class="op">&lt;&lt;</span> zbirSegmenta<span class="op">(</span>drvo<span class="op">,</span> a<span class="op">,</span> b<span class="op">)</span> <span class="op">&lt;&lt;</span> <span class="ch">&#39;</span><span class="sc">\n</span><span class="ch">&#39;</span><span class="op">;</span></span>
<span id="cb3-128"><a href="#cb3-128" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb3-129"><a href="#cb3-129" aria-hidden="true" tabindex=""></a>  <span class="op">}</span></span>
<span id="cb3-130"><a href="#cb3-130" aria-hidden="true" tabindex=""></a>  <span class="cf">return</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb3-131"><a href="#cb3-131" aria-hidden="true" tabindex=""></a><span class="op">}</span></span></code></pre></div>
<!--- sol:end --->
</div>
<div id="sol-cs" class="sol">
<h1 id="суме-сегмената-променљивог-низа---решење-1">Суме сегмената
променљивог низа - Решење</h1>
<!--- sol:ex2 --->
<p>Решење грубом силом подразумева да се одржава низ, да се упити
<code>p</code> извршавају директном променом елемената низа (то се ради
у <span class="math inline">\(O(1)\)</span>), а да се упити
<code>z</code> извршавају сабирањем елемената низа (то се ради у времену
<span class="math inline">\(O(n)\)</span>). Укупна сложеност таквог
приступа је <span class="math inline">\(O(mn)\)</span>.</p>
<div class="sourceCode" id="cb4"><pre class="sourceCode cs"><code class="sourceCode cs"><span id="cb4-1"><a href="#cb4-1" aria-hidden="true" tabindex=""></a><span class="kw">using</span> System<span class="op">;</span></span>
<span id="cb4-2"><a href="#cb4-2" aria-hidden="true" tabindex=""></a></span>
<span id="cb4-3"><a href="#cb4-3" aria-hidden="true" tabindex=""></a><span class="kw">class</span> Program</span>
<span id="cb4-4"><a href="#cb4-4" aria-hidden="true" tabindex=""></a><span class="op">{</span></span>
<span id="cb4-5"><a href="#cb4-5" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">Main</span><span class="op">(</span><span class="dt">string</span><span class="op">[]</span> args<span class="op">)</span></span>
<span id="cb4-6"><a href="#cb4-6" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb4-7"><a href="#cb4-7" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">());</span></span>
<span id="cb4-8"><a href="#cb4-8" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> a <span class="op">=</span> <span class="kw">new</span> <span class="dt">int</span><span class="op">[</span>n<span class="op">];</span></span>
<span id="cb4-9"><a href="#cb4-9" aria-hidden="true" tabindex=""></a>        <span class="dt">string</span><span class="op">[]</span> str <span class="op">=</span> Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">().</span><span class="fu">Split</span><span class="op">();</span></span>
<span id="cb4-10"><a href="#cb4-10" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> n<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb4-11"><a href="#cb4-11" aria-hidden="true" tabindex=""></a>            a<span class="op">[</span>i<span class="op">]</span> <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span>i<span class="op">]);</span></span>
<span id="cb4-12"><a href="#cb4-12" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> m <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">());</span></span>
<span id="cb4-13"><a href="#cb4-13" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> m<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb4-14"><a href="#cb4-14" aria-hidden="true" tabindex=""></a>        <span class="op">{</span></span>
<span id="cb4-15"><a href="#cb4-15" aria-hidden="true" tabindex=""></a>            str <span class="op">=</span> Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">().</span><span class="fu">Split</span><span class="op">();</span></span>
<span id="cb4-16"><a href="#cb4-16" aria-hidden="true" tabindex=""></a>            <span class="kw">if</span> <span class="op">(</span>str<span class="op">[</span><span class="dv">0</span><span class="op">]</span> <span class="op">==</span> <span class="st">&quot;p&quot;</span><span class="op">)</span></span>
<span id="cb4-17"><a href="#cb4-17" aria-hidden="true" tabindex=""></a>            <span class="op">{</span></span>
<span id="cb4-18"><a href="#cb4-18" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> p <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">1</span><span class="op">]);</span></span>
<span id="cb4-19"><a href="#cb4-19" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> v <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">2</span><span class="op">]);</span></span>
<span id="cb4-20"><a href="#cb4-20" aria-hidden="true" tabindex=""></a>                a<span class="op">[</span>p<span class="op">]</span> <span class="op">=</span> v<span class="op">;</span></span>
<span id="cb4-21"><a href="#cb4-21" aria-hidden="true" tabindex=""></a>            <span class="op">}</span></span>
<span id="cb4-22"><a href="#cb4-22" aria-hidden="true" tabindex=""></a>            <span class="kw">else</span> <span class="kw">if</span> <span class="op">(</span>str<span class="op">[</span><span class="dv">0</span><span class="op">]</span> <span class="op">==</span> <span class="st">&quot;z&quot;</span><span class="op">)</span></span>
<span id="cb4-23"><a href="#cb4-23" aria-hidden="true" tabindex=""></a>            <span class="op">{</span></span>
<span id="cb4-24"><a href="#cb4-24" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> l <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">1</span><span class="op">]);</span></span>
<span id="cb4-25"><a href="#cb4-25" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> d <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">2</span><span class="op">]);</span></span>
<span id="cb4-26"><a href="#cb4-26" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> zbir <span class="op">=</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb4-27"><a href="#cb4-27" aria-hidden="true" tabindex=""></a>                <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> k <span class="op">=</span> l<span class="op">;</span> k <span class="op">&lt;=</span> d<span class="op">;</span> k<span class="op">++)</span></span>
<span id="cb4-28"><a href="#cb4-28" aria-hidden="true" tabindex=""></a>                    zbir <span class="op">+=</span> a<span class="op">[</span>k<span class="op">];</span></span>
<span id="cb4-29"><a href="#cb4-29" aria-hidden="true" tabindex=""></a>                Console<span class="op">.</span><span class="fu">WriteLine</span><span class="op">(</span>zbir<span class="op">);</span></span>
<span id="cb4-30"><a href="#cb4-30" aria-hidden="true" tabindex=""></a>            <span class="op">}</span></span>
<span id="cb4-31"><a href="#cb4-31" aria-hidden="true" tabindex=""></a>        <span class="op">}</span></span>
<span id="cb4-32"><a href="#cb4-32" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb4-33"><a href="#cb4-33" aria-hidden="true" tabindex=""></a><span class="op">}</span></span></code></pre></div>
<!--- sol:end --->
<!--- sol:ex0 --->
<p>Задатак можемо ефикасније решити ако збирове одржавамо у сегментном
дрвету. Операције над дрветом можемо реализовати навише (од листова
према корену).</p>
<p>Формирање сегментног дрвета на основу датог низа је веома
једноставно. Прво се елементи полазног низа прекопирају у дрво, кренувши
од позиције <span class="math inline">\(n\)</span>. Затим се сви
унутрашњи чворови дрвета (од позиције <span
class="math inline">\(n-1\)</span>, па уназад до позиције <span
class="math inline">\(1\)</span>) попуњавају као збирови своје деце (на
позицију <span class="math inline">\(k\)</span> уписујемо збир елемената
на позицијама <span class="math inline">\(2k\)</span> и <span
class="math inline">\(2k+1\)</span>). Сложеност ове операције је
очигледно линеарна у односу на дужину низа <span
class="math inline">\(n\)</span>.</p>
<p>За све унутрашње елементе сегмента смо сигурни да се њихов збир
налази у чворовима изнад њих. Једини изузетак могу да буду елементи на
крајевима сегмента. Ако је елемент на левом крају сегмента лево дете
(што је еквивалентно томе да се налази на парној позицији) тада се у
његовом родитељском чвору налази његов збир са елементом десно од њега
који такође припада сегменту који треба сабрати (осим евентуално у
случају једночланог сегмента). У супротном (ако се налази на непарној
позицији), у његовом родитељском чвору је његов збир са елементом лево
од њега, који не припада сегменту који сабирамо. У тој ситуацији, тај
елемент ћемо посебно додати на збир и искључити из сегмента који
сабирамо помоћу родитељских чворова. Ако је елемент на десном крају
сегмента лево дете (ако се налази на парној позицији), тада се у његовом
родитељском чвору налази његов збир са елементом десно од њега, који не
припада сегменту који сабирамо. И у тој ситуацији, тај елемент ћемо
посебно додати на збир и искључити из сегмента који сабирамо помоћу
родитељских чворова. На крају, ако се крајњи десни елемент налази у
десном чвору (ако је на непарној позицији), тада се у његовом
родитељском чвору налази његов збир са елементом лево од њега који
припада сегменту који сабирамо (осим евентуално у случају једночланог
сегмента). Пошто се у сваком кораку дужина сегмента <span
class="math inline">\([a, b]\)</span> полови, а она је у почетку сигурно
мања или једнака <span class="math inline">\(n\)</span>, сложеност ове
операције је <span class="math inline">\(O(\log{n})\)</span>.</p>
<p>Приликом ажурирања неког елемента потребно је ажурирати све чворове
на путањи од тог листа до корена. С обзиром да знамо позицију родитеља
сваког чвора и ова операција се може веома једноставно имплементирати.
Пошто се <span class="math inline">\(k\)</span> полови у сваком кораку
петље, а крећа од вредности највише <span
class="math inline">\(2n-1\)</span>, и сложеност ове операције је <span
class="math inline">\(O(\log{n})\)</span>.</p>
<div class="sourceCode" id="cb5"><pre class="sourceCode cs"><code class="sourceCode cs"><span id="cb5-1"><a href="#cb5-1" aria-hidden="true" tabindex=""></a><span class="kw">using</span> System<span class="op">;</span></span>
<span id="cb5-2"><a href="#cb5-2" aria-hidden="true" tabindex=""></a></span>
<span id="cb5-3"><a href="#cb5-3" aria-hidden="true" tabindex=""></a><span class="kw">class</span> Program</span>
<span id="cb5-4"><a href="#cb5-4" aria-hidden="true" tabindex=""></a><span class="op">{</span></span>
<span id="cb5-5"><a href="#cb5-5" aria-hidden="true" tabindex=""></a></span>
<span id="cb5-6"><a href="#cb5-6" aria-hidden="true" tabindex=""></a>    <span class="co">// najmanji stepen dvojke veci ili jednak od n</span></span>
<span id="cb5-7"><a href="#cb5-7" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span> <span class="fu">stepenDvojke</span><span class="op">(</span><span class="dt">int</span> n<span class="op">)</span></span>
<span id="cb5-8"><a href="#cb5-8" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb5-9"><a href="#cb5-9" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> s <span class="op">=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb5-10"><a href="#cb5-10" aria-hidden="true" tabindex=""></a>        <span class="kw">while</span> <span class="op">(</span>s <span class="op">&lt;</span> n<span class="op">)</span></span>
<span id="cb5-11"><a href="#cb5-11" aria-hidden="true" tabindex=""></a>            s <span class="op">&lt;&lt;=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb5-12"><a href="#cb5-12" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> s<span class="op">;</span></span>
<span id="cb5-13"><a href="#cb5-13" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb5-14"><a href="#cb5-14" aria-hidden="true" tabindex=""></a></span>
<span id="cb5-15"><a href="#cb5-15" aria-hidden="true" tabindex=""></a>    <span class="co">// na osnovu datog niza a duzine n </span></span>
<span id="cb5-16"><a href="#cb5-16" aria-hidden="true" tabindex=""></a>    <span class="co">// u kom su elementi smesteni od pozicije 0</span></span>
<span id="cb5-17"><a href="#cb5-17" aria-hidden="true" tabindex=""></a>    <span class="co">// formira se segmentno drvo i elementi mu se smestaju u niz</span></span>
<span id="cb5-18"><a href="#cb5-18" aria-hidden="true" tabindex=""></a>    <span class="co">// drvo krenuvsi od pozicije 1</span></span>
<span id="cb5-19"><a href="#cb5-19" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span><span class="op">[]</span> <span class="fu">formirajDrvo</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> a<span class="op">)</span></span>
<span id="cb5-20"><a href="#cb5-20" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb5-21"><a href="#cb5-21" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> <span class="fu">stepenDvojke</span><span class="op">(</span>a<span class="op">.</span><span class="fu">Length</span><span class="op">);</span></span>
<span id="cb5-22"><a href="#cb5-22" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> drvo <span class="op">=</span> <span class="kw">new</span> <span class="dt">int</span><span class="op">[</span><span class="dv">2</span><span class="op">*</span>n<span class="op">];</span></span>
<span id="cb5-23"><a href="#cb5-23" aria-hidden="true" tabindex=""></a>        <span class="co">// kopiramo originalni niz u listove</span></span>
<span id="cb5-24"><a href="#cb5-24" aria-hidden="true" tabindex=""></a>        Array<span class="op">.</span><span class="fu">Copy</span><span class="op">(</span>a<span class="op">,</span> <span class="dv">0</span><span class="op">,</span> drvo<span class="op">,</span> n<span class="op">,</span> a<span class="op">.</span><span class="fu">Length</span><span class="op">);</span></span>
<span id="cb5-25"><a href="#cb5-25" aria-hidden="true" tabindex=""></a>        <span class="co">// ažuriramo roditelje već upisanih elemenata</span></span>
<span id="cb5-26"><a href="#cb5-26" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> k <span class="op">=</span> n<span class="dv">-1</span><span class="op">;</span> k <span class="op">&gt;=</span> <span class="dv">1</span><span class="op">;</span> k<span class="op">--)</span></span>
<span id="cb5-27"><a href="#cb5-27" aria-hidden="true" tabindex=""></a>            drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb5-28"><a href="#cb5-28" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> drvo<span class="op">;</span></span>
<span id="cb5-29"><a href="#cb5-29" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb5-30"><a href="#cb5-30" aria-hidden="true" tabindex=""></a></span>
<span id="cb5-31"><a href="#cb5-31" aria-hidden="true" tabindex=""></a>    <span class="co">// izracunava se zbir elemenata polaznog niza duzine n koji se </span></span>
<span id="cb5-32"><a href="#cb5-32" aria-hidden="true" tabindex=""></a>    <span class="co">// nalaze na pozicijama iz segmenta [a, b] na osnovu segmentnog drveta</span></span>
<span id="cb5-33"><a href="#cb5-33" aria-hidden="true" tabindex=""></a>    <span class="co">// koje je smesteno u nizu drvo, krenuvši od pozicije 1</span></span>
<span id="cb5-34"><a href="#cb5-34" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span> <span class="fu">zbirSegmenta</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> a<span class="op">,</span> <span class="dt">int</span> b<span class="op">)</span></span>
<span id="cb5-35"><a href="#cb5-35" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb5-36"><a href="#cb5-36" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span><span class="fu">Length</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb5-37"><a href="#cb5-37" aria-hidden="true" tabindex=""></a>        a <span class="op">+=</span> n<span class="op">;</span> b <span class="op">+=</span> n<span class="op">;</span></span>
<span id="cb5-38"><a href="#cb5-38" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> zbir <span class="op">=</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb5-39"><a href="#cb5-39" aria-hidden="true" tabindex=""></a>        <span class="kw">while</span> <span class="op">(</span>a <span class="op">&lt;=</span> b<span class="op">)</span></span>
<span id="cb5-40"><a href="#cb5-40" aria-hidden="true" tabindex=""></a>        <span class="op">{</span></span>
<span id="cb5-41"><a href="#cb5-41" aria-hidden="true" tabindex=""></a>            <span class="kw">if</span> <span class="op">(</span>a <span class="op">%</span> <span class="dv">2</span> <span class="op">==</span> <span class="dv">1</span><span class="op">)</span> zbir <span class="op">+=</span> drvo<span class="op">[</span>a<span class="op">++];</span></span>
<span id="cb5-42"><a href="#cb5-42" aria-hidden="true" tabindex=""></a>            <span class="kw">if</span> <span class="op">(</span>b <span class="op">%</span> <span class="dv">2</span> <span class="op">==</span> <span class="dv">0</span><span class="op">)</span> zbir <span class="op">+=</span> drvo<span class="op">[</span>b<span class="op">--];</span></span>
<span id="cb5-43"><a href="#cb5-43" aria-hidden="true" tabindex=""></a>            a <span class="op">/=</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb5-44"><a href="#cb5-44" aria-hidden="true" tabindex=""></a>            b <span class="op">/=</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb5-45"><a href="#cb5-45" aria-hidden="true" tabindex=""></a>        <span class="op">}</span></span>
<span id="cb5-46"><a href="#cb5-46" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> zbir<span class="op">;</span></span>
<span id="cb5-47"><a href="#cb5-47" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb5-48"><a href="#cb5-48" aria-hidden="true" tabindex=""></a></span>
<span id="cb5-49"><a href="#cb5-49" aria-hidden="true" tabindex=""></a>    <span class="co">// azurira segmentno drvo smesteno u niz drvo od pozicije 1</span></span>
<span id="cb5-50"><a href="#cb5-50" aria-hidden="true" tabindex=""></a>    <span class="co">// koje sadrzi elemente polaznog niza a duzine n u kom su elementi</span></span>
<span id="cb5-51"><a href="#cb5-51" aria-hidden="true" tabindex=""></a>    <span class="co">// smesteni od pozicije 0, nakon sto se na poziciju i polaznog</span></span>
<span id="cb5-52"><a href="#cb5-52" aria-hidden="true" tabindex=""></a>    <span class="co">// niza upise vrednost v</span></span>
<span id="cb5-53"><a href="#cb5-53" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">postavi</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> i<span class="op">,</span> <span class="dt">int</span> v<span class="op">)</span></span>
<span id="cb5-54"><a href="#cb5-54" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb5-55"><a href="#cb5-55" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span><span class="fu">Length</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb5-56"><a href="#cb5-56" aria-hidden="true" tabindex=""></a>        <span class="co">// prvo azuriramo odgovarajuci list</span></span>
<span id="cb5-57"><a href="#cb5-57" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> k <span class="op">=</span> i <span class="op">+</span> n<span class="op">;</span></span>
<span id="cb5-58"><a href="#cb5-58" aria-hidden="true" tabindex=""></a>        drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> v<span class="op">;</span></span>
<span id="cb5-59"><a href="#cb5-59" aria-hidden="true" tabindex=""></a>        <span class="co">// azuriramo sve roditelje izmenjenih cvorova</span></span>
<span id="cb5-60"><a href="#cb5-60" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span>k <span class="op">/=</span> <span class="dv">2</span><span class="op">;</span> k <span class="op">&gt;=</span> <span class="dv">1</span><span class="op">;</span> k <span class="op">/=</span> <span class="dv">2</span><span class="op">)</span></span>
<span id="cb5-61"><a href="#cb5-61" aria-hidden="true" tabindex=""></a>            drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb5-62"><a href="#cb5-62" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb5-63"><a href="#cb5-63" aria-hidden="true" tabindex=""></a>    </span>
<span id="cb5-64"><a href="#cb5-64" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">Main</span><span class="op">(</span><span class="dt">string</span><span class="op">[]</span> args<span class="op">)</span></span>
<span id="cb5-65"><a href="#cb5-65" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb5-66"><a href="#cb5-66" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">());</span></span>
<span id="cb5-67"><a href="#cb5-67" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> a <span class="op">=</span> <span class="kw">new</span> <span class="dt">int</span><span class="op">[</span>n<span class="op">];</span></span>
<span id="cb5-68"><a href="#cb5-68" aria-hidden="true" tabindex=""></a>        <span class="dt">string</span><span class="op">[]</span> str <span class="op">=</span> Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">().</span><span class="fu">Split</span><span class="op">();</span></span>
<span id="cb5-69"><a href="#cb5-69" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> n<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb5-70"><a href="#cb5-70" aria-hidden="true" tabindex=""></a>            a<span class="op">[</span>i<span class="op">]</span> <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span>i<span class="op">]);</span></span>
<span id="cb5-71"><a href="#cb5-71" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> drvo <span class="op">=</span> <span class="fu">formirajDrvo</span><span class="op">(</span>a<span class="op">);</span></span>
<span id="cb5-72"><a href="#cb5-72" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> m <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">());</span></span>
<span id="cb5-73"><a href="#cb5-73" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> m<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb5-74"><a href="#cb5-74" aria-hidden="true" tabindex=""></a>        <span class="op">{</span></span>
<span id="cb5-75"><a href="#cb5-75" aria-hidden="true" tabindex=""></a>            str <span class="op">=</span> Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">().</span><span class="fu">Split</span><span class="op">();</span></span>
<span id="cb5-76"><a href="#cb5-76" aria-hidden="true" tabindex=""></a>            <span class="kw">if</span> <span class="op">(</span>str<span class="op">[</span><span class="dv">0</span><span class="op">]</span> <span class="op">==</span> <span class="st">&quot;p&quot;</span><span class="op">)</span></span>
<span id="cb5-77"><a href="#cb5-77" aria-hidden="true" tabindex=""></a>            <span class="op">{</span></span>
<span id="cb5-78"><a href="#cb5-78" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> p <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">1</span><span class="op">]);</span></span>
<span id="cb5-79"><a href="#cb5-79" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> v <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">2</span><span class="op">]);</span></span>
<span id="cb5-80"><a href="#cb5-80" aria-hidden="true" tabindex=""></a>                <span class="fu">postavi</span><span class="op">(</span>drvo<span class="op">,</span> p<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb5-81"><a href="#cb5-81" aria-hidden="true" tabindex=""></a>            <span class="op">}</span></span>
<span id="cb5-82"><a href="#cb5-82" aria-hidden="true" tabindex=""></a>            <span class="kw">else</span> <span class="kw">if</span> <span class="op">(</span>str<span class="op">[</span><span class="dv">0</span><span class="op">]</span> <span class="op">==</span> <span class="st">&quot;z&quot;</span><span class="op">)</span></span>
<span id="cb5-83"><a href="#cb5-83" aria-hidden="true" tabindex=""></a>            <span class="op">{</span></span>
<span id="cb5-84"><a href="#cb5-84" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> l <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">1</span><span class="op">]);</span></span>
<span id="cb5-85"><a href="#cb5-85" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> d <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">2</span><span class="op">]);</span></span>
<span id="cb5-86"><a href="#cb5-86" aria-hidden="true" tabindex=""></a>                Console<span class="op">.</span><span class="fu">WriteLine</span><span class="op">(</span><span class="fu">zbirSegmenta</span><span class="op">(</span>drvo<span class="op">,</span> l<span class="op">,</span> d<span class="op">));</span></span>
<span id="cb5-87"><a href="#cb5-87" aria-hidden="true" tabindex=""></a>            <span class="op">}</span></span>
<span id="cb5-88"><a href="#cb5-88" aria-hidden="true" tabindex=""></a>        <span class="op">}</span></span>
<span id="cb5-89"><a href="#cb5-89" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb5-90"><a href="#cb5-90" aria-hidden="true" tabindex=""></a><span class="op">}</span></span></code></pre></div>
<!--- sol:end --->
<!--- sol:ex1 --->
<p>Претходни приступ формира дрво одоздо навише (прво се попуне листови,
па онда корен). Још један начин је да се дрво формира рекурзивно, одозго
наниже. Иако је ова имплементација компликованија и мало неефикаснија,
приступ одозго наниже је у неким каснијим операцијама неизбежан, па га
илуструјемо на овом једноставном примеру. Сваки чвор дрвета представља
збир одређеног сегмента позиција полазног низа. Сегмент је једнозначно
одређен позицијом <span class="math inline">\(k\)</span> у низу који
одговара сегментном дрвету, али да бисмо олакшали имлементацију границе
тог сегмента можемо кроз рекурзију прослеђивати као параметар функције,
заједно са вредношћу <span class="math inline">\(k\)</span> (нека је то
сегмент <span class="math inline">\([x, y]\)</span>). Дрво крећемо да
градимо од корена где је <span class="math inline">\(k=1\)</span> и
<span class="math inline">\([x,y] = [0, n-1]\)</span>. Ако родитељски
чвор покрива сегмент <span class="math inline">\([x, y]\)</span>, тада
лево дете покрива сегмент <span class="math inline">\([x,
\lfloor{\frac{x+y}{2}}\rfloor]\)</span>, а десно дете покрива сегмент
<span class="math inline">\([\lfloor{\frac{x+y}{2}}\rfloor+1,
y]\)</span>. Дрво попуњавамо рекурзивно, тако што прво попунимо лево
поддрво, затим десно и на крају вредност у корену израчунавамо као Дрво
попуњавамо рекурзивно, тако што прво попунимо лево поддрво, затим десно
и на крају вредност у корену израчунавамо као збир вредности у левом и
десном детету. Излаз из рекурзије представљају листови, које
препознајемо по томе што покривају сегменте дужине 1, и у њих само
копирамо елементе са одговарајућих позиција полазног низа.</p>
<p>И за операцију сабирања можемо направити и рекурзивну имплементацију
која врши израчунавање одозго наниже. За сваки чвор у сегментном дрвету
функција враћа колики је допринос сегмента који одговара том чвору и
његовим наследницима траженом збиру елемената на позицијама из сегмента
<span class="math inline">\([a, b]\)</span> у полазном низу. На почетку
крећемо од корена и рачунамо допринос целог дрвета збиру елемената из
сегмента <span class="math inline">\([a, b]\)</span>. Постоје три
различита могућа односа између сегмента <span class="math inline">\([x,
y]\)</span> који одговара текућем чвору и сегмента <span
class="math inline">\([a,b]\)</span> чији збир елемената тражимо. Ако су
дисјунктни, допринос текућег чвора збиру сегмента <span
class="math inline">\([a, b]\)</span> је нула. Ако је <span
class="math inline">\([x, y]\)</span> у потпуности садржан у <span
class="math inline">\([a, b]\)</span>, тада је допринос потпун, тј. цео
збир сегмента <span class="math inline">\([x, y]\)</span> (а то је број
уписан у низу на позицији <span class="math inline">\(k\)</span>)
доприноси збиру елемената на позицијама из сегмента <span
class="math inline">\([a, b]\)</span>. На крају, ако се сегменти секу,
тада је допринос текућег чвора једнак збиру доприноса његовог левог и
десног детета. Иако није сасвим очигледно, и ова процедура ће имати
сложност <span class="math inline">\(O(\log{n})\)</span>.</p>
<p>И операцију промене вредности елемената можемо имплементирати одозго
наниже. Сложеност је опет <span
class="math inline">\(O(\log{n})\)</span>, јер се дужина интервала <span
class="math inline">\([x, y]\)</span> у сваком кораку бар два пута
смањује.</p>
<div class="sourceCode" id="cb6"><pre class="sourceCode cs"><code class="sourceCode cs"><span id="cb6-1"><a href="#cb6-1" aria-hidden="true" tabindex=""></a><span class="kw">using</span> System<span class="op">;</span></span>
<span id="cb6-2"><a href="#cb6-2" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-3"><a href="#cb6-3" aria-hidden="true" tabindex=""></a><span class="kw">class</span> Program</span>
<span id="cb6-4"><a href="#cb6-4" aria-hidden="true" tabindex=""></a><span class="op">{</span></span>
<span id="cb6-5"><a href="#cb6-5" aria-hidden="true" tabindex=""></a>    <span class="co">// od elemenata niza a sa pozicija [x, y]</span></span>
<span id="cb6-6"><a href="#cb6-6" aria-hidden="true" tabindex=""></a>    <span class="co">// formira se segmentno drvo i elementi mu se smestaju u niz</span></span>
<span id="cb6-7"><a href="#cb6-7" aria-hidden="true" tabindex=""></a>    <span class="co">// drvo krenuvsi od pozicije k</span></span>
<span id="cb6-8"><a href="#cb6-8" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">formirajDrvo</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> a<span class="op">,</span> <span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> k<span class="op">,</span> <span class="dt">int</span> x<span class="op">,</span> <span class="dt">int</span> y<span class="op">)</span></span>
<span id="cb6-9"><a href="#cb6-9" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-10"><a href="#cb6-10" aria-hidden="true" tabindex=""></a>        <span class="kw">if</span> <span class="op">(</span>x <span class="op">==</span> y<span class="op">)</span></span>
<span id="cb6-11"><a href="#cb6-11" aria-hidden="true" tabindex=""></a>            <span class="co">// u listove prepisujemo elemente polaznog niza</span></span>
<span id="cb6-12"><a href="#cb6-12" aria-hidden="true" tabindex=""></a>            drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> x <span class="op">&lt;</span> a<span class="op">.</span><span class="fu">Length</span> <span class="op">?</span> a<span class="op">[</span>x<span class="op">]</span> <span class="op">:</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb6-13"><a href="#cb6-13" aria-hidden="true" tabindex=""></a>        <span class="kw">else</span></span>
<span id="cb6-14"><a href="#cb6-14" aria-hidden="true" tabindex=""></a>        <span class="op">{</span></span>
<span id="cb6-15"><a href="#cb6-15" aria-hidden="true" tabindex=""></a>            <span class="co">// rekurzivno formiramo levo i desno poddrvo</span></span>
<span id="cb6-16"><a href="#cb6-16" aria-hidden="true" tabindex=""></a>            <span class="dt">int</span> s <span class="op">=</span> <span class="op">(</span>x <span class="op">+</span> y<span class="op">)</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb6-17"><a href="#cb6-17" aria-hidden="true" tabindex=""></a>            <span class="fu">formirajDrvo</span><span class="op">(</span>a<span class="op">,</span> drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">,</span> x<span class="op">,</span> s<span class="op">);</span></span>
<span id="cb6-18"><a href="#cb6-18" aria-hidden="true" tabindex=""></a>            <span class="fu">formirajDrvo</span><span class="op">(</span>a<span class="op">,</span> drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">,</span> s<span class="op">+</span><span class="dv">1</span><span class="op">,</span> y<span class="op">);</span></span>
<span id="cb6-19"><a href="#cb6-19" aria-hidden="true" tabindex=""></a>            <span class="co">// izracunavamo vrednost u korenu</span></span>
<span id="cb6-20"><a href="#cb6-20" aria-hidden="true" tabindex=""></a>            drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb6-21"><a href="#cb6-21" aria-hidden="true" tabindex=""></a>        <span class="op">}</span></span>
<span id="cb6-22"><a href="#cb6-22" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-23"><a href="#cb6-23" aria-hidden="true" tabindex=""></a>    </span>
<span id="cb6-24"><a href="#cb6-24" aria-hidden="true" tabindex=""></a>    <span class="co">// najmanji stepen dvojke veci ili jednak od n</span></span>
<span id="cb6-25"><a href="#cb6-25" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span> <span class="fu">stepenDvojke</span><span class="op">(</span><span class="dt">int</span> n<span class="op">)</span></span>
<span id="cb6-26"><a href="#cb6-26" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-27"><a href="#cb6-27" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> s <span class="op">=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb6-28"><a href="#cb6-28" aria-hidden="true" tabindex=""></a>        <span class="kw">while</span> <span class="op">(</span>s <span class="op">&lt;</span> n<span class="op">)</span></span>
<span id="cb6-29"><a href="#cb6-29" aria-hidden="true" tabindex=""></a>            s <span class="op">&lt;&lt;=</span> <span class="dv">1</span><span class="op">;</span></span>
<span id="cb6-30"><a href="#cb6-30" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> s<span class="op">;</span></span>
<span id="cb6-31"><a href="#cb6-31" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-32"><a href="#cb6-32" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-33"><a href="#cb6-33" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-34"><a href="#cb6-34" aria-hidden="true" tabindex=""></a>    <span class="co">// na osnovu datog niza a duzine n u kom su elementi smesteni od</span></span>
<span id="cb6-35"><a href="#cb6-35" aria-hidden="true" tabindex=""></a>    <span class="co">// pozicije 0 formira se segmentno drvo i elementi mu se smestaju u</span></span>
<span id="cb6-36"><a href="#cb6-36" aria-hidden="true" tabindex=""></a>    <span class="co">// niz drvo krenuvši od pozicije 1</span></span>
<span id="cb6-37"><a href="#cb6-37" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span><span class="op">[]</span> <span class="fu">formirajDrvo</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> a<span class="op">)</span></span>
<span id="cb6-38"><a href="#cb6-38" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-39"><a href="#cb6-39" aria-hidden="true" tabindex=""></a>        <span class="co">// niz implicitno dopunjujemo nulama tako da mu duzina postane</span></span>
<span id="cb6-40"><a href="#cb6-40" aria-hidden="true" tabindex=""></a>        <span class="co">// najblizi stepen dvojke</span></span>
<span id="cb6-41"><a href="#cb6-41" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> <span class="fu">stepenDvojke</span><span class="op">(</span>a<span class="op">.</span><span class="fu">Length</span><span class="op">);</span></span>
<span id="cb6-42"><a href="#cb6-42" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> drvo <span class="op">=</span> <span class="kw">new</span> <span class="dt">int</span><span class="op">[</span><span class="dv">2</span><span class="op">*</span>n<span class="op">];</span></span>
<span id="cb6-43"><a href="#cb6-43" aria-hidden="true" tabindex=""></a>        <span class="co">// krecemo formiranje od korena koji se nalazi u nizu drvo</span></span>
<span id="cb6-44"><a href="#cb6-44" aria-hidden="true" tabindex=""></a>        <span class="co">// na poziciji 1 i pokriva elemente na pozicijama [0, n-1]</span></span>
<span id="cb6-45"><a href="#cb6-45" aria-hidden="true" tabindex=""></a>        <span class="fu">formirajDrvo</span><span class="op">(</span>a<span class="op">,</span> drvo<span class="op">,</span> <span class="dv">1</span><span class="op">,</span> <span class="dv">0</span><span class="op">,</span> n <span class="op">-</span> <span class="dv">1</span><span class="op">);</span></span>
<span id="cb6-46"><a href="#cb6-46" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> drvo<span class="op">;</span></span>
<span id="cb6-47"><a href="#cb6-47" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-48"><a href="#cb6-48" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-49"><a href="#cb6-49" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-50"><a href="#cb6-50" aria-hidden="true" tabindex=""></a>    <span class="co">// izracunava se zbir onih elemenata polaznog niza koji se</span></span>
<span id="cb6-51"><a href="#cb6-51" aria-hidden="true" tabindex=""></a>    <span class="co">// nalaze na pozicijama iz segmenta [a, b] koji se nalaze u </span></span>
<span id="cb6-52"><a href="#cb6-52" aria-hidden="true" tabindex=""></a>    <span class="co">// segmentnom drvetu koje cuva elemente polaznog niza koji se </span></span>
<span id="cb6-53"><a href="#cb6-53" aria-hidden="true" tabindex=""></a>    <span class="co">// nalaze na pozicijama iz segmenta [x, y] i smesteno je u nizu</span></span>
<span id="cb6-54"><a href="#cb6-54" aria-hidden="true" tabindex=""></a>    <span class="co">// drvo od pozicije k</span></span>
<span id="cb6-55"><a href="#cb6-55" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span> <span class="fu">zbirSegmenta</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> k<span class="op">,</span> <span class="dt">int</span> x<span class="op">,</span> <span class="dt">int</span> y<span class="op">,</span> <span class="dt">int</span> a<span class="op">,</span> <span class="dt">int</span> b<span class="op">)</span></span>
<span id="cb6-56"><a href="#cb6-56" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-57"><a href="#cb6-57" aria-hidden="true" tabindex=""></a>        <span class="co">// segmenti [x, y] i [a, b] su disjunktni</span></span>
<span id="cb6-58"><a href="#cb6-58" aria-hidden="true" tabindex=""></a>        <span class="kw">if</span> <span class="op">(</span>b <span class="op">&lt;</span> x <span class="op">||</span> a <span class="op">&gt;</span> y<span class="op">)</span> <span class="kw">return</span> <span class="dv">0</span><span class="op">;</span></span>
<span id="cb6-59"><a href="#cb6-59" aria-hidden="true" tabindex=""></a>        <span class="co">// segment [x, y] je potpuno sadržan unutar segmenta [a, b]</span></span>
<span id="cb6-60"><a href="#cb6-60" aria-hidden="true" tabindex=""></a>        <span class="kw">if</span> <span class="op">(</span>a <span class="op">&lt;=</span> x <span class="op">&amp;&amp;</span> y <span class="op">&lt;=</span> b<span class="op">)</span></span>
<span id="cb6-61"><a href="#cb6-61" aria-hidden="true" tabindex=""></a>            <span class="kw">return</span> drvo<span class="op">[</span>k<span class="op">];</span></span>
<span id="cb6-62"><a href="#cb6-62" aria-hidden="true" tabindex=""></a>        <span class="co">// segmenti [x, y] i [a, b] se seku</span></span>
<span id="cb6-63"><a href="#cb6-63" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> s <span class="op">=</span> <span class="op">(</span>x <span class="op">+</span> y<span class="op">)</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb6-64"><a href="#cb6-64" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> <span class="fu">zbirSegmenta</span><span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">,</span> x<span class="op">,</span> s<span class="op">,</span> a<span class="op">,</span> b<span class="op">)</span> <span class="op">+</span> </span>
<span id="cb6-65"><a href="#cb6-65" aria-hidden="true" tabindex=""></a>               <span class="fu">zbirSegmenta</span><span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">,</span> s<span class="op">+</span><span class="dv">1</span><span class="op">,</span> y<span class="op">,</span> a<span class="op">,</span> b<span class="op">);</span></span>
<span id="cb6-66"><a href="#cb6-66" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-67"><a href="#cb6-67" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-68"><a href="#cb6-68" aria-hidden="true" tabindex=""></a>    <span class="co">// izracunava se zbir elemenata polaznog niza duzine n koji se </span></span>
<span id="cb6-69"><a href="#cb6-69" aria-hidden="true" tabindex=""></a>    <span class="co">// nalaze na pozicijama iz segmenta [a, b] na osnovu segmentnog drveta</span></span>
<span id="cb6-70"><a href="#cb6-70" aria-hidden="true" tabindex=""></a>    <span class="co">// koje je smesteno u nizu drvo, krenuvši od pozicije 1</span></span>
<span id="cb6-71"><a href="#cb6-71" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">int</span> <span class="fu">zbirSegmenta</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> a<span class="op">,</span> <span class="dt">int</span> b<span class="op">)</span></span>
<span id="cb6-72"><a href="#cb6-72" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-73"><a href="#cb6-73" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span><span class="fu">Length</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb6-74"><a href="#cb6-74" aria-hidden="true" tabindex=""></a>        <span class="co">// krećemo od drveta smeštenog od pozicije 1 koje</span></span>
<span id="cb6-75"><a href="#cb6-75" aria-hidden="true" tabindex=""></a>        <span class="co">// sadrži elemente polaznog niza na pozicijama iz segmenta [0, n-1]</span></span>
<span id="cb6-76"><a href="#cb6-76" aria-hidden="true" tabindex=""></a>        <span class="kw">return</span> <span class="fu">zbirSegmenta</span><span class="op">(</span>drvo<span class="op">,</span> <span class="dv">1</span><span class="op">,</span> <span class="dv">0</span><span class="op">,</span> n<span class="dv">-1</span><span class="op">,</span> a<span class="op">,</span> b<span class="op">);</span></span>
<span id="cb6-77"><a href="#cb6-77" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-78"><a href="#cb6-78" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-79"><a href="#cb6-79" aria-hidden="true" tabindex=""></a>    <span class="co">// azurira segmentno drvo smesteno u niz drvo od pozicije k</span></span>
<span id="cb6-80"><a href="#cb6-80" aria-hidden="true" tabindex=""></a>    <span class="co">// koje sadrzi elemente polaznog niza a duzine n sa pozicija iz</span></span>
<span id="cb6-81"><a href="#cb6-81" aria-hidden="true" tabindex=""></a>    <span class="co">// segmenta [x, y], nakon sto se na poziciju i niza upise vrednost v</span></span>
<span id="cb6-82"><a href="#cb6-82" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">postavi</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> k<span class="op">,</span> <span class="dt">int</span> x<span class="op">,</span> <span class="dt">int</span> y<span class="op">,</span> <span class="dt">int</span> i<span class="op">,</span> <span class="dt">int</span> v<span class="op">)</span></span>
<span id="cb6-83"><a href="#cb6-83" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-84"><a href="#cb6-84" aria-hidden="true" tabindex=""></a>        <span class="kw">if</span> <span class="op">(</span>x <span class="op">==</span> y<span class="op">)</span></span>
<span id="cb6-85"><a href="#cb6-85" aria-hidden="true" tabindex=""></a>            <span class="co">// azuriramo vrednost u listu</span></span>
<span id="cb6-86"><a href="#cb6-86" aria-hidden="true" tabindex=""></a>            drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> v<span class="op">;</span></span>
<span id="cb6-87"><a href="#cb6-87" aria-hidden="true" tabindex=""></a>        <span class="kw">else</span> <span class="op">{</span></span>
<span id="cb6-88"><a href="#cb6-88" aria-hidden="true" tabindex=""></a>            <span class="co">// proveravamo da li se pozicija i nalazi levo ili desno</span></span>
<span id="cb6-89"><a href="#cb6-89" aria-hidden="true" tabindex=""></a>            <span class="co">// i u zavisnosti od toga azuriramo odgovarajuće poddrvo</span></span>
<span id="cb6-90"><a href="#cb6-90" aria-hidden="true" tabindex=""></a>            <span class="dt">int</span> s <span class="op">=</span> <span class="op">(</span>x <span class="op">+</span> y<span class="op">)</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb6-91"><a href="#cb6-91" aria-hidden="true" tabindex=""></a>            <span class="kw">if</span> <span class="op">(</span>x <span class="op">&lt;=</span> i <span class="op">&amp;&amp;</span> i <span class="op">&lt;=</span> s<span class="op">)</span></span>
<span id="cb6-92"><a href="#cb6-92" aria-hidden="true" tabindex=""></a>                <span class="fu">postavi</span><span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">,</span> x<span class="op">,</span> s<span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb6-93"><a href="#cb6-93" aria-hidden="true" tabindex=""></a>            <span class="kw">else</span></span>
<span id="cb6-94"><a href="#cb6-94" aria-hidden="true" tabindex=""></a>                <span class="fu">postavi</span><span class="op">(</span>drvo<span class="op">,</span> <span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">,</span> s<span class="op">+</span><span class="dv">1</span><span class="op">,</span> y<span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb6-95"><a href="#cb6-95" aria-hidden="true" tabindex=""></a>            <span class="co">// posto se postavila vrednost u nekom od dva poddrveta</span></span>
<span id="cb6-96"><a href="#cb6-96" aria-hidden="true" tabindex=""></a>            <span class="co">// moramo azurirati vrednost u korenu</span></span>
<span id="cb6-97"><a href="#cb6-97" aria-hidden="true" tabindex=""></a>            drvo<span class="op">[</span>k<span class="op">]</span> <span class="op">=</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">]</span> <span class="op">+</span> drvo<span class="op">[</span><span class="dv">2</span><span class="op">*</span>k<span class="op">+</span><span class="dv">1</span><span class="op">];</span></span>
<span id="cb6-98"><a href="#cb6-98" aria-hidden="true" tabindex=""></a>        <span class="op">}</span></span>
<span id="cb6-99"><a href="#cb6-99" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-100"><a href="#cb6-100" aria-hidden="true" tabindex=""></a></span>
<span id="cb6-101"><a href="#cb6-101" aria-hidden="true" tabindex=""></a>    <span class="co">// azurira segmentno drvo smesteno u niz drvo od pozicije 1</span></span>
<span id="cb6-102"><a href="#cb6-102" aria-hidden="true" tabindex=""></a>    <span class="co">// koje sadrzi elemente polaznog niza a dužine n u kom su elementi</span></span>
<span id="cb6-103"><a href="#cb6-103" aria-hidden="true" tabindex=""></a>    <span class="co">// smesteni od pozicije 0, nakon sto se na poziciju i polaznog</span></span>
<span id="cb6-104"><a href="#cb6-104" aria-hidden="true" tabindex=""></a>    <span class="co">// niza upise vrednost v</span></span>
<span id="cb6-105"><a href="#cb6-105" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">postavi</span><span class="op">(</span><span class="dt">int</span><span class="op">[]</span> drvo<span class="op">,</span> <span class="dt">int</span> i<span class="op">,</span> <span class="dt">int</span> v<span class="op">)</span></span>
<span id="cb6-106"><a href="#cb6-106" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-107"><a href="#cb6-107" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> drvo<span class="op">.</span><span class="fu">Length</span> <span class="op">/</span> <span class="dv">2</span><span class="op">;</span></span>
<span id="cb6-108"><a href="#cb6-108" aria-hidden="true" tabindex=""></a>        <span class="co">// krećemo od drveta smestenog od pozicije 1 koje</span></span>
<span id="cb6-109"><a href="#cb6-109" aria-hidden="true" tabindex=""></a>        <span class="co">// sadrzi elemente polaznog niza na pozicijama iz segmenta [0, n-1]</span></span>
<span id="cb6-110"><a href="#cb6-110" aria-hidden="true" tabindex=""></a>        <span class="fu">postavi</span><span class="op">(</span>drvo<span class="op">,</span> <span class="dv">1</span><span class="op">,</span> <span class="dv">0</span><span class="op">,</span> n<span class="dv">-1</span><span class="op">,</span> i<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb6-111"><a href="#cb6-111" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-112"><a href="#cb6-112" aria-hidden="true" tabindex=""></a>    </span>
<span id="cb6-113"><a href="#cb6-113" aria-hidden="true" tabindex=""></a>    <span class="kw">static</span> <span class="dt">void</span> <span class="fu">Main</span><span class="op">(</span><span class="dt">string</span><span class="op">[]</span> args<span class="op">)</span></span>
<span id="cb6-114"><a href="#cb6-114" aria-hidden="true" tabindex=""></a>    <span class="op">{</span></span>
<span id="cb6-115"><a href="#cb6-115" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> n <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">());</span></span>
<span id="cb6-116"><a href="#cb6-116" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> a <span class="op">=</span> <span class="kw">new</span> <span class="dt">int</span><span class="op">[</span>n<span class="op">];</span></span>
<span id="cb6-117"><a href="#cb6-117" aria-hidden="true" tabindex=""></a>        <span class="dt">string</span><span class="op">[]</span> str <span class="op">=</span> Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">().</span><span class="fu">Split</span><span class="op">();</span></span>
<span id="cb6-118"><a href="#cb6-118" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> n<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb6-119"><a href="#cb6-119" aria-hidden="true" tabindex=""></a>            a<span class="op">[</span>i<span class="op">]</span> <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span>i<span class="op">]);</span></span>
<span id="cb6-120"><a href="#cb6-120" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span><span class="op">[]</span> drvo <span class="op">=</span> <span class="fu">formirajDrvo</span><span class="op">(</span>a<span class="op">);</span></span>
<span id="cb6-121"><a href="#cb6-121" aria-hidden="true" tabindex=""></a>        <span class="dt">int</span> m <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">());</span></span>
<span id="cb6-122"><a href="#cb6-122" aria-hidden="true" tabindex=""></a>        <span class="kw">for</span> <span class="op">(</span><span class="dt">int</span> i <span class="op">=</span> <span class="dv">0</span><span class="op">;</span> i <span class="op">&lt;</span> m<span class="op">;</span> i<span class="op">++)</span></span>
<span id="cb6-123"><a href="#cb6-123" aria-hidden="true" tabindex=""></a>        <span class="op">{</span></span>
<span id="cb6-124"><a href="#cb6-124" aria-hidden="true" tabindex=""></a>            str <span class="op">=</span> Console<span class="op">.</span><span class="fu">ReadLine</span><span class="op">().</span><span class="fu">Split</span><span class="op">();</span></span>
<span id="cb6-125"><a href="#cb6-125" aria-hidden="true" tabindex=""></a>            <span class="kw">if</span> <span class="op">(</span>str<span class="op">[</span><span class="dv">0</span><span class="op">]</span> <span class="op">==</span> <span class="st">&quot;p&quot;</span><span class="op">)</span></span>
<span id="cb6-126"><a href="#cb6-126" aria-hidden="true" tabindex=""></a>            <span class="op">{</span></span>
<span id="cb6-127"><a href="#cb6-127" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> p <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">1</span><span class="op">]);</span></span>
<span id="cb6-128"><a href="#cb6-128" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> v <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">2</span><span class="op">]);</span></span>
<span id="cb6-129"><a href="#cb6-129" aria-hidden="true" tabindex=""></a>                <span class="fu">postavi</span><span class="op">(</span>drvo<span class="op">,</span> p<span class="op">,</span> v<span class="op">);</span></span>
<span id="cb6-130"><a href="#cb6-130" aria-hidden="true" tabindex=""></a>            <span class="op">}</span></span>
<span id="cb6-131"><a href="#cb6-131" aria-hidden="true" tabindex=""></a>            <span class="kw">else</span> <span class="kw">if</span> <span class="op">(</span>str<span class="op">[</span><span class="dv">0</span><span class="op">]</span> <span class="op">==</span> <span class="st">&quot;z&quot;</span><span class="op">)</span></span>
<span id="cb6-132"><a href="#cb6-132" aria-hidden="true" tabindex=""></a>            <span class="op">{</span></span>
<span id="cb6-133"><a href="#cb6-133" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> l <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">1</span><span class="op">]);</span></span>
<span id="cb6-134"><a href="#cb6-134" aria-hidden="true" tabindex=""></a>                <span class="dt">int</span> d <span class="op">=</span> <span class="dt">int</span><span class="op">.</span><span class="fu">Parse</span><span class="op">(</span>str<span class="op">[</span><span class="dv">2</span><span class="op">]);</span></span>
<span id="cb6-135"><a href="#cb6-135" aria-hidden="true" tabindex=""></a>                Console<span class="op">.</span><span class="fu">WriteLine</span><span class="op">(</span><span class="fu">zbirSegmenta</span><span class="op">(</span>drvo<span class="op">,</span> l<span class="op">,</span> d<span class="op">));</span></span>
<span id="cb6-136"><a href="#cb6-136" aria-hidden="true" tabindex=""></a>            <span class="op">}</span></span>
<span id="cb6-137"><a href="#cb6-137" aria-hidden="true" tabindex=""></a>        <span class="op">}</span></span>
<span id="cb6-138"><a href="#cb6-138" aria-hidden="true" tabindex=""></a>    <span class="op">}</span></span>
<span id="cb6-139"><a href="#cb6-139" aria-hidden="true" tabindex=""></a><span class="op">}</span></span></code></pre></