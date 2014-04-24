//~~ protocol::Payload getPayload() [var_int_list] ~~
Payload ret;

ret.push_back(var_int(size()));
for (unsigned int i = 0; i < size(); i++)
    ret.push_back(var_int(operator[](i)));

return ret;