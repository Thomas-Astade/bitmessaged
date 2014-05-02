//~~ bool getNode(data::node_info& info) [node_list] ~~
if (known_nodes.empty())
    RETURN(false);

//create a list of nodes, which are not connected and did not fail the last 15 minutes
std::vector<uint64_t> nodelist;

for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
{
    data::node_info res = (*it).second;
    if ((!res.isInUse()) && (!res.recentlyFailed()))
        nodelist.push_back(res.getID());
}

if (nodelist.empty())
    RETURN(false);

unsigned int select = rand() % nodelist.size(); // select a random node

data::node_info res = known_nodes[nodelist[select]];
res.incUse();
info = res;
known_nodes[res.getID()] = res;

#ifdef _TRACE_
    char buffer[50];
    sprintf(buffer,"%ld",res.getID());
    Trace2UML::notify_log(5,this,"node_list",buffer);
#endif

RETURN(true);
