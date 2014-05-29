//~~ int writeTo(int socketfd) [message] ~~
int ret;
int send;

ret = write(socketfd,&comand_defines[myType],sizeof(comand_defines[myType]));

if (ret < (int)sizeof(comand_defines[myType]))
{
    close(socketfd);
    return ret;
}

uint32_t len = htonl(myPayload.size());
send = write(socketfd,&len,sizeof(len));
ret += send;

if (send < (int)sizeof(len))
{
    close(socketfd);
    return ret;
}

uint32_t checksum = myPayload.getChecksum();
send = write(socketfd,&checksum,sizeof(checksum));
ret += send;

if (send < (int)sizeof(checksum))
{
    close(socketfd);
    return ret;
}

send = write(socketfd,&(*myPayload)[0],myPayload.size());
ret += send;

if (send < (int)myPayload.size())
{
    close(socketfd);
}

RETURN(ret);