// @file

#include <stdio.h>
#include "knowledge.h"

extern "C" {
void init(data::knowledge& data)
{
    printf("example plugin initialized\n");
}

void shutdown()
{
    printf("example plugin shut down\n");
}

}