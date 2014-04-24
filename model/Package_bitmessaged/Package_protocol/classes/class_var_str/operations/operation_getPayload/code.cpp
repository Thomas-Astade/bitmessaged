//~~ protocol::Payload getPayload() [var_str] ~~
Payload ret;

ret.push_back(var_int(value.size()));
for (unsigned int i = 0; i < value.size(); i++)
    ret.push_back(value[i]);

RETURN(ret);