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

class sampleAddMethod : public xmlrpc_c::method {
    public:
    sampleAddMethod() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "i:ii";
        // method's result and two arguments are integers
        this->_help = "This method adds two integers together";
        }
        void
        execute(xmlrpc_c::paramList const& paramList,
        xmlrpc_c::value * const retvalP) {
        int const addend(paramList.getInt(0));
        int const adder(paramList.getInt(1));
        paramList.verifyEnd(2);
        *retvalP = xmlrpc_c::value_int(addend + adder);
        // Sometimes, make it look hard (so client can see what it's like
        // to do an RPC that takes a while).
        if (adder == 1)
        SLEEP(2);
    }
};

void *aThread( void *ptr )
{
    isRunning++;
    while (keepRunning)
    {
        try {
            xmlrpc_c::registry myRegistry;
            xmlrpc_c::methodPtr const sampleAddMethodP(new sampleAddMethod);
            myRegistry.addMethod("sample.add", sampleAddMethodP);
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