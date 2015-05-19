#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Complex{
    int random,val,cnt,size;
    Complex *son[2];
    Complex(){
        random=rand();
        son[1]=son[2]=NULL;
    }
    inline void Maintain(){
        size=cnt;
        if(son[0]!=NULL)    size+=son[0]->size;
        if(son[1]!=NULL)    size+=son[1]->size;
    }
    inline int Compare(int x){
        if(x==val)  return -1;
        return x>val;
    }
}*root;

inline void Rotate(Complex *&a,int dir);
void Insert(Complex *&a,int x);
void Delete(Complex *&a,int x);
int Find(Complex *a,int x);
int FindK(Complex *a,int k);
int FindPre(Complex *a,int x,int best);
int FindNext(Complex *a,int x,int best);

int main()
{
    int i_case,flag,x;
    for(cin>>i_case;i_case;i_case--){
        scanf("%d%d",&flag,&x);
        switch(flag){
            case 1:
                Insert(root,x);
                break;
            case 2:
                Delete(root,x);
                break;
            case 3:
                printf("%d\n",Find(root,x)+1);
                break;
            case 4:
                printf("%d\n",FindK(root,x));
                break;
            case 5:
                printf("%d\n",FindPre(root,x,0));
                break;
            case 6:
                printf("%d\n",FindNext(root,x,0));
                break;
        }
    }
    return 0;
}

inline void Rotate(Complex *&a,int dir)
{
    Complex *k=a->son[dir^1];
    a->son[dir^1]=k->son[dir];
    k->son[dir]=a;
    a->Maintain(),k->Maintain();
    a=k;
}

void Insert(Complex *&a,int x)
{
    if(a==NULL){
        a=new Complex;
        a->cnt=a->size=1;
        a->val=x;
        return ;
    }
    int dir=a->Compare(x);
    if(dir==-1)
        a->cnt++;
    else{
        Insert(a->son[dir],x);
        if(a->son[dir]->random>a->random)
            Rotate(a,dir^1);
    }
    a->Maintain();
}

void Delete(Complex *&a,int x)
{
    int dir=a->Compare(x);
    if(dir!=-1)
        Delete(a->son[dir],x);
    else{
        if(a->cnt>1)
            a->cnt--;
        else{
            if(a->son[0]==NULL) a=a->son[1];
            else if(a->son[1]==NULL) a=a->son[0];
            else{
                int _dir=(a->son[0]->random > a->son[1]->random)?1:0;
                Rotate(a,_dir);
                Delete(a->son[_dir],x);
            }
        }
    }
    if(a!=NULL)
        a->Maintain();
}

int Find(Complex *a,int x)
{
    int dir=a->Compare(x);
    if(dir==-1)
        return a->son[0]==NULL?0:a->son[0]->size;
    if(!dir)
        return Find(a->son[0],x);
    return (a->son[0]==NULL?0:a->son[0]->size)+a->cnt+Find(a->son[1],x);
}

int FindK(Complex *a,int k)
{
    int t=0;
    if(a->son[0]!=NULL)
        t=a->son[0]->size;
    if(k<=t)
        return FindK(a->son[0],k);
    if(k>t+a->cnt)
        return FindK(a->son[1],k-t-a->cnt);
    return a->val;
}

int FindPre(Complex *a,int x,int best)
{
    if(a==NULL)
        return best;
    if(a->val>=x)
        return FindPre(a->son[0],x,best);
    return FindPre(a->son[1],x,a->val);
}

int FindNext(Complex *a,int x,int best)
{
    if(a==NULL)
        return best;
    if(a->val>x)
        return FindNext(a->son[0],x,a->val);
    return FindNext(a->son[1],x,best);
}