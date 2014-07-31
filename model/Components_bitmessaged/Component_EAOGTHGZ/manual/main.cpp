#include <stdio.h>

int main(int argc, char** argv)
{
    for (unsigned int messagesize = 256; messagesize < 300000; messagesize *= 2)
    {
        printf("%u Bytes,", messagesize);
        for (unsigned int ttl = 1; ttl <= 24*28; ttl *= 2)
        {
            printf("%u, ",ttl);
        }
        printf("\n");
    }
	return 0;
}
