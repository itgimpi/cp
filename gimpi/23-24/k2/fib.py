def primeFactors(n): # strahinja
    R = []
    while n % 2 == 0: 
        R.append(2)
        n = n // 2
    i = 3
    while i*i < n+1:
        while n % i== 0: 
            R.append(i)
            n = n // i 
        i += 2
    if n > 2: 
        R.append(n)
    return R
    
n,q = [int(i) for i in input().split()]
L = [int(input()) for i in range(q)]
for i in L:
    if i == 1:
        print("-1")
    else:
        print(n//primeFactors(i)[-1]-1)