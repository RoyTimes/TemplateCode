//Poj3468
//http://kenby.iteye.com/blog/962159
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 100010
int n,m;
long long a[N],b[N],sum[N];
void fix(long long arr[],int x,int y)
{
	for(int i=x;i<=n;i+=i&-i)
		arr[i]+=y;
}
long long query(long long arr[],int x)
{
	long long re=0;
	for(int i=x;i;i-=i&-i)
		re+=arr[i];
	return re;
}
bool getopt()
{
	char ch;
	while(!isalpha(ch=getchar()));
	if(ch=='Q') return true;
	return false;
}
int main()
{
	cin>>n>>m;
	for(int x,i=1;i<=n;i++)
		scanf("%d",&x),
		sum[i]=sum[i-1]+x;
	for(int x,y,z,i=1;i<=m;i++)
	{
		bool opt=getopt();
		scanf("%d%d",&x,&y);
		if(opt)
			printf("%lld\n",sum[y]-sum[x-1]+(y+1)*query(a,y)-query(b,y)-x*query(a,x-1)+query(b,x-1));
		else
			scanf("%d",&z),
			fix(a,x,z),fix(a,y+1,-z),
			fix(b,x,z*x),fix(b,y+1,-z*(y+1));
	}
	return 0;
}