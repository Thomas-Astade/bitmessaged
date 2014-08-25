namespace protocol {

std::ostream& operator<< (std::ostream &out,const  protocol::object &obj)
{
    char c[4];
    unsigned int* h = (unsigned int*)c;
    
    *h = obj.myPayload.size();
    out << c[0] << c[1] << c[2] << c[3];
    *h = obj.myType;
    out << c[0] << c[1] << c[2] << c[3];
    uint8_t* d = (uint8_t*)*obj.myPayload;

    for (unsigned int i = 0; i < obj.myPayload.size(); i++)
        out.put(d[i]);
    return out;
}

std::istream& operator>> (std::istream &in,  protocol::object &obj)
{
    unsigned int size;
    unsigned int type;
    wPayload p;
    char c[4];
    unsigned int* h = (unsigned int*)c;
    
    in >> c[0] >> c[1] >> c[2] >> c[3];
    size = *h;
    in >> c[0] >> c[1] >> c[2] >> c[3];
    type = *h;
    for (unsigned int i = 0; i < size; i++)
    {
        uint8_t d = in.get();
        p.push_back(d);
        if (in.eof())
            return in;
    }
    
    object tmp((protocol::message::command_t)type,p);
    obj = tmp;
    
    return in;
}
}