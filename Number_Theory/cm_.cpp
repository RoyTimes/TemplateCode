#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define N 3
using namespace std;
typedef unsigned long long LL;
struct Mx{LL x[N][N];Mx(){memset(x,0,sizeof(x));}};
LL m,a,c,x0,n,g;
LL Mul(LL _a , LL _b , LL mod)
{
    LL ans = 0;
    while(_b)
    {
        if(_b % 2 == 1) ans = (ans + _a) % mod;
        _a = (_a * 2) % mod;
        _b = _b >> 1;
    }return ans;
}
Mx mul(Mx a , Mx & b , LL mod)
{
    Mx ans;
    for(int i = 1 ; i <= 2 ; i ++)for(int j = 1 ; j <= 2 ; j ++)
    for(int k = 1 ; k <= 2 ; k ++){
    ans.x[i][j] += Mul(a.x[i][k],b.x[k][j] , mod) % mod;
    ans.x[i][j] = ans.x[i][j] % mod;}
    return ans;
}
Mx pow_(Mx & a , LL base , LL mod)
{
    Mx ret,ans;
    for(LL i = 1 ; i <= 2 ; i ++) ret.x[i][i] = 1;
    ans = a;
    while(base)
    {
        if(base & 1)ret = mul(ans,ret,mod);
        base = base >> 1;
        ans = mul(ans , ans , mod);
    }
    return ret;
}
int main()
{
    cin>>m>>a>>c>>x0>>n>>g;
     
    Mx prime, t;
    prime.x[1][1] = a;prime.x[1][2] = c;prime.x[2][1] = 0;prime.x[2][2] = 1;
     
    Mx last = pow_(prime,n,m);
    
    
    t.x[1][1] = x0;
    t.x[2][1] = 1;
    
    Mx ans = mul(last, t, m);
    printf("%lld\n",ans.x[1][1]%g);
    return 0;
}
