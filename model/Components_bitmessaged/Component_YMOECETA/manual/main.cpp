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
#include "thread.h"

void print_usage()
{
    printf("\ngenPOW: utility to generate the POW for the bitmessage network\n");
    printf("Usage: genPOW -t 3456 -h ABCDEFGHIJKLNM\n");
    printf("\nOptions:\n");
    printf("--help                   Display this information\n");
    printf("-t, --target             the target value for the POW.\n");
    printf("-i, --hash               the initial hash of the massage in hex.\n");
    printf("-c, --cpu                the number of threads we shall use (default=4).\n");
}

int main(int argc, char** argv)
{
    static struct option long_options[] = {
        {"help"       ,  no_argument,        0,  'h' },
        {"target"     ,  required_argument,  0,  't' },
        {"hash"       ,  required_argument,  0,  'i' },
        {"cpu"        ,  optional_argument,  0,  'c' },
        {0,          0,                      0,   0  }
    };

    int long_index =0;
    int opt;
    char* initial_hash_str = 0;
    uint64_t target_val = 0;
    char initial_hash[SHA512_DIGEST_LENGTH];
    unsigned int cpu = 4;
    
    while ((opt = getopt_long(argc, argv, "c:t:i:h", long_options, &long_index )) != -1) {
        switch (opt) {
        case 't':
                target_val = strtoull(optarg,0,10);
            break;
        case 'c':
                cpu = strtoull(optarg,0,10);
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
    

    for (unsigned int i = 0; i < cpu; i++)
        new genPOW::thread(i,cpu,target_val,initial_hash);
    
    while (1)
        sleep(50);
    
    return EXIT_SUCCESS;
}
