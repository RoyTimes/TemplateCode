#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX 201000<<2
using namespace std;

long long a[MAX],col[MAX];

inline int lson(int x){return x<<1;};
inline int rson(int x){return (x<<1)|1;};
inline void PushUp(int root){a[root] = a[lson(root)] + a[rson(root)];}
long long BuildLeafNodeArrived(){long long mid;scanf("%lld",&mid);return mid;}

void PushDown(int root, int m)
{
	if(col[root])
	{
		col[lson(root)] += col[root];
		col[rson(root)] += col[root];
		a[lson(root)] += (m - (m >> 1)) * col[root];
		a[rson(root)] += (m >> 1) * col[root];
		col[root] = 0;
	}
}

void Build(int x, int y, int root)
{
	col[root] = 0;	
	if(x == y){a[root] = BuildLeafNodeArrived(); return;}
	int mid = (x + y) >> 1;
	Build(x, mid, lson(root));
	Build(mid + 1, y, rson(root));
	PushUp(root);
}
void Update(int l, int r, int Val, int x, int y, int root)
{
	if(l <= x && y <= r)
	{
		col[root] += Val;
		a[root] += (long long)Val * (y - x + 1);
		return;
	}
	PushDown(root, y - x + 1);
	int mid = (x + y) >> 1;
	if(l <= mid) Update(l,r,Val,x,mid,lson(root));
	if(mid < r) Update(l,r,Val,mid + 1, y, rson(root));
	PushUp(root);
}

long long Ask(int l, int r, int x, int y, int root)
{
	if(l <= x && y <= r) return a[root];
	PushDown(root,y - x + 1);
	int mid = (x + y) >> 1;
	long long ret = 0;
	if(l <= mid) ret += Ask(l,r,x,mid,lson(root));
	if(mid < r) ret += Ask(l,r,mid + 1, y,rson(root));
	return ret;
}

int main()
{
	//freopen("data.in","r",stdin);	
	//freopen("data.out","w",stdout);	
	
	int n,q; cin>>n>>q;
	Build(1,n,1);
	for (unsigned int i = 0; i < q; i ++)
	{
		char s[4]; int mid1,mid2,mid3;
		scanf("%s",s);
		if(s[0] == 'Q')
		{			
			scanf("%d%d",&mid1,&mid2);
			printf("%lld\n",Ask(mid1,mid2,1,n,1));	
		}
		else
		{
			scanf("%d%d%d",&mid1,&mid2,&mid3);
			Update(mid1,mid2,mid3,1,n,1);
		}
	}
}
