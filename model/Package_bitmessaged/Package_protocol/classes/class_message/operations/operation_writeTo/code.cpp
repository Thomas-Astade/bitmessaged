//~~ int writeTo(int socketfd) [message] ~~
int ret;

if (bytesWritten == 0)
{
    ret = write(socketfd,&comand_defines[myType],sizeof(comand_defines[myType]));

    if (ret < (int)sizeof(comand_defines[myType]))
    {
        shutdown(socketfd, SHUT_RDWR);
        close(socketfd);
        socketfd = -1;
        RETURN(0);
    }

    uint32_t len = htonl(myPayload.size());
    ret = write(socketfd,&len,sizeof(len));

    if (ret < (int)sizeof(len))
    {
        shutdown(socketfd, SHUT_RDWR);
        close(socketfd);
        socketfd = -1;
        RETURN(0);
    }

    uint32_t checksum = myPayload.getChecksum();
    ret = write(socketfd,&checksum,sizeof(checksum));

    if (ret < (int)sizeof(checksum))
    {
        shutdown(socketfd, SHUT_RDWR);
        close(socketfd);
        socketfd = -1;
        RETURN(0);
    }
}

unsigned int bytesToSend = myPayload.size() - bytesWritten;

if (bytesToSend > 2000)
    bytesToSend = 2000;

ret = write(socketfd,&(*myPayload)[bytesWritten],bytesToSend);

if (ret < (int)bytesToSend)
{
    shutdown(socketfd, SHUT_RDWR);
    close(socketfd);
    socketfd = -1;
    RETURN(0);
}

bytesWritten += bytesToSend;

RETURN(myPayload.size() - bytesWritten);