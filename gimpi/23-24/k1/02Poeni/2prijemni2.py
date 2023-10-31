n = int(input())
bodovi = 0
for i in range(n):
    proba = input()
    resenje = input()
    if proba == resenje:
        bodovi += 4
    elif proba != "ooooo":
        bodovi -= 1
    # ako je proba ooooo, ne menjaju se bodovi

print(bodovi)
print(4 * n)
print(-1 * n)