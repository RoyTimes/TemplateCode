#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX 101000<<2
using namespace std;

int a[MAX],col[MAX];

inline int lson(int x){return x<<1;};
inline int rson(int x){return (x<<1)|1;};

void PushUp(int root){a[root] = a[lson(root)] + a[rson(root)];}
void PushDown(int root, int m)
{
	if(col[root])
	{
		col[lson(root)] = col[rson(root)] = col[root];
		a[lson(root)] = (m - (m >> 1)) * col[root];
		a[rson(root)] = (m >> 1) * col[root];
		col[root] = 0;
	}
}

void Build(int x, int y, int root)
{
	col[root] = 0;
	a[root] = 1;	
	
	if(x == y)return;
	int mid = (x + y) >> 1;
	Build(x, mid, lson(root));
	Build(mid + 1, y, rson(root));
	PushUp(root);
}
void Update(int l, int r, int Val, int x, int y, int root)
{
	if(l <= x && y <= r)
	{
		col[root] = Val;
		a[root] = Val * (y - x + 1);
		return;
	}
	PushDown(root, y - x + 1);
	int mid = (x + y) >> 1;
	if(l <= mid) Update(l,r,Val,x,mid,lson(root));
	if(r > mid) Update(l,r,Val,mid + 1, y, rson(root));
	PushUp(root);
}

int main()
{
	//freopen("data.in","r",stdin);	
	//freopen("data.out","w",stdout);	
	
	int cas,n,m; cin>>cas;
	for(int i = 1 ; i <= cas; i ++)
	{
		memset(a,0,sizeof a);
		scanf("%d%d",&n,&m);
		Build(1, n, 1);
		
		for(int j = 1 ; j <= m ; j ++)
		{
			int mid1,mid2,mid3;
			scanf("%d%d%d",&mid1,&mid2,&mid3);
			Update(mid1,mid2,mid3,1,n,1);
		}
		printf("Case %d: The total value of the hook is %d.\n",i , a[1]);
	}
}







