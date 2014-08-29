//~~ ~OutSocketHandler() [OutSocketHandler] ~~
theKnowledge.decOutgoingCount();
if (socketfd != -1)
{
    shutdown(socketfd, SHUT_RDWR);
    close(socketfd);
    socketfd = -1;
}