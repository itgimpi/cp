# Rešenje
	
| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Igor Pavlović | Igor Pavlović | Igor Pavlović | Nikola Pešić |
	
## Rešenje kada $N=M, a_i \leq c_i \leq b_i \leq d_i$
U ovom podzadatku je dovoljno duž dijagonale posaditi $b_i$ krompira.
	
## Rešenje kada $a_i = b_i, c_i = d_i$
Za rešavanje ovog podzadatka možemo primeniti tehniku dva pokazivača. Pokazivač $i$ iterira po redovima, a pokazivač $j$ iterira po kolonama.
Ako je $b_i=0$ ili $d_i=0$ tada uvećamo $i$ to jest $j$ za 1. Ako je $b_i \neq 0$ i $d_j \neq 0$ posadi $min(b_i,d_j)$ krompira na polje $i, j$ i smanji $b_i$ i $d_j$ za $min(b_i,d_j)$.
	
## Rešenje kada $a_i = b_i$
Ovaj podzadatak možemo rešiti analogno prethodnom. U ovom podzadatku je potrebno iterirati po kolonama 2 puta. Prvi put postavljamo broj krompira u svakoj koloni na donju granicu, a drugi put na gornju i ažuriramo broj krompira u svakoj koloni. Kada završimo sa iteracijom po redovima tada prekidamo iteraciju po kolonama takođe. Nakon što smo odredili broj krompira u svakoj koloni možemo primeniti rešenje iz prethodnog podzadatka.
	
## Rešenje kada $N = 1$
U slučaju da važi $\sum_{i=1}^{M} d_i \leq b_1$ dovoljno je samo u $i$-toj koloni posaditi $d_i$ krompira.
	
U suprotnom se rešenje ovog podzadatka svodi na rešenje prethodnog kada donju granicu postavimo da bude jednaka gornjoj (jer je neophodno posaditi $b_i$ krompira u prvom redu kako bismo maksimizovali prinos).
	
## Rešenje kada $a_i = c_i = 0$
Ovaj podzadatak možemo rešiti gramzivom metodom i tehnikom 2 pokazivača. Pokazivač $i$ iterira po redovima, a pokazivač $j$ iterira po kolonama.
Ako je $b_i=0$ ili $d_i=0$ tada uvećamo $i$ to jest $j$ za 1. Ako je $b_i \neq 0$ i $d_j \neq 0$ posadi $min(b_i,d_j)$ krompira na polje $i, j$ i smanji $b_i$ i $d_j$ za $min(b_i,d_j)$. Primetimo da je ovo rešenje identično podzadatku 2 samo što je u ovom slučaju neophono završiti iteraciju po kolonama čim se završi iteracija po vrstama i obrnuto. U podzadatku 2 se ove dve iteracije zaršavaju istovremeno s obirom da rešenje mora postojati.
	
## Glavno rešenje
Primetimo prvo da nije moguće posaditi više od $min(\sum_{i=1}^{N} b_i,\sum_{j=1}^{M} d_i)$ krompira ukupno. Dakle ukoliko konstruišemo rešenje sa tačno $min(\sum_{i=1}^{N} b_i,\sum_{j=1}^{M} d_i)$ krompira onda smo takođe dostigli maksimalan mogući prinos.
	
Bez umanjenja opštosti pretpostavimo da važi $\sum_{i=1}^{N} b_i \leq \sum_{j=1}^{M} d_i$. Da bismo maksimizovali prinos potrebno je u svakom redu posaditi $b_i$ krompira. Pošto nam je poznat broj krompira koji je potrebno posaditi u svakom redu sada se rešenje zadatka svodi na rešenje podzadatka 3. Primetimo takođe da ukuliko postoji neko rešenje tada važi $\sum_{j=1}^{M} c_i \leq \sum_{i=1}^{N} b_i$, odakle sledi da moguće konstruisati rešenje sa tačno $min(\sum_{i=1}^{N} b_i,\sum_{j=1}^{M} d_i)$ primenom algoritma iz podzadatka 3.
	
``` cpp title="05_krompiri.cpp" linenums="1"
#include <bits/stdc++.h>
#define maxN 50005
	
using namespace std;
	
int n,m,a[maxN],b[maxN],c[maxN],d[maxN],cnt[maxN],i,j;
bool transposed = false;
long long s1=0,s2=0,sl=0;
	
vector<pair<pair<int,int>,int>> ans;
	
int main() {
	std::ios_base::sync_with_stdio(false);
		
	cin>>n>>m;
	for(i=0;i<n;i++){
		cin>>a[i]>>b[i];
		s1+=b[i];
	}
		
	for(i=0;i<m;i++){
		cin>>c[i]>>d[i];
		s2+=d[i];
	}
		
	if(s2<s1){
		transposed=true;
		swap(s1,s2);
		swap(n,m);
		for(i=0;i<max(n,m);i++){
			swap(a[i],c[i]);
			swap(b[i],d[i]);
		}
	}
		
	cout<<s1<<endl;
		
	for(i=0;i<m;i++) sl+=c[i];
		
	long long dif = s1-sl;
		
	for(i=0;i<m;i++){
		cnt[i]=min((long long)d[i],c[i]+dif);
		dif-=cnt[i]-c[i];
	}
		
	i=j=0;
		
	while(i<n && j<m){
		if(b[i]==0){
			i++;
			continue;
		}
		if(cnt[j]==0){
			j++;
			continue;
		}
		int tmp = min(b[i],cnt[j]);
		ans.push_back({{i+1,j+1},tmp});
		b[i]-=tmp;
		cnt[j]-=tmp;
	}
		
	cout<<ans.size()<<endl;
		
	for(i=0;i<ans.size();i++){
		if(transposed) {
			swap(ans[i].first.first,ans[i].first.second);
		}
		cout<<ans[i].first.first<<" "<<ans[i].first.second<<" "<<ans[i].second<<endl;
	}
	return 0;
}
```
