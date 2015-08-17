#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int f[40010], a[40010], s[40010];
int LIS(int n)
{
    int top = 0;
    for (int i = 1; i <= n; i++)
    {
        int *t = lower_bound(s + 1, s + top + 1, a[i]);
        if (t - s > top) top++;
        *t = a[i];
        f[i] = t - s;
    }
    return top;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]),
              a[i] = -a[i];
    printf("%d\n", LIS(n));
    return 0;
}
