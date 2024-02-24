Oznake iz teksta zadatka: (ai) je poredak u kojem su vozovi došli na stanicu prvog dana, a (bi) je poredak u kojem su vozovi otišli sa stanica drugog dana.

ci je niz, takav da je ci jednak bj za koji važi da je aj = i. Drugim rečima, sortirajmo poredak odlaska vozova prema poretku dolaska vozova.

Na primer, neka je poredak dolaska vozova 3 5 2 4 1, a odlaska 3 2 5 1 4. Tada je c1 = b5 = 4 jer je a5 = 1, c2 = b3 = 5 jer je a3 = 2, c3 = b1 = 3 jer je a1 = 3, c4 = b4 = 1 jer je a4 = 4, te c5 = b2 = 2 jer je a2 = 5. Dakle, niz (ci) = 4 5 3 1 2.

Pratimo vozove u nizu (ci). U navedenom primeru, vozovi c1 i c2 ne mogu biti na istom peronu jer je c1 < c2, a to znači da bi voz c1 morao otići sa stanica pre voza c2, što je nemoguće jer je voz c1 došao na stanicu pre voza c2. S druge strane, vozovi c1 i c3 mogu biti na istom peronu jer je c1 > c3, a to znači da će voz c3 hteti otići sa stanice pre voza c1, što je moguće jer je voz c3 došao na stanicu posle voza c1. Iz ovog sledi da kad bi našli niz takav da je cx1 < cx2 < · · · < cxk , tada bi nam za te vozove trebalo k perona.

Zadatak je sveden na pronalaženje najdužeg takvog niza. Ovaj je problem poznat pod nazivom najduži rastući podniz (longest increasing subsequence). Tada je rešenje zadatka dužina najdužeg rastućeg podniza niza (ci). Primetimo da će vozovi koji su u tom podnizu biti prvi voz u svakom od perona, i da je moguće poređati ostale vozove u perone tako da svi vozovi mogu otići bez da im pritom smetaju ostali vozovi. Ukupna vremenska složenost je O(n log n).

https://cp-algorithms.com/sequences/longest_increasing_subsequence.html