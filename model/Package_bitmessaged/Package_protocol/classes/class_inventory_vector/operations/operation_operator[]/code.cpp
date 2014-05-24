//~~ uint8_t operator[](unsigned int index) [inventory_vector] ~~
if (index < 32)
    return data[index];
else
    return 0;