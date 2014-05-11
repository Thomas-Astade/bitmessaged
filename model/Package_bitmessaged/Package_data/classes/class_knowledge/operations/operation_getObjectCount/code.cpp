//~~ unsigned int getObjectCount() [knowledge] ~~
unsigned int ret;

while (sem_wait(&mySemaphore))
    ;

ret = collectedObjects.size();

sem_post(&mySemaphore);

RETURN(ret);
