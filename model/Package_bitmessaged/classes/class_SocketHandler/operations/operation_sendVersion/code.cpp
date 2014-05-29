//~~ void sendVersion(ACF_Message* event) [SocketHandler] ~~
protocol::version aVersion(theKnowledge.getTime(),
    *(uint32_t*)&sourceAddr.sin_addr,
    (uint16_t)sourceAddr.sin_port,
    *(uint32_t*)&destAddr.sin_addr,
    (uint16_t)destAddr.sin_port
);

protocol::message aMessage(protocol::message::version, aVersion.getPayload());

if (theKnowledge.getDebug())
{
    theKnowledge.dumpLock();
    printf("Message type Version:\n");
    dumpSend();
    aMessage.dump();
    theKnowledge.dumpUnlock();
}

aMessage.writeTo(socketfd);
