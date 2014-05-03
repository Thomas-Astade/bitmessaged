//~~ void setAgent(uint64_t id, cont std::string& agent) [node_list] ~~

if (known_nodes.find(id) == known_nodes.end())
    return;

node_info node = known_nodes[id];
node.setAgent(agent);
known_nodes[id] = node;