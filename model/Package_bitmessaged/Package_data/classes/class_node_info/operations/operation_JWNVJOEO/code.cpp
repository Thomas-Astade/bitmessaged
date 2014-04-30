//~~ int64_t getID() [node_info] ~~
int32_t i;
memcpy(&i,&myAddr.sin_addr,sizeof(i));
int64_t id = ((int64_t)myAddr.sin_port << 32) + i;
RETURN(id);