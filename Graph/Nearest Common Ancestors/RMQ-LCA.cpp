#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 10010
#define M 25
using namespace std;

struct edge {int from,to,weight,next;}e[N<<1];
int _pow[M],head[N],ver[N<<1],R[N<<1],first[N],in[N];
int dp[N << 1][M],tot;
bool vis[N];

void add_edge(int from, int to, int &num)
{
	e[num].from = from, e[num].to = to;
	e[num].next = head[from]; head[from] = num++;
}

void dfs(int root, int dep)
{
	vis[root] = 1;
	ver[++tot] = root;
	first[root] = tot;
	R[tot] = dep;

	for(int i = head[root] ; i != -1 ; i = e[i].next)
	{
		if(!vis[e[i].to])
		{
			dfs(e[i].to,dep+1);
			ver[++tot] = root;
			R[tot] = dep;
		}
	}
}

void ST(int len)
{
	int k = (int)(log((double)len) / log(2.0));
	for(int i = 1 ; i <= len ; i ++) dp[i][0] = i;
	for(int j = 1 ; j <= k ; j ++)
		for(int i = 1 ; i +_pow[j] - 1 <= len ; i ++)
		{
			int a = dp[i][j - 1], b = dp[i+_pow[j-1]][j-1];
			if(R[a] < R[b]) dp[i][j] = a;
			else dp[i][j] = b;
		}
}

int RMQ(int x, int y)
{
	int k = (int)(log((double)(y - x + 1)) / log(2.0));
	int a = dp[x][k], b = dp[y - _pow[k] + 1][k];
	if(R[a] < R[b]) return a;
	else return b;
}

int LCA(int from , int to)
{
	int x = first[from], y = first[to];
	if(x > y) swap(x,y);
	int res = RMQ(x,y);
	return ver[res];
}

int main()
{
	freopen("data.in","r",stdin);
 	for(int i=0; i<M; i++) _pow[i] = (1 << i);
	int cas,n,q,num;
	scanf("%d",&cas);
	while(cas --)
	{
		scanf("%d",&n);
		memset(head,-1,sizeof head);
		memset(vis, false, sizeof vis);
		memset(dp,0,sizeof dp);
		memset(in,0,sizeof in);
		memset(first,0 ,sizeof first);
		num = 0;
		
		for(int i = 1; i < n ; i ++)
		{
			int from,to,weight;
			scanf("%d%d",&from,&to);
			add_edge(from,to,num);
			in[to]++;
		}	
		int start; for(int i = 1 ; i <= n ; i ++) if(!in[i]) start = i;
		tot = 0;
		dfs(start,1);
		ST((n << 1) -1);
		
		int from,to;
		scanf("%d%d",&from,&to);
		printf("%d\n",LCA(from,to));
	}
	return 0;
}