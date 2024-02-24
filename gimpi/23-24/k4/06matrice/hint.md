Za prvi podzadatak treba samo odrediti najveći broj u matrici n × m.

Za podzadatak prolazi se po svim podmatricama veličine r × s i odredi najveći broj u
svakoj od njih na način da ćemo proći po svim elementima te podmatrice. Ukupna složenost ovog pristupa je O(nmrs).

Treći podzadatak zadatak ćemo rešavati u dve faze: 
u prvoj fazi određujemo matricu koju bi dobili da je okvir veličine 1 × s; 
a u drugoj fazi iz matrice dobijene u prvoj fazi stvorimo novu matricu pomoću ovkira r × 1, a ta je matrica upravo matrica koju tražimo.

Primetimo da u prvoj fazi možemo rešavati red po red. Dalje, prvi broj koji ćemo zapisati u i-ti red matrice na papiru je najveći broj među brojevima ai,1, ai,2, . . . , ai, s, a drugi broj koji ćemo zapisati je najveći broj među brojevima
ai,2, ai,3, . . . , ai,s+1. Skup brojeva koji posmatramo pri određivanju koji broj ćemo zapisati na prvo i drugo mesto razlikuje se samo u elementima ai,1 i ai,s+1; svi ostali elementi su jednaki. 
Zato možemo korisiti strukturu poput multiset-a, u koju možemo dodavati elemente u O(log n), i odrediti vrednost najvećeg elementa u O(1). Ubacimo prvih s elemenata prvog reda u strukturu, a najveći među njima zapišemo.
Zatim, izbacimo a1,1 iz strukture i dodamo a1,s+1. Najveći među njima zapišemo kao drugi broj u prvom redu nove matrice.
Ponavljanjem postupka do kraja reda, za svaki red, dobijamo matricu na kojoj ćemo ponoviti
postupak za kolone u drugoj fazi. Ukupna složenost ovog pristupa je O(nmlog n).

Za četvrti podzadatak potrebno je ubrzati pristup iz trećeg podzadatka. Umesto ubacivanja
elementa u strukturu u O(log n), želimo to napraviti u O(1). Za to ćemo iskoristiti strukturu
monotoni red. Ukupna složenost ovog pristupa je O(nm).

https://cp-algorithms.com/data_structures/stack_queue_modification.html