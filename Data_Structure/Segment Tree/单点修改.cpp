#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX 222222<<2
using namespace std;

int a[MAX];

inline int lson(int x){return x<<1;};
inline int rson(int x){return (x<<1)|1;};

void FatherUpdate(int root){a[root] = max(a[lson(root)] , a[rson(root)]);}
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
	if(x == y){a[root] = Val;return;}
	int mid = (x + y) >> 1;
	if(pos <= mid) Update(pos,Val,x,mid,lson(root));
	else Update(pos,Val,mid + 1,y,rson(root));
	FatherUpdate(root);
}

int Ask(int l, int r, int x, int y, int root)
{
	if(l <= x && y <= r) return a[root];
	int mid = (x + y) >> 1,ans = 0;
	if(l <= mid) ans = max(ans,Ask(l, r, x, mid, lson(root)));
	if(r > mid) ans = max(ans,Ask(l, r, mid + 1, y, rson(root)));
	return ans;	 
}

int main()
{
	freopen("data.in","r",stdin);	
	//freopen("data.out","w",stdout);	
	
	int ask,n;
	while(scanf("%d%d",&n,&ask) != EOF){
		
		memset(a,0,sizeof a);
		Build(1, n, 1);
		
		char temp[10]; 
		
		
		for(int i = 1 ;  i <= ask ; i ++)
		{
			scanf("%s",temp);
			int w,p; scanf("%d%d",&w,&p);
			
			if(temp[0] == 'S') Update(w,-p,1,n,1);
			else if(temp[0] == 'U') Update(w,p,1,n,1);
			else if(temp[0] == 'Q') printf("%d\n",Ask(w,p,1,n,1));
		}
	}
}
