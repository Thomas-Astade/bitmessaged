//~~ unsigned int getSuccessfulCount() [knowledge] ~~
unsigned int ret;

while (sem_wait(&mySemaphore))
    ;

ret = countSuccessfulConnections;

sem_post(&mySemaphore);

RETURN(ret);
