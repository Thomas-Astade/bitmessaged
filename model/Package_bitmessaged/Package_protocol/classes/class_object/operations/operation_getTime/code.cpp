//~~ uint64_t getTime() [object] ~~
const uint64_t* val = (const uint64_t*)((*myPayload)+8);
uint64_t t = myPayload.htonll(*val);

if (t > (uint64_t)0x1ffffff)
    t = t >> 32;

return t;