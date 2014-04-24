//~~ var_int(const Payload& data, unsigned int& index) [var_int] ~~
uint8_t first = data.get_uint8_t(index);

if (first < 0xfd)
{
    value = first;
    index += 1;
}
else if (first == 0xfd)
{
    value = data.get_uint16_t(index+1);
    index += 3;
}
else if (first == 0xfe)
{
    value = data.get_uint32_t(index+1);
    index += 5;
}
else
{
    value = data.get_uint64_t(index+1);
    index += 9;
}

