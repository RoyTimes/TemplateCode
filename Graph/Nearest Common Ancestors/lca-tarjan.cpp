#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define N 1000000
#define M 1000000
using namespace std;

struct edge {int from,to,weight,next;}e[N<<1];
struct ask  {int from,to,lca,next;}ea[M];

int head[N],_head[N];
int dir[N],fa[N],anc[N];
bool vis[N];

void add_edge(int from, int to, int weight, int &num)
{
	e[num].from = from, e[num].to = to, e[num].weight = weight;
	e[num].next = head[from]; head[from] = num++;
	from = from ^ to,to = from ^ to,from = from ^ to;
	e[num].from = from,e[num].to = to;e[num].weight = weight;
	e[num].next = head[from];head[from] = num++;
}
void add_ans(int from, int to, int &num)
{
	ea[num].from = from, ea[num].to = to, ea[num].lca = -1;
	ea[num].next = _head[from]; _head[from] = num++;
	from = from ^ to,to = from ^ to,from = from ^ to;
	ea[num].from = from, ea[num].to = to, ea[num].lca = -1;
	ea[num].next = _head[from]; _head[from] = num++;
}

int Find(int x) {return x == fa[x] ? x : fa[x] = Find(fa[x]);}
void Union(int u ,int v){fa[Find(v)] = fa[u];}

void tarjan(int root)
{
	vis[root] = 1;
	anc[root] = root;
	for(int i = head[root]; i != -1 ; i = e[i].next)
	{
		int to = e[i].to, weight = e[i].weight;
		if(vis[to]) continue;
		dir[to] = dir[root] + weight;
		tarjan(to);
		Union(root,to);
		anc[Find(root)] = root;
	}
	for(int i = _head[root] ; i != -1 ; i = ea[i].next)
	{
		int to = ea[i].to;
		if(vis[to]) ea[i].lca = ea[i ^ 1].lca = anc[Find(to)];
	}
}

void init(int n)
{
	memset(head,-1,sizeof head);
	memset(_head,-1,sizeof _head);
	for(int i = 1 ; i <= n ; i ++) fa[i] = i;
}

int main()
{
	freopen("data.in","r",stdin);
	int cas,n,q,num;
	scanf("%d",&cas);
	while(cas --)
	{
		scanf("%d%d",&n,&q);
		init(n);
		num = 0;
		
		for(int i = 1; i < n ; i ++)
		{
			int from,to,weight;
			scanf("%d%d%d",&from,&to,&weight);
			add_edge(from,to,weight,num);
		}
		
		num = 0;
		for(int i = 0 ; i < q ; i ++)
		{
			int from,to;
			scanf("%d%d",&from,&to);
			add_ans(from,to,num);
		}
		memset(vis,0,sizeof vis);
		dir[1] = 0;
		tarjan(1);
		for(int i = 0 ; i < q ; i ++)
		{
			int mid = i << 1,from = ea[mid].from, to = ea[mid].to,lca = ea[mid].lca;
			printf("%d\n",dir[from] + dir[to] - 2 * dir[lca]);
		}
	}
	return 0;
}
























	
