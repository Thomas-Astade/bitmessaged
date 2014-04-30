//~~ void freeNode(uint64_t id) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.freeNode(id);

sem_post(&mySemaphore);
