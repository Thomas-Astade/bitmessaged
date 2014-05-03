//~~ uint32_t getVersion() [version] ~~
RETURN(htonl(*((uint32_t*)&(*myPayload)[0])));