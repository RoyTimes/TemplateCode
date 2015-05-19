#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <stdlib.h>
#define N 1005
#define INF 100000
using namespace std;
 
int V,S,end,beg;
int dis[N],pre[N],mid[N],cut[N],d[N];
bool used[N];
 
typedef struct _edge_
{
    int weight;
    int to;
}edge;
 
vector<edge>e[N];
queue<int>q;
deque<int>dq;

/*
void Heap_SPFA()//Heap_Dijkstra
{
	memset(d,0x3f,sizeof(d));
	priority_queue<rec> q;
	q.push((rec){1,0}),d[1]=0;
	while(q.size())
	{
		int x,y;
		x=q.top().x,y=q.top().y,q.pop();
		if(d[x]!=y) continue;
		for(int i=head[x];i;i=next[i])
			if(d[ver[i]]>d[x]+edge[i])
			{
				d[ver[i]]=d[x]+edge[i];
				q.push((rec){ver[i],d[ver[i]]});
			}
	}
}*/
/*
bool spfa(const int st) //////////////HDU AC
{
    for(int i = 0 ; i <= V ; i ++)
    {
        if(i == st){dis[i] = 0 ; continue;}
        dis[i] = INF;
    }
    
    q.push(st);
    used[st] = 1;
    cut[st] = 1;
    
    while(!q.empty())
    {
        int temp = q.front();
        for(int i = 0; i <(int)e[temp].size() ; i ++)
        {
            edge *te = &e[temp][i];
            if(dis[temp] + (*te).weight < dis[(*te).to]) 
            {
                    dis[(*te).to] = dis[temp] + (*te).weight;
                    cut[(*te).to] = cut[temp] + 1;
                    if(cut[(*te).to] > V) return 0;
                    if(used[(*te).to] == 0)
                    {
                        q.push((*te).to);
                        used[(*te).to] = 1;
                    }
            }
        }
        q.pop();
        used[temp] = 0;
    }
    return 1;
}*/
/*void dijkstra(const int start)
{
    int temp = 0,flag = 0;
    for(int i = 1 ; i <= V ; i ++) dis[i] = INF;
    for(int i = 1 ; i < (int)e[start].size() ; i ++) dis[e[start][i].to] = e[start][i].weight;
    for(int i = 1 ; i < (int)e[start].size() ; i ++) pre[e[start][i].to] = start;
    for(int i = 1 ; i <= V ; i ++)
    {
        memset(mid,1,sizeof(mid));
        temp = INF + 1;
        for(int j = 1 ; j <= V ; j ++)
        {
            if(!used[j] && temp > dis[j])
            {
                temp = dis[j];
                flag = j;
            }
        }
        used[flag] = 1;
        for(int j = 1 ; j < (int)e[flag].size() ; j ++)
        {
            mid[e[flag][j].to] = e[flag][j].weight;
        }
        for(int j = start + 1 ; j <= V; j ++)
        {
            if(dis[flag] + mid[j] < dis[j])
            {
                dis[j] = dis[flag] + mid[j];
                pre[j] = flag;
            }
             
        }  
    }
}*/
/*void Print_Path()
{
	int shit = n;
    int b[N],num = 0;
    while(shit != 1)
    {
        b[num] = shit;
        shit = pre[shit];
        num++;
    }
    printf("1 ");
    for(int i = num - 1 ; i >= 0 ; i --) printf("%d ",b[i]);
}*             

void Init_Input()
{
//	cout<<"Type int V and S\n";
	cin>>V>>S;
//	cout<<"Type in Start and End\n"
//    cin>>beg>>end;
	for(int i = 1 ; i <= V ; i ++){ edge temp; e[i].push_back(temp);}
	for(int i = 0 ; i < S ; i ++)
    {
	    int x,y,z,shit;
	    scanf("%d%d%d",&x,&y,&z);
	    edge temp1,temp2;
	    temp1.weight = z;
	    temp1.to = y;
	    temp2.weight = z;
	    temp2.to = x;
	    e[x].push_back(temp1);
	    e[y].push_back(temp2);
    }
}*/ 


int main()
{
	//cout<<"Type int V and S\n";
	while(cin>>V>>S && V != 0){
		memset(dis,0,sizeof(dis));
//	cout<<"Type in Start and End\n"
//    cin>>beg>>end;
	for(int i = 1 ; i <= V ; i ++){ edge temp; e[i].push_back(temp);}
	for(int i = 0 ; i < S ; i ++)
    {
	    int x,y,z,shit;
	    scanf("%d%d%d",&x,&y,&z);
	    edge temp1,temp2;
	    temp1.weight = z;
	    temp1.to = y;
	    temp2.weight = z;
	    temp2.to = x;
	    e[x].push_back(temp1);
	    e[y].push_back(temp2);
    }
    //dijkstra(beg);
    spfa(1);
    printf("%d\n",dis[V]);}
    //printf("\nShortest Path Lenth is : %d\n",dis[end]);}
}