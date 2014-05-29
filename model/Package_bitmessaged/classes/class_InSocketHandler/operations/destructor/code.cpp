//~~ ~InSocketHandler() [InSocketHandler] ~~
theKnowledge.decIncommingCount();
if (socketfd != -1)
{
    close(socketfd);
    socketfd = -1;
}