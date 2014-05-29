//~~ void sendInv(ACF_Message* event) [SocketHandler] ~~
protocol::Payload* aPayload = (protocol::Payload*)event->Data;
protocol::message aMessage(protocol::message::inv, *aPayload);

if (theKnowledge.getDebug())
{
    theKnowledge.dumpLock();
    printf("Message type inv:\n");
    dumpSend();
    aMessage.dump();
    theKnowledge.dumpUnlock();
}

aMessage.writeTo(socketfd);
