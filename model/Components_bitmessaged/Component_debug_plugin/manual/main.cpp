// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <curses.h>
#include <string.h>
#include "knowledge.h"

static pthread_t thread1;
static volatile bool keepRunning = true;
static volatile bool isRunning = false;
data::knowledge* database;

void *aThread( void *ptr )
{
    isRunning = true;
    initscr();
    while (keepRunning)
    {
        char Buffer[200];
        sprintf(Buffer,"heartbeat %d   ",database->getHeartbeat());
        mvaddnstr(2,2,Buffer,strlen(Buffer));
        sprintf(Buffer,"known nodes: %d   ",database->getNodeCount());
        mvaddnstr(3,2,Buffer,strlen(Buffer));
        sprintf(Buffer,"outgoing connections: %d   ",database->getOutgoingCount());
        mvaddnstr(4,2,Buffer,strlen(Buffer));
        sprintf(Buffer,"successful connections: %d   ",database->getSuccessfulCount());
        mvaddnstr(5,2,Buffer,strlen(Buffer));
        sprintf(Buffer,"unsuccessful connections: %d   ",database->getUnsuccessfulCount());
        mvaddnstr(6,2,Buffer,strlen(Buffer));
        sprintf(Buffer,"received objects: %d   ",database->getObjectCount());
        mvaddnstr(7,2,Buffer,strlen(Buffer));
        refresh();
        usleep(100000);
    }
    endwin();
    isRunning = false;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread1, NULL, aThread, 0);
    printf("debug plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("debug plugin shut down\n");
}
}