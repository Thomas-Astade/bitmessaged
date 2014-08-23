//~~ void sendData(ACF_Message* event) [BitmessageLogic] ~~
try {
    unsigned int index = 0;
    protocol::getdata aGet(*((protocol::Payload*)event->Data),index);
    
    for (std::set<protocol::inventory_vector>::iterator it = aGet.begin(); it != aGet.end(); it++)
    {
        protocol::object anObject = theKnowledge.getObject(*it);
        
        if (anObject.getType() != protocol::message::unknown)
        {
            ACF_sendMessage(MessageReceiver(),toSocket,ev_object,new protocol::object(anObject));
            theKnowledge.incSendCount();
        }
    }
}
catch (...) //we received a malformated message
{
    disconnect(event);
}