#include <stdio.h>
#include <dos.h>
#include <string.h>

int fi[24] = {523, 554, 578, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1046, 1109,
              1175, 1245, 1318, 1397, 1480, 1568, 1661, 1760, 1865, 1976};
int offs[7] = {0, 2, 4, 5, 7, 9, 11};

void space (int a)
{
     int i;
     for (i = 0; i < a; i++) printf(" ");
     return;
}

int stdh, stdt, allo;
int process (int height, int eight, double time)
{
    int rs, u;
    if (height == 0)
    {
       space(24);
       printf("DELAY %g\n", time);
       sleep((int)(time * stdt));
       return 0;
    }
    else
    {
        if (height < 0)
        {
           height = -height;
           u = 1;
        }
        else u = 0;
        rs = fi[offs[height - 1] + stdh + u];
        if (allo == 1) rs *= 2;
        if (eight == 1) rs *= 2;
        if (eight == 2) rs *= 4;
        if (allo == -1) rs /= 2;
        if (eight == -2) rs /= 4;
        if (eight == -1) rs /= 2;
        space(offs[height - 1] + stdh + u + 12 * (eight + allo) + 18);
        printf("VOICE %d %d %g %dHz\n", height, eight, time, rs);
        beep(rs, (int)(time * stdt));
        return 1;
    }
}

FILE *fin;

int main ()
{
    int height, eight, tstdh, tstdt, tallo, ln = 1, ul, ull; double time; char filename[255];
    printf("Please contract your melody file: ");
    gets(filename);
    fin = fopen(filename, "r");
    if (fin == NULL) printf("Cannot find your file or other error occured.\n");
    else
    {
        system("cls");
        fscanf(fin, "%d %d", &stdh, &stdt);
        if (stdh < 0)
        {
           stdh += 12;
           allo = -1;
        }
        else if (stdh >= 12)
        {
             stdh -= 12;
             allo = 1;
        } else allo = 0;
        tstdh = stdh, tstdt = stdt, tallo = allo;
        while (1)
        {
              fscanf(fin, "%d %d %lf", &height, &eight, &time);
              if (height == -100)
              {
                 stdh = tstdh, stdt = tstdt, allo = tallo;
                 rewind(fin); fscanf(fin, "%d %d", &ul, &ull); ln = 1;
                 system("cls");
              }
              else if (height == -101)
              {
                   stdh = eight, stdt = time;
                   if (stdh < 0)
                   {
                      stdh += 12;
                      allo = -1;
                   }
                   else if (stdh >= 12)
                   {
                        stdh -= 12;
                        allo = 1;
                   } else allo = 0;
              }
              else process(height, eight, time);
        }
    }
    system("pause");
    return 0;
}
