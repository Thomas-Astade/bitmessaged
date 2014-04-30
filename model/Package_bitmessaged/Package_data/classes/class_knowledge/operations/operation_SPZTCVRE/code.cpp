//~~ unsigned int getOutgoingCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
unsigned int ret = OutSocketCount;
sem_post(&mySemaphore);

RETURN(ret);