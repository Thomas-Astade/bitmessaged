//~~ version(const Payload& data, unsigned int index) [version] ~~
wPayload aPayload;
aPayload.push_back(&(*data)[index], data.size() - index);
myPayload = aPayload;