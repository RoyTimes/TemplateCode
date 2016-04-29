#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#define lson pos<<1
#define rson pos<<1|1
using namespace std;
int n,sum[524288],f[524288],a[131072];
void build(int pos,int l,int r)
{
    int mid=(l+r)>>1;
    if(l==r) {sum[pos]=a[l];return;}
    build(lson,l,mid);
    build(rson,mid+1,r);
    sum[pos]=sum[lson]+sum[rson];
}
void lazy(int pos,int l,int r)
{
	int mid=(l+r)>>1;
	sum[lson]+=(mid-l+1)*f[pos];
	f[lson]+=f[pos];
	sum[rson]+=(r-mid)*f[pos];
	f[rson]+=f[pos];
	f[pos]=0;
}
void fix(int pos,int l,int r,int x,int y,int z)
{
	int mid=(l+r)>>1;
	if(x<=l&&r<=y)
	{
		sum[pos]+=(r-l+1)*z;
		f[pos]+=z;
		return;
	}
	if(f[pos]) lazy(pos,l,r);
	if(y<=mid)
		fix(lson,l,mid,x,y,z);
	else if(mid<x)
		fix(rson,mid+1,r,x,y,z);
	else
	{
		fix(lson,l,mid,x,y,z);
		fix(rson,mid+1,r,x,y,z);
	}
	sum[pos]=sum[lson]+sum[rson];
}
int getsum(int pos,int l,int r,int x,int y)
{
	int re=0;
	if(x<=l&&r<=y) return sum[pos];
	if(f[pos])
		lazy(pos,l,r);
	int mid=(l+r)>>1;
	if(y<=mid)
		re+=getsum(lson,l,mid,x,y);
	else if(mid<x)
		re+=getsum(rson,mid+1,r,x,y);
	else
	{
		re+=getsum(lson,l,mid,x,y);
		re+=getsum(rson,mid+1,r,x,y);
	}
	return re;
}
int main()
{
	cin>>n;
	build(1,1,n);
	
	return 0;
}
