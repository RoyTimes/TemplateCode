#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 105
bool mp[N][N];
int deep[N],low[N],f[N],tot,ans,n,m;
void tarjan(int x)
{
	deep[x]=low[x]=++tot;
	for(int y=1;y<=n;y++)
		if(mp[x][y])
			if(!deep[y])
			{
				tarjan(y),low[x]=min(low[x],low[y]);
				if(low[y]>=deep[x])
					f[x]++;
			}
			else low[x]=min(low[x],deep[y]);
}
int main()
{
	int x,y;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&x,&y),
		mp[x][y]=mp[y][x]=true;
	for(int i=1;i<=n;i++)
		f[i]=1;
	for(int i=1;i<=n;i++)
		if(!deep[i])
			f[i]--,tarjan(i);
	for(int i=1;i<=n;i++)
		if(f[i]>=2)
			ans++;
	printf("%d\n",ans);
	return 0;
}
