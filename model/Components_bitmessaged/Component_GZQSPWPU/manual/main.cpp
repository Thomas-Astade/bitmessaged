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

static pthread_t thread[4];
static volatile bool keepRunning = true;
static volatile int isRunning = 0;
data::knowledge* database;

void *aThread( void *ptr )
{
    isRunning++;
    while (keepRunning)
    {
        std::set<protocol::inventory_vector> v2Objects = database->getObjects(2);
        std::set<std::string> hashes;
        
        for (std::set<protocol::inventory_vector>::iterator it = v2Objects.begin(); it != v2Objects.end(); it++)
        {
            protocol::object o = database->getObject(*it);
            hashes.insert(o.getContentHash());
        }
    
        std::set<protocol::inventory_vector> v3Objects = database->getObjects(3);
        std::set<protocol::inventory_vector> bridgeObjects;
        
        for (std::set<protocol::inventory_vector>::iterator it = v3Objects.begin(); it != v3Objects.end(); it++)
        {
            protocol::object o = database->getObject(*it);
            
            if ((o.getPayload().size() < (256*1024)) && 
                    (o.getPayload().size() > 20) &&
                    (hashes.find(o.getContentHash()) == hashes.end()))
                bridgeObjects.insert(*it);
        }
    
        if (!bridgeObjects.empty())
        {
            long num = rand() % bridgeObjects.size();
            for (int i = 0; i < num; i++)
            {
                if (!bridgeObjects.empty())
                    bridgeObjects.erase(*bridgeObjects.begin());
            }
            
            if (!bridgeObjects.empty())
            {
                protocol::object o = database->getObject(*bridgeObjects.begin());
                
                protocol::wPayload p;
                uint64_t time = o.getTime();
                uint64_t nonceTime = (60 * 60 * 60);
                protocol::message::command_t theType = protocol::message::unknown;

                switch (o.getObjectType()) {
                    case 2:
                        time -= nonceTime;
                        p.push_back(time);
                        theType = protocol::message::msg;
                    break;
                    case 0:
                        time -= nonceTime;
                        p.push_back(time);
                        theType = protocol::message::getpubkey;
                    break;
                    case 1:
                        nonceTime = (28 * 24 * 60 * 60);
                        time -= nonceTime;
                        p.push_back(time);
                        theType = protocol::message::pubkey;
                    break;
                    case 3:
                        time -= nonceTime;
                        p.push_back(time);
                        theType = protocol::message::broadcast;
                    break;
                    default:
                    break;
                }
                
                const uint8_t* pp = *o.getPayload();
                pp += 20;
                
                for (int i=0; i < (o.getPayload().size()-20); i++)
                    p.push_back(*(pp + i));
                
                uint8_t initialHash[SHA512_DIGEST_LENGTH];
                uint8_t buffer[8+SHA512_DIGEST_LENGTH];
                
                uint64_t target = p.pow_target_V2();
                
                SHA512(*p, p.size(), initialHash);
                memcpy(&buffer[8], initialHash, SHA512_DIGEST_LENGTH);
                
                uint64_t trialValue = (uint64_t)0xffffffffffffffff;
                uint64_t nonce = 0;
                
                uint8_t resultHash1[SHA512_DIGEST_LENGTH];
                uint8_t resultHash2[SHA512_DIGEST_LENGTH];
                
                while (trialValue > target)
                {
                    nonce++;
                    memcpy(buffer, &nonce, 8);
                    SHA512(buffer, SHA512_DIGEST_LENGTH + 8, resultHash1);
                    SHA512(resultHash1, SHA512_DIGEST_LENGTH, resultHash2);
                    memcpy(&trialValue, resultHash2, sizeof(trialValue));
                    trialValue = protocol::Payload::htonll(trialValue);
                }
                
                protocol::wPayload p2;
                p2.push_back(protocol::Payload::htonll(nonce));
                p2.push_back(p);
                protocol::object o2(theType,p2);
                if (o2.PowOk())
                    printf("generated a V2 object\n");
                    
                database->addObject(0,o2);
            }
            else
            {
                sleep(5);
            }
        }
        else
        {
            sleep(3+(rand() % 10));
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
    pthread_create( &thread[0], NULL, aThread, (void*)10);
    pthread_create( &thread[0], NULL, aThread, (void*)20);
    pthread_create( &thread[0], NULL, aThread, (void*)30);
    printf("V3toV2 plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("V3toV2 plugin shut down\n");
}
}