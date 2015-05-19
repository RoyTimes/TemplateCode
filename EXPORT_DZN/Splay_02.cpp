#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 500010
int n,m;
int a[N];
struct node
{
	node *ch[2],*fa;
	int v,s,rev,same,sum,lmax,rmax,tmax;
	inline void pushdown()
	{
		if(rev)
			ch[0]->reverse(),
			ch[1]->reverse();
		if(same)
		{
			if(ch[0]->s)
				ch[0]->clear(v);
			if(ch[1]->s)
				ch[1]->clear(v);
		}
		rev=same=0;
	}
	inline void maintain()
	{
		pushdown();
		s=ch[0]->s+ch[1]->s+1;
		sum=ch[0]->sum+ch[1]->sum+v;
		lmax=max(ch[0]->lmax,ch[0]->sum+v+max(ch[1]->lmax,0));
		rmax=max(ch[1]->rmax,ch[1]->sum+v+max(ch[0]->rmax,0));
		tmax=max(max(ch[0]->tmax,ch[1]->tmax),max(ch[0]->rmax,0)+v+max(ch[1]->lmax,0));
	}
	inline bool check()
	{
		return fa->ch[1]==this;
	}
	inline void combine(node *a,int d)
	{
		ch[d]=a;
		a->fa=this;
	}
	inline void reverse()
	{
		rev^=1;
		swap(lmax,rmax);
		swap(ch[0],ch[1]);
	}
	inline void clear(int x)
	{
		same=1;
		v=x;sum=s*x;
		lmax=rmax=tmax=x>0?x*s:x;
	}
};
node *null=new node();
node *root=null;
inline node *newnode(node *f,int val)
{
	node *re=new node();
	re->s=1;
	re->lmax=re->rmax=re->tmax=re->v=val;
	re->rev=re->same=0;
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
node *build(int l,int r)
{
	if(l>r) return null;
	int mid=(l+r)>>1;
	node *re=newnode(re,a[mid]);
	re->combine(build(l,mid-1),0);
	re->combine(build(mid+1,r),1);
	re->maintain();
	return re;
}
void del(node *x)
{
	if(x->ch[0]!=null)
		del(x->ch[0]);
	if(x->ch[1]!=null)
		del(x->ch[1]);
	delete x;
}
node *kth(node *x,int k)
{
	x->pushdown();
	if(k<=x->ch[0]->s)
		return kth(x->ch[0],k);
	k-=x->ch[0]->s;
	if(k==1) return x;
	return kth(x->ch[1],k-1);
}
inline int read()
{
	char ch;int f=1,re=0;
	for(ch=getchar();(ch<'0'||ch>'9')&&ch!='-';ch=getchar());
	if(ch=='-')f=-1,re=0; else re=ch-'0';
	for(ch=getchar();ch>='0'&&ch<='9';ch=getchar())
	re=(re<<3)+(re<<1)+ch-'0';
	return re*f;
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		a[i]=read();
	root=build(0,n+1);
	root->fa=null;
	null->tmax=-1010;
	for(int i=1;i<=m;i++)
	{
		char str[20];
		int x,y,z;
		scanf("%s",str);
		if(str[2]=='S')		//INSERT
		{
			scanf("%d%d",&x,&y);
			for(int i=1;i<=y;i++)
				a[i]=read();
			splay(kth(root,x+1),null);
			splay(kth(root,x+2),root);
			root->ch[1]->combine(build(1,y),0);
			root->ch[1]->maintain();
			root->maintain();
		}
		else if(str[2]=='L')//DELETE
		{
			scanf("%d%d",&x,&y);
			splay(kth(root,x),null);
			splay(kth(root,x+y+1),root);
			del(root->ch[1]->ch[0]);
			root->ch[1]->ch[0]=null;
			root->ch[1]->maintain();
			root->maintain();
		}
		else if(str[2]=='K')//MAKE-SAME
		{
			scanf("%d%d%d",&x,&y,&z);
			splay(kth(root,x),null);
			splay(kth(root,x+y+1),root);
			root->ch[1]->ch[0]->clear(z);
			root->ch[1]->maintain();
			root->maintain();
		}
		else if(str[2]=='V')//REVERSE
		{
			scanf("%d%d",&x,&y);
			splay(kth(root,x),null);
			splay(kth(root,x+y+1),root);
			root->ch[1]->ch[0]->reverse();
			root->ch[1]->maintain();
			root->maintain();
		}
		else if(str[2]=='T')//GET-SUM
		{
			scanf("%d%d",&x,&y);
			splay(kth(root,x),null);
			splay(kth(root,x+y+1),root);
			printf("%d\n",root->ch[1]->ch[0]->sum);
		}
		else				//MAX-SUM
		{
			splay(kth(root,1),null);
			splay(kth(root,root->s),root);
			printf("%d\n",root->ch[1]->ch[0]->tmax);
		}
	}
}