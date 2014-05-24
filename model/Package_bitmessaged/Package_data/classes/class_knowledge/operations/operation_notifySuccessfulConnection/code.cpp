//~~ void notifySuccessfulConnection(uint64_t id) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.notifySuccessfulConnection(id);
countSuccessfulConnections++;

sem_post(&mySemaphore);
