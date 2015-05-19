#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define lson (pos<<1)
#define rson (pos<<1|1)
#define INF 0x7fffffff
#define N 300010
int n,m,a[N];
int cnt,head[N],next[2*N],to[2*N];
int now,size[N],deep[N],fa[N],son[N],p_id[N],id_p[N],top[N];
int maxt[4*N],sum[4*N];
void add(int x,int y)
{
	to[++cnt]=y;
	next[cnt]=head[x];
	head[x]=cnt;
}
void dfs(int x,int d)
{
	size[x]=1;deep[x]=d;
	for(int y,i=head[x];i;i=next[i])
		if((y=to[i])!=fa[x])
		{
			fa[y]=x;
			dfs(y,d+1);
			if(size[y]>size[son[x]])
				son[x]=y;
			size[x]+=size[y];
		}
}
void create(int x,int d)
{
	p_id[x]=++now;
	id_p[now]=x;
	top[x]=d;
	if(son[x])
		create(son[x],d);
	for(int y,i=head[x];i;i=next[i])
		if((y=to[i])!=fa[x]&&y!=son[x])
			create(y,y);
}
/*BFS
void bfs()
{
	int h=0,r=0;
	q[++r]=1;
	while(r!=h)
	{
		int x=q[++h],y;
		size[x]=1;deep[x]=deep[fa[x]]+1;
		for(int i=head[x];i;i=next[i])
			if((y=to[i])!=fa[x])
				fa[y]=x,q[++r]=y;
	}
	for(int i=n;i;i--)
	{
		int x=q[i];
		size[fa[x]]+=size[x];
		if(size[x]>size[son[fa[x]]])
			son[fa[x]]=x;
	}
	p_id[1]=top[1]=1;
	for(int i=1;i<=n;i++)
	{
		int x=q[i],y;
		int now=p_id[x];
		id_p[now]=x;
		if(son[x])
			top[son[x]]=top[x],
			p_id[son[x]]=now+1,
			now+=size[son[x]];
		for(int j=head[x];j;j=next[j])
			if((y=to[j])!=fa[x]&&y!=son[x])
				top[y]=y,
				p_id[y]=now+1,
				now+=size[y];
	}
}

*/
void build(int pos,int l,int r)
{
	if(l==r){ sum[pos]=maxt[pos]=a[id_p[l]]; return; }
	int mid=(l+r)>>1;
	build(lson,l,mid);
	build(rson,mid+1,r);
	sum[pos]=sum[lson]+sum[rson];
	maxt[pos]=max(maxt[lson],maxt[rson]);
}
void fix(int pos,int l,int r,int x,int y)
{
	if(l==x&&r==x){ sum[pos]=maxt[pos]=y; return; }
	int mid=(l+r)>>1;
	if(x<=mid)
		fix(lson,l,mid,x,y);
	else fix(rson,mid+1,r,x,y);
	sum[pos]=sum[lson]+sum[rson];
	maxt[pos]=max(maxt[lson],maxt[rson]);
}
int query_max(int pos,int l,int r,int x,int y)
{
	if(x<=l&&r<=y) return maxt[pos];
	int mid=(l+r)>>1;
	if(y<=mid)
		return query_max(lson,l,mid,x,y);
	if(x>mid)
		return query_max(rson,mid+1,r,x,y);
	return max(query_max(lson,l,mid,x,y),query_max(rson,mid+1,r,x,y));
}
int query_sum(int pos,int l,int r,int x,int y)
{
	if(x<=l&&r<=y) return sum[pos];
	int mid=(l+r)>>1;
	if(y<=mid)
		return query_sum(lson,l,mid,x,y);
	else if(x>mid)
		return query_sum(rson,mid+1,r,x,y);
	return query_sum(lson,l,mid,x,y)+query_sum(rson,mid+1,r,x,y);
}
int findmax(int x,int y)
{
	int f1=top[x],f2=top[y],re=-INF;
	while(f1!=f2)
	{
		if(deep[f1]<deep[f2])
			swap(x,y),swap(f1,f2);
		re=max(re,query_max(1,1,n,p_id[f1],p_id[x]));
		x=fa[f1];
		f1=top[x];
	}
	if(deep[x]>deep[y])
		swap(x,y);
	return max(re,query_max(1,1,n,p_id[x],p_id[y]));
}
int findsum(int x,int y)
{
	int f1=top[x],f2=top[y],re=0;
	while(f1!=f2)
	{
		if(deep[f1]<deep[f2])
			swap(x,y),swap(f1,f2);
		re+=query_sum(1,1,n,p_id[f1],p_id[x]);
		x=fa[f1];
		f1=top[x];
	}
	if(deep[x]>deep[y])
		swap(x,y);
	return re+query_sum(1,1,n,p_id[x],p_id[y]);
}
int getopt()
{
	char ch[10];
	scanf("%s",ch);
	if(ch[0]=='C') return 1;
	if(ch[1]=='M') return 2;
	return 3;
}
int main()
{
	cin>>n;
	for(int x,y,i=1;i<n;i++)
		scanf("%d%d",&x,&y),
		add(x,y),add(y,x);
	dfs(1,1);
	create(1,1);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	build(1,1,n);
	cin>>m;
	for(int opt,x,y,i=1;i<=m;i++)
	{
		opt=getopt();
		scanf("%d%d",&x,&y);
		if(opt==1)
			fix(1,1,n,p_id[x],y);
		else if(opt==2)
			printf("%d\n",findmax(x,y));
		else
			printf("%d\n",findsum(x,y));
	}
	return 0;
}