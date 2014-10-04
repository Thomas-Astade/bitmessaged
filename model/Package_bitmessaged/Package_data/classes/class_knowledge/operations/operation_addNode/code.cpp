//~~ bool addNode(const std::string& addr) [knowledge] ~~
if (m_fixed_mode)
    RETURN(true);

if (addr.find("127.") == 0)
    RETURN(true);

if (addr.find("0.0.0.0") == 0)
    RETURN(true);

while (sem_wait(&mySemaphore))
    ;

bool ret = known_node_list.addNode(addr);

sem_post(&mySemaphore);

RETURN(ret);