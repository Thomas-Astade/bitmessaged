//~~ bool getNode(data::node_info& info) [node_list] ~~
if (known_nodes.empty())
    RETURN(false);
    
for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
{
    data::node_info& res = (*it).second;
    if (!res.isInUse())
    {
        res.incUse();
        info = res;
        RETURN(true);
    }
}

RETURN(false);