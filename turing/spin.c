#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h> //Linux-specifikus fejléc, ütemezéssel kapcsolatos hívásokat tartalmaz
#include <sys/sysinfo.h>

int main(int argc, char **argv)
{
    get_nprocs_conf();
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    sched_setaffinity(0, sizeof(cpus), &cpus); //Csak a 0-ás számú magon akarunk futni

    while(1);

    return 0;
}