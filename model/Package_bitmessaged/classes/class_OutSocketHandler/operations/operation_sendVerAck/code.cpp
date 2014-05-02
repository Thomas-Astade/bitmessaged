//~~ void sendVerAck(ACF_Message* event) [OutSocketHandler] ~~
protocol::message aMessage(protocol::message::verack,protocol::Payload());


if (theKnowledge.getDebug())
{
    theKnowledge.dumpLock();
    printf("Message type Verack:\n");
    dumpSend();
    aMessage.dump();
    theKnowledge.dumpUnlock();
}

aMessage.writeTo(socketfd);
