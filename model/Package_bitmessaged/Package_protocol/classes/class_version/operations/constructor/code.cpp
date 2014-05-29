//~~ version(uint64_t timestamp, uint32_t sourceIP, uint16_t sourcePort, uint32_t destIP, uint16_t destPort) [version] ~~
wPayload aPayload;

aPayload.push_back(current_version);
aPayload.push_back(current_service);
aPayload.push_back(timestamp);

//addr receive
aPayload.push_back((uint64_t)0);
for (unsigned int i = 0; i < 10; i++)
    aPayload.push_back((uint8_t)0);
for (unsigned int i = 0; i < 2; i++)
    aPayload.push_back((uint8_t)0xff);
aPayload.push_back(destIP);
aPayload.push_back(destPort);

//addr from
aPayload.push_back(current_service);
for (unsigned int i = 0; i < 10; i++)
    aPayload.push_back((uint8_t)0);
for (unsigned int i = 0; i < 2; i++)
    aPayload.push_back((uint8_t)0xff);
aPayload.push_back((uint32_t)0);
aPayload.push_back(listenPort);

aPayload.push_back(myOwnNonce);
aPayload.push_back(user_agent.getPayload());
aPayload.push_back(current_streams.getPayload());

myPayload = aPayload;