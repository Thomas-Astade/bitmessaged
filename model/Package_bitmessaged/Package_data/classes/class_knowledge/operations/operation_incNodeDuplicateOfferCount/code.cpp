//~~ void incNodeDuplicateOfferCount(uint64_t NodeID, unsigned int count) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.incDuplicateOfferCount(NodeID,count);

sem_post(&mySemaphore);
