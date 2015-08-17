#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX 55555<<2
using namespace std;

int a[MAX];

inline int lson(int x){return x<<1;};
inline int rson(int x){return (x<<1)|1;};

void FatherUpdate(int root){a[root] = a[lson(root)] + a[rson(root)];}
int BuildLeafNodeArrived(){int mid;scanf("%d",&mid);return mid;}

void Build(int x, int y, int root)
{
	if(x == y){a[root] = BuildLeafNodeArrived();return;}
	int mid = (x + y) >> 1;
	Build(x, mid, lson(root));
	Build(mid + 1, y, rson(root));
	FatherUpdate(root);
}

void Update(int pos,int Val , int x, int y, int root)
{
	if(x == y){a[root] += Val;return;}
	int mid = (x + y) >> 1;
	if(pos <= mid) Update(pos,Val,x,mid,lson(root));
	else Update(pos,Val,mid + 1,y,rson(root));
	FatherUpdate(root);
}

int Ask(int l, int r, int x, int y, int root)
{
	if(l <= x && y <= r) return a[root];
	int mid = (x + y) >> 1,ans = 0;
	if(l <= mid) ans += Ask(l, r, x, mid, lson(root));
	if(r > mid) ans += Ask(l, r, mid + 1, y, rson(root));
	return ans;	 
}

int main()
{
	//freopen("data.in","r",stdin);	
	//freopen("data.out","w",stdout);	
	
	int cas,n; cin>>cas;
	for(int i = 1 ; i <= cas; i ++)
	{
		memset(a,0,sizeof a);
		
		printf("Case %d:\n",i);
		scanf("%d",&n);
		Build(1, n, 1);
		
		
		char temp[10]; 
		while(scanf("%s",temp))
		{
			if(temp[0] == 'E') break;
			int w,p; scanf("%d%d",&w,&p);
			
			if(temp[0] == 'S') Update(w,-p,1,n,1);
			else if(temp[0] == 'A') Update(w,p,1,n,1);
			else if(temp[0] == 'Q') printf("%d\n",Ask(w,p,1,n,1));
		}
	}
}
