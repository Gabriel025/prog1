#define _GNU_SOURCE
#include <unistd.h>
#include <sched.h>
#include <sys/sysinfo.h>

int main(int argc, char **argv)
{
    get_nprocs_conf();
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    sched_setaffinity(0, sizeof(cpus), &cpus); //we only want to run on core 0

    while(1);

    return 0;
}