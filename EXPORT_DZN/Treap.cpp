#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n;
struct node
{
	node *ch[2];
	int r,v,s,cnt;
	int cmp(int x)
	{
		if(x==v)
			return -1;
		return x>v?1:0;
	}
	void maintain()
	{
		s=ch[0]->s+ch[1]->s+cnt;
	}
};
node *null=new node();
void rotate(node* &o,int d)
{
	node* k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain();
	k->maintain();
	o=k;
}
void insert(node* &o,int x)
{
	if(o==null)
	{
		o=new node();
		o->ch[0]=o->ch[1]=null;
		o->r=rand();
		o->v=x;
		o->cnt=1;
	}
	else
	{
		int d=o->cmp(x);
		if(d==-1)
			o->cnt++;
		else
		{
			insert(o->ch[d],x);
			if(o->ch[d]->r>o->r)
				rotate(o,d^1);
		}
	}
	o->maintain();
}
void remove(node* &o,int x)
{
	int d=o->cmp(x);
	if(d==-1)
	{
		if(o->cnt>1)
			o->cnt--;
		else
		{
			if(o->ch[0]==null)
				o=o->ch[1];
			else if(o->ch[1]==null)
				o=o->ch[0];
			else
			{
				int d2=o->ch[0]->r>o->ch[1]->r?1:0;
				rotate(o,d2);
				remove(o->ch[d2],x);
			}
		}
	}
	else remove(o->ch[d],x);
	if(o!=null) o->maintain();
}
int rank(node* &o,int x)
{
	int re;
	if(o->ch[0]==null) re=0;
	else re=o->ch[0]->s;
	int d=o->cmp(x);
	if(d==-1)
		return re+1;
	else if(d==0)
		return rank(o->ch[0],x);
	else return re+o->cnt+rank(o->ch[1],x);
}
int kth(node* &o,int k)
{
	if(o==null||k<=0||k>o->s) return 0;
	int temp=o->ch[0]->s;
	if(temp+1<=k&&temp+o->cnt>=k) return o->v;
	else if(k<=temp)
		return kth(o->ch[0],k);
	else return kth(o->ch[1],k-temp-o->cnt);
}
int pre(node* &o,int x)
{
	if(o==null) return -INF;
	int d=x>o->v?1:0;
	if(d==0)
		return pre(o->ch[0],x);
	int re=pre(o->ch[1],x);
	if(re==-1)
		return o->v;
	return re;
}
int suf(node* &o,int x)
{
	if(o==null) return INF;
	int d=x>=o->v?1:0;
	if(d==1)
		return suf(o->ch[1],x);
	int re=suf(o->ch[0],x);
	if(re==-1)
		return o->v;
	return re;
}
int main()
{
	cin>>n;
	node *root=null;
	for(int opt,x,i=1;i<=n;i++)
	{
		scanf("%d%d",&opt,&x);
		switch(opt)
		{
			case 1: insert(root,x);break;
			case 2: remove(root,x);break;
			case 3: printf("%d\n",rank(root,x));break;
			case 4: printf("%d\n",kth(root,x));break;
			case 5: printf("%d\n",pre(root,x));break;
			case 6: printf("%d\n",suf(root,x));break;
		}
	}
	return 0;
}