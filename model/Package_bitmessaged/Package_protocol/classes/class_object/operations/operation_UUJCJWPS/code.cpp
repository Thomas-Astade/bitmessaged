//~~ unsigned int getObjectType() [object] ~~
const uint32_t* val = (const uint32_t*)((*myPayload)+16);
return myPayload.htonll(*val);