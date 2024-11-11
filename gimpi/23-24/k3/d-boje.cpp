#include <iostream>
using namespace std;
/* Gleda se slučaj u kojem pokušaj ne sadrži dva ista slova. Rešenje za ovaj slucaj nosilo je 15 bodova.
Petljom se prolazi po slovima pokušaja i ispisuje ’G’ ako se trenutno slovo podudara s
odgovarajucim slovom tražene reci, inače drugom petljom prolazimo po svim slovima tražene
reci i ispisujemo ’R’ ako medju njima pronadjemo trenutno slovo pokušaja, a u suprotnom ispisujemo ’B’.
Za sve bodove ovo rešenje nadogradjujemo pomocnim nizom xmz u koji za svako slovo xmz(slovo) 
na pocetku zapisujemo odgovarajucu vrijednost X − Z, gdje X i Z odgovaraju oznakama iz teksta zadatka. 
Pri ispisu rešenja, za svako slovo u pokušaju koje nije zeleno, provjeravamo je li xmz(slovo) > 0. 
Ako jeste, ispisuje se ’R’ i smanjuje vrednost xmz(slovo) za 1, a u suprotnom ispisujemo ’B’. */
int xmz[30];

string color(string guess, string sol) {
    string ret = "";
    for (int i = 0; i < 5; i++) {
        xmz[sol[i] - 'a']++;
        if (guess[i] == sol[i])
            xmz[guess[i] - 'a']--;     } 
    for (int i = 0; i < 5; i++) {
        int l = guess[i] - 'a';
        if (guess[i] == sol[i])
            ret += 'G';
        else if (xmz[l] > 0) {
            ret += 'R';
            xmz[l]--; }
        else
            ret += 'B'; }
    return ret; }

int main() {
    string guess, sol;
    cin >> guess >> sol;
    cout << color(guess, sol) << endl;
    return 0; }