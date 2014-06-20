//~~ void closeConnection(ACF_Message* event) [SocketHandler] ~~
if (socketfd)
{
    close(socketfd);
    socketfd = -1;
}