#include <iostream>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

const int MAXN = 10000000;
const int MAXS = 60 * 1024 * 1024;

int numbers[MAXN];
char buf[MAXS];

void analyse(char *buf, int len = MAXS)
{
    int i;
    numbers[i = 0] = 0;
    for (char *p = buf; *p && p - buf < len; p++)
        if (*p == ' ')
            numbers[++i] = 0;
        else
            numbers[i] = numbers[i] * 10 + *p - '0';
}
///////////////////READ////////////////////
void scanf_read()
{
    freopen("data.in", "r", stdin);
    int *p = numbers, total = MAXN;
    while(total --) scanf("%d", p),p ++;
    fclose(stdin);
}
void cin_read()
{
    freopen("data.in", "r", stdin);
    int *p = numbers, total = MAXN;
    while(total --) cin >> *p ,p ++;
    fclose(stdin);
}
void sy_cin_read()
{
    ios::sync_with_stdio(false);
    freopen("data.in", "r", stdin);
    int *p = numbers, total = MAXN;
    while(total --) cin >> *p ,p ++;
    fclose(stdin);
}
void fread_analyse()
{
    freopen("data.in", "rb", stdin);
    int len = fread(buf, 1, MAXS, stdin);
    buf[len] = '\0';
    analyse(buf, len);
    fclose(stdin);
}
void read_analyse()
{
    int fd = open("data.in", O_RDONLY);
    int len = read(fd, buf, MAXS);
    buf[len] = '\0';
    analyse(buf, len);
    fclose(stdin);
}
int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
void Hand_write_read()
{
	freopen("data.in","r",stdin);
	for(int i = 0 ;i < MAXN; i ++)
		numbers[i] = read();
	fclose(stdin);
}

/*void mmap_analyse()
{
    int fd = open("data.in",O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *mbuf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);
    analyse(mbuf,len);
}*/
////////////////////////////////////////////////
int main()
{
    int start = clock();
    scanf_read();
    printf("scanf >> Time is %.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);


    start = clock();
    cin_read();
    printf("cin >> Time is %.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);


    start = clock();
    sy_cin_read();
    printf("nosy_cin >> Time is %.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);


    start = clock();
    fread_analyse();
    printf("fread_analyse >> Time is %.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);


    start = clock();
    read_analyse();
    printf("read_analyse >> Time is %.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);

    start = clock();
    Hand_write_read();
    printf("Hand_write_read >> Time is %.3lf\n", double(clock() - start) / CLOCKS_PER_SEC);

    getchar();

    fclose(stdout);
    return 0;
}
