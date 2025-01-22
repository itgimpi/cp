#include <iostream>
using namespace std;

int ack(int m, int n) {
	if (m == 0) // prvi arg. je 0
		return n + 1;
	else if((m > 0) && (n == 0)) // drugi arg. je 0
		return ack(m - 1, 1);
	//else if((m > 0) && (n > 0))
		return ack(m - 1, ack(m, n - 1)); }


int main() {
	
    for (int m = 0; m < 6; m++)
        for (int n = 0; n < 6; n++)
            cout << "ack(" << m << "," << n << ")=" << ack(m,n) << endl; 

	return 0; }


