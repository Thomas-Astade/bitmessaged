#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <signal.h>     /* signal, raise, sig_atomic_t */
#include <set>
#include <string>
#include <map>
#include <arpa/inet.h> 
#include <getopt.h>
#include "string.h"
#include "knowledge.h"
#include "ACF.h"
#include "OutSocketHandler.h"
#include "OutConnectionHandler.h"
#include "Trace2UML.h"

volatile bool keepRunning = true;

void my_handler (int param)
{
  keepRunning = false;
}

void print_usage()
{
    printf("\nbitmessaged: a bitmessage daemon Copyright (C) Thomas Spitzer\n");
    printf("Usage: nbitmessaged [-p <plugin>]\n");
    printf("\nOptions:\n");
    printf("--help              Display this information\n");
    printf("-p, --plugin        plugin to load.\n");
    printf("-i, --initial       ip:port of the initial client connection.\n");
    printf("                    (you may have multiple addresses).\n");
}

ACF soketContext;
pthread_t socketThread;
std::set<std::string> plugins;
std::map<std::string, void*> plugin_handles;
static data::knowledge database;

bool create_outgoing_connection(const char* arg)
{
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8444);
    inet_pton(AF_INET, "10.49.69.83", &serv_addr.sin_addr);
    
    OutSocketHandler* aHandler = new OutSocketHandler(&soketContext, serv_addr, database);
    aHandler->Initialize(0);
    return true;
}

void start_plugin(std::string filename)
{
    printf("Loading plugin %s\n",filename.c_str());
    void* handle = dlopen (filename.c_str(), RTLD_LAZY);
    if (dlerror())
    {
        printf("ERROR: cannot find %s\n",filename.c_str());
    }
    else
    {
        plugin_handles[filename] = handle;
        void(* func)(data::knowledge&) = (void(*)(data::knowledge&)) dlsym (handle, "init");
        func(database);
    }
}

void stop_plugin(std::string filename)
{
    if (plugin_handles.find(filename) == plugin_handles.end())
        return;
    printf("sutting down plugin %s\n",filename.c_str());
    void(* func)() = (void(*)()) dlsym (plugin_handles[filename], "shutdown");
    func();
}

int main(int argc, char *argv[]) {

    Trace2UML::ms_ofile.open("Trace2UML.seq");
    static struct option long_options[] = {
        {"help"       ,  no_argument,        0,  'h' },
        {"plugin"     ,  optional_argument,  0,  'p' },
        {"initial"    ,  required_argument,  0,  'i' },
        {0,          0,                      0,   0  }
    };

    int long_index =0;
    int opt;

    while ((opt = getopt_long(argc, argv, "p:i:h", long_options, &long_index )) != -1) {
        switch (opt) {
        case 'p':
                plugins.insert(optarg);
            break;
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;
        case 'i':
            if (!database.addNode(optarg))
            {
                printf("ERROR: -i <addr>:<port> e.g.: -i 127.0.0.1:8444\n");
                exit (EXIT_FAILURE);
            }
            break;
        default:
            break;
        }
    }
    
    for (std::set<std::string>::iterator it = plugins.begin(); it != plugins.end(); it++)
    {
        start_plugin(*it);
    }

    signal (SIGINT, my_handler); // install a signal handler
    
    pthread_create(&socketThread,0,&ACF::staticExec,&soketContext);

    OutConnectionHandler aHandler(&soketContext);
    aHandler.Initialize(0);
    
    while (keepRunning)
    {
        database.incHeartbeat();
        sleep(1);
    }
    
    for (std::set<std::string>::iterator it = plugins.begin(); it != plugins.end(); it++)
    {
        stop_plugin(*it);
    }

    return EXIT_SUCCESS;
}
