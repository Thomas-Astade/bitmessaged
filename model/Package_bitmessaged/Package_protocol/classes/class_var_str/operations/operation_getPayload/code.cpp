//~~ protocol::Payload getPayload() [var_str] ~~
wPayload ret;

ret.push_back(var_int(size()));
for (unsigned int i = 0; i < size(); i++)
    ret.push_back(operator[](i));

return ret;