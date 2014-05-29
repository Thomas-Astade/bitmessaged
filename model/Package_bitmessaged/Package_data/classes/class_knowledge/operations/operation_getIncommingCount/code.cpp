//~~ unsigned int getIncommingCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
unsigned int ret = InSocketCount;
sem_post(&mySemaphore);

RETURN(ret);