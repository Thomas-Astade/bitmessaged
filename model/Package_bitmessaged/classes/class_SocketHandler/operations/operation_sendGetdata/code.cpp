//~~ void sendGetdata(ACF_Message* event) [SocketHandler] ~~
protocol::Payload* aPayload = (protocol::Payload*)event->Data;
protocol::message aMessage(protocol::message::getdata, *aPayload);

if (theKnowledge.getDebug())
{
    theKnowledge.dumpLock();
    printf("Message type getdata:\n");
    dumpSend();
    aMessage.dump();
    theKnowledge.dumpUnlock();
}

myMessageQueue.push_back(aMessage);
