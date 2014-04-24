//~~ void push_back(Payload data) [Payload] ~~
unsigned int count = data.size();
const uint8_t* pdata = *data;

for (unsigned int i = 0; i < count; i++)
{
    push_back(pdata[i]);
}