//~~ ~OutSocketHandler() [OutSocketHandler] ~~
theKnowledge.decOutgoingCount();
if (socketfd)
{
    close(socketfd);
    socketfd = -1;
}