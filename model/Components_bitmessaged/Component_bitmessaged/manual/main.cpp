#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <set>
#include <string>
#include <map>
#include <getopt.h>
#include "knowledge.h"

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

bool create_outgoing_connection(const char* arg)
{
    return true;
}

std::set<std::string> plugins;
std::map<std::string, void*> plugin_handles;
data::knowledge database;

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

    static struct option long_options[] = {
        {"help"       ,  no_argument,        0,  'h' },
        {"plugin"     ,  optional_argument,  0,  'p' },
        {"initial"    ,  required_argument,  0,  'i' },
        {0,          0,                      0,   0  }
    };

    int long_index =0;
    int opt;

    printf("hallo\n");
    
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
            if (!create_outgoing_connection(optarg))
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
    
    sleep(3);
    
    for (std::set<std::string>::iterator it = plugins.begin(); it != plugins.end(); it++)
    {
        stop_plugin(*it);
    }

    return EXIT_SUCCESS;
}
