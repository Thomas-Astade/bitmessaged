//~~ void sendData(ACF_Message* event) [BitmessageLogic] ~~
try {
    unsigned int index = 0;
    protocol::getdata aGet(*((protocol::Payload*)event->Data),index);
    
    if (m_Protocol_Version == 3)
        printf("Some objects Requested\n");

    for (std::set<protocol::inventory_vector>::iterator it = aGet.begin(); it != aGet.end(); it++)
    {
        protocol::object anObject = theKnowledge.getObject(*it);
        
        if (anObject.getType() != protocol::message::unknown)
        {
            if (m_Protocol_Version == 3)
                printf("Send object\n");
            ACF_sendMessage(MessageReceiver(),toSocket,ev_object,new protocol::object(anObject));
            theKnowledge.incSendCount();
        }
    }
}
catch (...) //we received a malformated message
{
    disconnect(event);
}