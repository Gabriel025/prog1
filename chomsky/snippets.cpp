#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include<stdlib.h>
int f(int, int);
int f(int);
int f(int*);


int main(int argc, char **argv)
{
    __sighandler_t jelkezelo;

    if(signal(SIGINT, jelkezelo)==SIG_IGN)
        signal(SIGINT, SIG_IGN);
    /*
    Ha a SIGINT jelet ezelőtt figyelmen kívül hagytuk, ezután is ignorájuk,
    ha pedig volt jelkezelő megadva hozzá, azt lecseréljük a jelkezelo függvényre
    */

    if(signal(SIGINT, SIG_IGN)!=SIG_IGN)
        signal(SIGINT, jelkezelo);
    //Ugyanaz, mint az előző. A signal(...) függvény a megadott szignál
    //előző jelkezelő függvényével tér vissza (függvénypointer).

    int i;

    for(i=0; i<5; ++i)
        ;
    //Szokásos for ciklus, ötször fut le, i első értéke 0, utolsó értéke 4.

    for(i=0; i<5; i++)
        ;
    //Ugyanaz, mint az előző. A preincrement/postincrement között ezesetben nincs különbség,
    //mivel az i++ és ++i kifejezéseknek egyedül az értéke különbözik.
    //(Mely értékkel ezesetben nem kezdünk semmit)

    /*
    Szemléltetésképp, a fenti for ciklus a következő kóddal egyenértékű:
    */
    i=0;
loop_begin:
    if(!(i<5)) goto loop_end;

    {/*ciklusmag*/}

    i++;
    goto loop_begin;
loop_end:





    int tomb[5];

    for(i=0; i<5; tomb[i] = i++);



    int n, *d, *s;

    for(i=0; i<n && (*d++ = *s++); ++i); //= helyett == kellene; így is lefordítható, de nincs sok haszna



    int a;

    printf("%d %d", f(a, ++a), f(++a, a));

    printf("%d %d", f(a), a);

    printf("%d %d", f(&a), a);

    return 0;
}