//~~ void addObject(const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
if (collectedObjects.find(object.getVector()) == collectedObjects.end())
{
    struct tm *tmp;
    time_t t;
    char nowstr[200];
    char ostr[200];

    t = getTime();
    tmp = localtime(&t);
    strftime(nowstr, sizeof(nowstr), "%a, %d %b %y %T %z",tmp);

    t = object.getTime();
    tmp = localtime(&t);
    strftime(ostr, sizeof(ostr), "%a, %d %b %y %T %z",tmp);

    bool oldObject = ((object.getType() == protocol::message::pubkey) && ((t + maximumKeyAcceptAge) < getTime())) ||
                       (((t + maximumAcceptAge) < getTime()))
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