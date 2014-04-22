#include <stdio.h>
#include "knowledge.h"

extern "C" {
void init(data::knowledge& data)
{
    printf("debug plugin initialized\n");
}

void shutdown()
{
    printf("debug plugin shut down\n");
}
}