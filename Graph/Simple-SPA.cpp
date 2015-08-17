#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define N 1005
#define INF 100000
using namespace std;
  
int V,S;
int dis[N],pre[N],mid[N],cut[N];
bool used[N];
  
typedef struct _edge_
{
    int weight;
    int to;
}edge;
  
vector<edge>e[N];
queue<int> q;

bool spfa(const int st)
{
    for(int i = 0 ; i <= V ; i ++)
    {
        if(i == st){dis[i] = 0 ; continue;}
        dis[i] = INF;
    }
    
    q.push(st);
    used[st] = 1;
    cut[st] = 1;
    
    while(!q.empty())
    {
        int temp = q.front();
        for(int i = 0; i <(int)e[temp].size() ; i ++)
        {
            edge *te = &e[temp][i];
            if(dis[temp] + (*te).weight < dis[(*te).to]) 
            {
                    dis[(*te).to] = dis[temp] + (*te).weight;
                    cut[(*te).to] = cut[temp] + 1;
                    if(cut[(*te).to] > V) return 0;
                    if(used[(*te).to] == 0)
                    {
                        q.push((*te).to);
                        used[(*te).to] = 1;
                    }
            }
        }
        q.pop();
        used[temp] = 0;
    }
    return 1;
}

bool dijkstra(const int start , const int end)
{
    int temp = 0,flag = 0;
    for(int i = start ; i <= end ; i ++) dis[i] = INF;
    for(int i = start ; i < (int)e[start].size() ; i ++) dis[e[start][i].to] = e[start][i].weight;
    for(int i = start ; i < (int)e[start].size() ; i ++) pre[e[start][i].to] = start;
    for(int i = start ; i <= end ; i ++)
    {
        memset(mid,1,sizeof(mid));
        temp = INF + 1;
        for(int j = 1 ; j <= end ; j ++)
        {
            if(!used[j] && temp > dis[j])
            {
                temp = dis[j];
                flag = j;
            }
        }
        used[flag] = 1;
        for(int j = 1 ; j < (int)e[flag].size() ; j ++)
      		mid[e[flag][j].to] = e[flag][j].weight;
        for(int j = start + 1 ; j <= end; j ++)
        {
            if(dis[flag] + mid[j] < dis[j])
            {
                dis[j] = dis[flag] + mid[j];
                pre[j] = flag;
            }
              
        } 
    }
}
/*

void Dijkstra(const int start, const int end)
{
    memset(dis + start, 0x3f, (sizeof int) * (end - start));
    for (int i = head[start], i + 1, i = e[i].next)
        dis[e[i].to] = e[i].weight;
    for (int i = start ; i <= end ; i ++)
    {
        int temp = 0x3f3f3f3f + 1, flag = 0;
        for (int j  = 1; j <= end ; j ++)
            if (!used[j] && temp > dis[j])
                temp = dis[j], flag = j;
        used[flag] = 1;
        for (int j = head[flag] ; j + 1; j = e[j].next)
            if (dis[flag] + e[j].weight < dis[e[j].to])
                dis[e[j].to] = dis[flag] + e[i].weight;
    }
}
*/
int main()
{
    int n; cin>>n;
    for(int i = 1 ; i <= n ; i ++){edge temp; e[i].push_back(temp);}
    for(int i = 1 ; i <= n ; i ++)
    {
        for(int j = 1 ; j <= n ; j ++)
        {
            int god; scanf("%d",&god);
            if(god != 0)
            {
                edge temp1;
                temp1.to = j;
                temp1.weight = god;
                e[i].push_back(temp1);
            }
        }
    }
    dijkstra(1,n);
    int shit = n;
    int b[N],num = 0;
    while(shit != 1)
    {
        b[num] = shit;
        shit = pre[shit];
        num++;
    }
    printf("1 ");
    for(int i = num - 1 ; i >= 0 ; i --) printf("%d ",b[i]);
    printf("\n%d",dis[n]);
}
