//~~ void incHeartbeat() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
heartbeat++;
sem_post(&mySemaphore);