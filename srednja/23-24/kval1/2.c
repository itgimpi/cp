#include <stdio.h>

int main()
{
    int n, q;
    scanf("%d", &n);
    long long a[n], c[n];
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    for(int i = 0; i < n; i++) {
        scanf("%lld", &c[i]);
    }

    scanf("%d", &q);
    long long x, k;
    for(int i = 0; i < q; i++) {
        scanf("%lld %lld", &k, &x);
        a[k-1] += x;
    }
    for(int i = 0; i < n - 1; i++) {
        if(a[i] > c[i]) {
            a[i+1] += a[i] - c[i];
            a[i] = c[i];
        }
    }
    if(a[n-1] > c[n-1]) {
        a[n-1] = c[n-1];
    }
    for(int i = 0; i < n; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n");
    return 0;
}