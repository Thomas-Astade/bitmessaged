//~~ void push_back(uint64_t data) [Payload] ~~
uint64_t tmp = htonll(data);
uint8_t* mem = (uint8_t*)&tmp;
VECTOR.push_back(mem[0]);
VECTOR.push_back(mem[1]);
VECTOR.push_back(mem[2]);
VECTOR.push_back(mem[3]);
VECTOR.push_back(mem[4]);
VECTOR.push_back(mem[5]);
VECTOR.push_back(mem[6]);
VECTOR.push_back(mem[7]);