//~~ protocol::Payload getPayload() [var_str] ~~
Payload ret;

ret.push_back(var_int(size()));
for (unsigned int i = 0; i < size(); i++)
    ret.push_back(operator[](i));

return ret;