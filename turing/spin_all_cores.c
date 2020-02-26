#define _GNU_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>

int main(int argc, char **argv)
{
    get_nprocs_conf();
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    

    pthread_setaffinity_np(0, sizeof(cpus), &cpus);
    
    return 0;
}