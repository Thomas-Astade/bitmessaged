//~~ uint16_t getPort() [node_info] ~~
RETURN(htons(myAddr.sin_port));