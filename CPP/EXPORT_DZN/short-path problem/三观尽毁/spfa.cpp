#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <queue>
using namespace std;
#define N 100
#define M 10000
int head[N],to[M],next[M],val[M],cnt;
int v[N];long long d[N];
int n,m;
queue<int> q;
void add(int x,int y,int z)
{
	val[++cnt]=z;
	to[cnt]=y;
	next[cnt]=head[x];
	head[x]=cnt;
}
int spfa(int s)
{
	int re=0;
	memset(d,0x3f,sizeof d);
	memset(v,0,sizeof v);
	q.push(s);d[s]=0;v[s]=1;
	while(!q.empty())
	{
		int x=q.front(),y;
		q.pop();
		re++;
		v[x]=0;
		for(int i=head[x];i;i=next[i])
		{
			if(d[y=to[i]]>d[x]+val[i])
			{
				d[y]=d[x]+val[i];
				if(v[y]==0)
					q.push(y),v[y]=1;
			}
		}
	}
	return re;
}
int main()
{
	int start,end;
	start=clock();
	cin>>n>>m;
	for(int x,y,z,i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	cout<<spfa(1)<<endl;
	cout<<d[n]<<endl;
	end=clock();
	printf("%lf\n",(double)(end-start)/1000);
	return 0;
}