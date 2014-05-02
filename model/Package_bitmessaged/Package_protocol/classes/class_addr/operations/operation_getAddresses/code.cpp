//~~ std::vector<std::string> getAddresses() [addr] ~~
std::vector<std::string> ret;

for (std::vector<net_addr>::iterator it = myAddresses.begin(); it != myAddresses.end(); it++)
{
    ret.push_back((*it).getNodeStr());
}

return ret;