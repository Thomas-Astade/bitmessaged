//~~ void sendVersion(ACF_Message* event) [OutSocketHandler] ~~
protocol::version aVersion(theKnowledge.getTime(),
    *(uint32_t*)&sourceAddr.sin_addr,
    (uint16_t)sourceAddr.sin_port,
    *(uint32_t*)&destAddr.sin_addr,
    (uint16_t)destAddr.sin_port
);

protocol::message aMessage(aVersion);

if (theKnowledge.getDebug())
{
    printf("Message type Version:\n");
    dumpSend();
    aMessage.dump();
}

aMessage.writeTo(socketfd);
