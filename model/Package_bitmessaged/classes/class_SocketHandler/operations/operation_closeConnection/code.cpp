//~~ void closeConnection(ACF_Message* event) [SocketHandler] ~~
if (socketfd != -1)
{
    close(socketfd);
    socketfd = -1;
}