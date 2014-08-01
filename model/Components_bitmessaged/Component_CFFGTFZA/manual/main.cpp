#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

unsigned int getTimeTick(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000000 + time.tv_usec;
}

void doMHash()
{
    uint8_t initialHash[SHA512_DIGEST_LENGTH];
    uint8_t buffer[8+SHA512_DIGEST_LENGTH];
    
    for (unsigned int i = 0; i < SHA512_DIGEST_LENGTH; i++)
        initialHash[i] = rand();

    memcpy(&buffer[8], initialHash, SHA512_DIGEST_LENGTH);
    
    uint64_t nonce = 0;
    uint8_t resultHash1[SHA512_DIGEST_LENGTH];
    uint8_t resultHash2[SHA512_DIGEST_LENGTH];
    
    for (int i = 0; i < 1000000; i++)
    {
        nonce++;
        memcpy(buffer, &nonce, 8);
        SHA512(buffer, SHA512_DIGEST_LENGTH + 8, resultHash1);
        SHA512(resultHash1, SHA512_DIGEST_LENGTH, resultHash2);
    }

 }

int main(int argc, char** argv)
{
    unsigned int start = getTimeTick();
    doMHash();
    unsigned int stop = getTimeTick();
    unsigned int t = stop - start;
    printf("need %d uSec for 1 million Hashes, which is %lld (double)hashes per second\n",t,1000000000000/t);
    return 0;
}
