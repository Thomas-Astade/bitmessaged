//~~ void setServices(uint64_t id, uint64_t services) [node_list] ~~

if (known_nodes.find(id) == known_nodes.end())
    return;

node_info node = known_nodes[id];
node.setServices(services);
known_nodes[id] = node;