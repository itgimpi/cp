---
hide:
  - toc
---

# A1 - Kodovi

#  "Zadatak"

| Vremensko ograničenje | Memorijsko ograničenje |
|:-:|:-:|
| 500ms | 64MB |


#  "Rešenje"

| Autor | Tekst i test primeri | Analiza rеšenja | Testiranje |
|:-:|:-:|:-:|:-:|
| Nikola Milosavljević | Nikola Milosavljević | Nemanja Majski | Marko Savić |


``` cpp title="04_kodovi.cpp" linenums="1"
#include <cstdlib>
#include <cstdio>

const int MAX_N = 100010;

int n;
long long x, solCount = 0, solTime = 0;
long long p[MAX_N], h[MAX_N];
int left = 0, right = 1;

int main()
{
	scanf("%d%lld", &n, &x);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld%lld", &p[i], &h[i]);
		if (p[i] < x) left = i;
	}
	right = left + 1;
	
	while (left != 0 && right != n + 1)
	{
		int Height = (h[right] <= h[left] ? h[right] : h[left]);

		solCount += Height * 2;
		solTime += (p[right] - p[left]) * Height * 2;
		h[left] -= Height;
		h[right] -= Height;

		if (h[right] == 0LL) 
			right++;
		else
			left--;
	}

	if (right == n + 1)
	{
		solTime -= (x - p[left]);
	}
	else
	{
		solCount++;
		solTime += (p[right] - x);
	}

	printf("%lld\n%lld\n", solCount, solTime);
	return 0;
}
```
