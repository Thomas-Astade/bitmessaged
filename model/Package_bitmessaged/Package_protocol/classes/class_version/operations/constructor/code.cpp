//~~ version(uint64_t timestamp, uint32_t sourceIP, uint16_t sourcePort, uint32_t destIP, uint16_t destPort) [version] ~~
myPayload.push_back(current_version);
myPayload.push_back(current_service);
myPayload.push_back(timestamp);

//addr receive
myPayload.push_back((uint64_t)0);
for (unsigned int i = 0; i < 10; i++)
    myPayload.push_back((uint8_t)0);
for (unsigned int i = 0; i < 2; i++)
    myPayload.push_back((uint8_t)0xff);
myPayload.push_back(destIP);
myPayload.push_back(destPort);

//addr from
myPayload.push_back(current_service);
for (unsigned int i = 0; i < 10; i++)
    myPayload.push_back((uint8_t)0);
for (unsigned int i = 0; i < 2; i++)
    myPayload.push_back((uint8_t)0xff);
myPayload.push_back(sourceIP);
myPayload.push_back(sourcePort);

myPayload.push_back(myOwnNonce);
myPayload.push_back(user_agent.getPayload());
myPayload.push_back(current_streams.getPayload());