#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#define N 20010
using namespace std;
  
vector<int>e[N];
stack<int>st;
bool v[N],inz[N];
int f[N];
int deep[N],low[N],belong[N],out[N];
int tot = 0,dep = 0;
  
void tarjan(int i)
{
    st.push(i); inz[i] = 1; v[i] = 1;
    low[i] = deep[i] = ++dep;
    for(int j = 0 ; j < (int)e[i].size() ; j++)
    {
        int temp = e[i][j];
        if(v[temp] == 0) tarjan(temp),low[i] = min(low[i],low[temp]);
        else if(inz[temp] == 1) low[i] = min(low[i],deep[temp]);
    }
    if(low[i] == deep[i])
    {
        int to = 0;
        while(1)
        {
            int temp = st.top(); st.pop();inz[temp] = 0;
            belong[temp] = tot;
            to++;
            if(temp == i) break;
        }
        f[tot] = to;
        tot++;
    }
}
int main()
{
    int n,m; cin>>n>>m;
    for(int i = 1 ; i <= m; i ++)
    {
        int x,y; scanf("%d%d",&x,&y);
        e[x].push_back(y);
    }
    for(int i = 1 ; i <= n ; i ++)
    if(!v[i]) tarjan(i);
    for(int i = 1 ; i  <= n ; i ++)
    {
        for(int j = 0 ; j < (int)e[i].size() ; j++)
        {
            int temp = e[i][j];
            if(belong[temp] != belong[i]) out[belong[i]]++;
        }
    }
    int cut = 0,ans;
   for(int i = 0 ; i < tot ; i ++) if(out[i] == 0) cut++,ans = f[i];
  if(cut == 1)cout<<ans;
    else cout<<0;
     
    return 0;
}