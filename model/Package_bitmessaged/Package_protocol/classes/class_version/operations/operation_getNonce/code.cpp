//~~ uint64_t getNonce() [version] ~~
if (myPayload.size() < 80)
    throw Malformated();

RETURN(htonll(*((uint64_t*)&(*myPayload)[72])));