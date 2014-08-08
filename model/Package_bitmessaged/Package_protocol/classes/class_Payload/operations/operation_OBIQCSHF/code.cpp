//~~ uint64_t pow_target_V3(uint64_t ttl) [Payload] ~~
uint64_t mSize = (uint64_t)1000 + m_Data->size();

uint64_t target = (uint64_t)(0x8000000000000000) /
                ((uint64_t)500 * (mSize+((uint64_t)ttl*(mSize)/65536)));

return target;
