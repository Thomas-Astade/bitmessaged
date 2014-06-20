//~~ bool getNode(data::node_info& info) [node_list] ~~
if (known_nodes.empty())
    RETURN(false);

//create a list of nodes, which are not connected and did not fail the last 15 minutes
std::vector<uint64_t> nodelist;

// try to find a node which did not fail or is used the last 15 minutes
for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
{
    data::node_info res = (*it).second;
    if ((!res.isInUse()) && (!res.recentlyFailed()) && (!res.recentlyUsed()))
        nodelist.push_back(res.getID());
}

// if we cannot find one we might except a resently used node again
if (nodelist.empty())
{
    for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
    {
        data::node_info res = (*it).second;
        if ((!res.isInUse()) && (!res.recentlyFailed()))
            nodelist.push_back(res.getID());
    }
}

if (nodelist.empty())
    RETURN(false);

unsigned int searchsize = nodelist.size();

unsigned int select = rand() % searchsize; // select a random node from the best 1000

data::node_info res = known_nodes[nodelist[select]];

res.incUse();
info = res;
known_nodes[res.getID()] = res;

#ifdef _TRACE_
    char buffer[50];
    sprintf(buffer,"%ld",res.getID());
    Trace2UML::notify_log(5,this,"node_list",buffer);
#endif

if (known_nodes.size() > 2100) // List is to big, lets delete some
{
    std::multiset<node_info> sorted; 
    for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
    {
        sorted.insert((*it).second);
    }
    for (std::multiset<node_info>::iterator it = sorted.begin(); it != sorted.end(); it++)
    {
        known_nodes.erase((*it).getID());
        if (known_nodes.size() <= 2000)
            RETURN(true);
    }
}

RETURN(true);
