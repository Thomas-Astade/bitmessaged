//~~ std::string getIP() [node_info] ~~
char ret[16] = "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\x00\x00\x00";
memcpy(&ret[12],&myAddr.sin_addr,5);
RETURN(std::string(ret,16));