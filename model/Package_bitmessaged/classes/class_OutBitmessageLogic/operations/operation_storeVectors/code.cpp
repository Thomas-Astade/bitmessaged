//~~ void storeVectors(ACF_Message* event) [OutBitmessageLogic] ~~
unsigned int index = 0;
protocol::inv aInv(*((protocol::Payload*)event->Data),index);
theKnowledge.incNodeDuplicateOfferCount(nodeID,aInv.duplicate());

for (std::set<protocol::inventory_vector>::iterator it = aInv.begin();
        it != aInv.end(); it++)
{
    if (offeredVectors.find(*it) == offeredVectors.end())
    {
        offeredVectors.insert(*it);
        if (theKnowledge.doWeNeed(*it))
            VectorsToRequest.insert(*it);
        theKnowledge.incNodeOfferCount(nodeID,1);
    }
    else
        theKnowledge.incNodeDuplicateOfferCount(nodeID,1);
}