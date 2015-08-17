#include <cstdio>

int x,y;
int exgcd(int a, int b)
{
	if(b == 0){
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b);
	int temp = x;
	x = y, y = temp - a/b * y;
	return d;
}

int main()
{
	int n,m; scanf("%d%d",&n,&m);
	int gcd = exgcd(n,m);
	printf("%d\n",x);
}