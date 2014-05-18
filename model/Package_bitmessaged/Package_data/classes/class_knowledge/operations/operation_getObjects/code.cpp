//~~ std::set<protocol::inventory_vector> getObjects(uint64_t minTime, uint64_t maxTime) [knowledge] ~~
std::set<protocol::inventory_vector> ret;

if (maxTime < minTime)
    return ret;

while (sem_wait(&mySemaphore))
    ;

std::set<protocol::inventory_vector> toDelete;

for (std::list<std::pair<uint64_t, protocol::inventory_vector> >::iterator it = receivedTimes.begin();
     it != receivedTimes.end(); it++)
{
    protocol::object anObject = collectedObjects[(*it).second];
    
    if ((getTime() - anObject.getTime()) > (2.5*24*60*60))
        toDelete.insert((*it).second);
    
    if ((*it).first > maxTime)
        break;

    if ((getTime() - anObject.getTime()) < (2*24*60*60))
    {
        if ((*it).first >= minTime)
            ret.insert((*it).second);
    }
}

sem_post(&mySemaphore);

return ret;