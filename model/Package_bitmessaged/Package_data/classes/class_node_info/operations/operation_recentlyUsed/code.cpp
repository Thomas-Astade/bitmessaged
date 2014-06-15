//~~ bool recentlyUsed() [node_info] ~~
if (lastConnectedTime == 0)
    RETURN(false);
    
uint64_t time = std::time(0);

if ((time - lastConnectedTime) < (3*60*60))
    RETURN(true);

RETURN(false);