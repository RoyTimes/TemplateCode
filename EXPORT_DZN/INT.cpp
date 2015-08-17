#include <cstdio>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
#define LEN 25005
#define MOD 10000
struct INT
{
	int num[LEN],len;
	bool sign;
	inline INT(long long x=0)
	{
		*this=x;
	}
	inline INT(const string &str)
	{
		*this=str;
	}
	inline INT(const int a[],int b,bool c)
	{
		memcpy(num,a,sizeof num);
		len=b; sign=c;
	}
	inline INT &operator =(const string &str)
	{
		int start=0;
		len=0;sign=false;
		memset(num,0,sizeof num);
		if(str[0]=='-') sign=true,start=1;
		while(str[start]=='0') start++;
		for(int i=str.length()-1;i>=start;i-=4,len++)
			for(int j=max(start,i-3);j<=i;j++)
				num[len]=(num[len]<<3)+(num[len]<<1)+str[j]-'0';
		if(!len) sign=false;
		if(len) len--;
		return *this;
	}
	inline INT &operator =(long long x)
	{
		len=0;sign=false;
		memset(num,0,sizeof num);
		if(x<0) sign=true,x=-x;
		while(x)
			num[len++]=x%MOD,
			x/=MOD;
		if(len) len--;
		return *this;
	}
	inline int length() const
	{
		int re=len<<2,t=num[len];
		while(t) t/=10,re++;
		return re;
	}
	inline void print()
	{
		if(sign) putchar('-');
		printf("%d",num[len]);
		for(int i=len-1;i>=0;i--)
			printf("%04d",num[i]);
	}
	inline friend void print_to_string(const INT &x,string &y)
	{
		stringstream stream;
		stream<<x;
		stream>>y;
	}
	inline friend INT pow(const INT &x,int y)
	{
		INT re=1,_x=x;
		while(y)
		{
			if(y&1)
				re*=_x;
			y>>=1;
			_x*=_x;
		}
		return re;
	}
	inline friend INT pow(const INT &x,const INT &y)
	{
		INT re=1,_x=x,_y=y;
		while(_y!=0)
		{
			if(_y.num[0]%2==1)
				re*=_x;
			_y=shr(_y);
			_x*=_x;
		}
		return re;
	}
	inline friend istream &operator >>(istream &in,INT &x)
	{
		string str;
		in>>str;
		x=str;
		return in;
	}
	inline friend ostream &operator <<(ostream &out, const INT &x)
	{
		if(x.sign) out<<'-';
		out<<x.num[x.len];
		for(int i=x.len-1;i>=0;i--)
			out.fill('0'),out.width(4),out<<x.num[i];
		return out;
	}
	inline INT operator -() const
	{
		return INT(num,len,!sign);
	}
	inline friend INT abs(const INT &x)
	{
		return INT(x.num,x.len,false);
	}
	inline friend bool operator <(const INT &x,const INT &y)
	{
		if(x.sign^y.sign) return x.sign;
		int lx=x.length(),ly=y.length();
		if(lx==ly)
		{
			for(int i=x.len;i>=0;i--)
				if(x.num[i]!=y.num[i])
					return (x.num[i]<y.num[i])^x.sign;
			return false;
		}
		return (lx<ly)^x.sign;
	}
	inline friend bool operator >(const INT &x,const INT &y){ return y<x; }
	inline friend bool operator <=(const INT &x,const INT &y){ return !(y<x); }
	inline friend bool operator >=(const INT &x,const INT &y){ return !(x<y); }
	inline friend bool operator ==(const INT &x,const INT &y){ return !(x<y||y<x); }
	inline friend bool operator !=(const INT &x,const INT &y){ return !(x==y); }

