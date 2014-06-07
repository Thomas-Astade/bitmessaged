// @file

#include "fcgi_stdio.h" /* fcgi library; put it first*/

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

int count;

void initialize(void)
{
  count=0;
}

void *aThread( void *ptr )
{
  while (FCGI_Accept() >= 0)   {
    printf("Content-type: text/html\r\n"
           "\r\n"
           "<title>FastCGI Hello! (C, fcgi_stdio library)</title>"
           "<h1>FastCGI Hello! (C, fcgi_stdio library)</h1>"
           "Request number %d running on host <i>%s</i>\n",
            ++count, getenv("SERVER_HOSTNAME"));
  }
  return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread1, NULL, aThread, 0);
    printf("fcgi plugin initialized\n");
}

void shutdown_plugin()
{
    printf("fcgi plugin shut down\n");
}
}