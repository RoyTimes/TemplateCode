#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 200001
int n,a[N];

inline void Stooge_Sort(int l,int r)
{
	if(a[r]<a[l])
		swap(a[l],a[r]);
	if(r-l+1>=3)
	{
		int t=(r-l+1)/3;
		Stooge_Sort(l,r-t);
		Stooge_Sort(l+t,r);
		Stooge_Sort(l,r-t);
	}
}


inline void Suffle()
{
	for(int randnum,i=1;i<=n;i++)
		randnum=rand()%(n-i+1),
		swap(a[i],a[i+randnum]);
}
inline bool Check()
{
	for(int i=2;i<=n;i++)
		if(a[i]<a[i-1])
			return false;
	return true;
}
void Bogo_Sort()
{
	srand((unsigned)time(NULL));
	while(!Check())
		Suffle();
}


void Gnome_Sort()
{
	int i=1;
	while(i<=n)
		i>1&&a[i-1]>a[i]?swap(a[i-1],a[i]),i--:i++;
} 

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	Gnome_Sort();
	for(int i=1;i<=n;i++)
		cout<<a[i]<<' ';
}