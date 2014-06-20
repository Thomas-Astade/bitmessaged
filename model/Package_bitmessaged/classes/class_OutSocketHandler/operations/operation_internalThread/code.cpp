//~~ void internalThread() [OutSocketHandler] ~~
socketfd = socket(AF_INET, SOCK_STREAM, 0);

if (socketfd < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

if (connect(socketfd, (struct sockaddr *)&destAddr, sizeof(destAddr)) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

struct timeval timeout;
timeout.tv_sec = 3;
timeout.tv_usec = 0;

if (setsockopt (socketfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,sizeof(timeout)) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_connected,0);


threadloop();
