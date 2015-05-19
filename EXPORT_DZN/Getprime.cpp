int p[100005],tot;
bool flag[100005];
void getprime()
{
	for(int i=2;i<=100000;i++)
	{
		if(!flag[i]) p[++tot]=i;
		for(int j=1;i*p[j]<=100000;j++)
		{
			flag[i*p[j]]=1;
			if(i%p[j]==0) break;
		}
	}
}
