// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "knowledge.h"
#include "message.h"
#include "mongoose.h"
#include "wPayload.h"

static pthread_t thread1;
static volatile bool keepRunning = true;
static volatile bool isRunning = false;
data::knowledge* database;
struct mg_server *server;

static void unknown(struct mg_connection *conn) {
    mg_send_header(conn, "Content-Type", "text/html");
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

static void upload(struct mg_connection *conn, protocol::message::command_t c, const char* t) {
    mg_send_header(conn, "Content-Type", "text/html");
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>upload_%s</title>\n",t);
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");

    mg_printf_data(conn,"<h1>upload a %s</h1>\n",t);

    const char *data;
    int data_len;
    char var_name[1000], file_name[1000];
    
    if (mg_parse_multipart(conn->content, conn->content_len,
                     var_name, sizeof(var_name),
                     file_name, sizeof(file_name),
                     &data, &data_len) > 0) {

        mg_printf_data(conn, "You upload a file of size %d to add it as %s object<br>", data_len, t);
        protocol::wPayload p;
        for (int i = 0; i < data_len; i++)
            p.push_back(data[i]);
        
        protocol::object o(c,p);
        
        if (!o.PowOk())
        {
            mg_printf_data(conn, "It is not accepted, because the POW is not correct!<br>");
        } else {
            mg_printf_data(conn, "The POW is correct!<br>");
            uint64_t aTime = o.getTime();
            if (aTime > database->getTime())
                mg_printf_data(conn, "It is not accepted, because the time is in the future!<br>");
            else if (aTime < (database->getTime()-data::knowledge::maximumAcceptAge))
                mg_printf_data(conn, "It is not accepted, because its too old!<br>");
            else {
                mg_printf_data(conn, "It is accepted!<br>");
                database->addObject(0,o);
            }
        }
        
    } else {
        mg_printf_data(conn,"<form action=\"upload_%s\" method=\"post\" enctype=\"multipart/form-data\">\n",t);
            mg_printf_data(conn,"<input type=\"submit\" value=\"upload_%s\">\n",t);
            mg_printf_data(conn,"<input name=\"file\" type=\"file\" size=\"20\">\n");
        mg_printf_data(conn,"</form>\n");
    }

    mg_printf_data(conn,"</body>\n");
    mg_printf_data(conn,"</html>\n");
}

static void overview(struct mg_connection *conn) {
    mg_send_header(conn, "Content-Type", "text/html");
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>overview</title>\n");
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");
    
    mg_printf_data(conn,"<table border=\"1\">\n");
    unsigned int t = database->getHeartbeat();
    mg_printf_data(conn,"<tr><td>uptime</td><td>%d days %d:%02d:%02d hours</td></tr>\n",
        t/(24*60*60),t/(60*60) % (24*60*60),t/(60) % (60*60),t % 60);

    mg_printf_data(conn,"<tr><td>known nodes</td><td>%d</td></tr>\n",database->getNodeCount());
    std::vector<data::node_info> nodes = database->getNodesToProvideToOthers();
    mg_printf_data(conn,"<tr><td>really responding nodes</td><td>%d</td></tr>\n",nodes.size());
    
    mg_printf_data(conn,"<tr><td>outgoing connections</td><td>%d</td></tr>\n",database->getOutgoingCount());
    mg_printf_data(conn,"<tr><td>incomming connections</td><td>%d</td></tr>\n",database->getIncommingCount());
    mg_printf_data(conn,"<tr><td>successful connections</td><td>%d</td></tr>\n",database->getSuccessfulCount());
    mg_printf_data(conn,"<tr><td>unsuccessful connections</td><td>%d</td></tr>\n",database->getUnsuccessfulCount());
    mg_printf_data(conn,"<tr><td>received objects</td><td>%d</td></tr>\n",database->getObjectCount());
    
    
    std::set<protocol::inventory_vector> objects = database->getObjects();
    
    unsigned int messagecount = 0;
    unsigned int broadcastcount = 0;
    unsigned int pubkeycount = 0;
    unsigned int getpubkeycount = 0;
    
    uint64_t memsize = 0;
    
    for (std::set<protocol::inventory_vector>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        protocol::object anObject = database->getObject(*it);
        memsize += anObject.getPayload().size();
        switch (anObject.getType()) {
            case protocol::message::getpubkey: getpubkeycount++;break;
            case protocol::message::pubkey: pubkeycount++;break;
            case protocol::message::msg: messagecount++;break;
            case protocol::message::broadcast: broadcastcount++;break;
            default:break;
        }
    }

    mg_printf_data(conn,"<tr><td>objects to advertise</td><td>%d</td></tr>\n",objects.size());
    mg_printf_data(conn,"<tr><td>received messages</td><td>%d (%d/h)</td></tr>\n",messagecount, messagecount/60);
    mg_printf_data(conn,"<tr><td>received broadcasts</td><td>%d (%d/h)</td></tr>\n",broadcastcount, broadcastcount/60);
    mg_printf_data(conn,"<tr><td>active addresses (pubkeys)</td><td>%d</td></tr>\n",pubkeycount);
    mg_printf_data(conn,"<tr><td>used memory</td><td>%d MByte</td></tr>\n",memsize/(1024*1024));
    mg_printf_data(conn,"<tr><td>sent objects</td><td>%d</td></tr>\n",database->getSentObjectCount());

    mg_printf_data(conn,"</table>\n");

    mg_printf_data(conn,"</body>\n");
    mg_printf_data(conn,"</html>\n");
}

static void nodes(struct mg_connection *conn) {
    mg_send_header(conn, "Content-Type", "text/html");
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>nodes</title>\n");
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");
    
    mg_printf_data(conn,"<table border=\"1\">\n");
    mg_printf_data(conn,"<tr><th></th><th>IP</th><th>port</th><th>stream</th><th>agent name</th></tr>\n",database->getHeartbeat());

    std::vector<data::node_info> nodes = database->getNodesToProvideToOthers();
    
    unsigned int number = 0;
    
    for (std::vector<data::node_info>::iterator it = nodes.begin(); it != nodes.end(); it++)
    {
        mg_printf_data(conn,"<tr><td>%d</td><td>%s</td><td>%d</td><td>%d</td><td>%s</td></tr>\n",
            ++number,
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

static void objects(struct mg_connection *conn, protocol::message::command_t c) {
    mg_send_header(conn, "Content-Type", "text/html");
    mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
    mg_printf_data(conn,"<html>\n");
    mg_printf_data(conn,"<head>\n");
    mg_printf_data(conn,"<title>objects</title>\n");
    mg_printf_data(conn,"</head>\n");
    mg_printf_data(conn,"<body>\n");
    
    mg_printf_data(conn,"<table border=\"1\">\n");
    mg_printf_data(conn,"<tr><th></th><th>vector</th><th>type</th><th>size</th><th>time</th></tr>\n",database->getHeartbeat());

    std::set<protocol::inventory_vector> objects = database->getObjects();
    
    unsigned int number = 0;
    
    for (std::set<protocol::inventory_vector>::iterator it = objects.begin(); it != objects.end(); it++)
    {
        protocol::object anObject = database->getObject(*it);
        if ((c == protocol::message::unknown) || (c == anObject.getType()))
        mg_printf_data(conn,"<tr><td>%d</td><td><a href=\"/object/%s\">%s</a></td><td>%s</td><td>%d</td><td>%lld</td></tr>\n",
            ++number,
            anObject.getVectorStr().c_str(),
            anObject.getVectorStr().c_str(),
            anObject.getTypeStr().c_str(),
            anObject.getSize(),
            anObject.getTime()
        );
    }
    
    mg_printf_data(conn,"</table>\n");

    mg_printf_data(conn,"</body>\n");
    mg_printf_data(conn,"</html>\n");
}

static void object(struct mg_connection *conn) {
    protocol::inventory_vector v(std::string(conn->uri).substr(8));
    protocol::object o = database->getObject(v);
    
    if (o.isValid())
    {
        mg_send_header(conn, "Content-Type", "application/octet-stream");
        protocol::Payload p(o.getPayload());
        mg_printf(conn,"Content-Length: %zu\r\n\r\n", p.size());
        mg_write(conn, *p, p.size());
        mg_write(conn, "\r\n", 2);
    }
    else
    {
        mg_send_header(conn, "Content-Type", "text/html");
        mg_printf_data(conn,"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n");
        mg_printf_data(conn,"<html>\n");
        mg_printf_data(conn,"<head>\n");
        mg_printf_data(conn,"<title>NOT FOUND</title>\n");
        mg_printf_data(conn,"</head>\n");
        mg_printf_data(conn,"<body>\n");
        mg_printf_data(conn, "ERROR: a object with vector [%s] is not known", v.getAsStr().c_str());
        mg_printf_data(conn,"</body>\n");
        mg_printf_data(conn,"</html>\n");
    }
}

static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
    int result = MG_FALSE;

    if ((ev == MG_REQUEST) && (strcmp("/overview", conn->uri) == 0)) {
        overview(conn);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/upload_msg", conn->uri) == 0)) {
        upload(conn, protocol::message::msg, "msg");
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/nodes", conn->uri) == 0)) {
        nodes(conn);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/objects", conn->uri) == 0)) {
        objects(conn, protocol::message::unknown);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/msgs", conn->uri) == 0)) {
        objects(conn, protocol::message::msg);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/getpubkeys", conn->uri) == 0)) {
        objects(conn, protocol::message::getpubkey);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/pubkeys", conn->uri) == 0)) {
        objects(conn, protocol::message::pubkey);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (strcmp("/broadcasts", conn->uri) == 0)) {
        objects(conn, protocol::message::broadcast);
        result = MG_TRUE;
    } else if ((ev == MG_REQUEST) && (memcmp("/object/", conn->uri, 8) == 0)) {
        object(conn);
        result = MG_TRUE;
    } else if (ev == MG_REQUEST) {
        unknown(conn);
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