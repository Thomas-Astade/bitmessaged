//~~ void incIncommingCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
InSocketCount++;
sem_post(&mySemaphore);