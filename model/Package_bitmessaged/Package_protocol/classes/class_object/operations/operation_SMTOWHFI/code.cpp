//~~ bool extractKeyR(std::string& data) [object] ~~
if (myType != protocol::message::msg)
    RETURN(false);

if (myPayload.size() < 20+17)
    RETURN(false);

uint16_t xLength = myPayload.get_uint16_t(18+17);

if (myPayload.size() < (xLength + 22 + 17))
    RETURN(false);

uint16_t yLength = myPayload.get_uint16_t(20 + 17 + xLength);

if (myPayload.size() < (xLength + yLength + 24 + 17))
    RETURN(false);
    
unsigned int copysize = 4 + xLength + yLength;
char* dataStart = (char*)(&(*myPayload)[18 + 17]);

data += std::string(dataStart, copysize);

RETURN(true);