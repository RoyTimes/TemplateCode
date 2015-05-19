#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
 
const int N = 50100;
int father[N], relation[N];
int cut = 0, n;
 
int Find(int x)
{
    if (x != father[x])
    {
        int fx = Find(father[x]);
        relation[x] = (relation[x] + relation[father[x]]) % 3;
        father[x] = fx;
    }
    return father[x];
}
 
bool Union(int d, int x, int y)
{
    int fx = Find(x), fy = Find(y);
    if (fx == fy)
    {
        if ((relation[y] - relation[x] + 3) % 3 != d)
            return true;
        return false;
    }
    father[fy] = fx;
    relation[fy] = (relation[x] - relation[y] + d + 3) % 3;
    return false;
}
int main()
{
    cin.sync_with_stdio(false);
 
    int cas; cin >> n >> cas;
 
    for (int i = 0 ; i <= n ; i ++ )
        father[i] = i, relation[i] = 0;
 
    for (int i = 1 ; i <= cas ; i ++)
    {
        int d, x, y; cin >> d >> x >> y;
        if (x > n || y > n || (x == y && d == 2))
            cut ++;
        else if ( Union(d - 1, x, y) )
            cut ++;
    }
    cout << cut << endl;
    return 0;
}
