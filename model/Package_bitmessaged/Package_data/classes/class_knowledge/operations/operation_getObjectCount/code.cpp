//~~ unsigned int getObjectCount(unsigned int protocol_version) [knowledge] ~~
unsigned int ret = 0;

while (sem_wait(&mySemaphore))
    ;

if (protocol_version == 3)
    ret = collectedObjectsV3.size();
else if (protocol_version == 2)
    ret = collectedObjectsV2.size();

sem_post(&mySemaphore);

RETURN(ret);
