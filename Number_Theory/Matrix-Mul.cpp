#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define N 100
#define mod 12345678
using namespace std;
struct Mx{long long x[N][N];Mx(){memset(x,0,sizeof(x));}};

Mx mul(Mx a , Mx b)
{
	Mx ans;
	for(int i = 1 ; i <= 4 ; i ++)
		for(int j = 1 ; j <= 4 ; j ++)
		{
			for(int k = 1 ; k <= 4 ; k ++){
			ans.x[i][j] += (a.x[i][k] * b.x[k][j]) % mod;
			ans.x[i][j] = ans.x[i][j] % mod;
			}
		}
	return ans;
}

Mx pow_(Mx a , int base)
{
	Mx ret,ans;
	for(int i = 1 ; i <= 4 ; i ++) ret.x[i][i] = 1;
	ans = a;
	while(base)
	{
		if(base & 1)ret = mul(ans,ret);
		base = base >> 1;
		ans = mul(ans , ans);
	}
	return ret;
}

int main()
{
	//freopen("data.in","r",stdin);
	long long f0,f1,a,b,c,d;
	int n;
	cin>>f0>>f1>>a>>b>>c>>d;
	cin>>n;
	
	Mx prime;
	prime.x[1][1] = a;prime.x[1][2] = b;prime.x[1][3] = c;prime.x[1][4] = d;
	prime.x[2][1] = 1;prime.x[3][3] = 1;prime.x[3][4] = 1;prime.x[4][4] = 1;
	Mx Last = pow_(prime,n - 1);
	
	long long  _ans = (f1 * Last.x[1][1] + f0 * Last.x[1][2] -Last.x[1][3] + Last.x[1][4]) % mod;
	printf("%lld\n",_ans);
}
				
