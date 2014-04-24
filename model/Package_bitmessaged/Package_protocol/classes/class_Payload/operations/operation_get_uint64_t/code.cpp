//~~ uint64_t get_uint64_t(unsigned int index) [Payload] ~~
if ((index+7) >= size())
{
    RETURN(0);
}
else
{
    uint64_t* tmp = (uint64_t*)(operator*()+index);
    RETURN(htonll(*tmp));
}