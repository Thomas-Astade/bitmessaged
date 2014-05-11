//~~ bool doWeNeed(const protocol::inventory_vector& parameter) [knowledge] ~~
bool ret;

while (sem_wait(&mySemaphore))
    ;

ret = (collectedObjects.find(parameter) == collectedObjects.end());

sem_post(&mySemaphore);

RETURN(ret);