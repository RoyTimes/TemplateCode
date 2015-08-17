#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
int n;
struct node
{
	node *ch[2],*fa;
	int v,s,cnt;
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
	bool check()
	{
		return fa->ch[1]==this;
	}
};

node *null=new node();
node *root=null;

inline node *newnode(node *f,int val)
{
	node *re=new node();
	re->cnt=re->s=1;
	re->v=val;
	re->ch[0]=re->ch[1]=null;
	re->fa=f;
	return re;
}

inline void rotate(node *x,int d)
{
	node *k=x->fa;
	k->ch[d^1]=x->ch[d];
	k->ch[d^1]->fa=k;
	x->ch[d]=k;
	x->fa=k->fa;
	k->fa->ch[k->fa->ch[0]==k?0:1]=x;
	k->fa=x;
	k->maintain();
	x->maintain();
	if(root==k) root=x;
}

inline void splay(node *x,node *aim)
{
	while(x->fa!=aim)
	{
		if(x->fa->fa==aim)
			rotate(x,x->check()?0:1);
		else if(!x->fa->check())
			x->check()?rotate(x,0):rotate(x->fa,1),
			rotate(x,1);
		else
			x->check()?rotate(x->fa,0):rotate(x,1),
			rotate(x,0);
		x->maintain();
	}
}

void update(node *o)
{
	o->maintain();
	if(o!=root)
		update(o->fa);
}

inline void insert(int x)
{
	if(root==null)
	{
		root=newnode(null,x);
		return;
	}
	node *k=root;
	while(1)
	{
		int d=k->cmp(x);
		if(d==-1)
		{
			k->cnt++;
			update(k);
			splay(k,null);
			return;
		}
		else if(k->ch[d]!=null)
			k=k->ch[d];
		else
		{
			k->ch[d]=newnode(k,x);
			update(k);
			splay(k->ch[d],null);
			return;
		}
	}
}

void remove(node* &o,int x)
{
	int d=o->cmp(x);
	if(d!=-1)
		remove(o->ch[d],x);
	else
	{
		if(o->cnt>1)
			o->cnt--;
		else
		{
			if(o->ch[0]==null)
				o->ch[1]->fa=o->fa,
				o=o->ch[1];
			else if(o->ch[1]==null)
				o->ch[0]->fa=o->fa,
				o=o->ch[0];
			else
				rotate(o->ch[0],1),
				remove(o->ch[1],x);
		}
	}
	if(o!=null) o->maintain();
}

int rank(node *o,int x)
{
	int re=o->ch[0]->s;
	int d=o->cmp(x);
	if(d==-1)
	{
		splay(o,null);
		return re+1;
	}
	if(!d)
		return rank(o->ch[0],x);
	return re+o->cnt+rank(o->ch[1],x);
}

int kth(node *o,int k)
{
	int l=o->ch[0]->s;
	if(k<=l)
		return kth(o->ch[0],k);
	k-=l;
	if(k<=o->cnt)
	{
		splay(o,null);
		return o->v;
	}
	k-=o->cnt;
	return kth(o->ch[1],k);
}

int pre(node *o,int x)
{
	if(o==null)
		return -INF;
	int d=x>o->v?1:0;
	if(d==0)
		return pre(o->ch[0],x);
	int re=pre(o->ch[1],x);
	if(re==-INF)
	{
		splay(o,null);
		return o->v;
	}
	return re;
}

int suf(node *o,int x)
{
	if(o==null) return INF;
	int d=x>=o->v?1:0;
	if(d==1)
		return suf(o->ch[1],x);
	int re=suf(o->ch[0],x);
	if(re==INF)
	{
		splay(o,null);
		return o->v;
	}
	return re;
}

/*
int pre(node *o,int x)
{
	if(o==null)
		return -INF;
	if(x==o->v)
	{
		splay(o,null);
		return x;
	}
	int d=x>o->v?1:0;
	if(d==0)
		return pre(o->ch[0],x);
	int re=pre(o->ch[1],x);
	if(re==-INF)
	{
		splay(o,null);
		return o->v;
	}
	return re;
}

int suf(node *o,int x)
{
	if(o==null) return INF;
	if(x==o->v)
	{
		splay(o,null);
		return x;
	}
	int d=x>o->v?1:0;
	if(d==1)
		return suf(o->ch[1],x);
	int re=suf(o->ch[0],x);
	if(re==INF)
	{
		splay(o,null);
		return o->v;
	}
	return re;
}
*/

int main()
{
	cin>>n;
	for(int opt,x,i=1;i<=n;i++)
	{
		scanf("%d%d",&opt,&x);
		switch(opt)
		{
			case 1: insert(x);break;
			case 2: remove(root,x);break;
			case 3: printf("%d\n",rank(root,x));break;
			case 4: printf("%d\n",kth(root,x));break;
			case 5: printf("%d\n",pre(root,x));break;
			case 6: printf("%d\n",suf(root,x));break;
		}
	}
	return 0;
}