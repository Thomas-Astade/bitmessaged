//~~ void store_addr_info(ACF_Message* event) [BitmessageLogic] ~~
try {
    //~~ void store_addr_info(ACF_Message* event) [BitmessageLogic] ~~
    protocol::Payload* aPayload = (protocol::Payload*)event->Data;
    unsigned int index = 0;
    protocol::addr addrObject(*aPayload, index);

    std::vector<std::string> data = addrObject.getAddresses();

    for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++)
    {
        theKnowledge.addNode(*it);
    }

    VectorsWeCouldOffer = theKnowledge.getObjects(m_Protocol_Version);
    printf("we offer %d objects to a node of version %d\n",VectorsWeCouldOffer.size(),m_Protocol_Version);
}
catch (...) //we received a malformated message
{
    disconnect(event);
}