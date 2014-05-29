//~~ void storeVectors(ACF_Message* event) [BitmessageLogic] ~~
unsigned int index = 0;
protocol::inv aInv(*((protocol::Payload*)event->Data),index);

if (nodeID)
    theKnowledge.incNodeDuplicateOfferCount(nodeID,aInv.duplicate());

for (std::set<protocol::inventory_vector>::iterator it = aInv.begin();
        it != aInv.end(); it++)
{
    if (VectorsWeGotOffered.find(*it) == VectorsWeGotOffered.end())
    {
        VectorsWeGotOffered.insert(*it);
        if (theKnowledge.doWeNeed(*it))
            VectorsToRequest.insert(*it);
        if (nodeID)
            theKnowledge.incNodeOfferCount(nodeID,1);
    }
    else if (nodeID)
        theKnowledge.incNodeDuplicateOfferCount(nodeID,1);
}
