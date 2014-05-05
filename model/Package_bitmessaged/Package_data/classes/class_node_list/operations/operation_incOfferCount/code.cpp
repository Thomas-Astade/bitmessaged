//~~ void incOfferCount(uint64_t NodeID, unsigned int count) [node_list] ~~

if (known_nodes.find(NodeID) == known_nodes.end())
    return;

node_info node = known_nodes[NodeID];
node.incOfferCount(count);
known_nodes[NodeID] = node;