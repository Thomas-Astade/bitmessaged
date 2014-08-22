//~~ ~InSocketHandler() [InSocketHandler] ~~
theKnowledge.decIncommingCount();
if (socketfd != -1)
{
    shutdown(socketfd, SHUT_RDWR);
    socketfd = -1;
}