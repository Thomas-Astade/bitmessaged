//~~ std::set<protocol::inventory_vector> getObjects() [knowledge] ~~
std::set<protocol::inventory_vector> ret;

while (sem_wait(&mySemaphore))
    ;

std::set<protocol::inventory_vector> toDelete;

for (std::map<protocol::inventory_vector,protocol::object>::iterator it = collectedObjects.begin();
     it != collectedObjects.end(); it++)
{

    if ((*it).second.isActuell())
    {
        ret.insert((*it).first);
    } 
    else if ((*it).second.isOld())
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