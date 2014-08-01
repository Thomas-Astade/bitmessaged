#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

uint64_t htonll(uint64_t value)
{
    uint32_t high_part = htonl((uint32_t)(value >> 32));
    uint32_t low_part = htonl((uint32_t)(value & 0xFFFFFFFFLL));
    return (((uint64_t)low_part) << 32) | high_part;
}

unsigned int getTimeTick(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000 + time.tv_usec;
}

void doPow(uint64_t target)
{
    uint8_t initialHash[SHA512_DIGEST_LENGTH];
    uint8_t buffer[8+SHA512_DIGEST_LENGTH];
    
    for (unsigned int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        initialHash[i] = rand();

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
        trialValue = htonll(trialValue);
    }

 }

int main(int argc, char** argv)
{
    unsigned int messagesize = 1024 * 5;
    unsigned int ttl = 60;
    unsigned int repeats = 10;

    unsigned int seconds = 0;
    for (unsigned int i = 0; i < repeats; i++)
    {
        unsigned int start = getTimeTick();
        uint64_t target = (uint64_t)(0x8000000000000000) /
                        ((uint64_t)160 * ((uint64_t)140000 + messagesize+((uint64_t)3600*ttl*messagesize/65535)));
        doPow(target);
        unsigned int stop = getTimeTick();
        seconds += (stop-start)/1000000;
    }
    printf("Doing POW for %u messages at size %u takes %u seconds (average %u) with 1 CPU\n",
        repeats,messagesize,seconds,seconds/repeats);
    return 0;
}
