//~~ unsigned int getUnsuccessfulCount() [knowledge] ~~
unsigned int ret;

while (sem_wait(&mySemaphore))
    ;

ret = countUnsuccessfulConnections;

sem_post(&mySemaphore);

RETURN(ret);
