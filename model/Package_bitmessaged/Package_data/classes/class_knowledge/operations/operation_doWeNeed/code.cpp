//~~ bool doWeNeed(const protocol::inventory_vector& aVector) [knowledge] ~~
bool ret;

while (sem_wait(&mySemaphore))
    ;

ret = ((collectedObjectsV2.find(aVector) == collectedObjectsV2.end()) &&
       (collectedObjectsV3.find(aVector) == collectedObjectsV3.end()));

sem_post(&mySemaphore);

RETURN(ret);