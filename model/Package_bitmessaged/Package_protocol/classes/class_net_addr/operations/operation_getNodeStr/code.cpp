//~~ std::string getNodeStr() [net_addr] ~~
char buffer[100];

sprintf(buffer, "%d.%d.%d.%d:%d",
    (*myPayload)[32],
    (*myPayload)[33],
    (*myPayload)[34],
    (*myPayload)[35],
    htons(*((uint16_t*)&((*myPayload)[36]))));

RETURN(std::string(buffer));