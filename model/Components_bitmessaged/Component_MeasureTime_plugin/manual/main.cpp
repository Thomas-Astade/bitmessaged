// @file

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include "knowledge.h"

static pthread_t thread1;
static volatile bool keepRunning = true;
static volatile bool isRunning = false;
data::knowledge* database;

unsigned int getTimeTick(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000 + time.tv_usec;
}

void *aThread( void *ptr )
{
    isRunning = true;
    while (keepRunning)
    {
        std::string keyData; // here the keydata will go

        int start = getTimeTick();
        unsigned int eCount = 0;
        
        std::set<protocol::inventory_vector> objects = database->getObjects(2);
        std::vector<protocol::inventory_vector> testObjects;
    
        uint64_t limit = database->getTime() - (3600 * 4); //the last four hours
        
        for (std::set<protocol::inventory_vector>::iterator it = objects.begin(); it != objects.end(); it++)
        {
            protocol::object anObject = database->getObject(*it);
            uint64_t t = anObject.getTime();
            if ((t > limit) && (anObject.getType() == protocol::message::msg) && (anObject.getPayload().size() > 64))
            {
                testObjects.push_back(*it);
            }
        }

        int middle = getTimeTick();

        for (std::vector<protocol::inventory_vector>::iterator it = testObjects.begin(); it != testObjects.end(); it++)
        {
            protocol::object anObject = database->getObject(*it);
            if (anObject.extractKeyR(keyData))
                eCount++;
        }
        
        int middle2 = getTimeTick();
        
        for (std::vector<protocol::inventory_vector>::iterator it = testObjects.begin(); it != testObjects.end(); it++)
        {
            protocol::object anObject = database->getObject(*it);
            unsigned char hash[SHA256_DIGEST_LENGTH];
            const char key_m[] = "1234567890123456789012"; // this is just a dummy, because we dont have correct values, now
            protocol::Payload p = anObject.getPayload();
            
            SHA256_CTX context;
            SHA256_Init(&context);
            SHA256_Update(&context, (unsigned char*)key_m, 32);
            SHA256_Update(&context, *p, p.size());
            SHA256_Final(hash, &context);
        }
        
        int stop = getTimeTick();
        
        printf("Searching %d objects and found %d msgs for the last four hours\n",(int)objects.size(),(int)testObjects.size());
        printf("This took %d uSec\n",middle-start);
        printf("%d keys could be extracted, generating %d bytes of key_M data. It took %d uSec\n",eCount, (int)keyData.size(), middle2 - middle);
        printf("checking the key_m of %d messages took %d uSec\n\n",eCount, stop - middle2);

        sleep(10);
    }
    isRunning = false;
    return 0;
}

extern "C" {
void init_plugin(data::knowledge& data)
{
    database = &data;
    pthread_create( &thread1, NULL, aThread, 0);
    printf("Measure plugin initialized\n");
}

void shutdown_plugin()
{
    keepRunning = false;
    while (isRunning)
        ;
    printf("Measure plugin shut down\n");
}
}