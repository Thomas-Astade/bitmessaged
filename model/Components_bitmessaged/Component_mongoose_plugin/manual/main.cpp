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

static void unknown(struct mg_connection *conn) {
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>ERROR</title>\n");
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");
    mg_printf_data(conn, "ERROR: not such file: [%s]", conn->uri);
    mg_printf_data(conn,"</body>\n");
    mg_printf_data(conn,"</html>\n");
}

static void overview(struct mg_connection *conn) {
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>overview</title>\n");
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");
    
    mg_printf_data(conn,"<table border=\"1\">\n");
    mg_printf_data(conn,"<tr><td>heartbeat</td><td>%d</td></tr>\n",database->getHeartbeat());
    mg_printf_data(conn,"<tr><td>known nodes</td><td>%d</td></tr>\n",database->getNodeCount());
    mg_printf_data(conn,"<tr><td>outgoing connections</td><td>%d</td></tr>\n",database->getOutgoingCount());
    mg_printf_data(conn,"<tr><td>incomming connections</td><td>%d</td></tr>\n",database->getIncommingCount());
    mg_printf_data(conn,"<tr><td>successful connections</td><td>%d</td></tr>\n",database->getSuccessfulCount());
    mg_printf_data(conn,"<tr><td>unsuccessful connections</td><td>%d</td></tr>\n",database->getUnsuccessfulCount());
    mg_printf_data(conn,"<tr><td>received objects</td><td>%d</td></tr>\n",database->getObjectCount());
    mg_printf_data(conn,"<tr><td>sent objects</td><td>%d</td></tr>\n",database->getSentObjectCount());
    mg_printf_data(conn,"</table>\n");

    mg_printf_data(conn,"</body>\n");
    mg_printf_data(conn,"</html>\n");
}

static void nodes(struct mg_connection *conn) {
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>nodes</title>\n");
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");
    
    mg_printf_data(conn,"<table border=\"1\">\n");
    mg_printf_data(conn,"<tr><th>IP</th><th>port</th><th>stream</th><th>agent name</th></tr>\n",database->getHeartbeat());

    std::vector<data::node_info> nodes = database->getNodesToProvideToOthers();
    
    for (std::vector<data::node_info>::iterator it = nodes.begin(); it != nodes.end(); it++)
    {
        mg_printf_data(conn,"<tr><td>%s</td><td>%d</td><td>%d</td><td>%s</td></tr>\n",
            (*it).getIPasString().c_str(),
            (*it).getPort(),
            (*it).getStreamNo(),
            (*it).getAgent().c_str()
        );
    }
    
    mg_printf_data(conn,"</table>\n");

    mg_printf_data(conn,"</body>\n");
    mg_printf_data(conn,"</html>\n");
}


static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    int result = MG_FALSE;

    if ((ev == MG_REQUEST) && (strcmp("/bitmessaged/oveview", conn->uri) == 0)) {
        overview(conn);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/bitmessaged/nodes", conn->uri) == 0)) {
        nodes(conn);
        result = MG_TRUE;
    }
    else if (ev == MG_REQUEST) {
        unknown(conn);
        result = MG_TRUE;
    }
    else if (ev == MG_REQUEST) {
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