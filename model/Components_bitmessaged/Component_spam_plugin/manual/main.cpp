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

static pthread_t thread1;
static volatile bool keepRunning = true;
static volatile bool isRunning = false;
data::knowledge* database;

void *aThread( void *ptr )
{
    isRunning = true;
    while (keepRunning)
    {
        protocol::wPayload p;
        p.push_back(database->getTime());
        p.push_back(protocol::var_int(1));
        unsigned int len = rand() % 100 + 100;
        for (unsigned int i = 0; i < len; i++)
            p.push_back((unsigned int)rand());
        
        uint8_t initialHash[SHA512_DIGEST_LENGTH];
        uint8_t buffer[8+SHA512_DIGEST_LENGTH];
        
        uint64_t target = p.pow_target();
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
        protocol::object o(protocol::message::msg,p2);
        database->addObject(0,o);
    }
    isRunning = false;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread1, NULL, aThread, 0);
    printf("spam plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("spam plugin shut down\n");
}
}