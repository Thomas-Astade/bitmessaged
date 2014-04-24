//~~ protocol::Payload getPayload() [var_int] ~~
Payload ret;
if (value < 0xfd)
{
    ret.push_back((uint8_t)value);
}
else if (value <= 0xffff)
{
    ret.push_back((uint8_t)0xfd);
    ret.push_back((uint16_t)value);
}
else if (value <= 0xffffffff)
{
    ret.push_back((uint8_t)0xfe);
    ret.push_back((uint32_t)value);
}
else
{
    ret.push_back((uint8_t)0xff);
    ret.push_back((uint64_t)value);
}

return ret;