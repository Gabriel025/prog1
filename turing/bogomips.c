#include <stdio.h>
#include <time.h>

/*
A sizeof(int) saját olvasatom szerint nem ad pontos választ a szóhosszra,
többek között az én gépemen sem ad helyes választ.
Egy jobb megoldás a pointerek méretének vizsgálata, mivel sok esetben
a címek hossza megegyezik a gépi szó méretével.
(Még ez a megoldás sem teljesen pontos)
*/

void spin(unsigned long long iter)
{
    for(; iter > 0; iter--);
}

int main(int argc, char **argv)
{
    unsigned long long loops_per_sec = 1;
    unsigned long long mcsecs;

    while(loops_per_sec <<= 1)
    {
        mcsecs = clock();
        spin(loops_per_sec);
        mcsecs = clock() - mcsecs;

        if (mcsecs >= 1000000)
        {
            loops_per_sec = loops_per_sec / mcsecs * 1000000;

            printf("ok - %llu.%02llu BogoMIPS\n", loops_per_sec / 500000,
                (loops_per_sec / 5000) % 100); //redo this line

            return 0;
        }
    }

    printf("failed\n");
    return -1;
}
