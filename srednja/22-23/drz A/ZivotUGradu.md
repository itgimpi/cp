Zadatak:

Odrediti da li se matricom a, na kojoj su raspoređane vrednosti 0 ili 1, može stići od polja a[1][1] do a[n][m] pomerajima desno i dole, ako se se na putu do polja a[n][m] vrednosti sabiraju, a da u polju a[n][m] zbir bude vrednost k?
Ako je u ulazu za vrednost z unešen broj 0, ispisati samo "DA" ili "NE", ako je to moguće odnosno nemoguće, a ako je z ==1, ispisati i poteze gde je "S" dole, a "D" desno.

Rešenje:

Na prvi pogled je klasičan dp zadatak, ali su ipak potrebne 2 $dp$ matrice. $dp_0$ matrica broji najmanji mogući zbir koji može biti na tom polju, dok $dp_1$ matrica broji najveći mogući zbir. Ako je zadata vrednost k, veća od dp[0][n][m] i manja od dp[1][n][m], vrednost k je moguće naći, dok u ostalim slučajevima je nemoguće. Ako je z==1, krene se od a[n][m] pa sve do a[1][1] i prati se trenutna vrednost i dp vrednosti obe matrice da se ne bi skrenulo sa puta.