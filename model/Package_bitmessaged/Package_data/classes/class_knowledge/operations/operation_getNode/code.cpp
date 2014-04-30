//~~ bool getNode(data::node_info& info) [knowledge] ~~
while (sem_wait(&mySemaphore))
    ;

bool ret = known_node_list.getNode(info);

sem_post(&mySemaphore);

RETURN(ret);