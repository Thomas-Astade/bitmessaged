//~~ void sendObject(ACF_Message* event) [SocketHandler] ~~

protocol::object* anObject = (protocol::object*)event->Data;

protocol::message aMessage(anObject->getType(), anObject->getPayload());

if (theKnowledge.getDebug())
{
    theKnowledge.dumpLock();
    printf("Message type \"object\":\n");
    dumpSend();
    aMessage.dump();
    theKnowledge.dumpUnlock();
}

myMessageQueue.push_back(aMessage);
