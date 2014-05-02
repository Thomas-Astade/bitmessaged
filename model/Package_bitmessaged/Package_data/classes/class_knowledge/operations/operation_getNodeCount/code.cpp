//~~ unsigned int getNodeCount() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;
    
unsigned int ret = known_node_list.getNodeCount();

sem_post(&mySemaphore);

RETURN(ret);