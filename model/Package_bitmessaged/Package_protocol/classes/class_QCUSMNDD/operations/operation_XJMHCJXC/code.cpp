//~~ void push_back(uint32_t data) [Payload] ~~
uint32_t tmp = htonl(data);
uint8_t* mem = (uint8_t*)&tmp;
m_Data->push_back(mem[0]);
m_Data->push_back(mem[1]);
m_Data->push_back(mem[2]);
m_Data->push_back(mem[3]);