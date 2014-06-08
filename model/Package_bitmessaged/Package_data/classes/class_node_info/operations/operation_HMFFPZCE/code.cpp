//~~ std::string getIPasString() [node_info] ~~
RETURN(inet_ntoa(myAddr.sin_addr));