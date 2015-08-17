#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define N 100010
using namespace std;
int f1[N][40],f2[N][40],num[N];
int log[N];
int n;
void Initialize()
{
	for(int i=2;i<=N;i++)
		log[i]=log[i>>1]+1;
}
inline int ask(int i , int j)
{
	int k =	log[j-i+1];
	int t1,t2;
	//t1 = max(f1[i][k], f1[j - (1<<k) + 1][k]);
	t2 = min(f2[i][k], f2[j - (1<<k) + 1][k]);
	return t2;
}
int st()
{
	for(int i = 1 ; i <= n ; i ++)
		f1[i][0] = f2[i][0] = num[i];
	for(int j = 1 ; (1 << j) <= n ; j ++)
		for(int i = 1 ; i + (1 << j) - 1 <= n ; i++)
		{
			//f1[i][j] = max(f1[i][j-1], f1[i + (1 << (j - 1))][j-1]);
			f2[i][j] = min(f2[i][j-1], f2[i + (1 << (j - 1))][j-1]);
		}
}
int main()
{
	freopen("data.in","r",stdin);
	Initialize();
	int m; cin>>n>>m;
	for(int i = 1 ; i <= n ; i ++) 
	scanf("%d",&num[i]);
	st();
	for(int i = 1 ; i <= m ;i ++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		int ans = ask(x,y);
		if(i == m) {printf("%d",ans);return 0;}
		printf("%d ",ans);
		
	}
	return 0;
}
