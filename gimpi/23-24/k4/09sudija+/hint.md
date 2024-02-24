Odvojeno se posmatraju parovi timova u kojima je pobeda stroga (najbolja pozicija pobednika, po sudijama, strogo je veća od najbolje pozicije gubitnika, po sudijama) i parove u kojima pobeda nije stroga, što znači da su najbolje pozicije igrača po sudijama izjednacene. Ovih drugih parova ima najviše O(n): dovoljno je za svaku poziciju od 1 do n proveriti hoće li se neki takav mec dogoditi meću nekim od (najviše tri) tima kojima je ta pozicija najbolja po sudijama. 

Ostatak se odnosi na prvi skup meceva (stroge pobede). Svaki tim ide u bitmasku, koja označava sudiju kod kog je njegova pozicija najbolja. Npr. tim koji je kod svih sudija najbolji na trecoj podlozi ide u bitmasku 001, a tim koji je najbolji (sa istim rangom) kod prvog i drugog sudije ide u 110.

Odabere se jedan tim (njegova najbolja pozicija je p) i bitmaska drugog tima. Koliko timova u toj bitmaski njega strogo pobjeđuje? To su timovi
iz bitmaske čija je najbolja pozicija bolja od p. Njihov broj možemo izračunati binarnom pretragom
sortiranog niza najboljih pozicija igraca u maski. Sudiju tih meceva određujemo iz same maske, tj. iz
pozicije jedinice u bitmaski. Ako bitmaska ima dve ili tri jedinice (izjednačene sudije pobednika),
upoređujemo pozicije odabranog igrača (gubitnika) na tim podlogama.