//~~ uint32_t get_uint32_t(unsigned int index) [Payload] ~~
if ((index+3) >= size())
{
    RETURN(0);
}
else
{
    uint32_t* tmp = (uint32_t*)(operator*()+index);
    RETURN(htonl(*tmp));
}