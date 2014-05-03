//~~ uint64_t getServices() [version] ~~
RETURN(htonll(*((uint64_t*)&(*myPayload)[4])));