//~~ uint64_t getTime() [object] ~~
const uint64_t* val = (const uint64_t*)((*myPayload)+8);
return myPayload.htonll(*val);