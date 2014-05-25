//~~ protocol::object getObject(const protocol::inventory_vector& aVector) [knowledge] ~~
protocol::object ret;

while (sem_wait(&mySemaphore))
    ;
    
std::map<protocol::inventory_vector,protocol::object>::const_iterator it = collectedObjects.find(aVector);

if (it != collectedObjects.end())
    ret = (*it).second;

sem_post(&mySemaphore);

countSentObjects++;

return ret;