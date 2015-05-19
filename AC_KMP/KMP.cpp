#ifdef _MSC_VER
#define DEBUG
#endif

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char src[1000005], Patten[10005];
int NextVal[10005];
int len_p, len_src;

void GetNext()
{
    int fix = 0; NextVal[1] = 0;
    for(int i = 2 ; i <= len_p ; i ++){
        while(fix && Patten[fix + 1] != Patten[i])
            fix = NextVal[fix];
        if(Patten[fix + 1] == Patten[i]) fix ++;
        NextVal[i] = fix;
    } 
}

int KMP()
{
    int ans = 0, fix = 0;
    for(int i = 1 ; i <= len_src ; i ++)
    {
        while(fix && Patten[fix + 1] != src[i]) fix = NextVal[fix];
        if(Patten[fix + 1] == src[i]) fix ++;
        if(fix == len_p) ans ++, fix = NextVal[fix];
    }
    return ans;
}

int main()
{
#ifdef DEBUG
    freopen("data.in", "r", stdin);
    //freopen("data.out","w",stdout);
#endif
    cin.sync_with_stdio(false);

    int cas; cin >> cas;
    while (cas -- )
    {
        cin >> Patten + 1 >> src + 1;
        len_src = strlen(src + 1);
        len_p = strlen(Patten + 1);
        GetNext();
        cout << KMP() << endl;
    }
    return 0;
}