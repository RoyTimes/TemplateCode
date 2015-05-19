#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAX 12000
using namespace std;
struct edge{int from,to,next;}e[MAX];
int n,tot = 0;
int head[MAX],father[MAX],deep[MAX];

void add_edge(int from, int to)
{
	e[tot].from = from, e[tot].to = to;
	e[tot].next = head[from], head[from] = tot++;
	father[to] = from;
}
void dfs(int x, int dep)
{
	deep[x] = dep;
	for(int i = head[x] ; i + 1 ; i = e[i].next)
		dfs(e[i].to, dep+1);
}
int FindLCA(int x, int y)
{
	if(deep[x] < deep[y]) swap(x,y);
	while(deep[x] > deep[y]) x = father[x];
	while(x != y) x = father[x],y = father[y];
	return y; 
}
int main()
{
	freopen("data.in","r",stdin);

	int cas; cin >> cas;
	while(cas --)
	{
		memset(head,-1,sizeof head);
		memset(father,-1,sizeof father);
		scanf("%d",&n);
		for(int i = 1 ; i < n ; i ++)
		{
			int a,b; scanf("%d%d",&a,&b);
			add_edge(a,b);
		}
		int start;
		for(int i = 1 ; i <= n ; i ++) if(father[i] == -1) start = i;
		dfs(start,1);
		int Q1,Q2; scanf("%d%d",&Q1,&Q2);
		printf("%d\n",FindLCA(Q1,Q2));

	}
}