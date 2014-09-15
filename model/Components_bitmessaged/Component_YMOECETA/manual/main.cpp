#include <cinttypes>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <string>

void print_usage()
{
    printf("\ngenPOW: utility to generate the POW for the bitmessage network\n");
    printf("Usage: genPOW -t 3456 -h ABCDEFGHIJKLNM\n");
    printf("\nOptions:\n");
    printf("--help                   Display this information\n");
    printf("-t, --target             the target value for the POW.\n");
    printf("-i, --hash               the initial hash of the massage in hex.\n");
}

uint64_t htonll(uint64_t value)
{
    uint64_t h;
    char* i = (char*)&value;
    char* o = (char*)&h;
    
    o[0] = i[7];
    o[1] = i[6];
    o[2] = i[5];
    o[3] = i[4];
    o[4] = i[3];
    o[5] = i[2];
    o[6] = i[1];
    o[7] = i[0];
    
    return h;
}

uint64_t doMHash(uint64_t target, char* initialHash)
{
    uint8_t buffer[8+SHA512_DIGEST_LENGTH];
    
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
    return nonce;
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
    char* initial_hash_str = 0;
    uint64_t target_val = 0;
    char initial_hash[SHA512_DIGEST_LENGTH];
    
    while ((opt = getopt_long(argc, argv, "t:i:h", long_options, &long_index )) != -1) {
        switch (opt) {
        case 't':
                target_val = strtoull(optarg,0,10);
            break;
        case 'i':
                initial_hash_str = optarg;
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
    
    if (target_val == 0)
    {
        printf("ERROR: you must specify a target value.\n");
        exit (EXIT_FAILURE);
    }

    if (initial_hash_str == 0)
    {
        printf("ERROR: you must specify a hash string.\n");
        exit (EXIT_FAILURE);
    }

    if (strlen(initial_hash_str) != SHA512_DIGEST_LENGTH*2)
    {
        printf("ERROR: the initial hash string must have %d digits.\n",SHA512_DIGEST_LENGTH*2);
        exit (EXIT_FAILURE);
    }
    
    char *pos = initial_hash_str;

    while( *pos )
    {
        if( !((pos-initial_hash_str)&1) )
        {
            unsigned int i;
            sscanf(pos,"%02x",&i);
            initial_hash[(pos- initial_hash_str)>>1] = i;
        }
        ++pos;
    }
    

    printf("%" PRIu64 "\n",doMHash(target_val, initial_hash));
    
    return EXIT_SUCCESS;
}
