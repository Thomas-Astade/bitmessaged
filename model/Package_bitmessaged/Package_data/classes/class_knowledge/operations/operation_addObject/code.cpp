//~~ void addObject(uint64_t NodeID, const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

if (
        (
            (object.getType() != protocol::message::object) && 
            (collectedObjectsV2.find(object.getVector()) == collectedObjectsV2.end())
        ) ||
        (
            (object.getType() == protocol::message::object) && 
            (collectedObjectsV3.find(object.getVector()) == collectedObjectsV3.end())
        )
    )
{
    if (object.isActuell())
    {
        
        if (object.getType() == protocol::message::object)
            collectedObjectsV3[object.getVector()] = object;
        else
            collectedObjectsV2[object.getVector()] = object;
            
        printf("Accepted a new object\n");
        ACF_sendMessage(0,toOutConnectionHandler,ev_newObject,new protocol::inventory_vector(object.getVector()));
        ACF_sendMessage(0,toInConnectionHandler,ev_newObject,new protocol::inventory_vector(object.getVector()));
    }
    else
    {
        printf("Skipped an old object\n");
        if (NodeID)
        {
            known_node_list.incOldOfferCount(NodeID,1);
        }
    }
}
else
{
    printf("Skipped a duplicate object\n");
}

sem_post(&mySemaphore);