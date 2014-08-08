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
        std::set<protocol::inventory_vector> v3Objects = database->getObjects(3);
        std::set<std::string> hashes;
        
        for (std::set<protocol::inventory_vector>::iterator it = v3Objects.begin(); it != v3Objects.end(); it++)
        {
            protocol::object o = database->getObject(*it);
            hashes.insert(o.getContentHash());
        }
    
        std::set<protocol::inventory_vector> v2Objects = database->getObjects(2);
        std::set<protocol::inventory_vector> bridgeObjects;
        
        for (std::set<protocol::inventory_vector>::iterator it = v2Objects.begin(); it != v2Objects.end(); it++)
        {
            protocol::object o = database->getObject(*it);
            
            if ((o.getPayload().size() < 256000) && (hashes.find(o.getContentHash()) == hashes.end()))
                bridgeObjects.insert(*it);
        }
    
        if (!bridgeObjects.empty())
        {
            protocol::object o = database->getObject(*bridgeObjects.begin());
            
            protocol::wPayload p;
            uint64_t time = o.getTime();
            unsigned int nonceTime = (60 * 60 * 60);
 
            switch (o.getType()) {
                case protocol::message::msg:
                    time += nonceTime;
                    p.push_back(time);
                    p.push_back((uint32_t)2);
                break;
                case protocol::message::getpubkey:
                    nonceTime = (28 * 24 * 60 * 60);
                    time += nonceTime;
                    p.push_back(time);
                    p.push_back((uint32_t)0);
                break;
                case protocol::message::pubkey:
                    time += nonceTime;
                    p.push_back(time);
                    p.push_back((uint32_t)1);
                break;
                case protocol::message::broadcast:
                    time += nonceTime;
                    p.push_back(time);
                    p.push_back((uint32_t)3);
                break;
                default:
                break;
            }
            
            p.push_back(o.getPayload());
            
            uint8_t initialHash[SHA512_DIGEST_LENGTH];
            uint8_t buffer[8+SHA512_DIGEST_LENGTH];
            uint64_t s = p.size();
            
            uint64_t target = (uint64_t)(0x8000000000000000) /
                            ((uint64_t)500 * (s+((uint64_t)nonceTime*(s)/65536)));
            
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
            protocol::object o2(protocol::message::object,p2);
            if (!o2.PowOk())
                printf("POW failed\n");
            else
                printf("POW ok\n");
            database->addObject(0,o2);
        }
        else
        {
            sleep(1);
        }
    }
    isRunning--;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread[0], NULL, aThread, 0);
    printf("V1toV3 plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("V1toV3 plugin shut down\n");
}
}