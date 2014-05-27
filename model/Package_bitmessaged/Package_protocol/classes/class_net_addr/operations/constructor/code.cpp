//~~ net_addr(const Payload& data, unsigned int& index) [net_addr] ~~
if (index+38 > data.size())
    throw Malformated();

wPayload aPayload;
aPayload.push_back(&((*data)[index]),38);
myPayload = aPayload;
index += 38;