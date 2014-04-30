//~~ void push_back(void* data, unsigned int size) [Payload] ~~
for (unsigned int i = 0; i < size; i++)
    VECTOR.push_back(((uint8_t*)data)[i]);