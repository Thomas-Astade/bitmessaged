// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "knowledge.h"
#include "mongoose.h"

static pthread_t thread1;
static volatile bool keepRunning = true;
static volatile bool isRunning = false;
data::knowledge* database;
struct mg_server *server;

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  int result = MG_FALSE;

  if (ev == MG_REQUEST) {
    mg_printf_data(conn,"heartbeat %d   \n",database->getHeartbeat());
    mg_printf_data(conn,"known nodes: %d   \n",database->getNodeCount());
    mg_printf_data(conn,"outgoing connections: %d   \n",database->getOutgoingCount());
    mg_printf_data(conn,"incomming connections: %d   \n",database->getIncommingCount());
    mg_printf_data(conn,"successful connections: %d   \n",database->getSuccessfulCount());
    mg_printf_data(conn,"unsuccessful connections: %d   \n",database->getUnsuccessfulCount());
    mg_printf_data(conn,"received objects: %d   \n",database->getObjectCount());
    mg_printf_data(conn,"sent objects: %d   \n",database->getSentObjectCount());
    result = MG_TRUE;
  } else if (ev == MG_AUTH) {
    result = MG_TRUE;
  }

  return result;
}

void *aThread( void *ptr )
{
    isRunning = true;
    while (keepRunning)
    {
        mg_poll_server(server, 1000);
    }
    isRunning = false;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    // Create and configure the server
    server = mg_create_server(NULL, ev_handler);
    mg_set_option(server, "listening_port", "8080");
    
    pthread_create( &thread1, NULL, aThread, 0);
    
    printf("mongoose plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
        
    // Cleanup, and free server instance
    mg_destroy_server(&server);
    
    printf("mongoose plugin shut down\n");
}
}