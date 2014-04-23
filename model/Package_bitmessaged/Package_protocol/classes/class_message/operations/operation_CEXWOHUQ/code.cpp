//~~ int writeTo(int socketfd) [message] ~~
int ret;

ret = write(socketfd,&comand_defines[myType],sizeof(comand_defines[myType]));

if (ret == 0)
{
    uint32_t len = htonl((*myPayload).size());
    ret = write(socketfd,&len,sizeof(len));
}

RETURN(ret);