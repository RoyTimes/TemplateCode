#include <cstdio>
#include <cstring>
#include <cstdlib>
#define N 10000
using namespace std;
int problem[N];
int main()
{
	int t;
	FILE *in;
	in=fopen("find.in","r");
	while(fscanf(in,"%d",&t)!=EOF)problem[t]=1;
	while(scanf("%d",&t),t)
	{
		if(problem[t])printf("AC\n");
		else printf("!!!\n");
	}
	return 0;
}
