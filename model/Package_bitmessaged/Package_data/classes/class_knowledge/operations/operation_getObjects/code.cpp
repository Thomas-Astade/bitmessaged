//~~ std::set<protocol::inventory_vector> getObjects(unsigned int protocol_version) [knowledge] ~~
std::set<protocol::inventory_vector> ret;

while (sem_wait(&mySemaphore))
    ;

std::set<protocol::inventory_vector> toDelete;

if (protocol_version == 3) {
    for (std::map<protocol::inventory_vector,protocol::object>::iterator it = collectedObjectsV3.begin();
         it != collectedObjectsV3.end(); it++)
    {

        if ((*it).second.isActuell())
            ret.insert((*it).first);
        else if ((*it).second.isOld())
            toDelete.insert((*it).first);
    }

    for (std::set<protocol::inventory_vector>::iterator it = toDelete.begin();
            it != toDelete.end(); it++)
        collectedObjectsV3.erase(*it);
}
else if (protocol_version == 2) {
    for (std::map<protocol::inventory_vector,protocol::object>::iterator it = collectedObjectsV2.begin();
         it != collectedObjectsV2.end(); it++)
    {

        if ((*it).second.isActuell())
            ret.insert((*it).first);
        else if ((*it).second.isOld())
            toDelete.insert((*it).first);
    }

    for (std::set<protocol::inventory_vector>::iterator it = toDelete.begin();
            it != toDelete.end(); it++)
        collectedObjectsV2.erase(*it);
}


sem_post(&mySemaphore);

return ret;