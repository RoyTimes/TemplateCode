#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char s[30000] = {0};
char code[100000];
int len = 0;
int  stack[100];
int stack_len = 0;

int main(int argc, char *argv[])
{
    char c;
    int i = 0, j, k;
    char *p = s + 10000;


    freopen("bf.txt", "r", stdin);
    scanf("%s", code);

    int len = strlen(code);
    setbuf(stdout,NULL);
    while (i < len)
    {

        //  printf("%c ", code[i]);
        switch (code[i])
        {
            case '+': (*p)++; break;
            case '-': (*p)--; break;
            case '>': p++; break;
            case '<': p--; break;
            case '.': putchar((int)(*p)); break;
            case ',': *p = getchar(); break;
            case '[':
                if (*p)
                    stack[stack_len++] = i;
                else{
                    for (k = i, j = 0; k < len; k++)
                    {
                        code[k] == '['&&j++;
                        code[k] == ']'&&j--;
                        if (j == 0)break;
                    }
                    if (j == 0) i = k;
                    else
                    {
                        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
                        return 3;
                    }
                }
                break;

            case ']': i = stack[stack_len-- - 1] - 1; break;
            default: break;
        }
        i++;
    }

    puts("\n");
    puts("The brain is fucked");
    freopen(stdin, "r",stdin);
    getchar();
    return 0;
}
