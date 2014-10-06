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
#include <xmlrpc-c/girerr.hpp>
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

#include "sampleAdd.h"


static pthread_t thread[4];
static volatile bool keepRunning = true;
static volatile int isRunning = 0;
data::knowledge* database;

class getV2ObjectsMethod : public xmlrpc_c::method 
{
    protocol::message::command_t m_Type;
    public:
    getV2ObjectsMethod(protocol::message::command_t aType) : m_Type(aType)
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
            protocol::object anObject = database->getObject(*it);
            if (m_Type == anObject.getType())
            {
                vector<unsigned char> myBytes(32);
                memcpy(&myBytes[0],(*it).getData(),32);
                arrayData.push_back(xmlrpc_c::value_bytestring(myBytes));
            }
        }

        *retvalP = xmlrpc_c::value_array(arrayData);
    }
};

class getV2ObjectMethod : public xmlrpc_c::method 
{
    public:
    getV2ObjectMethod() 
    {
            this->_signature = "A:6";
            this->_help = "This method returns an object, identified by an inventory vector";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) 
    {
    
        std::vector<unsigned char> ivector = paramList.getBytestring(0);
        paramList.verifyEnd(1);
        
        if (ivector.size() != 32)
            throw(girerr::error("a vector has to contain 32 bytes"));
        
        protocol::inventory_vector v(&ivector[0]);
        protocol::object o = database->getObject(v);

        if (!o.isValid())
            throw(girerr::error("ther is no such object"));

        protocol::Payload p(o.getPayload());
      
        vector<unsigned char> myBytes(p.size());
        memcpy(&myBytes[0],*p,p.size());
        
        *retvalP = xmlrpc_c::value_bytestring(myBytes);
    }
};

class addV2ObjectMethod : public xmlrpc_c::method 
{
    protocol::message::command_t m_Type;
    public:
    addV2ObjectMethod(protocol::message::command_t aType) : m_Type(aType)
    {
            this->_signature = "6:6";
            this->_help = "This method adds an object to the network";
    }

    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value * const retvalP) 
    {
    
        std::vector<unsigned char> ivector = paramList.getBytestring(0);
        paramList.verifyEnd(1);
        
        protocol::wPayload p;
        p.push_back(&ivector[0],ivector.size());
        protocol::object o(m_Type,p);
        
        if (!o.PowOk())
            throw(girerr::error("Your POW nonce is not correct"));
            
        if (!o.isActuell())
            throw(girerr::error("the time of the object is not correct"));
        
        database->addObject(0,o);
        
        vector<unsigned char> myBytes(32);
        memcpy(&myBytes[0],o.getVector().getData(),32);
       
        *retvalP = xmlrpc_c::value_bytestring(myBytes);
    }
};

void *aThread( void *ptr )
{
    isRunning++;
    while (keepRunning)
    {
        try {
            xmlrpc_c::registry myRegistry;
            myRegistry.addMethod("sample.add", new methods::sampleAdd);
            myRegistry.addMethod("v2.getMessages", new getV2ObjectsMethod(protocol::message::msg));
            myRegistry.addMethod("v2.getBroadcasts", new getV2ObjectsMethod(protocol::message::broadcast));
            myRegistry.addMethod("v2.getPubkeys", new getV2ObjectsMethod(protocol::message::pubkey));
            myRegistry.addMethod("v2.addMessage", new addV2ObjectMethod(protocol::message::msg));
            myRegistry.addMethod("v2.addBroadcast", new addV2ObjectMethod(protocol::message::broadcast));
            myRegistry.addMethod("v2.addPubkey", new addV2ObjectMethod(protocol::message::pubkey));
            myRegistry.addMethod("v2.getObject", new getV2ObjectMethod);
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