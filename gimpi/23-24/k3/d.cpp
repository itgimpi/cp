#include <iostream>
using namespace std;

int xmz[30];

string color(string guess, string sol) {
    string ret = "";
    for (int i = 0; i < 5; i++) {
        xmz[sol[i] - 'a']++;
        if (guess[i] == sol[i])
            xmz[guess[i] - 'a']--;
    } 
    for (int i = 0; i < 5; i++) {
        int l = guess[i] - 'a';
        if (guess[i] == sol[i])
            ret += 'G';
        else
            if (xmz[l] > 0) {
                ret += 'R';
                xmz[l]--;            
            }
        else
            ret += 'B';
    }
    return ret;
}

int main() {
    string guess, sol;
    cin >> guess >> sol;
    cout << color(guess, sol) << endl;
    return 0;
}