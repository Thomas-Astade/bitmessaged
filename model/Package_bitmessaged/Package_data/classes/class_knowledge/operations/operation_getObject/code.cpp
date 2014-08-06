//~~ protocol::object getObject(const protocol::inventory_vector& aVector) [knowledge] ~~
protocol::object ret;

while (sem_wait(&mySemaphore))
    ;
    
std::map<protocol::inventory_vector,protocol::object>::const_iterator it = collectedObjectsV3.find(aVector);

if (it != collectedObjectsV3.end()) {
    ret = (*it).second;
} else {
    it = collectedObjectsV2.find(aVector);
    if (it != collectedObjectsV2.end())
        ret = (*it).second;
}

sem_post(&mySemaphore);

return ret;