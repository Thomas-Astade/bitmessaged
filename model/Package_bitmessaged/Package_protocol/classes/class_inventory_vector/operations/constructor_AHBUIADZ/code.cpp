//~~ inventory_vector(const protocol::Payload& theData, unsigned int& index) [inventory_vector] ~~
memcpy(data,&(*theData)[index],sizeof(data));
index += sizeof(data);