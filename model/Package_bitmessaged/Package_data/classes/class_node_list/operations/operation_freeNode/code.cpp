//~~ void freeNode(uint64_t id) [node_list] ~~
if (known_nodes.find(id) == known_nodes.end())
    return;

known_nodes[id].decUse();