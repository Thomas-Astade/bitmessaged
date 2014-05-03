//~~ void closeConnection(ACF_Message* event) [OutSocketHandler] ~~
if (socketfd)
{
    close(socketfd);
    socketfd = 0;
}