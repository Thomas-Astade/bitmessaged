//~~ uint64_t htonll(uint64_t value) [version] ~~
int num = 42;
if (*(char *)&num == 42) {
    uint32_t high_part = htonl((uint32_t)(value >> 32));
    uint32_t low_part = htonl((uint32_t)(value & 0xFFFFFFFFLL));
    return (((uint64_t)low_part) << 32) | high_part;
} else {
    return value;
}