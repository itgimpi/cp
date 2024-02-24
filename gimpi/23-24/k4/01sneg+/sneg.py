def length(x, y, dx, dy, symbol):
    length = 0
    x += dx
    y += dy
   
    while (0 <= x and x < n and
           0 <= y and y < m and
           drawing[x][y] == symbol):
        x += dx
        y += dy
        length += 1

    return length

n, m = map(int, input().split())

drawing = []
for i in range(n):
    drawing.append(input())

max_size = 0

for i in range(n):
    for j in range(m):
        if drawing[i][j] != '+':
            continue
        
        size = length(i, j, -1, -1, '\\')
        size = min(size, length(i, j, -1, 0, '|'))
        size = min(size, length(i, j, -1, 1, '/'))
        size = min(size, length(i, j, 0, -1, '-'))
        size = min(size, length(i, j, 0, 1, '-'))
        size = min(size, length(i, j, 1, -1, '/'))
        size = min(size, length(i, j, 1, 0, '|'))
        size = min(size, length(i, j, 1, 1, '\\'))

        max_size = max(max_size, size)

print(max_size)
