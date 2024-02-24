Svaka pahuljica, nezavisno od veličine, ima + u sredini. Dakle, pahuljica ima onoliko koliko ima znakova + na crtežu.
Svakoj pahuljici se određuje veličina, najveća se ispisuje.

Ugnježdenim petljama prolazimo kroz svaki znak na crtežu. Ako je taj znak +, tada se nalazimo u sredini pahuljice i određujemo njenu veličinu. Za veličinu pahuljice, potrebno je
odrediti dužine nizova odgovarajućih znakova u svakom od osam smerova od sredine pahuljica, a dužina najkraćeg jednaka je veličini pahuljice. 

Neka je gornji-levi ugao crteža u koordinatnom sistemu (0, 0), a donji-desni (n−1, m−1). Pretpostavimo da se znak + nalazi u x-tom redu i y-toj koloni, tj. na koordinati (x, y).
Odredimo dužinu niza znakova | u smeru dole. Primetimo da je koordinata prvog polja ispod znaka + jednaka (x + 1, y), a svakog sledećeg polja u tom smeru možemo dobiti tako da povećamo x koordinatu za 1, dok y koordinata ostaje nepromenjena.
Napravimo brojac i postavimo na 0. Petljom while menjamo
koordinate sve dok je znak na trenutnom polju jednak |, i svaki put povećavamo brojac za 1.
Pritom pazimo da ne izađemo izvan granica crteža, tj. da je x-koodinata trenutnog polja veća ili jednaka
0 i manja od n, a y-koordinata trenutnog polja veća ili jednaka 0 i manja od m.

