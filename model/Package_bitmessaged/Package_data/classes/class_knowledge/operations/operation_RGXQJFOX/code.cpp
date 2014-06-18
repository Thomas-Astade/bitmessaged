//~~ void incSendCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
countSentObjects++;

sem_post(&mySemaphore);
