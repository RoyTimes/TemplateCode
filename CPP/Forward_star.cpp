#include <stdio.h>
#include <string.h>
 
#define MAXN 1001
#define INF 0x3f3f3f3f
struct node
{
    int to;
    int next;
    int val;
}edge[MAXN * MAXN];
int head[MAXN], pre[MAXN], dis[MAXN], que[MAXN*MAXN];
int n, cnt;
void init()
{
    memset(head, -1, sizeof(head));
    cnt = 1;
}
void addedge(int from, int to, int val)
{
    edge[cnt].to = to;
    edge[cnt].val = val;
    edge[cnt].next = head[from];
    head[from] = cnt++;
}
void print(int n)
{
    if(n == 0)
    {
        return ;
    }
    print(pre[n]);
    printf("%d ", n);
}
/*
void dijkstra(int src)
{
    int is_visit[MAXN], i, j;
    for(i = 1; i <= n; i++)
    {
        dis[i] = INF;
        is_visit[i] = 0;
    }
    dis[src] = 0;
    for(i = 1; i <= n; i++)
    {
        int min = INF;
        int u = src;
        for(j = 1; j <= n; j++)
        {
            if(is_visit[j] == 0 && dis[j] < min)
            {
                min = dis[j];
                u = j;
            }
        }
        for(j = head[u]; j != -1; j = edge[j].next)
        {
            int to = edge[j].to;
            if(dis[u] + edge[j].val < dis[to] && is_visit[to] == 0)
            {
                dis[to] = dis[u] + edge[j].val;
                pre[to] = u;
            }
        }
        is_visit[u] = 1;
    }
}
*/
void spfa(int src)
{
    int is_visit[MAXN], i, j;
    for(i = 1; i <= n; i++)
    {
        dis[i] = INF;
        is_visit[i] = 0;
    }
    int hed = 0, tail = 0;
     
    dis[src] = 0;
    is_visit[src] = 1;
    que[tail++] = src;
     
    while(hed < tail)
    {
        i = que[hed++];
        is_visit[i] = 0;
        for(j = head[i]; j != -1; j = edge[j].next)
        {
            int u = edge[j].to;
            if(dis[u] > dis[i] + edge[j].val)
            {
                dis[u] = dis[i] + edge[j].val;
                pre[u] = i;
                if(is_visit[u] == 0)
                {
                    is_visit[u] = 1;
                    que[tail++] = u;
                }
            }
        }
    }
}
int main()
{
    int i, j;
    scanf("%d", &n);
    init();
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            int t;
            scanf("%d", &t);
            if(t)
            {
                addedge(i, j, t);
            }
        }
    }
    //dijkstra(1);
    spfa(1);
    print(n);
    printf("\n%d\n", dis[n]);
    return 0;      
}