//~~ ~OutSocketHandler() [OutSocketHandler] ~~
theKnowledge.decOutgoingCount();
if (socketfd != -1)
{
    close(socketfd);
    socketfd = -1;
}