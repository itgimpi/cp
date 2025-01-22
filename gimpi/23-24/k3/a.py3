n = int(input())
k = int(input())

broj = [1] + [0 for i in range(n - 1)]
zadnja = n - 1
zbroj = 1
while zadnja >= 0 and zbroj + 9 - broj[zadnja] <= k:
    zbroj += 9 - broj[zadnja]
    broj[zadnja] = 9
    zadnja -= 1
broj[zadnja] += k - zbroj
print(''.join(map(str, broj)))

broj = [9 for i in range(n)]
zadnja = n - 1
zbroj = 9 * n
while zbroj - 9 >= k:
    zbroj -= 9
    broj[zadnja] = 0
    zadnja -= 1
broj[zadnja] -= zbroj - k
print(''.join(map(str, broj)))