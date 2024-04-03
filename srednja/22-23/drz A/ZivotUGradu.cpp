#include <bits\stdc++.h>
#define MAXN 3007
using namespace std;
int a[MAXN][MAXN],dp[2][MAXN][MAXN]; // dve dp matric, jedna traži min druga max vrednost do tog polja
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t,z;
    for(int i=0;i<MAXN;i++) dp[0][0][i]=dp[0][i][0]=1000000000;
    cin>>t>>z;
    while(t--)
    {
        int n,m,k;
        cin>>n>>m>>k;
        for(int i=1;i<=n;i++)
        {
            string s;
            cin>>s;
            for(int j=1;j<=m;j++) a[i][j]=s[j-1]-'0'; //unos koncerata
        }
        dp[0][1][1]=dp[1][1][1]=a[1][1]; //početno polje ulazi u dp matrice i kao minimalan i kao maksimalan broj koncerata do tog polja
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)
        {
            if(i==1 && j==1) continue; // preskace se to prvo polje
            dp[0][i][j]=min(dp[0][i-1][j],dp[0][i][j-1])+a[i][j]; //dp[0] je min i tu se belezi najamanji broj koncerata
            dp[1][i][j]=max(dp[1][i-1][j],dp[1][i][j-1])+a[i][j]; //dp[1] je max i tu se belezi najveći broj koncerata
        }
        if((k<dp[0][n][m]) || (k>dp[1][n][m])) {cout<<"NE"<<endl; continue;} //ako je broj potrebnih koncerata na zadnjem polju  manji od najmanjeg mogućeg ili veći od najvećeg mogućeg, ispisuje se NE
        cout<<"DA\n"; // u drugom slučaju se ispisue DA
        if(!z) continue; //Ako je z==0, ne treba se ispisati resenje
        int x=n,y=m,cur=k; //x i z uzimaju vrednosti n i m, koje se u while petlji smanjuju jer u stringu res (sledeći red) se unose karakteri D i S u obrnutom redosledu. current je trenutni broj koncerata, odnosno koliko još fale do 0
        string res="";
        while(x!=1 || y!=1) //petlja proverava sve dok nisu na početnom polju, dok se na x==0 ili y==0 nalaze vrednosti 1000000000 koji nikada nece biti izabran
        {
    
            cur-=a[x][y]; //ako je na polju gde se održava koncert, umanji se za 1
            if(cur>=dp[0][x-1][y] && cur<=dp[1][x-1][y]) {x--; res+='S';} //ako je polje iznad u dobrom opsegu, do trenutnog polja se dolazi karaktreom S, ako ne može, onda je karakter D
            else {y--; res+='D';}
        }
        reverse(res.begin(),res.end()); //Pošto se krenulo od kraja, obrne se rešenje
        cout<<res<<endl;
    }
}