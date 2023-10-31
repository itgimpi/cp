#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
    string rec;
    int n,z,k,r,e,t,p,mini,red[4],red2[4],p1,maksi,k1,e1,t1,r1;
    cin>>n>>z>>rec;
    k=0;
    r=0;
    e=0;
    t=0;
    p=0;
    k1=0;
    r1=0;
    e1=0;
    t1=0;
    p1=0;
    for(int i=0;i<n;i++){
        if(rec[i]=='k')k+=1;
        else if(rec[i]=='r')r+=1;
        else if(rec[i]=='e')e+=1;
        else if(rec[i]=='t')t+=1;
    }
    k1=k;
    r1=r;
    e1=e;
    t1=t;
    maksi=max(max(k,r),max(e,t));
    
    if(maksi==k1)k1+=z;
    else if(maksi==e1)e1+=z;
    else if(maksi==t1)t1+=z;
    else if(maksi==r1)r1+=z;
    mini=min(min(k1/2,e1/2),min(t1,r1));
    p1=k1*k1+r1*r1+t1*t1+e1*e1+mini*7;
    
    for(int j=0;j<z;j++){
        mini=min(min(k/2,e/2),min(t,r));
        if(mini==k/2)k++;
        else if(mini==e/2)e++;
        else if(mini==t)t++;
        else if(mini==r)r++;
        
        
    }
    mini=min(min(k/2,e/2),min(t,r));
    p=k*k+r*r+e*e+t*t+mini*7;
    cout<<max(p,p1);

    return 0;
}