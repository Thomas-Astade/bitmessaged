//~~ inventory_vector(const std::string& printable) [inventory_vector] ~~
std::string input(printable);

while (input.size() < (2*sizeof(data)))
    input += "0";
    
for (unsigned int i = 0; i < sizeof(data); i++)
    data[i] = strtol(input.substr(2*i,2).c_str(),0,16);