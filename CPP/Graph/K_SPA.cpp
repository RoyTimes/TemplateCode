//// poj 2449
#ifdef _MSC_VER  
#define DEBUG  
#endif  

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#define N 1010
#define M 100010
#define INF 0x5f5f5f5f
using namespace std;

struct edge{int to,weight,next;}e[M],eo[M];
struct A_star{
    int to,f,g;
    inline bool operator < (const A_star &t) const{
        if(t.f == f)return t.g < g;
        return t.f < f;
    }
};

int head[N],_head[N],h[N];
int num = 0,tot = 0,n,m,k;
bool in_q[N];

inline void add_edge(int from,int to, int weight)
{
    e[num].to = to, e[num].weight = weight;
    e[num].next = head[from], head[from] = num++;
}
inline void _add_edge(int from,int to, int weight)
{
    eo[tot].to = to, eo[tot].weight = weight;
    eo[tot].next = _head[from], _head[from] = tot++;
}

void SPFA(const int st)
{
    for(int i = 1 ; i <= n ; i ++){
        h[i] = INF;
        if(i == st) h[i] = 0;
    }
    queue<int> q;
    q.push(st),in_q[st] = 1;
    while(!q.empty())
    {
        int temp = q.front();q.pop(),in_q[temp] = 0;
        for(int i = head[temp] ; i + 1; i = e[i].next)
            if(h[temp] + e[i].weight < h[e[i].to])
            {
                h[e[i].to] = h[temp] + e[i].weight;
                if(!in_q[e[i].to]){
                    q.push(e[i].to);
                    in_q[e[i].to] = 1;
                }
            }
    }
}

int A_Star(int start, int end, int k)
{
    if(start == end) k ++;
    if(h[start] == INF) return -1;
    priority_queue<A_star> pq;
    A_star x,ne;
    int cut = 0; //to == v
    x.to = start, x.g = 0, x.f = x.g + h[x.to];pq.push(x);
    while(!pq.empty())
    {
        x = pq.top();pq.pop();
        if(x.to == end) cut++;
        if(cut == k)return x.g;
        for(int i = _head[x.to]; i + 1 ; i = eo[i].next)
        {
            ne.to = eo[i].to;
            ne.g = x.g + eo[i].weight;
            ne.f = ne.g + h[ne.to];
            pq.push(ne);
        }
    }
    return -1;
}

int main()
{
#ifdef DEBUG
    freopen("data.in","r",stdin);
//  freopen("data.out","w",stdout);
#endif
    
    while(scanf("%d%d",&n,&m) != EOF){
        memset(head, -1 ,sizeof head);
        memset(_head, - 1, sizeof _head);
        memset(in_q,0,sizeof in_q);
        
        num = 0,tot = 0;

        for(int i =1 ; i <= m ; i ++)
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            add_edge(y,x,z);
            _add_edge(x,y,z);
        }
    
        int start,end;
        cin >> start >> end >> k;
        SPFA(end);
        int ans = A_Star(start,end,k);
        cout << ans << endl;
    }
    return 0;
}
