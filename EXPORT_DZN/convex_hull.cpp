#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 10050 
int n,st[N],top;
double ans;
pair<double,double> a[N],s;

pair<double,double> operator -(pair<double,double> x,pair<double,double> y)
{
	return make_pair(x.first-y.first,x.second-y.second);
}

double operator *(pair<double,double> x,pair<double,double> y)
{
	return x.first*y.second-x.second*y.first;
}

double dist(pair<double,double> x,pair<double,double> y)
{
	return sqrt((x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second));
}

int convex_hull()
{
	for(int i=1;i<=n;i++)
	{
		while(top-2>=0&&(a[st[top-1]]-a[st[top-2]])*(a[i]-a[st[top-1]])<=0) top--;
		st[top++]=i;
	}
	for(int i=n-1;i;i--)
	{
		while(st[top-1]!=n&&(a[st[top-1]]-a[st[top-2]])*(a[i]-a[st[top-1]])<=0) top--;
		st[top++]=i;
	}
	if(n>=2) top--;
	return top;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%lf%lf",&a[i].first,&a[i].second);
	sort(a+1,a+n+1);
	convex_hull();
	for(int i=1;i<=top;i++) ans+=dist(a[st[i]],a[st[i-1]]);
	printf("%.2lf\n",ans);
}
