//~~ uint8_t get_uint8_t(unsigned int index) [Payload] ~~
if (index >= size())
{
    RETURN(0);
}
else
{
    RETURN(*(operator*()+index));
}