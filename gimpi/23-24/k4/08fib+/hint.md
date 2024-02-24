Prvih k+1 elemenata niza se ciklično ponavlja kroz celi niz. Odnosno, važi XA = XA +k+1 za svaki A. 

Svojstva operacije xor:
A ^ 0 = A
A ^ A = 0
A ^ B = B ^ A

X L ^ X L+1 ^ … ^ X R = (X 1 ^ X 2 ^ … ^ X R ) ^ (X 1 ^ X 2 ^ … ^ X L1)

to jest xor od l-tog do r-tog elementa je (xor do l-1og) xor (xor do r-tog).

Koristeći cikličnost niza i gornja svojstva jasno je da je xor prvih N elemenata niza jednak xoru prvih N’ elemenata niza gde je 0 <= N’ <= 2(K+1).

Dakle, dovoljno je prethodno obraditi xorove
prvih 2(K+1) elemenata i pomoću njih u O(1) odgovoriti na sve zadane upite.
