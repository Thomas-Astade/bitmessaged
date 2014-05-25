//~~ std::set<protocol::inventory_vector> getObjects() [knowledge] ~~
std::set<protocol::inventory_vector> ret;

while (sem_wait(&mySemaphore))
    ;

std::set<protocol::inventory_vector> toDelete;

for (std::map<protocol::inventory_vector,protocol::object>::iterator it = collectedObjects.begin();
     it != collectedObjects.end(); it++)
{
    uint64_t oTime = (*it).second.getTime();
    uint64_t now = getTime();
    bool oldObject = (((*it).second.getType() == protocol::message::pubkey) && ((oTime + maximumKeyAdvertiseAge) < now)) ||
                       (((*it).second.getType() != protocol::message::pubkey) && ((oTime + maximumAdvertiseAge) < now))
                      ;
                      
    if (!oldObject)
    {
        ret.insert((*it).first);
    }

    oldObject = (((*it).second.getType() == protocol::message::pubkey) && ((oTime + maximumKeyAcceptAge) < now)) ||
                 (((*it).second.getType() != protocol::message::pubkey) && ((oTime + maximumAcceptAge) < now))
                ;

    if (oldObject)
    {
        toDelete.insert((*it).first);
    }
}

for (std::set<protocol::inventory_vector>::iterator it = toDelete.begin();
     it != toDelete.end(); it++)
{
    collectedObjects.erase(*it);
}


sem_post(&mySemaphore);

return ret;