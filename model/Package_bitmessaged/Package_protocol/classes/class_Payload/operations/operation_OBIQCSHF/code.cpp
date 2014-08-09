//~~ uint64_t pow_target_V3(uint64_t ttl) [Payload] ~~
uint64_t Size = m_Data->size() + 1000;

uint64_t target = (uint64_t)(0x8000000000000000) /
                ((Size+(ttl*Size/65536))*500);

return target;
