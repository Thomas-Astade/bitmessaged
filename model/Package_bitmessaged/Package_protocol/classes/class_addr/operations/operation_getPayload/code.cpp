//~~ protocol::Payload getPayload() [addr] ~~
wPayload ret;

ret.push_back(var_int(myAddresses.size()));

for (std::vector<net_addr>::const_iterator it = myAddresses.begin(); it != myAddresses.end(); it++)
{
    ret.push_back((*it).getPayload());
}

return ret;