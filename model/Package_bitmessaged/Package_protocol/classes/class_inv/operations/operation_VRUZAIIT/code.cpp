//~~ protocol::Payload getPayload() [inv] ~~
Payload ret;

ret.push_back(size());

for (std::set<inventory_vector>::iterator it = begin(); it != end(); it++)
{
    ret.push_back((*it).getData(),32);
}

return ret;