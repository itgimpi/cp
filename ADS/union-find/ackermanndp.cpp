#include <iostream>
#include <string>
#include <vector>
typedef long long int ll;
using namespace std;

ll Ackermann(int m, int n){  // Bottom Up Approach 
	// creating 2D LIST 
	vector<vector<long long int>> dp(m + 1, vector<long long int>(n + 1, 0));

	for (int rows = 0 ; rows < m + 1 ; rows++){ 
		for (int cols = 0 ; cols < n + 1 ; cols++){ 

			// base case A ( 0, n ) = n + 1 
			if (rows == 0)
				dp[rows][cols] = cols + 1;

			// base case A ( m, 0 ) = A ( m-1, 1) [Computed already] 
			else if (cols == 0)
				dp[rows][cols] = dp[rows-1][1];

			else {
				// if rows and cols > 0 
				// then A ( m, n ) =  A ( m-1, A ( m, n-1 ) ) 
				long long int r = rows - 1;
				long long int c = dp[rows][cols-1];
				long long int ans;
				
				// applying equation (2) A ( 0, n ) = n + 1 
				if (r == 0)
					ans = c + 1;
				else if (c <= n)
					// using stored value in dp 
					ans = dp[rows-1][dp[rows][cols-1]];
				else
					// Using the Derived Formula 
					// to compute mystery values in O(1) time 
					ans = (c-n)*(r) + dp[r][n];

				dp[rows][cols] = ans; }	} }
	return dp[m][n]; }


// Driver code
int main()
{

	// very small values 
	int m = 2; 
	int n = 2;

	// a bit higher value 
	int m1 = 5; 
	int n1 = 7;


	cout << "Ackermann value for m = " << m <<
	" and n = " << n << " is -> " << 
	Ackermann(m, n) << endl;

	cout << "Ackermann value for m = " << 
	m1 << " and n = " << n1 << " is -> " <<
	Ackermann(m1, n1) << endl;
	
	return 0;
}

// This code is contributed by subhamgoyal2014.
