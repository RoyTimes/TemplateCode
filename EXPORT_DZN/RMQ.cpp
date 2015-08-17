#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 200010
int n, m, log2[N], f[N][20];
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%d", &f[i][0]);
    for (int i = 2; i <= n; i++)
        log2[i] = log2[i >> 1] + 1;
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
    cin >> m;
    for (int a, b, i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        if (a > b) swap(a, b);
        printf("%d\n", max(f[a][log2[b - a + 1]], f[b - (1 << log2[b - a + 1]) + 1][log2[b - a + 1]]));
    }
    return 0;
}
