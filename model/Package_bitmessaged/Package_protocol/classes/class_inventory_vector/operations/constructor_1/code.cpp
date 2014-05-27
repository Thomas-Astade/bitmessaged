//~~ inventory_vector(const protocol::Payload& theData, unsigned int& index) [inventory_vector] ~~
if (index+sizeof(data) > theData.size())
    throw Malformated();
    
memcpy(data,&(*theData)[index],sizeof(data));
index += sizeof(data);