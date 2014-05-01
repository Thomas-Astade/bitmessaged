//~~ int writeTo(int socketfd) [message] ~~
int ret;

ret = write(socketfd,&comand_defines[myType],sizeof(comand_defines[myType]));

uint32_t len = htonl(myPayload.size());
ret += write(socketfd,&len,sizeof(len));
uint32_t checksum = myPayload.getChecksum();
ret += write(socketfd,&checksum,sizeof(checksum));
ret += write(socketfd,&(*myPayload)[0],myPayload.size());

RETURN(ret);