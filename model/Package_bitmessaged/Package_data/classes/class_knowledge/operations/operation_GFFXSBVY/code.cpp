//~~ void decOutgoingCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
OutSocketCount--;
sem_post(&mySemaphore);