#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    for (int i = 1; i <= 100000; i++)
    {
        system("data");
        system("std <in.in >out.out");
        system("splay <in.in >out2.out");
        if (system("fc out.out out2.out >res.txt"))
        {
            printf("WA");
            break;
        }
        else
            printf("Case %d : AC\n", i);
    }
}
