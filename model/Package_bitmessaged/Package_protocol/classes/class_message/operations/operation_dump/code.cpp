//~~ void dump() [message] ~~
Payload aPayload;

aPayload.push_back(&comand_defines[myType],sizeof(comand_defines[myType]));

uint32_t len = htonl(myPayload.size());
aPayload.push_back(&len,sizeof(len));
uint32_t checksum = myPayload.getChecksum();
aPayload.push_back(&checksum,sizeof(checksum));
aPayload.push_back(&(*myPayload)[0],myPayload.size());

aPayload.dump();