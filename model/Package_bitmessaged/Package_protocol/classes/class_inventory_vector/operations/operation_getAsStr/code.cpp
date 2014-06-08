//~~ std::string getAsStr() [inventory_vector] ~~
char buffer[200];
char* p = buffer;

for (int i = 0; i < 32; i++)
{
    p += sprintf(p,"%02x",data[i]);
}

return buffer;