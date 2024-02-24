def tombola(polje, numbers):
    for i in range(5):
        for j in range(5):
            if polje[i][j] in numbers:
                polje[i][j] = 0

    for i in range(5):
        if polje[i][0] == polje[i][1] == polje[i][2] == polje[i][3] == polje[i][4] == 0:
            return True

    for i in range(5):
        if polje[0][i] == polje[1][i] == polje[2][i] == polje[3][i] == polje[4][i] == 0:
            return True

    if polje[0][0] == polje[1][1] == polje[2][2] == polje[3][3] == polje[4][4] == 0:
        return True

    if polje[0][4] == polje[1][3] == polje[2][2] == polje[3][1] == polje[4][0] == 0:
        return True

    return False

n = int(input())

imena = []
polja = []

for i in range(n):
    ime = input()
    polje = []
    for j in range(5):
        polje.append(list(map(int, input().split())))

    imena.append(ime)
    polja.append(polje)

m = int(input())
numbers = list(map(int, input().split()))

nagrada = []

for i in range(n):
    if tombola(polja[i], numbers):
        nagrada.append(imena[i])

print(len(nagrada))

for ime in nagrada:
    print(ime)
