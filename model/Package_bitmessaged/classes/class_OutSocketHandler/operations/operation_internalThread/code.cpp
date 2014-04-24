//~~ void internalThread() [OutSocketHandler] ~~
socketfd = socket(AF_INET, SOCK_STREAM, 0);

if (socketfd < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    return;
}

if (connect(socketfd, (struct sockaddr *)&destAddr, sizeof(destAddr)) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_disconnected,0);
    return;
}

socklen_t len = sizeof(sourceAddr);

if (getsockname(socketfd, (struct sockaddr *) &sourceAddr, &len) < 0)
{
    ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_error,0);
    return;
}

ACF_sendMessage(MessageReceiver(),MessageReceiver(),ev_connected,0);

printf("ip: %s port %d connected to\n",
    inet_ntoa(sourceAddr.sin_addr),
    htons(sourceAddr.sin_port)
    );

printf("ip: %s port %d\n",
    inet_ntoa(destAddr.sin_addr),
    htons(destAddr.sin_port)
    );

while (1)
{
    sleep(1);
}