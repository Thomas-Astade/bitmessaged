//~~ addr(const std::vector<data::node_info>& nodes) [addr] ~~
for (std::vector<data::node_info>::const_iterator it = nodes.begin(); it != nodes.end(); it++)
{
    myAddresses.push_back(net_addr(*it));
}