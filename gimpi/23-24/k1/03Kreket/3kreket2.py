n,z = [int(i) for i in input().split()]
s = input()
k = 0
r = 0
e = 0
t = 0
b = 0
for i in range(n):
    if s[i] == 'k':
        k += 1
    elif s[i] == 'r':
        r += 1
    elif s[i] == 'e':
        e += 1
    else:
        t += 1
brk = min(k//2,r,e//2,t)
k1 = k
r1 = r
e1 = e
t1 = t
k1 -= brk*2
r1 -= brk
e1 -= brk*2
t1 -= brk
b += brk*7
kf = 0
rf = 0
ef = 0
tf = 0
if k1 < 2:
    kf += 2 - k1
if e1 < 2:
    ef += 2 - e1
if r1 == 0:
    rf += 1
if t1 == 0:
    tf += 1
naj = max(k,r,e,t)
f = kf+rf+ef+tf
if f > 1 or z < f:
    if naj == k:
        k += z
    elif naj == r:
        r += z
    elif naj == e:
        e += z
    else:
        t += z
else:
    k += kf
    r += rf
    e += ef
    t += tf
    if naj == k:
        k += z - f
    elif naj == r:
        r += z - f
    elif naj == e:
        e += z - f
    else:
        t += z - f
    b += 7
b += k * k
b += r * r
b += e * e
b += t * t
print(b)