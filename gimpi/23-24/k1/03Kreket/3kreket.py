def resi(t, k, e, r):
    x = t * t + k * k + e * e + r * r
    x += 7 * min(k // 2, r, e // 2, t)
    return x

n, z = map(int, input().split())
s = input()

t = 0 # broj pojavljivanja svakog slova
k = 0
e = 0
r = 0

for c in s: # za svaki znak...
    if c == 't':
        t += 1
    elif c == 'k':
        k += 1
    elif c == 'e':
        e += 1
    else:
        r += 1

bodovi = resi(t, k, e, r)

for tt in range (z + 1):
    for kk in range (z + 1):
        for ee in range (z + 1):
            for rr in range (z + 1):
                if tt + kk + ee + rr <= z:
                    bodovi2 = resi(t + tt, k + kk, e + ee, r + rr)
                    bodovi = max(bodovi, bodovi2)

print(bodovi)
