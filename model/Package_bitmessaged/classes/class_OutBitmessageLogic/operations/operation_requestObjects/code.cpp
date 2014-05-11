//~~ void requestObjects(ACF_Message* event) [OutBitmessageLogic] ~~
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
        
    aGet.insert(*it);
    
    if (!theKnowledge.doWeNeed(*it))
    {
        VectorsToRequest.erase(*it);
        ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_request,0);
        return;
    }
}
else
    aGet.insert(*VectorsToRequest.begin());

ACF_sendMessage(MessageReceiver(),toSocket,ev_getdata,new protocol::Payload(aGet.getPayload()));