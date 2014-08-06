//~~ void setVersion(uint64_t id, unsigned int version) [node_list] ~~

if (known_nodes.find(id) == known_nodes.end())
    return;

node_info node = known_nodes[id];
node.setVersion(version);
known_nodes[id] = node;