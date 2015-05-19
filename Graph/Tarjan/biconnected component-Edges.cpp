////
//// POJ 3352 
//// COPY RIGHT RESERVED ROYTIMES 2014
////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define N 100010
using namespace std;

struct edge{int from,to,weight,next;}e[N];
int head[N];
int num = 0,n,m,dep = 0;
int vis[N],deep[N],low[N],de[N];

inline void add_edge(int from, int to){
	e[num].to = to;e[num].next = head[from];
	head[from] = num++; swap(from,to);
	e[num].to = to;e[num].next = head[from];
	head[from] = num++;
}

void tarjan(int x,int father)
{
	st.push(x);ins[x] = 1;
	low[x] = deep[x] = dep++;
	for(int i = head[x] ; i + 1 ; i = e[i].next)
	{
		if(e[i].to == father) continue;
		if(!vis[e[i].to]){
			tarjan(e[i].to, x);
			low[x] = min(low[x], low[e[i].to]);
		}
		else if(vis[e[i].to] == 1)
			low[x] = min(low[x], deep[e[i].to]);
	}
	if(low[x] == deep[x])
	{

	}
}

int main()
{
//	freopen("data.in","r",stdin);

	while(cin >> n >> m)
	{
		num = dep = 0;
		memset(head,-1,sizeof head);

		for(int i = 1 ; i <= m ; i ++)
		{
			int x,y; scanf("%d%d",&x,&y);
			add_edge(x,y);
		}

		memset(deep,0,sizeof deep);
		memset(vis,0,sizeof deep);
		memset(low,0,sizeof low);

		for(int i = 1 ; i <= n ; i ++)
			if(!vis[i]) tarjan(i,i);

		
	}
}