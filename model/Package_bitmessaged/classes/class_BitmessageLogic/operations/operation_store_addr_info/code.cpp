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

    VectorsWeCouldOffer = theKnowledge.getObjects();
}
catch (...) //we received a malformated message
{
    disconnect(event);
}