//~~ unsigned int getSentObjectCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
unsigned int ret = countSentObjects;
sem_post(&mySemaphore);

RETURN(ret);