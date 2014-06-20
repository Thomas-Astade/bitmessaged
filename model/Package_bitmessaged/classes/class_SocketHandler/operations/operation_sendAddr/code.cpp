//~~ void sendAddr(ACF_Message* event) [SocketHandler] ~~
protocol::Payload* aPayload = (protocol::Payload*)event->Data;
protocol::message aMessage(protocol::message::addr, *aPayload);

if (theKnowledge.getDebug())
{
    theKnowledge.dumpLock();
    printf("Message type Addr:\n");
    dumpSend();
    aMessage.dump();
    theKnowledge.dumpUnlock();
}

myMessageQueue.push_back(aMessage);
