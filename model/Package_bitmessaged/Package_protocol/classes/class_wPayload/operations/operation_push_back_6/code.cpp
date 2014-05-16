//~~ void push_back(uint64_t data) [Payload] ~~
uint64_t tmp = htonll(data);
uint8_t* mem = (uint8_t*)&tmp;
m_Data->push_back(mem[0]);
m_Data->push_back(mem[1]);
m_Data->push_back(mem[2]);
m_Data->push_back(mem[3]);
m_Data->push_back(mem[4]);
m_Data->push_back(mem[5]);
m_Data->push_back(mem[6]);
m_Data->push_back(mem[7]);