#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 105
#define M 40050
#define inf 0x3f3f3f3f
queue<int> q;
int a[N][N];
int n, m, s, t, v[N], d[N], inc[N], from[N], ans;
int head[N], next[M], to[M], val[M], cost[M], cnt = 1;
void add(int x, int y, int z, int w)
{
    to[++cnt] = y; val[cnt] = z; cost[cnt] = w;
    next[cnt] = head[x]; head[x] = cnt;
}
bool spfa()
{
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d);
    d[s] = 0; v[s] = 1; inc[s] = inf;
    q.push(s);
    while (!q.empty())
    {
        int x = q.front(), y; q.pop(); v[x] = 0;
        for (int i = head[x]; i; i = next[i])
            if (val[i] && d[y = to[i]] > d[x] + cost[i])
            {
                d[y] = d[x] + cost[i];
                inc[y] = min(inc[x], val[i]);
                from[to[i]] = i;
                if (!v[y])
                    v[y] = 1, q.push(y);
            }
    }
    if (d[t] == inf) return false;
    return true;
}
int update()
{
    int x = t;
    while (x != s)
    {
        val[from[x]] -= inc[t];
        val[from[x] ^ 1] += inc[t];
        x = to[from[x] ^ 1];
    }
    return d[t] * inc[t];
}
void build(int x)
{
    memset(head, 0, sizeof head); cnt = 1; ans = 0;
    for (int i = 1; i <= n; i++)
        add(s, i, 1, 0), add(i, s, 0, 0),
            add(i + n, t, 1, 0), add(t, i + n, 0, 0);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            add(i, j + n, 1, a[i][j]*x),
                add(j + n, i, 0, -a[i][j]*x);
}
int main()
{
    cin >> n;
    s = 0; t = n * 2 + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    build(1);
    while (spfa()) ans += update();
    cout << ans << endl;
    build(-1);
    while (spfa()) ans += update();
    cout << -ans << endl;
    return 0;
}
//jdfzoj 2505
