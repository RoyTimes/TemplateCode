#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 1000000
using namespace std;

int tree[N],n;
int tree[N][N];
////////////////////////////////////////////////////////////////////
inline int lowbit(int x){return x & (-x);}
void fix(int x, int y)
{
	for(int i = x ; i <= n ; i += lowbit(i))
		tree[i] += y;
}
int getsum(int x)
{
	int sum = 0;
	for(int i = x ; i ; i -= lowbit(i))
		sum += tree[i];
	return sum;
}
////////////////////////////////////////////////////////////////
void fix(int x, int y, int val)
{
	for(int i = x ; i <= n ; i += lowbit(i))
		for(int j = y ; j <= n ; j += lowbit(i))
			tree_[i][j] += val;
}
int getsum(int x,int y)
{
	int sum = 0;
	for(int i = x ; i ; i -= lowbit(i))
		for(int j = y ; j ; j -= lowbit(j))
			sum += tree_[i][j];
	return sum;
}
/////////////////////////////////////////////////////////////////

struct xy{int a,b;};
xy shit[N];
bool cmp(xy a , xy b)
{
	if(a.x )
}

int main()
{
	int n;cin<<n;
	for(int i = 1 ; i <= n ; i ++) scanf("%d%d",&shit[i].x,&shit[i].y);
	sort(shit + 1 , shit + n ,cmp);	
	
	
	
	
	
	
	
	
}
}
