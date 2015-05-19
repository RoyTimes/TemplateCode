#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int n, m, l;

const int N = 6000;
const int INF = 0x3f3f3f3f;
priority_queue <int> q;
struct edge
{
    int from, to, weight, next;
} e[N];
int head[N], cut = 0, dis[N], cnt[N];
bool used[N];

void add_edge(int from, int to, int weight)
{
    e[cut].to = to, e[cut].weight = weight;
    e[cut].next = head[from], head[from] = cut ++;
}

bool SPFA_HEAP_JUDGE(const int start, const int end)
{
    for (int i = 1; i <= n ; i ++)
        dis[i] = INF;

    dis[start] = 0;

    q.push(start), cnt[start] ++;

    while (!q.empty())
    {
        int x = q.top(); q.pop(), used[x] = 0;
        for (int i = head[x]; i + 1; i = e[i].next)
            if (dis[x] + e[i].weight < dis[e[i].to])
            {
                dis[e[i].to] = dis[x] + e[i].weight;
                if (!used[e[i].to])
                {
                    used[e[i].to] = 1;
                    q.push(e[i].to);
                    if ( ++ cnt[e[i].to] > n - 1) return 0;
                }
            }
    }
    return 1;
}

void Init()
{
    cut = 0;
    memset(head, -1, sizeof head);
    memset(e, 0, sizeof e);
    memset(used, 0, sizeof used);
    memset(dis, 0x3f,sizeof dis);
    memset(cnt, 0, sizeof cnt);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("data.in", "r", stdin);
#endif
    cin.sync_with_stdio(false);


    int cas; cin >> cas;
    while (cas --)
    {
        cin >> n >> m >> l;
        Init();

        for (int i = 1; i <= m ; i ++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            add_edge(x, y, z);
            add_edge(y, x, z);
        }
        for (int i = 1 ; i <= l ; i ++)
        {
            int x, y, z;
            cin >> x >> y >> z;
            add_edge(x, y, - z);
        }

        if (!SPFA_HEAP_JUDGE(1, n))
            puts("YES");
        else puts("NO");
    }
    return 0;
}