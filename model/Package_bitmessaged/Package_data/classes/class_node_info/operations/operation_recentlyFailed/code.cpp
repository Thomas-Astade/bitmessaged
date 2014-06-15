//~~ bool recentlyFailed() [node_info] ~~
if (lastFailedTime == 0)
    RETURN(false);
    
uint64_t time = std::time(0);

if ((time - lastFailedTime) < (60*60))
    RETURN(true);

RETURN(false);