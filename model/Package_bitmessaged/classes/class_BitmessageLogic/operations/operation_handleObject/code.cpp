//~~ void handleObject(ACF_Message* event) [BitmessageLogic] ~~
try {
    protocol::object* anObject = (protocol::object*)event->Data;

    theKnowledge.addObject(nodeID,*anObject);
}
catch (...) //we received a malformated message
{
    disconnect(event);
}