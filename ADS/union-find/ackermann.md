# Ackermann's Function

$$
A(m,n)=
\begin{cases}
n+1 & \quad ,m=0\\ 
A(m-1,1) & \quad , m \neq 0, n=0\\
A(m-1,A(m,n-1)) & \quad , m \neq 0, n \neq 0
\end{cases}
$$

Neka je $m$ red a $n$ kolona.
Prvi red je, po definiciji, za m=0:

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |
| -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   |

Prvi element u svakom sledećem redu je, po definiciji, element gore desno od njega:

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |
| -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   |
|  m=1  |   2|    |    |    |    |    |

Kako se dobijaju sledeći elementi? Npr. A(1,1):

$
A(1,1)=A(0,A(1,0))=A(0,2)=2
$

Dakle, $A(red,kolona)=A(red-1,A(red,kolona-1))$

U prevodu, element na poziciji red, kolona
se čita iz prethodnog reda, 
a na kolonu ukazuje vrednost elementa levo od njega.

Levo od (1,1) je 2, u prvom redu u koloni 2 je 3.
Levo od (1,2) je sada 3, u prvom redu u koloni 3 je 4.
I tako dalje...

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |
| -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   |
|  m=1  |   2| 3  | 4  |  5 | 6  |7   |

Prvi element u svakom sledećem redu je, po definiciji, element gore desno od njega:

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |
| -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   |
|  m=1  |   2| 3  | 4  |  5 | 6  |7   |
|  m=2  |   3|   |   |   |   |   |

Sledeći element se čita iz prethodnog reda, iz kolone 3, to je 5.
Sledeći iz prethodnog reda, iz kolone 5, je 7. 
I tako dalje, svaki drugi...

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |
| -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   |
|  m=1  |   2| 3  | 4  |  5 | 6  |7   |
|  m=2  |   3| 5  | 7  |  9 | 11  | 13  |
|  m=3  |   5|   |   |   |   |   |

Do sada vrednosti nešto i ne rastu...

Sledeći je iz prethodnog reda iz kolone 5, 13.

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |
| -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   |
|  m=1  |   2| 3  | 4  |  5 | 6  |7   |
|  m=2  |   3| 5  | 7  |  9 | 11  | 13  |
|  m=3  |   5| 13  |   |   |   |   |

Sledeći nije vidljiv u tabeli,
ali je u linearnom nizu $2n+3$ na poziciji 13,
dakle $2 * 13 + 3 = 29 $.
Dalje $2 * 29 + 3 = 61 $...

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |6 |7 |
| -: | -: | -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   | 7| 8|
|  m=1  |   2| 3  | 4  |  5 | 6  |7   | 8| 9|
|  m=2  |   3| 5  | 7  |  9 | 11 | 13 | 15| 17|
|  m=3  |   5| 13 | 29 | 61 | 125| 253| 509 | 1021 |

Elementi u sadnjem redu su elementi niza $2^{n+3}-3$.
Već u 4. redu se javlja eksponencijalna f-ja.

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |6 |7 |
| -: | -: | -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   | 7| 8|
|  m=1  |   2| 3  | 4  |  5 | 6  |7   | 8| 9|
|  m=2  |   3| 5  | 7  |  9 | 11 | 13 | 15| 17|
|  m=3  |   5| 13 | 29 | 61 | 125| 253| 509 | 1021 |
|  m=3  |   13|  |  | | | |  |  |

Sledeći je $2^{13+3}-3 = 2^{16}-3$
Za posmatranje kako rastu elementi Akermanove f-ja
nisu bitne tačne vrednosti, neka budu približne...

$2^{16}$ je $2^{2^{2^{2}}}$ tj. $65.536$

Posle $2^{16}$ je $2^{2^{16}}$ ili $2^{2^{2^{2^{2}}}}$

Sledeći je $2^{2^{2^{16}}}$ ili $2^{2^{2^{2^{2^{2}}}}}$

I tako dalje, svaki sledeći je $2^{prethodni}$...

|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |6 |7 |
| -: | -: | -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   | 7| 8|
|  m=1  |   2| 3  | 4  |  5 | 6  |7   | 8| 9|
|  m=2  |   3| 5  | 7  |  9 | 11 | 13 | 15| 17|
|  m=3  |   5| 13 | 29 | 61 | 125| 253| 509 | 1021 |
|  m=4  |   13| $2^{16}$ | $2^{2^{16}}$ |$2^{2^{2^{16}}}$ |$2^{2^{2^{2^{16}}}}$ |... |...  |...  |



|  n-> | 0 | 1 | 2 | 3 | 4 | 5 |6 |7 |opis |
| -: | -: | -: | -: | -: | -: | -: | -: | -: | -: |
|  m=0  |   1| 2  |3   |  4 | 5  |6   | 7| 8| n+1|
|  m=1  |   2| 3  | 4  |  5 | 6  |7   | 8| 9| n+2|
|  m=2  |   3| 5  | 7  |  9 | 11 | 13 | 15| 17| 2n+3|
|  m=3  |   5| 13 | 29 | 61 | 125| 253| 509 | 1021 | $2^{n+3}$|
|  m=4  |   13| $2^{16}$ | $2^{2^{16}}$ |$2^{2^{2^{16}}}$ |$2^{2^{2^{2^{16}}}}$ |$2^{2^{2^{2^{2^{16}}}}}$ |$2^{2^{2^{2^{2^{2^{16}}}}}}$  |$2^{2^{2^{2^{2^{2^{2^{16}}}}}}}$  | ...|
|  m=5  |   $2^{16}$| ... | ... |... |... |... |...  |...  | ...|
                 ^
                 |
                 65.536-ti element u prethodnom redu              