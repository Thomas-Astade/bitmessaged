// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "knowledge.h"


#define WIN32_LEAN_AND_MEAN /* required by xmlrpc-c/server_abyss.hpp */
#include <cassert>
#include <stdexcept>
#include <iostream>
#ifdef _WIN32
# include <windows.h>
#else
# include <unistd.h>
#endif

#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#ifdef _WIN32
#define SLEEP(seconds) SleepEx(seconds * 1000);
#else
#define SLEEP(seconds) sleep(seconds);
#endif

#include "sampleAdd.h"
#include "getV2Objects.h"
#include "getObject.h"
#include "addObject.h"
#include "getV3Objects.h"


static pthread_t thread[4];
static volatile bool keepRunning = true;
static volatile int isRunning = 0;
data::knowledge* database;

void *aThread( void *ptr )
{
    isRunning++;
    while (keepRunning)
    {
        try {
            xmlrpc_c::registry myRegistry;
            myRegistry.addMethod("sample.add", new method::sampleAdd);
            myRegistry.addMethod("v2.getMessages", new method::getV2Objects(database, protocol::message::msg));
            myRegistry.addMethod("v2.getBroadcasts", new method::getV2Objects(database, protocol::message::broadcast));
            myRegistry.addMethod("v2.getPubkeys", new method::getV2Objects(database, protocol::message::pubkey));
            myRegistry.addMethod("v2.addMessage", new method::addObject(database, protocol::message::msg));
            myRegistry.addMethod("v2.addBroadcast", new method::addObject(database, protocol::message::broadcast));
            myRegistry.addMethod("v2.addPubkey", new method::addObject(database, protocol::message::pubkey));
            myRegistry.addMethod("v2.getObject", new method::getObject(database));
            myRegistry.addMethod("v3.getObject", new method::getObject(database));
            myRegistry.addMethod("v3.getMessages", new method::getV3Objects(database, 2));
            myRegistry.addMethod("v3.getBroadcasts", new method::getV3Objects(database, 3));
            myRegistry.addMethod("v3.getPubkeys", new method::getV3Objects(database, 1));
            myRegistry.addMethod("v3.addObject", new method::addObject(database, protocol::message::object));
            xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8081));
            myAbyssServer.run();
            // xmlrpc_c::serverAbyss.run() never returns
            assert(false);
            } catch (std::exception const& e) {
                std::cerr << "Something failed. " << e.what() << std::endl;
            }
        }
    isRunning--;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread[0], NULL, aThread, (void*)0);
    printf("XML plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("XML plugin shut down\n");
}
}