//~~ void addObject(const protocol::object& object) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
collectedObjects[object.getVector()] = object;
sem_post(&mySemaphore);