//~~ uint16_t get_uint16_t(unsigned int index) [Payload] ~~
if ((index+1) >= size())
{
    RETURN(0);
}
else
{
    uint16_t* tmp = (uint16_t*)(operator*()+index);
    RETURN(htons(*tmp));
}