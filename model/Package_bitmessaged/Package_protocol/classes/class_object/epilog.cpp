namespace protocol {

std::ostream& operator<< (std::ostream &out,const  protocol::object &obj)
{
    out << obj.myPayload.size() << obj.myType;
    for (unsigned int i = 0; i < obj.myPayload.size(); i++)
        out << (*obj.myPayload)[i];
    return out;
}

std::istream& operator>> (std::istream &in,  protocol::object &obj)
{
    unsigned int size;
    unsigned int type;
    wPayload p;
    
    in >> size;
    in >> type;
    for (unsigned int i = 0; i < size; i++)
    {
        uint8_t d;
        in >> d;
        p.push_back(d);
    }
    
    object tmp((protocol::message::command_t)type,p);
    obj = tmp;
    
    return in;
}
}