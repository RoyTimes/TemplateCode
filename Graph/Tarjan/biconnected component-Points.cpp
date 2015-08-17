////
//// POJ 1144 
//// COPY RIGHT RESERVED ROYTIMES 2014
////
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#define N 10010
using namespace std;

struct edge{int from,to,weight,next;}e[N];
int head[N],n,m,num = 0,dep = 0,root = 0;
int low[N],deep[N],Spoints[N];

void add_edge(int from,int to,int weight)
{
	e[num].from = from,e[num].to = to,e[num].weight = weight;
	e[num].next = head[from],head[from] = num++;
}

void tarjan(int x)
{
	low[x] = deep[x] = ++dep;
	for(int i = head[x] ; i + 1 ; i = e[i].next)
	{
		if(!deep[e[i].to]) {
			tarjan(e[i].to);
			low[x] = min(low[x],low[e[i].to]);
			if(low[e[i].to] >= deep[x] && x != 1)
				Spoints[x]++;
			else if(x == 1) root++;
		}
		else low[x] = min(low[x], deep[e[i].to]);
	}
}
int main()
{	
	//freopen("data.in","r",stdin);
	while(scanf("%d",&n) && n)
	{
		root = num = dep = 0; 
		memset(head, -1, sizeof head);
		memset(Spoints, 0,sizeof Spoints);
		memset(low,-1,sizeof low);
		memset(deep,0,sizeof deep);

		while (scanf("%d", &m) && m)  
            while (getchar() != '\n')  
            { 
            	int v;scanf("%d", &v);  
               	add_edge(v,m,0);
               	add_edge(m,v,0); 	
            }
		
		tarjan(1);

		int ans = 0;
		if(root > 1) ans++;
		for(int i = 2 ; i <= n ; i ++)
			if(Spoints[i]) ans++;
		printf("%d\n",ans);
	}
}