	inline friend INT operator +(const INT &x,const INT &y)
	{
		if(x.sign^y.sign)
			return x-(-y);
		INT re;
		re.sign=x.sign;
		re.len=max(x.len,y.len);
		for(int i=0;i<=re.len;i++)
		{
			re.num[i]+=x.num[i]+y.num[i];
			re.num[i+1]=re.num[i]/MOD;
			re.num[i]%=MOD;
		}
		if(re.num[re.len+1]) re.len++;
		return re;
	}
	inline friend INT operator -(const INT &x,const INT &y)
	{
		if(x.sign^y.sign)
			return x+(-y);
		INT re,_x=x,_y=y;
		re.sign=_x<_y;
		if(re.sign^_x.sign)
			swap(_x,_y);
		for(int i=0;i<=_x.len;i++)
		{
			re.num[i]+=_x.num[i]-_y.num[i];
			if(re.num[i]<0)
				re.num[i]+=MOD,
				re.num[i+1]--;
		}
		re.len=_x.len;
		while(!re.num[re.len]&&re.len>=0) re.len--;
		return re;
	}
	inline friend INT operator *(const INT &x,const INT &y)
	{
		INT re;
		if((!x.len&&!x.num[0])||(!y.len&&!y.num[0])) return re;
		re.sign=x.sign^y.sign;
		re.len=x.len+y.len;
		for(int i=0;i<=y.len;i++)
		{
			for(int j=0;j<=x.len;j++)
			{
				re.num[i+j]+=x.num[j]*y.num[i];
				re.num[i+j+1]+=re.num[i+j]/MOD;
				re.num[i+j]%=MOD;
			}
		}
		if(re.num[re.len+1]) re.len++;
		return re;
	}
	inline friend INT operator /(const INT &x,const INT &y)
	{
		if((!y.len&&!y.num[0])||(!x.len&&!x.num[0])||abs(x)<abs(y)){ return INT(); }
		INT re,left,_y=abs(y);
		re.sign=x.sign^y.sign;
		re.len=x.len-y.len+1;
		left.len=-1;
		for(int i=x.len;i>=0;i--)
		{
			memmove(left.num+1,left.num,sizeof(left.num)-sizeof(int));
			left.len++;
			left.num[0]=x.num[i];
			int l=0,r=MOD-1,mid;
			if(left<y) r=1;
			while(l<r)
			{
				mid=(l+r)>>1;
				INT t=mid;
				if(t*_y<=left)
					l=mid+1;
				else r=mid;
			}
			re.num[i]=r-1;
			INT t=r-1;
			left=left-(t*_y);
		}
		while(re.num[re.len]==0&&re.len) re.len--;
		return re;
	}
	inline friend INT operator %(const INT &x,const INT &y)
	{
		if((!y.len&&!y.num[0])||(!x.len&&!x.num[0])){ return INT(); }
		INT left,_y=abs(y);
		left.sign=(x.sign&&!y.sign);
		left.len=-1;
		for(int i=x.len;i>=0;i--)
		{
			memmove(left.num+1,left.num,sizeof(left.num)-sizeof(int));
			left.len++;
			left.num[0]=x.num[i];
			int l=0,r=MOD-1,mid;
			while(l<r)
			{
				mid=(l+r)>>1;
				INT t=mid;
				if(t*_y<=left)
					l=mid+1;
				else r=mid;
			}
			INT t=r-1;
			left=left-(t*_y);
		}
		return left;
	}
	inline friend INT shr(const INT &x)
	{
		INT re;
		re.len=x.len;
		for(int i=re.len;i>=0;i--)
		{
			if(x.num[i]&1&&i-1>=0)
				re.num[i-1]+=MOD>>1;
			re.num[i]+=x.num[i]>>1;
		}
		if(!re.num[re.len]) re.len--;
		return re;
	}
	inline friend INT shr(const INT &x)
	{
		INT re;
		re.len=x.len;
		for(int i=re.len;i>=0;i--)
		{
			if(x.num[i]&1&&i-1>=0)
				re.num[i-1]+=MOD>>1;
			re.num[i]+=x.num[i]>>1;
		}
		if(re.len&&!re.num[re.len]) re.len--;
		return re;
	}
	INT &operator +=(const INT &x){ return *this=*this+x; }
	INT &operator -=(const INT &x){ return *this=*this-x; }
	INT &operator *=(const INT &x){ return *this=*this*x; }
	INT &operator /=(const INT &x){ return *this=*this/x; }
	INT &operator %=(const INT &x){ return *this=*this%x; }
};
int main()
{
	INT a,b;
	string str;
	cin>>a>>b;
	print_to_string(pow(a,b),str);
	cout<<str<<endl;
}
