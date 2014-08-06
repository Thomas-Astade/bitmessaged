//~~ void addObject(uint64_t NodeID, const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
if (collectedObjects.find(object.getVector()) == collectedObjects.end())
{
    if (object.isActuell())
    {
        collectedObjects[object.getVector()] = object;
        ACF_sendMessage(0,toOutConnectionHandler,ev_newObject,new protocol::inventory_vector(object.getVector()));
        ACF_sendMessage(0,toInConnectionHandler,ev_newObject,new protocol::inventory_vector(object.getVector()));
    }
    else
    {
        if (NodeID)
        {
            known_node_list.incOldOfferCount(NodeID,1);
        }
    }
}

sem_post(&mySemaphore);