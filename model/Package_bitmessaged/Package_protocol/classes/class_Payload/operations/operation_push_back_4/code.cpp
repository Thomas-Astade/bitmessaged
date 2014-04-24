//~~ void push_back(uint32_t data) [Payload] ~~
uint32_t tmp = htonl(data);
uint8_t* mem = (uint8_t*)&tmp;
VECTOR.push_back(mem[0]);
VECTOR.push_back(mem[1]);
VECTOR.push_back(mem[2]);
VECTOR.push_back(mem[3]);