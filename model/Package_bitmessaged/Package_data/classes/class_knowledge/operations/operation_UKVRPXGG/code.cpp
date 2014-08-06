//~~ void setNodeVersion(uint64_t NodeID, unsigned int version) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.setVersion(NodeID,version);

sem_post(&mySemaphore);
