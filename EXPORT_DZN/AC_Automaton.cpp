#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 1000010
int t,n;
char str[N];
struct trie
{
	trie *ch[26],*fail;
	int cnt;
};
trie *root;
queue<trie*> q;
trie *newtrie()
{
	trie *re=new trie();
	memset(re->ch,0,sizeof(re->ch));
	re->fail=NULL;
	re->cnt=0;
	return re;
}
void insert(trie *root,char str[])
{
	trie *p=root;
	int now=0;
	while(str[now])
	{
		if(p->ch[str[now]-'a']==NULL)
			p->ch[str[now]-'a']=newtrie();
		p=p->ch[str[now++]-'a'];
	}
	p->cnt++;
}
void build_AC_Automaton(trie *root)
{
	for(int i=0;i<26;i++)
		if(root->ch[i]!=NULL)
			root->ch[i]->fail=root,
			q.push(root->ch[i]);
	while(!q.empty())
	{
		trie *now=q.front();q.pop();
		for(int i=0;i<26;i++)
			if(now->ch[i]!=NULL)
			{
				trie *p=now->fail;
				while(p!=root&&p->ch[i]==NULL)
					p=p->fail;
				if(p->ch[i]!=NULL)
					p=p->ch[i];
				now->ch[i]->fail=p;
				q.push(now->ch[i]);
			}
	}
}
int query(trie *root,char str[])
{
	int now=-1,re=0;
	trie *p=root;
	while(str[++now])
	{
		while(p->ch[str[now]-'a']==NULL&&p!=root)
			p=p->fail;
		if(p->ch[str[now]-'a']!=NULL)
			p=p->ch[str[now]-'a'];
		trie *temp=p;
		while(temp!=root&&temp->cnt!=-1)
		{
			re+=temp->cnt;
			temp->cnt=-1;
			temp=temp->fail;
		}
	}
	return re;
}
int main()
{
	cin>>t;
	while(t--)
	{
		root=newtrie();
		scanf("%d\n",&n);
		for(int i=1;i<=n;i++)
		{
			gets(str);
			insert(root,str);
		}
		build_AC_Automaton(root);
		gets(str);
		printf("%d\n",query(root,str));
	}
	return 0;
}
