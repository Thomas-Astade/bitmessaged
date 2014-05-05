//~~ net_addr(const data::node_info& node) [net_addr] ~~
myPayload.push_back(node.getLastConnectedTime());
myPayload.push_back(node.getStreamNo());
myPayload.push_back(node.getServices());
myPayload.push_back(node.getIP());
myPayload.push_back(node.getPort());
