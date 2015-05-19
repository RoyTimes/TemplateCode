#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#define N 210
using namespace std;
int map[N][N],sum[N],ans[N];
int topsort(int n)
{
	queue<int>q;
	int in[N], cut = 0;
	bool _flag = 0;
	memcpy(in, sum, sizeof sum);

	for(int i = 1 ; i <= n ; i ++)
		if(!in[i]) q.push(i);
	if(q.size() > 1) _flag = 1;

	while(!q.empty())
	{
		int temp = q.front(); q.pop();
		ans[++cut] = temp,in[temp] = 1 << 18;
		for(int j = 1 ; j <= n ; j ++)
			if(map[temp][j])
			{
				in[j] --;
				if(!in[j]) q.push(j);
			}
			if(q.size() > 1) _flag = 1;
	}
	if(cut == n && _flag == 1) return 2; // not unique
	if(cut != n) return 1; //No solution 
	if(cut == n) return 0;
}
int main()
{
	int x,y;
	bool flag = 1;
	while(scanf("%d%d",&x,&y) != EOF && x && y)
	{
		memset(map,0,sizeof(map));
		memset(sum,0,sizeof(sum));
		memset(ans,0,sizeof(ans));
		for(int i = 1 ; i <= y ; i ++)
		{
			char n,m,u;
			getchar();
			scanf("%c%c%c",&n,&u,&m);
			if(flag == 1)
			{ 
				if(map[n - 'A' + 1][m - 'A' + 1] == 0)
					sum[m - 'A' + 1]++;
				map[n - 'A' + 1][m - 'A' + 1] = 1;
			
				int _ans = topsort(x);
				if( _ans == 0) 
				{
					printf("Sorted sequence determined after %d relations: ",i);
					for(int i = 1 ; i <= x ; i ++) printf("%c",ans[i] + 'A' - 1);
					printf(".\n");
					flag = 0;
					continue;
				}
				if(_ans == 1) {printf("Inconsistency found after %d relations.\n", i);flag = 0;}
				if(_ans == 2 && i == y) {printf("Sorted sequence cannot be determined.\n");flag = 0;}
			}
		}
		flag = 1;
		getchar();
	}
	return 0;
}
