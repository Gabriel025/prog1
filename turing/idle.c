#define _GNU_SOURCE
#include <signal.h>

int main(int argc, char **argv)
{
    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    
    int sig;
    sigwait(&sigset, &sig); //Várjuk a SIGINT jelre (Ctrl+C)

    return 0;
}