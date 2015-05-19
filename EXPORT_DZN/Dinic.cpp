#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 105
#define M 5005
#define inf 0x3f3f3f3f
queue<int> q;
int head[N],next[M],to[M],val[M],cnt=1;
int n,m,s,t,d[N];
void add(int x,int y,int z)
{
	to[++cnt]=y;
	val[cnt]=z;
	next[cnt]=head[x];
	head[x]=cnt;
}
bool bfs()
{
	memset(d,0,sizeof d);
	while(!q.empty()) q.pop();
	d[s]=1; q.push(s);
	while(!q.empty())
	{
		int x=q.front(),y; q.pop();
		for(int i=head[x];i;i=next[i])
			if(val[i]&&!d[y=to[i]])
			{
				d[y]=d[x]+1;
				if(y==t) return true;
				q.push(y);
			}
	}
	return false;
}
int dinic(int x,int f)
{
	if(x==t) return f;
	int temp=f,y;
	for(int i=head[x];i;i=next[i])
		if(val[i]&&temp&&d[y=to[i]]==d[x]+1)
		{
			int k=dinic(y,min(val[i],temp));
			if(!k) d[y]=0;
			val[i]-=k; val[i^1]+=k;
			temp-=k;
		}
	return f-temp;
}
int maxflow()
{
	int re=0,x;
	while(bfs())
		while(x=dinic(s,inf))
			re+=x;
	return re;
}
int main()
{
	cin>>m>>n;
	s=0;t=n+1;
	for(int i=1;i<=m;i++)
		add(s,i,1),add(i,s,0);
	for(int i=m+1;i<=n;i++)
		add(i,t,1),add(t,i,0);
	int x,y;
	while(scanf("%d%d",&x,&y),x!=-1)
		add(x,y,1),add(y,x,0);
	cout<<maxflow()<<endl;
	for(int i=1;i<=m;i++)
		for(int j=head[i];j;j=next[j])
			if(val[j]==0&&to[j]!=0)
				printf("%d %d\n",i,to[j]);
	return 0;
}
