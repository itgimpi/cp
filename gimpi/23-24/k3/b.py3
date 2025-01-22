import sys
n = int(input())
k = int(input())

s = [int(z) for z in str(n)]
if sum(s) == k:
    print(n)
    sys.exit(0)

M = 19
while len(s) < M:
    s = [0] + s
best = float('inf')

for m in range(M):
    for z in range(10):
        if z == s[m]:
            continue
        preostalo = M - m - 1
        broj = s[:m] + [z] + [0 for i in range(preostalo)]
        if sum(broj) > k or sum(broj) + 9 * preostalo < k:
            continue
        if z > s[m]:
            while sum(broj) < k:
                for i in range(-1, -M, -1):
                    if broj[i] < 9:
                        broj[i] += 1
                        break
        else:
            while sum(broj) < k:
                for i in range(m + 1, M):
                    if broj[i] < 9:
                        broj[i] += 1
                        break
        x = int(''.join(map(str, broj)))
        if abs(x - n) < abs(best - n) or\
                abs(x - n) == abs(best - n) and x < best:
            best = x
print(best)