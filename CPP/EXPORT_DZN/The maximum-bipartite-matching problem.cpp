#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 205
#define M 20005
int m,n;
int head[N],next[M],to[M],cnt;
int v[N],match[N],ans;
void add(int x,int y)
{
	to[++cnt]=y;
	next[cnt]=head[x];
	head[x]=cnt;
}
int dfs(int x)
{
	for(int y,i=head[x];i;i=next[i])
	{
		if(!v[y=to[i]])
		{
			v[y]=1;
			if(!match[y]||dfs(match[y]))
			{
				match[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	cin>>n>>m;
	int x,y;
	while(scanf("%d%d",&x,&y),x>0||y>0)
		add(x,y),add(y,x);
	for(int i=1;i<=n;i++)
	{
		memset(v,0,sizeof v);
		ans+=dfs(i);
	}
	cout<<ans<<endl;
}
