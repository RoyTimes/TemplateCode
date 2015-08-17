inline void read(int &a)
{
    char ch;
    while ((ch = getchar()) < '0' || ch > '9');
    a = ch - '0';
    while ((ch = getchar()) >= '0' && ch <= '9')
        a = (a << 3) + (a << 1) + ch - '0';
}
