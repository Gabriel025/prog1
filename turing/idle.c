#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <sched.h>

int main(int argc, char **argv)
{
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    sched_setaffinity(0, sizeof(cpus), &cpus); //we only want to "run" on core 0

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    
    int sig;
    sigwait(&sigset, &sig); //wait for SIGINT (Ctrl+C)

    return 0;
}