// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>
#include "knowledge.h"
#include "wPayload.h"
#include "var_int.h"


#define WIN32_LEAN_AND_MEAN /* required by xmlrpc-c/server_abyss.hpp */
#include <cassert>
#include <stdexcept>
#include <iostream>
#ifdef _WIN32
# include <windows.h>
#else
# include <unistd.h>
#endif
using namespace std;
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#ifdef _WIN32
#define SLEEP(seconds) SleepEx(seconds * 1000);
#else
#define SLEEP(seconds) sleep(seconds);
#endif


static pthread_t thread[4];
static volatile bool keepRunning = true;
static volatile int isRunning = 0;
data::knowledge* database;

class sampleAddMethod : public xmlrpc_c::method
{
    public:
    sampleAddMethod() 
    {
        this->_signature = "i:ii";
        this->_help = "This method adds two integers together";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) 
    {
        int const addend(paramList.getInt(0));
        int const adder(paramList.getInt(1));
        paramList.verifyEnd(2);
        *retvalP = xmlrpc_c::value_int(addend + adder);
    }
};

class getV2ObjectsMethod : public xmlrpc_c::method 
{
    public:
    getV2ObjectsMethod() 
    {
            this->_signature = "A:";
            this->_help = "This method returns the inventory vectors of all current version2 objects";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) 
    {
        vector<xmlrpc_c::value> arrayData;

        std::set<protocol::inventory_vector> objects = database->getObjects(2);

        for (std::set<protocol::inventory_vector>::iterator it = objects.begin(); it != objects.end(); it++)
        {
            vector<unsigned char> myBytes(32);
            memcpy(&myBytes[0],(*it).getData(),32);
            arrayData.push_back(xmlrpc_c::value_bytestring(myBytes));
        }

        *retvalP = xmlrpc_c::value_array(arrayData);
    }
};

void *aThread( void *ptr )
{
    isRunning++;
    while (keepRunning)
    {
        try {
            xmlrpc_c::registry myRegistry;
            myRegistry.addMethod("sample.add", new sampleAddMethod);
            myRegistry.addMethod("v2.getObjects", new getV2ObjectsMethod);
            xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8081));
            myAbyssServer.run();
            // xmlrpc_c::serverAbyss.run() never returns
            assert(false);
            } catch (exception const& e) {
                cerr << "Something failed. " << e.what() << endl;
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