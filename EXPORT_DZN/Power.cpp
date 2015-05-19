int power(int a, int b, int c)
{
    int re = 1;
    a = a % c;
    while (b)
    {
        if (b & 1)
            re = (re * a) % c;
        b >>= 1;
        a = (a * a) % c;
    }
    return re;
}
