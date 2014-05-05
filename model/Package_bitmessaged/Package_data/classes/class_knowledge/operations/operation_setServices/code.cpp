//~~ void setServices(uint64_t id, uint64_t services) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.setServices(id,services);

sem_post(&mySemaphore);
