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
int d[N];
int n,m;
priority_queue<pair<int,int> > q;
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
	q.push(make_pair(0,s));d[s]=0;
	while(!q.empty())
	{
		int x=q.top().second,y=-q.top().first;
		q.pop();
		if(y!=d[x]) continue;
		re++;
		y=0;
		for(int i=head[x];i;i=next[i])
		{
			if(d[y=to[i]]>d[x]+val[i])
			{
				d[y]=d[x]+val[i];
				q.push(make_pair(-d[y],y));
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