//~~ void addObject(const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
if (collectedObjects.find(object.getVector()) == collectedObjects.end())
{
    if ((getTime() - object.getTime()) < ((2*24*60*60) + 600))
    {   //only if less than 2 days old
        collectedObjects[object.getVector()] = object;
        std::pair<uint64_t, protocol::inventory_vector> aPair(getTime(), object.getVector());
        receivedTimes.push_back(aPair);
    }
}

sem_post(&mySemaphore);