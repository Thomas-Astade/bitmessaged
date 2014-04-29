//~~ bool addNode(const std::string& addr) [node_list] ~~
size_t pos = addr.find(':');

if (pos == std::string::npos)
    RETURN(false);



struct sockaddr_in serv_addr;
memset(&serv_addr, '0', sizeof(serv_addr)); 

serv_addr.sin_family = AF_INET;
int port = atoi(addr.substr(pos+1).c_str());
serv_addr.sin_port = htons(port);

if (inet_pton(AF_INET, addr.substr(0,pos).c_str(), &serv_addr.sin_addr)==0)
{
    RETURN(false);
}

char buffer[100];
if (inet_ntop(AF_INET, &serv_addr, buffer, sizeof(buffer)) && serv_addr.sin_port)
{
    char buffer2[100];
    sprintf(buffer2,"%s:%d",buffer,port);
    known_nodes[buffer2] = node_info(serv_addr);
    RETURN(true);
}
else
{
    RETURN(false);
}