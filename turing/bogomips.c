#include <stdio.h>
#include <time.h>

/*
A szóhossz, mint fogalom, alapvetően a jelen hardver
"adatbuszának" a méretére utal (data bus - rémes dolog magyarul informatikáról beszélni).
Ezt szoftveren keresztül nem triviális lekérdezni, bár rendszerinformációkon át
el lehet hozzá jutni, de közvetlenül nem igazán van mód rá.
Átfogalmazva a problémát, a gépi szó hossza megfelel annak az adatmennyiségnek,
mellyel a processzor alapvetően egyszerre dolgozni tud (kerüljük ki a Single Instruction Multiple Data kérdéskörét),
ami célszerűen egybeesik a regiszterek méretével egy adott architektúrán.
Ezt még mindg nem deríthető ki egyszerűen, legalábbis nem magas szintű prog. nyelveken írt kóddal.
...

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
    printf("sizeof(void*) = %zu .. * 8 = %u bits\n\n", sizeof(void*), (unsigned)sizeof(void*) * 8);

    printf("*** For actually accurate BOGOMips values, have a look at /proc/cpuinfo ***\n"); //just saying

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

            //printf("BOGOMips: %llu.%02llu\n", loops_per_sec / 500000,
            //    (loops_per_sec / 5000) % 100); //redo this line
            
            printf("BOGOMips: %llu\n", loops_per_sec / 100000);

            return 0;
        }
    }

    printf("failed\n");
    return -1;
}
