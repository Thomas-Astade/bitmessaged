//~~ json_spirit::mArray get_info() [node_list] ~~
json_spirit::mArray saveNodes;
std::multiset<node_info> sorted; 

for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
{
    sorted.insert((*it).second);
}

for (std::multiset<node_info>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); it++)
{
    saveNodes.push_back((*it).get_info());
}

return saveNodes;