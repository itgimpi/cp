n = int(input())
k = int(input())

# Koristi se niz lista cifara, ne celobrojni tip podataka.

# Najmanji broj se dobija od broja 10...0, 
broj = [1] + [0 for i in range(n - 1)]
zadnja = n - 1
zbir = 1
# Povecavaju se cifre sa desne strane (to su najmanje promene) dok njihov zbir ne postane K.
# Ide se od broja 10 na N−1 i sve dok je zbir cifara manji od K, trazi prvu cifru s desne strane koja je manja od 9 i poveca za jedan. 
# Može da se ubrza tako da se cifre sdesna odmah povecavaju na 9 dok do zbira K ne ostane razlika manja od 9.
while zadnja >= 0 and zbir + 9 - broj[zadnja] <= k:
    zbir += 9 - broj[zadnja]
    broj[zadnja] = 9
    zadnja -= 1

broj[zadnja] += k - zbir
print(''.join(map(str, broj)))

# Najveci broj se dobija od broja 9...9, 
broj = [9 for i in range(n)]
zadnja = n - 1
zbir = 9 * n
# Smanjuju se cifre s desne strane (to su najmanje promene) dok njihov zbir ne postane K. 
# Ide se od broja 10 na N − 1 i sve dok je zbir cifara veci od K, trazi prvu cifru s desne strane koja je veca od 0 i smanji je za jedan. 
# Može da se ubrza tako da se cifre sdesna odmah smanjuju na 0 dok do zbira K ne ostane razlika manja od 9.
while zbir - 9 >= k:
    zbir -= 9
    broj[zadnja] = 0
    zadnja -= 1

broj[zadnja] -= zbir - k
print(''.join(map(str, broj)))