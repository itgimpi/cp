Za prvi podzadatak treba samo odrediti najveći broj u matrici n × m.

Za podzadatak prolazi se po svim podmatricama veličine r × s i odredi najveći broj u svakoj od njih tako što se prođe po svim elementima te podmatrice. Ukupna složenost ovog pristupa je O(nmrs).

Treći podzadatak zadatak se rešava u dve faze: 
u prvoj fazi se određuje matrica koju bi dobili da je okvir veličine 1 × s; 
a u drugoj fazi iz matrice dobijene u prvoj fazi stvori nova matrica pomoću ovkira r × 1, a ta je matrica upravo matrica koja se traži.

U prvoj fazi se rešava red po red. Dalje, prvi broj koji se zapisuje u i-ti red matrice je najveći broj među brojevima ai,1, ai,2, . . . , ai, s, a drugi broj koji se zapisuje je najveći broj među brojevima ai,2, ai,3, . . . , ai,s+1. Skup brojeva koji se posmatra pri određivanju koji broj se zapisuje na prvo i drugo mesto razlikuje se samo u elementima ai,1 i ai,s+1; svi ostali elementi su isti.

Zato može da se korisi struktura poput multiset-a, u koju se dodaju elementi u O(log n), i odredii vrednost najvećeg elementa u O(1). Prvih s elemenata prvog reda ide u strukturu, a najveći među njima se zapiše.
Onda, izbaci se a1,1 iz strukture i doda a1,s+1. Najveći među njima se zapiše kao drugi broj u prvom redu nove matrice.
Ponavljanjem postupka do kraja reda, za svaki red, dobija se matrica na kojoj se ponavlja postupak za kolone u drugoj fazi. Ukupna složenost ovog pristupa je O(nmlog n).

Za četvrti podzadatak treba ubrzati pristup iz trećeg. Umesto ubacivanja
elementa u strukturu u O(log n), treba to uraditi u O(1). Za to se koristi struktura monotoni red. Ukupna složenost ovog pristupa je O(nm).

https://cp-algorithms.com/data_structures/stack_queue_modification.html