#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 10005
#define M 50005
int z[N],v[N],inz[N],deep[N],low[N],re[N],belong[N],out[N],sum,cnt,top,m,n;
int head[N],next[M],to[M],x[M],y[M],num,ans;
void add(int x,int y)
{
	next[++num]=head[x];
	head[x]=num;
	to[num]=y;
}
void tarjan(int x)
{
	z[++top]=x;v[x]=1;inz[x]=1;
	deep[x]=low[x]=++cnt;
	for(int y,i=head[x];i;i=next[i])
		if(v[y=to[i]]==0)
			tarjan(y),
			low[x]=min(low[x],low[y]);
		else if(inz[to[i]]==1)
			low[x]=min(low[x],deep[y]);
	if(deep[x]==low[x])
	{
		sum++;
		int t;
		do{
			t=z[top--];
			inz[t]=0;
			belong[t]=sum;
			re[sum]++;
		}while(t!=x);
	}
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&x[i],&y[i]),
		add(x[i],y[i]);
	for(int i=1;i<=n;i++)
		if(v[i]==0)
			tarjan(i);
	for(int i=1;i<=m;i++)
		if(belong[x[i]]!=belong[y[i]])
			out[belong[x[i]]]++;
	for(int i=1;i<=sum;i++)
		if(out[i]==0)
			ans++;
	if(ans!=1) printf("0");
	else for(int i=1;i<=sum;i++)
		if(out[i]==0)
		{
			printf("%d",re[i]);
			break;
		}
	return 0;
}