Ako se gradi reč koja se sastoji od slova koja se izgovaraju, a na svaku naredbu UPIT prebrojimo tražena slova u reči, dobili smo algoritam vremenske složenosti O(Q*N) što je dovoljno za 40% bodova na zadatku. 

Dodatnih 20% bodova moglo se osvojiti tako da paralelnono s pravljenjem stringa se pamti koliko se kog slova do sad pojavilo. Sad je moguće na svaku naredbu UPIT odgovoriti u O(1).

Za ceo zadatak treba primetiti da će, ako nema upita, posle prvih N % 26 izgovorenih slova, svako slovo se pojavljuje tačno N/26 puta (ciklus dužine 26), / je celobrojno deljenje. 

Koristeći ovo svojstvo možemo svaku naredbu simulirati u konstantnom vremenu.