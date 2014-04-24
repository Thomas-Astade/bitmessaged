//~~ void push_back(uint16_t data) [Payload] ~~
uint16_t tmp = htons(data);
uint8_t* mem = (uint8_t*)&tmp;
VECTOR.push_back(mem[0]);
VECTOR.push_back(mem[1]);