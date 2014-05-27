//~~ var_int(const Payload& data, unsigned int& index) [var_int] ~~
if (index >= data.size())
    throw Malformated();

uint8_t first = data.get_uint8_t(index);

if (first < 0xfd)
{
    value = first;
    index += 1;
}
else if (first == 0xfd)
{
    if (index+3 > data.size())
        throw Malformated();
        
    value = data.get_uint16_t(index+1);
    index += 3;
}
else if (first == 0xfe)
{
    if (index+5 > data.size())
        throw Malformated();
        
    value = data.get_uint32_t(index+1);
    index += 5;
}
else
{
    if (index+9 > data.size())
        throw Malformated();
        
    value = data.get_uint64_t(index+1);
    index += 9;
}

