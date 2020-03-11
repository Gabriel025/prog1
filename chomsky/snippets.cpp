#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int f(int, int);
int f(int);
int f(int*);


int main(int argc, char **argv)
{
    __sighandler_t jelkezelo;

    if(signal(SIGINT, jelkezelo)==SIG_IGN)
        signal(SIGINT, SIG_IGN);

    if(signal(SIGINT, SIG_IGN)!=SIG_IGN)
        signal(SIGINT, jelkezelo);

    int i;

    for(i=0; i<5; ++i);

    for(i=0; i<5; i++);

    int tomb[5];

    for(i=0; i<5; tomb[i] = i++);

    int n, *d, *s;

    for(i=0; i<n && (*d++ = *s++); ++i);

    int a;

    printf("%d %d", f(a, ++a), f(++a, a));

    printf("%d %d", f(a), a);

    printf("%d %d", f(&a), a);

    return 0;
}