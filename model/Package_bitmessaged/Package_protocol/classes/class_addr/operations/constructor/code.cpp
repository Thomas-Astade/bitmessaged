//~~ addr(const Payload& data, unsigned int& index) [addr] ~~
var_int count(data,index);
uint64_t addrcount = count.getValue();

if (addrcount > 1000) // an addr with mote than 1000 addesses is invalid
    throw Malformated();

while (addrcount--)
{
    net_addr anAddr(data,index);
    myAddresses.push_back(anAddr);
}