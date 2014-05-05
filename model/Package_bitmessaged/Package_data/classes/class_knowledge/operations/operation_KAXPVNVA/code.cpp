//~~ std::vector<node_info> getNodesToProvideToOthers() [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

std::vector<data::node_info> ret = known_node_list.getNodesToProvideToOthers();

sem_post(&mySemaphore);

RETURN(ret);