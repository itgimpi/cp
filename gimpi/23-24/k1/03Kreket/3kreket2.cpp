#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    int m,n,rmax=0;
    std::string s;

    std::cin >> m >> n;
    std::cin >> s;

    for(int i=0;i<1<<(n*2);++i)
    {
        std::string l("kret");
        int b[4]={0, 0, 0, 0};
        int k=i;
        std::string sz=s;
        for(int j=0;j<n;++j)
        {
            sz+=l[k%4];
            k/=4;
        }
        for(int j=0;j<(int)sz.size();++j) ++b[l.find_first_of(sz[j])];
        int r=0;
        for(int j=0;j<4;++j) r+=b[j]*b[j];
        b[0]/=2;
        b[2]/=2;
        r+=*(std::min_element(b,b+4))*7;
        if(rmax<r) rmax=r;
    }
    std::cout << rmax << std::endl;
    return 0;
}