//~~ uint64_t calcNonce() [version] ~~
srand (time(NULL));

uint64_t ret = 0;

for (int i = 0; i < 20; i++)
    ret = (ret << 4) + rand();
    
return ret;