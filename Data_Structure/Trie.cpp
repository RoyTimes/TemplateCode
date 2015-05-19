#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#define N 10000
#define CHAR 52
#define DIGIT 12
using namespace std;
char Line[DIGIT], Input1[DIGIT], Input2[DIGIT];

struct  Trie
{
    Trie * Next[30];
    char Character[12];
    Trie(){for(int i = 0 ; i <= 26 ; i ++) Next[i] = NULL;}
    
}root;

void Add(char *Content, char *Key)
{
    Trie *p = &root;
    for(int i = 0 ;Content[i];i++)
    {
        int temp = Content[i] - 'a';
        if(p -> Next[temp] == NULL) p -> Next[temp] = new Trie;
        p = p -> Next[temp];
    }
    strcpy(p -> Character, Key);
}

void Find(char *Input)
{
    Trie *p = &root;
    int Lenth = (unsigned int)strlen(Input);
    for(int i = 0 ; i < Lenth ; i ++)
    {
        if(p -> Next[Input[i] - 'a'] == NULL) return;
        p = p -> Next[Input[i] - 'a'];
    }
  //  if(p -> Character[0] == 0)printf("eh\n");
    printf("\nPFD : %s\n",p -> Character);
}

int main()
{
#ifdef DEBUG
    freopen("data.in","r",stdin);
#endif
    
    char str[30];
    while(gets(str))
    {
        if(str[0] == '\0') break;
        sscanf(str,"%s%s",Input1,Input2);
        Add(Input1,Input2);
    }
    while(scanf("%s",Line) != EOF)
        Find(Line);
}
