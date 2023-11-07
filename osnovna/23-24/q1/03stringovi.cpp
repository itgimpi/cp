#include <bits/stdc++.h>
using namespace std;



int main() {

    vector <string> v;
    string s;

    bool kraj = false;

    while(!kraj)
    {

        cin >> s;

        if (s == "gotovo")
        {

            kraj = true;

        }

        else{

            v.push_back(s);

        }


    }

    int n = v.size();
    for (int i = 0; i <= n-2; i++)
    {

        cout << v[i] << ", ";



    }

    if (n == 1)
    {

        cout << v[0];

    }

    else{
        cout << "i " << v[n-1];}

    

    return 0;
}