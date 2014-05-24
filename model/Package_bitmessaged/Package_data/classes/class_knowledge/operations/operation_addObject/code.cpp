//~~ void addObject(uint64_t NodeID, const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
if (collectedObjects.find(object.getVector()) == collectedObjects.end())
{
    uint64_t oTime = object.getTime();
    uint64_t now = getTime();
    bool oldObject = ((object.getType() == protocol::message::pubkey) && ((oTime + maximumKeyAcceptAge) < now)) ||
                       (((oTime + maximumAcceptAge) < now))
                      ;

    if (!oldObject)
    {
        collectedObjects[object.getVector()] = object;
        std::pair<uint64_t, protocol::inventory_vector> aPair(getTime(), object.getVector());
        receivedTimes.push_back(aPair);
    }
    else
    {
        known_node_list.incOldOfferCount(NodeID,1);
    }
}

sem_post(&mySemaphore);