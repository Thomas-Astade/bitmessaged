//~~ json_spirit::mArray get_info() [node_list] ~~
json_spirit::mArray saveNodes; 

for (std::map<int64_t, node_info>::iterator it = known_nodes.begin(); it != known_nodes.end(); it++)
{
    saveNodes.push_back((*it).second.get_info());
}

return saveNodes;