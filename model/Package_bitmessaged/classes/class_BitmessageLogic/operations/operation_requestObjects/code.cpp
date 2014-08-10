//~~ void requestObjects(ACF_Message* event) [BitmessageLogic] ~~
while (!VectorsToRequest.empty() && !theKnowledge.doWeNeed(*VectorsToRequest.begin()))
    VectorsToRequest.erase(VectorsToRequest.begin());

if (VectorsToRequest.empty())
    return;

protocol::getdata aGet;

if (VectorsToRequest.size() > 250)
{
    std::set<protocol::inventory_vector>::iterator it = VectorsToRequest.begin();
    unsigned int step = (rand() % 200) + 3;
    
    while (step--)
        it++;
        
    if ((!theKnowledge.doWeNeed(*it)) ||
        (VectorsWeRequested.find(*it) != VectorsWeRequested.end())
       )
    {
        VectorsToRequest.erase(it);
        return;
    }
    
    aGet.insert(*it);
    
    VectorsWeRequested.insert(*it);
    VectorsToRequest.erase(it);
}
else
{
    aGet.insert(*VectorsToRequest.begin());

    if (VectorsWeRequested.find(*VectorsToRequest.begin()) != VectorsWeRequested.end())
    {
        VectorsToRequest.erase(VectorsToRequest.begin());
        return;
    }

    VectorsWeRequested.insert(*VectorsToRequest.begin());
    VectorsToRequest.erase(VectorsToRequest.begin());
}

ACF_sendMessage(MessageReceiver(),toSocket,ev_getdata,new protocol::Payload(aGet.getPayload()));