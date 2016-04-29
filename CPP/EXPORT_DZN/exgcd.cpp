int x,y;
int exgcd(int a,int b)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	int re=exgcd(b,a%b);
	int tmp=x;
	x=y;
	y=tmp-a/b*y;
	return re;
}