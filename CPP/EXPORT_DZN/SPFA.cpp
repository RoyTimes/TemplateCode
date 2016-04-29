priority_queue<pair<int,int> > q;
void add(int x,int y,int z)
{
	val[++cnt]=z;
	to[cnt]=y;
	next[cnt]=head[x];
	head[x]=cnt;
}
void spfa(int s)
{
	memset(d,0x3f,sizeof d);
	q.push(make_pair(0,s));d[s]=0;
	while(!q.empty())
	{
		int x=q.top().second,y=-q.top().first;
		q.pop();
		if(y!=d[x]) continue;
		y=0;
		for(int i=head[x];i;i=next[i])
		{
			if(d[y=to[i]]>d[x]+val[i])
			{
				d[y]=d[x]+val[i];
				q.push(make_pair(-d[y],y));
			}
		}
	}
}
