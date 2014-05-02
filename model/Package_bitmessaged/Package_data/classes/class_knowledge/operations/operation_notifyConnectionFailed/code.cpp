//~~ void notifyConnectionFailed(uint64_t id) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.notifyConnectionFailed(id);

sem_post(&mySemaphore);
