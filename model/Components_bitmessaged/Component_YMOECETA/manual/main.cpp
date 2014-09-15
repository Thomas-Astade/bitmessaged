#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <getopt.h>


void print_usage()
{
    printf("\ngenPOW: utility to generate the POW for the bitmessage network\n");
    printf("Usage: genPOW -t 3456 -h ABCDEFGHIJKLNM\n");
    printf("\nOptions:\n");
    printf("--help                   Display this information\n");
    printf("-t, --target             the target value for the POW.\n");
    printf("-i, --hash               the initial hash of the massage in hex.\n");
}

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
    static struct option long_options[] = {
        {"help"       ,  no_argument,        0,  'h' },
        {"target"     ,  required_argument,  0,  't' },
        {"hash"       ,  required_argument,  0,  'i' },
        {0,          0,                      0,   0  }
    };

    int long_index =0;
    int opt;

    while ((opt = getopt_long(argc, argv, "t:i:h", long_options, &long_index )) != -1) {
        switch (opt) {
        case 't':
            break;
        case 'i':
            break;
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;
        default:
            print_usage();
            exit (EXIT_FAILURE);
            break;
        }
    }

    return EXIT_SUCCESS;
}
