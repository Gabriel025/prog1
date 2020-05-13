#include <stdio.h>
#include <time.h>

void spin(unsigned long long iter)
{
    for(; iter > 0; iter--);
}

int main(int argc, char **argv)
{
    printf("sizeof(void*) = %zu .. * 8 = %u bits\n\n", sizeof(void*), (unsigned)sizeof(void*) * 8);

    printf("*** Ténylegesen pontos BOGOMips értékekhez keresd fel a /proc/cpuinfo-t! ***\n");

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
            
            printf("BOGOMips: %llu\n", loops_per_sec / 100000);

            return 0;
        }
    }

    printf("failed\n");
    return -1;
}
