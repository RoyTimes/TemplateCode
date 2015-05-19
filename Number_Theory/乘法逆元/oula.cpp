#include <cstdio>
#define N 100100
using namespace std;

long long a[N],Prime[N];
bool able[N];

void q_Oula(long long n)
{
	long long cut = 0;
	for(int i = 2 ; i <= n ; i ++)
	{
		if(able[i] == 0) a[i] = i - 1,Prime[++cut] = i;
		for(int j = 1 ; Prime[j] * i <= n && j <= cut ; j ++)
		{
			able[Prime[j] * i] = 1;
			if(i % Prime[j] == 0)
			{
				a[i * Prime[j]] = a[i] * Prime[j];
				break;
			}
			else a[i * Prime[j]] = a[i] * (Prime[j] - 1);
		}
	}
}
int pow(int x, long long y, int mod)
{
	int ans = x;
	for(int i = 1 ; i < y ; i ++)
		ans *= x,ans = ans % mod;
	return ans;
}

int main()
{
	q_Oula(100000);
	int n,m; 
	n = 2, m = 9901;
	printf("%d\n",pow(n,a[m] - 1,m));
}
