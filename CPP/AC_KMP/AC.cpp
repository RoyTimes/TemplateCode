#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 10010;
char Patten[N], src[N * 100];

struct Trie
{
    int cut;
    Trie *NextNode[30], * Fail;
    Trie()
    {
        memset(NextNode, NULL, sizeof NextNode);
        Fail = NULL;
        cut = 0;
    }
} *root;
void insert(char *in)
{
    Trie *location = root;
    int lenth = strlen(in);
    for (int i = 0 ; i < lenth ; i ++)
    {
        if (location -> NextNode[in[i] - 'a'] == NULL)
            location -> NextNode[in[i] - 'a'] = new Trie;
        location = location -> NextNode[in[i] - 'a'];
    }
    location -> cut ++;
}
Trie * GetFail(Trie * location, int k)
{
    if(location -> NextNode[k] != NULL)
        return location -> NextNode[k];
    else if(location == root) return root;
    else return GetFail(location -> Fail, k);
}
void Build_AC_automation()
{
    Trie * location = new Trie;
    queue <Trie *> q; q.push(root);
    while(!q.empty())
    {
        location = q.front(); q.pop();
        for(int j = 0 ; j < 26 ; j ++)
            if(location -> NextNode[j] != NULL){
                q.push(location -> NextNode[j]);
                if(location == root)
                    location -> NextNode[j] -> Fail = root;
                else location -> NextNode[j] -> Fail = GetFail(location -> Fail, j);
            }
    }
}
int Ask(char * src)
{
    int len = strlen(src), sum = 0;
    Trie * temp, * location = root;
    for(int j = 0 ; j < len ; j ++)
    {
        while(location -> NextNode[src[j] - 'a'] == NULL && location != root)
            location = location -> Fail;
        if(location -> NextNode[src[j] - 'a'] == NULL)
            location = root;
        else location = location -> NextNode[src[j] - 'a'];
        temp = location;
        while(temp != root){
            sum += temp -> cut;
            temp -> cut = 0;
            temp = temp -> Fail;
        }
    }
    return sum;
}
int main()
{
#ifdef DEBUG
    freopen("data.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);

    int cas; cin >> cas;
    root = new Trie;
    for (int i = 1; i <= cas ; i ++)
        cin >> Patten, insert(Patten);

    Build_AC_automation();
    cin >> src;
    cout << Ask(src) << endl;
}
