#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define P1 i*2+1
#define P2 i*2+2
#define P3 i*2+3
using namespace std;
int main()
{
    int N;
    cin>>N;
    int n=N*2+1,m=N*3;
    printf("%d %d\n",n,m);
    for(int i=0;i<N;i++)
    {
        printf("%d %d %d\n",P2,P3,-(1<<(N-i)));
        printf("%d %d %d\n",P1,P3,-(1<<(N-i-1)));
        printf("%d %d %d\n",P1,P2,0);
    }
    return 0;
}