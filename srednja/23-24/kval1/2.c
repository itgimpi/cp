#include <stdio.h>

int main()
{
    int n, q;
    scanf("%d", &n);
    int a[n], c[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &c[i]);
    }

    scanf("%d", &q);
    int k[q], x[q];
    for(int i = 0; i < q; i++) {
        scanf("%d", &k[i]);
    }
    for(int i = 0; i < q; i++) {
        scanf("%d", &x[i]);
    }
    
    int dod[n + 1];
    for(int i = 0; i <= n; i++) {
        dod[i] = 0;
    }
    for(int i = 0; i < q; i++) {
        dod[k[i] - 1] += x[i];
    }
    for(int i = 0; i < n; i++) {
        a[i] += dod[i];
        if(a[i] > c[i]) {
            dod[i + 1] += a[i] - c[i];
            a[i] = c[i];
        }
    }
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}