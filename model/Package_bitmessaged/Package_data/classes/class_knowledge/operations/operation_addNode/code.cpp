//~~ bool addNode(const std::string& addr) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

bool ret = known_node_list.addNode(addr);

sem_post(&mySemaphore);

RETURN(ret);