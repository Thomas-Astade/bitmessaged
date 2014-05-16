//~~ protocol::Payload getPayload() [inv] ~~
wPayload ret;

ret.push_back(var_int(size()));

for (std::set<inventory_vector>::iterator it = begin(); it != end(); it++)
{
    ret.push_back((*it).getData(),32);
}

return ret;