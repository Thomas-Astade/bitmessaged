//~~ void closeConnection(ACF_Message* event) [InSocketHandler] ~~
if (socketfd)
{
    close(socketfd);
    socketfd = -1;
}