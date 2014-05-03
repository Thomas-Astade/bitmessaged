//~~ void setAgent(uint64_t id, cont std::string& agent) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.setAgent(id,agent);

sem_post(&mySemaphore);
