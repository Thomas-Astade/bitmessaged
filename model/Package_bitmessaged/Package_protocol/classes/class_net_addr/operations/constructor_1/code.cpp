//~~ net_addr(const data::node_info& node) [net_addr] ~~
wPayload aPayload;

aPayload.push_back(node.getLastConnectedTime());
aPayload.push_back(node.getStreamNo());
aPayload.push_back(node.getServices());
aPayload.push_back(node.getIP());
aPayload.push_back(node.getPort());

myPayload = aPayload;
