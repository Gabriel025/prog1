#define _GNU_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <sys/sysinfo.h>

void spin(int proc)
{
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(proc, &cpus);
    pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpus);

    while(1);
}

int main(int argc, char **argv)
{
    int nprocs = get_nprocs_conf();
    
    pthread_t threads[nprocs];

    for(int i = 0; i < nprocs; i++)
        pthread_create(&threads[i], NULL, spin, &i);
    
    pthread_join(threads[0], NULL);

    return 0;
}