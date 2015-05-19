#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 1000050
char a[N], b[N];
int pre[N];
void getpre(char str[])
{
    memset(pre, 0, sizeof pre);
    for (int fix = 0, i = 2; str[i] != '\0'; i++)
    {
        while (fix && str[fix + 1] != str[i])
            fix = pre[fix];
        if (str[fix + 1] == str[i])
            fix++;
        pre[i] = fix;
    }
}
int getsum(char str1[], char str2[])
{
    int re = 0;
    for (int fix = 0, i = 1; str2[i] != '\0'; i++)
    {
        while (fix && str1[fix + 1] != str2[i])
            fix = pre[fix];
        if (str1[fix + 1] == str2[i])
            fix++;
        if (str1[fix + 1] == '\0')
        {
            re++;
            fix = pre[fix];
        }
    }
    return re;
}
int main()
{
    scanf("%s%s", a + 1, b + 1);
    getpre(b);
    printf("%d\n", getsum(b, a));
    return 0;
}
