#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define  N 100010
using namespace std;
int n,m;
struct edge
{
	int from,to,weight,next;
	bool used;
	edge(){used = 0;}
}e[N];
int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
inline bool operator < (edge x, edge y){
		return x.weight < y.weight;
}
int fa[N],deep[N];
int head[N],tot = 0;
struct EDGE{int to,from,weight,next;}a[N],_a[N];
struct Father{int fat,weight;}father[N]; 
void add_edge(int from, int to, int weight)
{
	a[tot].from = from,a[tot].to = to, a[tot].weight = weight;
	a[tot].next = head[from],head[from] = tot++; father[to].fat = from;
	father[to].weight = weight;
}
int _head[N],num = 0;
void _add_edge(int from, int to, int weight)
{
	_a[num].from = from,_a[num].to = to, _a[num].weight = weight;
	_a[num].next = _head[from],_head[from] = num++;
	from = from ^ to, to = from ^ to, from = from ^ to;
	_a[num].from = from, _a[num].to= to,_a[num].weight= weight;
	_a[num].next = _head[from], _head[from] = num++;
}
int find(int x)
{
	if(fa[x] == x) return x;
	fa[x] = find(fa[x]);
	return fa[x];
}
void Union(int x, int y)
{
	int Fax = find(x),Fay = find(y);
	if(Fax != Fay) fa[Fax] = Fay;
}
int Kruskal()
{
	for(int i = 1 ; i <= n ; i ++)
		fa[i] = i;
	long long ans = 0;
	sort(e + 1, e + m + 1);
	for(int i = 1; i <= m ; i ++)
	{
		int x = find(e[i].from);
		int y = find(e[i].to);
		if(x != y)
		{
			ans += (long long)e[i].weight;
			Union(e[i].from,e[i].to);
			e[i].used = 1;
			add_edge(e[i].from,e[i].to,e[i].weight);
		}
	}
	return ans;
}
void dfs(int x, int dep)
{
	deep[x] = dep;
	for(int i = head[x] ; i + 1 ; i = a[i].next)
		dfs(a[i].to, dep+1);
}
int FindLCA(int x, int y,int limit)
{
	int lenth = -1;
	if(deep[x] < deep[y]) swap(x,y);
	while(deep[x] > deep[y]){
		lenth = max(lenth, (father[x].weight >= limit ? 0:father[x].weight));
		x = father[x].fat;
	}
	while(x ^ y){
		lenth = max(lenth, (father[y].weight >= limit ? 0:father[y].weight));
		lenth = max(lenth, (father[x].weight >= limit ? 0:father[x].weight));
		x = father[x].fat;
		y = father[y].fat;
	}
	return lenth; 
}
int main()
{
//	freopen("data.in","r",stdin);	
	memset(head,-1,sizeof head);
	memset(father,-1,sizeof father);
	memset(_head,-1,sizeof head);
	
	n = read();m = read();
	for(int i = 1 ; i <= m ; i ++){

		e[i].from = read();
		e[i].to = read();
		e[i].weight = read();
		_add_edge(e[i].from,e[i].to,e[i].weight);
	}
	long long Lenth = Kruskal();
	long long res = 0x5f5f5f5f,start;
	for(int i = 1 ; i <= n ; i ++) if(father[i].fat == -1) {start = i;break;}
	dfs(start,1);

	for(int i = 1 ; i <= m ; i ++)
		if(!e[i].used)
			res = min(res, Lenth + e[i].weight - FindLCA(e[i].from,e[i].to,e[i].weight));
	printf("%d\n",res);
	return 0;
}
