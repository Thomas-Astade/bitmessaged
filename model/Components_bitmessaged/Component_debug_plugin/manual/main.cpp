#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "knowledge.h"

static pthread_t thread1;
static volatile bool keepRunning = true;
static volatile bool isRunning = false;

void *aThread( void *ptr )
{
    isRunning = true;
    while (keepRunning)
    {
        printf("hallo\n");
        usleep(100000);
    }
    isRunning = false;
    return 0;
}

extern "C" {
void init(data::knowledge& data)
{
    pthread_create( &thread1, NULL, aThread, 0);
    printf("debug plugin initialized\n");
}

void shutdown()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("debug plugin shut down\n");
}
}