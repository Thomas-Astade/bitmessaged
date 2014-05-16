//~~ void addObject(const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
collectedObjects[object.getVector()] = object;
std::pair<uint64_t, protocol::inventory_vector> aPair(getTime(), object.getVector());
receivedTimes.push_back(aPair);
sem_post(&mySemaphore);