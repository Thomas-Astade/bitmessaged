//~~ void push_back(uint16_t data) [Payload] ~~
uint16_t tmp = htons(data);
uint8_t* mem = (uint8_t*)&tmp;
m_Data->push_back(mem[0]);
m_Data->push_back(mem[1]);