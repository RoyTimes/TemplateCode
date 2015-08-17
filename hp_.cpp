#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define N 27000
#define mod 10000
using namespace std;

struct hp
{
    long long a[N];
    bool flag;
      
    hp(){memset(a,0,sizeof(a));flag = 0;}
    hp & operator = (const char* c)
    {
        int shit = 0;
        if(c[0] == '-') {flag = 1;shit = 1;}
        int len = strlen(c) - shit,mul = 1,digit = 1;
        for(int i = 1 ; i <= len ; i ++)
        {
            if(mul == mod) digit ++, mul = 1;
            a[digit] += mul * (c[len - i + shit] - '0');
            mul *= 10;
        }
        a[0] = digit;
        return *this;
    }      
    hp & operator = (int x)
    {
        char s[N];
        sprintf(s, "%d" ,x);
        return *this = s;
    }
    
    bool operator > (hp & x)
    {
        if( a[0]  >  x.a[0] ) return true;
        else if(a[0] < x.a[0] )return false;
        else
        {
            for(int i = a[0] ; i >= 0 ; i --)
            {
                if(a[i] > x.a[i]) return true;
                if(a[i] < x.a[i]) return false;
            }
        }
        return false;
    }
    bool operator <  (hp & x) {return x > *this;}
    bool operator >= (hp & x){return !(*this < x);}
    bool operator <= (hp & x){return !(*this > x);}
    bool operator == (hp & x){return !(*this < x)&&( *this > x);}
    bool operator != (hp & x){return !(*this == x);}
    hp & operator + (hp & x)
    {
        if(flag == 1) return x - *this;
        if(x.flag == 1) return *this;
          
        hp ans;
        ans.a[0] = max(x.a[0] , a[0]);
        for(int i = 1 ; i <= ans.a[0] ; i ++)
        {
            ans.a[i] += a[i] + x.a[i];
            if(ans.a[i] >= mod)
            {
                ans.a[i] -= mod;
                ans.a[i + 1] ++;
            }
        }
        if(ans.a[ans.a[0] + 1] > 0) ans.a[0]++;
        return &ans;
    } 
    hp & operator - (hp & x)
    {
        hp ans;
        if(*this < x)
        {
            ans.flag = 1;
            hp t;
            t = *this; *this = x; x = t;
        }
        ans.a[0] = a[0];
        for(int i = 1 ; i <= ans.a[0] ; i ++)
        {
            ans.a[i] += a[i] - x.a[i];
            if(ans.a[i] < 0)
            {
                ans.a[i] += mod;
                ans.a[i + 1] --;
            }
        }
        while(ans.a[ans.a[0]] == 0 && ans.a[0] > 1) ans.a[0]--;
        return &ans;
    }
   hp & operator * (hp & x)
    {
        hp ans;
        if((flag == 1 && x.flag == 0) || (flag == 0 && x.flag == 1))
        {
            ans.flag = 1;
            if((x.a[0] == 1 && x.a[1] == 0) || (a[0] == 1 && a[1] == 0)) ans.flag = 0;
        }
          
        ans.a[0] = a[0] + x.a[0] + 1;
        for(int i = 1 ; i <= a[0] ; i ++)
        {
            for(int j = 1 ; j <= x.a[0] ; j ++)
            {
                ans.a[i + j - 1] += a[i] * x.a[j];
                ans.a[i + j] += ans.a[i + j - 1] / mod;
                ans.a[i + j - 1] = ans.a[i + j - 1] % mod;
            }
        }
        while(ans.a[ans.a[0]] == 0 && ans.a[0] > 1) ans.a[0]--;
        return &ans;
    }
    hp & operator % (hp & x)
    {
        hp ans,left;
        ans.a[0] = a[0] - x.a[0] + 1;
         
        for(int i = a[0] ; i >= 1 ; i --)
        {
            memmove(left.a + 2 , left.a + 1, sizeof(left.a) - sizeof(int)*2);
            left.a[0]++;
            left.a[1] = a[i];
             
            int l = 0, ri = 9999, mid;
             
            while(l < ri)
            {
                mid = (l + ri) >> 1;
                hp temp; temp = mid;
                if(x * temp <= left) l = mid + 1;
                else ri = mid;
                 
            }
             
            ans.a[i] = ri - 1;
            hp temp; temp = ri - 1;
         
            hp tmp = x * temp;
            left = left - tmp;
        }
        while(ans.a[ans.a[0]] == 0 && ans.a[0] > 1) ans.a[0]--;
        return &left;
    }
    hp & operator / (hp & x)
    {
        hp ans,left;
        ans.a[0] = a[0] - x.a[0] + 1;
         
        for(int i = a[0] ; i >= 1 ; i --)
        {
            memmove(left.a + 2 , left.a + 1, sizeof(left.a) - sizeof(int)*2);
            left.a[0]++;
            left.a[1] = a[i];
             
            int l = 0, ri = mod - 1, mid;
            while(l < ri)
            {
                mid = (l + ri) >> 1;
                hp temp; temp = mid;
                if(x * temp <= left) l = mid + 1;
                else ri = mid;
                 
            }
            ans.a[i] = ri - 1;
            hp temp; temp = ri - 1;
            hp tmp = x * temp;
            left = left - tmp;
        }
        while(ans.a[ans.a[0]] == 0 && ans.a[0] > 1) ans.a[0]--;
        ans.print();
        left.print();
        return &ans;
    }
    void print()
    {
        if(flag == 1) printf("-");
        printf("%lld",a[a[0]]);
        for(int i = a[0] - 1 ; i >= 1 ; i --)
            printf("%04lld",a[i]);
        printf("\n");
        return;
    }
};
  
  
char q[100020],p[100020];
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%s%s",q,p);
    hp a,b,c;
    a = q;
    b = p;
    c = a / b;
   // c.power(a,6);
   // c.print();
    return 0;
}
