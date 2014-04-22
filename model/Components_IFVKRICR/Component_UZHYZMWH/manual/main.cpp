#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_usage()
{
    printf("\nbitmessaged: a bitmessage daemon Copyright (C) Thomas Spitzer\n");
    printf("Usage: nbitmessaged [-p <plugin>]\n");
    printf("\nOptions:\n");
    printf("--help              Display this information\n");
    printf("-p, --plugin        plugin to load.\n");
}

int main(int argc, char *argv[]) {

    static struct option long_options[] = {
        {"help"       ,  no_argument,        0,  'h' },
        {"plugin"     ,  optional_argument,  0,  'p' },
        {0,          0,                      0,   0  }
    };

    int long_index =0;
    int opt;

    while ((opt = getopt_long(argc, argv, "p:", long_options, &long_index )) != -1) {
        switch (opt) {
        case 'h':
            print_usage();
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}
