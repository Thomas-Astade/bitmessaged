//~~ void addObject(uint64_t NodeID, const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
if (collectedObjects.find(object.getVector()) == collectedObjects.end())
{
    uint64_t oTime = object.getTime();
    uint64_t now = getTime();
    bool oldObject = ((object.getType() == protocol::message::pubkey) && ((oTime + maximumKeyAcceptAge) < now)) ||
                       ((object.getType() != protocol::message::pubkey) && ((oTime + maximumAcceptAge) < now))
                      ;
                      
    bool futureObject = (oTime > now);

    if ((!oldObject) && (!futureObject))
    {
        collectedObjects[object.getVector()] = object;
        ACF_sendMessage(0,toOutConnectionHandler,ev_newObject,new protocol::inventory_vector(object.getVector()));
        ACF_sendMessage(0,toInConnectionHandler,ev_newObject,new protocol::inventory_vector(object.getVector()));
    }
    else
    {
        if (NodeID)
        {
            if (oldObject)
                known_node_list.incOldOfferCount(NodeID,1);
            else
                known_node_list.incFutureOfferCount(NodeID,1);
        }
    }
}

sem_post(&mySemaphore);