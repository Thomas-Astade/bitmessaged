#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "knowledge.h"

void print_usage()
{
    printf("\nbitmessaged: a bitmessage daemon Copyright (C) Thomas Spitzer\n");
    printf("Usage: nbitmessaged [-p <plugin>]\n");
    printf("\nOptions:\n");
    printf("--help              Display this information\n");
    printf("-p, --plugin        plugin to load.\n");
    printf("-i, --initial       ip:port of the initial client connection.\n");
    printf("                    (you may have multiple addresses).\n");
}

bool create_outgoing_connection(const char* arg)
{
    return true;
}

int main(int argc, char *argv[]) {

    data::knowledge database;

    static struct option long_options[] = {
        {"help"       ,  no_argument,        0,  'h' },
        {"plugin"     ,  optional_argument,  0,  'p' },
        {"initial"    ,  required_argument,  0,  'i' },
        {0,          0,                      0,   0  }
    };

    int long_index =0;
    int opt;

    while ((opt = getopt_long(argc, argv, "p:i:", long_options, &long_index )) != -1) {
        switch (opt) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;
        case 'i':
            if (!create_outgoing_connection(optarg))
            {
                printf("ERROR: -i <addr>:<port> e.g.: -i 127.0.0.1:8444\n");
                exit (EXIT_FAILURE);
            }
            break;
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}
