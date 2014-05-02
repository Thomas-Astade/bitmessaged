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

node_info newnode(serv_addr);

if (known_nodes.find(newnode.getID()) == known_nodes.end())
    known_nodes[newnode.getID()] = newnode;

RETURN(true);
