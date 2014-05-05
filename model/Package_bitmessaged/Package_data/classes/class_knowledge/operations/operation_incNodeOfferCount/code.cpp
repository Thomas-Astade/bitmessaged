//~~ void incNodeOfferCount(uint64_t NodeID, unsigned int count) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

known_node_list.incOfferCount(NodeID,count);

sem_post(&mySemaphore);
