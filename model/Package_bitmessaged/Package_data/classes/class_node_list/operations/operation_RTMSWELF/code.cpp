//~~ std::vector<data::node_info> getNodesToProvideToOthers() [node_list] ~~

std::vector<data::node_info> ret;

std::multiset<node_info> sorted; 

for (std::map<int64_t, node_info>::const_iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
{
    sorted.insert((*it).second);
}

for (std::multiset<node_info>::iterator it = sorted.begin(); it != sorted.end(); it++)
{
    if (ret.size() > 500) // 500 nodes are enough 
        return ret;
    if ((*it).getValue() <= 0)
        return ret;
    if (((*it).getServices() > 0) && ((*it).getLastConnectedTime() > 0))
       ret.push_back(*it); 
}

return ret;
