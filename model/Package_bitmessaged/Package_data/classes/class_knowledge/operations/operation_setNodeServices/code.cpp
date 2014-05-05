//~~ void setNodeServices(uint64_t NodeID, uint64_t services) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.setServices(NodeID,services);

sem_post(&mySemaphore);
