//~~ void setNodeAgent(uint64_t NodeID, const std::string& agent) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.setAgent(NodeID,agent);

sem_post(&mySemaphore);
