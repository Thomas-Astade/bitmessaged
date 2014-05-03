//~~ var_str(const Payload& data, unsigned int index) [var_str] ~~
unsigned int len = var_int(data,index).getValue();
std::string::operator=(std::string((const char*)&(*data)[index],len));