//~~ void closeConnection(ACF_Message* event) [SocketHandler] ~~
if (socketfd != -1)
{
    shutdown(socketfd, SHUT_RDWR);
    close(socketfd);
    socketfd = -1;
}