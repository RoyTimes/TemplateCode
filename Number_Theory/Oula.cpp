#include <cstdio>
#include <cstring>
#include <iostream>
#define N 10000000
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

int main()
{
	int n;
	q_Oula(1000000);
	while(scanf("%d",&n) && n != 0)
	{
		//long long tot = 0;
		//for(long long i = 1 ; i <= n ; i ++)tot += i[a];
		printf("%lld\n\n",a[n]);
	}
}
